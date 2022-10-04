/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2022 Codasip s.r.o.
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 * \file
 * \date    2022-09-10
 * \author  Codasip (c) C compiler backend generator
 * \version 9.1.1-1255
 * \brief   Source for compiler backend
 * \project ia_riscv32i.ia
 * \note          Codasip Studio version: 9.1.1-1255
 *                Licensee: Lockular Limited  (C60_2111_2104)
 *                Project: ia_riscv32i.ia
 *                Date: 2022-09-10 04:29:16
 *                Copyright (C) 2022 Codasip s.r.o.
 */


#define DEBUG_TYPE "vliw-noop-adder"

#include "Codasip.h"
#include "CodasipTargetMachine.h"
#include "CodasipHazardRec.h"

#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineInstrBundle.h"
#include "llvm/Support/Debug.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

namespace {

struct VliwNoopAdder : public MachineFunctionPass {
  CodasipTargetMachine &TM;
  const TargetInstrInfo *TII;
  const TargetRegisterInfo *TRI;
  const InstrItineraryData *IID;

  MachineHazardRecognizer HR; // object for detect structural hazard
  std::map<unsigned, std::pair<const MachineInstr *, unsigned>>
      mapRegToLat; // map for detect data hazard dependency
  std::set<const MachineInstr *> alreadyProcess;

  static char ID;
  VliwNoopAdder(CodasipTargetMachine &tm)
      : MachineFunctionPass(ID), TM(tm), TII(tm.getInstrInfo()),
        TRI(tm.getRegisterInfo()), IID(tm.getInstrItineraryData()),
        HR(IID, TII, TRI) {}

  StringRef getPassName() const override { return "Codasip Vliw Noop Adder"; }

  bool runOnMachineFunction(MachineFunction &F) override;
  void InsertBundleNoop(MachineBasicBlock *BB, MachineBasicBlock::iterator MI);
  void goThroughBasicBlock(MachineBasicBlock *BB);
  void AdvanceCycle();
  bool getDataHazard(const MachineInstr *MInst);
  void emitInstruction(const MachineInstr *MInst);
  bool suitableForLatencyBypass(const MachineInstr *TargetMInst,
                                unsigned TargetOperand, unsigned Reg,
                                std::pair<const MachineInstr *, unsigned> Orig);
  bool canRemoveRecDueBypass(const MachineInstr *TargetMInst,
                             unsigned TargetOperand, unsigned Reg,
                             std::pair<const MachineInstr *, unsigned> Orig);
};
}

char VliwNoopAdder::ID;

/// InsertBundleNoop - insert bundle full of noops, before instruction, which
/// create any kind of hazard.
void VliwNoopAdder::InsertBundleNoop(MachineBasicBlock *BB,
                                     MachineBasicBlock::iterator MI) {
  MachineBasicBlock::instr_iterator startMI = (&*MI)->getIterator();
  const CodasipBaseInstrInfo *CTII =
      static_cast<const CodasipBaseInstrInfo *>(TII);
  for (unsigned i = 0; i < IID->SchedModel.IssueWidth; ++i) {
    CTII->insertNoopOnPos(*BB, MI, i);
  }
  for (unsigned i = 0; i < IID->SchedModel.IssueWidth; ++i) {
    if (startMI != BB->instr_begin()) {
      --startMI;
    }
  }
  MachineBasicBlock::instr_iterator start = startMI;
  MachineBasicBlock::instr_iterator end = (&*MI)->getIterator();
  finalizeBundle(*BB, start, end);
}

/// AdvanceCycle - go through the map for data hazard detection,
/// and decrement the latencies
void VliwNoopAdder::AdvanceCycle() {
  // go through the map:
  auto it = mapRegToLat.begin();
  while (it != mapRegToLat.end()) {
    assert(it->second.second != 0);
    it->second.second--;
    if (it->second.second == 0) {
      auto forErase = it;
      ++it;
      mapRegToLat.erase(forErase);
    } else {
      ++it;
    }
  }
  HR.AdvanceCycle();
}

/// is there a bypass?
bool VliwNoopAdder::suitableForLatencyBypass(
    const MachineInstr *TargetMInst, unsigned TargetOperand, unsigned Reg,
    std::pair<const MachineInstr *, unsigned> Orig) {
  // can we actualy bypass remaining core latency?
  // e.g. instruction has latency 2, but if consumer is from certain class,
  // result is ready after 1 cycle

  unsigned ElapsedCycles = TII->getInstrLatency(IID, *Orig.first) - Orig.second;
  // now we compute latency by operand
  // first identify index of definition in original instruction
  int OrigDefOpInd =
      Orig.first->findRegisterDefOperandIdx(Reg, false, false, TRI);
  // first false: must be def dead? no.
  // second false: can be overlap def? no as well
  if (OrigDefOpInd == -1) {
    return false; // this would mean that no definition was found
  }
  int OperandLatency = TII->getOperandLatency(
      IID, *Orig.first, OrigDefOpInd, *TargetMInst, TargetOperand);
  if (OperandLatency < 0)
    OperandLatency = TII->getInstrLatency(IID, *Orig.first);
  // operand latency before (tail)calls/returns can be lowered by one if the 
  // operand is only used after the call:
  if (OperandLatency > 0 &&
      TargetOperand >= TargetMInst->getDesc().getNumOperands())
    OperandLatency--;
  if (OperandLatency <= (int) ElapsedCycles) {
    return true; // if operand latency has already passed than we are in clear
  }
  return false;
}

/// getDataHazard - check if instruction has any register in the map for data
/// hazard detection
bool VliwNoopAdder::getDataHazard(const MachineInstr *MInst) {
  for (unsigned i = 0; i < MInst->getNumOperands(); ++i) {
    const MachineOperand &op = MInst->getOperand(i);
    if (op.isReg()) {
      unsigned reg = op.getReg();
      if (mapRegToLat.find(reg) != mapRegToLat.end()) {
        // We have found some record in reg<->lat map, but we need to check if
        // there's some available bypass.
        // For this, we are going to need defining instruction, operand in
        // question and our current instruction
        // (and some kind of metric - how much time has passed since defining
        // instr was issued by hazard recognizer)
        if (!suitableForLatencyBypass(MInst, i, reg,
                                      mapRegToLat.find(reg)->second))
          return true;
      }
    }
  }
  return false;
}

bool VliwNoopAdder::canRemoveRecDueBypass(
    const MachineInstr *TargetMInst, unsigned TargetOperand, unsigned Reg,
    std::pair<const MachineInstr *, unsigned> Orig) {
  // reasoning behind this method: RegToLat maps register definitions to elapsed
  // time from issue of defining instruction.
  // when we guarantee that register contains new value, we remove its record
  // from the map.
  // but there are special cases (producer-consumer bypass, special writes in
  // not-totally-last cycle etc.) when instruction isn't "finished" but we can
  // guarantee new value already written

  // if register is used AND defined in our candidate instruction, we assume
  // that is passed through because of bypass, otherwise bail, we don't know
  // what's going on
  int TargetUseIdx = TargetMInst->findRegisterUseOperandIdx(Reg, false, TRI);
  if (TargetUseIdx < 0)
    return true; // Register not used, carry on
  if ((unsigned)TargetUseIdx != TargetOperand && Orig.second > 0) {
    return true;
  }
  return false;
}

/// emitInstruction - put latency to the map for data hazard and EmitInstruction
/// in HazardRecognizer
void VliwNoopAdder::emitInstruction(const MachineInstr *MInst) {
  unsigned lat = TII->getInstrLatency(IID, *MInst);
  for (unsigned i = 0; i < MInst->getNumOperands(); ++i) {
    const MachineOperand &op = MInst->getOperand(i);
    if (op.isReg() && op.isDef()) {
      unsigned reg = op.getReg();
      // if register is already in map, this can lead to serious problems but if
      // this is a remnant record, which was rendered invalid by operandbypass,
      // we can safely remove it and make a new one
      if (mapRegToLat.find(reg) != mapRegToLat.end() &&
          canRemoveRecDueBypass(MInst, i, reg, mapRegToLat.find(reg)->second)) {
        mapRegToLat.erase(mapRegToLat.find(reg));
      }
      assert(mapRegToLat.find(reg) == mapRegToLat.end());
      if (lat != 0) {
        mapRegToLat[reg] = std::make_pair(MInst, lat);
      }
    }
  }
  HR.EmitMachInstruction2(MInst);
}

/// goThroughBasicBlock - consumes BasicBlock and go through bundle and
/// instruction in the bundle, check for hazard
void VliwNoopAdder::goThroughBasicBlock(MachineBasicBlock *BB) {
  // we are checking the next basic block. In case of checking multiple
  // successors, we need to somehow save the state of the hazardRec and
  // mapRegToLat.
  unsigned numHazardRecAdvancements = 0;
  auto mapRegToLatCopy = mapRegToLat;
  for (MachineBasicBlock::iterator MI = BB->begin(); MI != BB->end(); ++MI) {
    if (!MI->isBundle())
      continue;

    MachineBasicBlock::const_instr_iterator MII = (&*MI)->getIterator();
    ++MII;
    bool hasCall = false;
    MachineBasicBlock::const_instr_iterator MIIBundle = MII;
    while (MIIBundle != BB->instr_end() && MIIBundle->isInsideBundle()) {
      const MachineInstr *MInst = &*MIIBundle;
      if (MInst->isCall()) {
        hasCall = true;
      }
      while (HR.getMachHazardType(MInst) || getDataHazard(MInst)) {
        InsertBundleNoop(BB, MI);
        AdvanceCycle();
        ++numHazardRecAdvancements;
      }
      ++MIIBundle;
    }
    while (MII != BB->instr_end() && MII->isInsideBundle()) {
      const MachineInstr *MInst = &*MII;
      if (MInst->isCall()) {
        ++MII;
        continue;
        emitInstruction(MInst);
      }
      ++MII;
    }
    if (hasCall) {
      HR.Reset();
      mapRegToLat.clear();
      hasCall = false;
    } else {
      AdvanceCycle();
      numHazardRecAdvancements++;
    }
  }
  mapRegToLat = mapRegToLatCopy;
  // restore the state of HR
  for (unsigned i = 0; i < numHazardRecAdvancements; ++i) {
    HR.RecedeCycle();
  }
}

bool VliwNoopAdder::runOnMachineFunction(MachineFunction &F) {
  LLVM_DEBUG(dbgs() << "** Codasip Vliw Noop Adder **\n"
               << "** Function: " << F.getName() << '\n');

  for (MachineFunction::iterator it = F.begin(); it != F.end(); ++it) {
    MachineBasicBlock *MBB = &*it;
    HR.Reset();
    mapRegToLat.clear();
    alreadyProcess.clear();
    bool processFallThrough = true;
    // first go through parent BasicBlock
    for (MachineBasicBlock::iterator MI = MBB->begin(); MI != MBB->end();
         ++MI) {
      if (!MI->isBundle())
        continue;
      MachineBasicBlock::const_instr_iterator MII = (&*MI)->getIterator();
      ++MII;
      bool haveBranch = false;
      bool hasCall = false;
      const MachineInstr *procesInst = nullptr;
      MachineBasicBlock *succBB = nullptr;
      // go through bundle
      MachineBasicBlock::const_instr_iterator MIIBundle = MII;
      while (MIIBundle != MBB->instr_end() && MIIBundle->isInsideBundle()) {
        const MachineInstr *MInst = &*MIIBundle;
        // test for branch instruction
        if ((MInst->isBranch()) &&
            (alreadyProcess.find(MInst) == alreadyProcess.end())) {
          // get destination MBB
          for (unsigned i = 0; i < MInst->getNumOperands(); ++i) {
            const MachineOperand &op = MInst->getOperand(i);
            if (op.isMBB()) {
              assert(succBB == nullptr &&
                     "More the one branch instruction in one bundle");
              succBB = op.getMBB();
              break;
            }
          }
        }
        // if we have branch instruction, set it to the procesInst
        // and check other instruction in bundle. After bundle end
        // process the instruction
        if (succBB != nullptr && !haveBranch) {
          haveBranch = true;
          procesInst = MInst;
        }
        // if instruction creates hazard, push bundle full of noops before it
        while (HR.getMachHazardType(MInst) || getDataHazard(MInst)) {
          InsertBundleNoop(MBB, MI);
          AdvanceCycle();
        }
        if (MInst->isCall()) {
          hasCall = true;
        }
        ++MIIBundle;
      }
      // emit instruction for all bundle in one time
      while (MII != MBB->instr_end() && MII->isInsideBundle()) {
        const MachineInstr *MInst = &*MII;
        if (MInst->isCall()) {
          ++MII;
          continue;
        }
        // finally emit instruction
        emitInstruction(MInst);
        ++MII;
      }
      // if we have call, don't care about call, only reset HazardRecognizers
      // and clear the map, for data hazard
      if (hasCall) {
        HR.Reset();
        mapRegToLat.clear();
        hasCall = false;
      } else {
        AdvanceCycle();
      }
      // We are out of bundle, and in the last bundle was branch
      // instruction, so process it.
      // throw branch instruction go to the BasicBlock, which branch
      // instruction pointing, and check instruction for hazards
      if (haveBranch && succBB != nullptr) {
        assert(procesInst != nullptr);
        // take latency of jump
        unsigned lat = TII->getInstrLatency(IID, *procesInst);
        if (lat != 0 && lat - 1 > 0) {
          for (unsigned i = 0; i < lat - 1; ++i) {
            // advance cycle in count of latency
            AdvanceCycle();
          }
        }

        // check instruction in the successor BasicBlock:
        goThroughBasicBlock(succBB);

        if (procesInst->isUnconditionalBranch()) {
          // if basic block and with unconditional branch, we don't have to
          // check the fallthrough block.
          processFallThrough = false;
          break;
        }

        if (processFallThrough) {
          continue;
        } else {
          // reset HazardRecognizer and clear the map for data hazard
          HR.Reset();
          mapRegToLat.clear();
          MI = MBB->begin();
          alreadyProcess.insert(procesInst);
          break;
        }
      }
    }
    // process fallThrough BasicBlock
    MachineFunction::iterator tmpIt = it;
    ++tmpIt;
    if (processFallThrough && tmpIt != F.end()) {
      MachineBasicBlock *fallMBB = &*tmpIt;
      goThroughBasicBlock(fallMBB);
      AdvanceCycle();
    }
  }
  return true;
}

// create the vliw noop adder
FunctionPass *llvm::createCodasipVliwNoopAdderPass(CodasipTargetMachine &tm) {
  return new VliwNoopAdder(tm);
}
