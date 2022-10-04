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


#include "CodasipHazardRec.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>

#define DEBUG_TYPE "codasip-hazardrec"

void llvm::RegisterBoard::reset(unsigned depth)
{
  clear();
  assign(depth,regList());
}

// Destroys the last, inserts a new first.
void llvm::RegisterBoard::advance()
{
  pop_front();
  push_back(regList());
}

void llvm::RegisterBoard::addReg(unsigned n, unsigned r)
{
  assert(n<size());
  iterator it;
  for (it=begin(); n--; ++it);
  it->insert(r);
}

bool llvm::RegisterBoard::isPending(unsigned r, const TargetRegisterInfo &TRI)
{
  for (auto reglist : *this) {
    if (reglist.count(r))
      return true;
    // check if any reg is a sub/super of this one: if so, we're still pending:
    auto it = std::find_if(reglist.begin(), reglist.end(), [&](const unsigned reg) {
      return TRI.isSubRegister(r, reg) || TRI.isSuperRegister(r, reg);
    });

    if (it != reglist.end()) {
      return true;
    }
  }
  return false;
}

void llvm::RegisterBoard::dump() const
{
  /*for (const_iterator it=begin(); it!=end(); ++it)
  {
    for (regList::const_iterator jt=it->begin(); jt!=it->end(); ++jt)
    {
      dbgs() << *jt << " ";
    }
    dbgs() << "\n";
  }*/
}

bool llvm::MachineHazardRecognizer::Empty()
{
  for (unsigned i=0; i<ReservedScoreboard.getDepth(); ++i)
  {
    if (ReservedScoreboard[i]) return false;
  }
  for (unsigned i=0; i<RequiredScoreboard.getDepth(); ++i)
  {
    if (RequiredScoreboard[i]) return false;
  }
  for (RegisterBoard::iterator it=Registers.begin(); it!=Registers.end(); ++it)
  {
    if (!it->empty()) return false;
  }
  return true;
}

void llvm::MachineHazardRecognizer::Reset()
{
  ScoreboardHazardRecognizer::Reset();
  Registers.reset(ReservedScoreboard.getDepth());
}

void llvm::MachineHazardRecognizer::AdvanceCycle()
{
  Registers.advance();
  ScoreboardHazardRecognizer::AdvanceCycle();
}

llvm::ScheduleHazardRecognizer::HazardType
llvm::MachineHazardRecognizer::getMachHazardType(const MachineInstr *MI, int Stalls)
{
  if (!ItinData || ItinData->isEmpty())
    return NoHazard;
  // Note that stalls will be negative for bottom-up scheduling.
  int cycle = Stalls;
  // Use the itinerary for the instruction to check for
  // free FU's in the scoreboard at the appropriate future cycles.
  const MCInstrDesc *MCID = &(MI->getDesc());
  if (MCID == NULL) {
    // Don't check hazards for non-machineinstr Nodes.
    return NoHazard;
  }
  unsigned idx = MCID->getSchedClass();
  for (const InstrStage *IS = ItinData->beginStage(idx), *E = ItinData->endStage(idx); IS != E; ++IS)
  {
    // We must find one of the stage's units free for every cycle the
    // stage is occupied. note it would be more accurate to find the
    // same unit free in all the cycles.
    for (unsigned int i = 0; i < IS->getCycles(); ++i) {
      int StageCycle = cycle + (int)i;
      if (StageCycle < 0)
        continue;
      if (StageCycle >= (int)RequiredScoreboard.getDepth()) {
        assert((StageCycle - Stalls) < (int)RequiredScoreboard.getDepth() &&
               "Scoreboard depth exceeded!");
        // This stage was stalled beyond pipeline depth, so cannot conflict.
        break;
      }
      unsigned long long freeUnits = IS->getUnits();
      switch (IS->getReservationKind()) {
      case InstrStage::Required:
        // Required FUs conflict with both reserved and required ones
        freeUnits &= ~ReservedScoreboard[StageCycle];
        LLVM_FALLTHROUGH;
      case InstrStage::Reserved:
        // Reserved FUs can conflict only with required ones.
        freeUnits &= ~RequiredScoreboard[StageCycle];
        break;
      }
      if (!freeUnits) {
        //DEBUG(dbgs() << "*** Hazard in cycle +" << StageCycle);
        LLVM_DEBUG(MI->dump());
        return Hazard;
      }
    }
    // Advance the cycle to the next stage.
    cycle += IS->getNextCycles();
  }
  // data hazards (do this first?)
  for (unsigned i = 0; i < MI->getNumOperands(); ++i) {
    const MachineOperand &op = MI->getOperand(i);
    if (op.isReg() /*&& op.isUse()*/) {
      if (Registers.isPending(op.getReg(), *TRI))
        return Hazard;
    }
  }
  return NoHazard;
}

void llvm::MachineHazardRecognizer::EmitMachInstruction(const MachineInstr *MI)
{
  EmitMachInstruction2(MI);
  AdvanceCycle();
}

void llvm::MachineHazardRecognizer::EmitMachInstruction2(const MachineInstr *MI)
{
  if (!ItinData || ItinData->isEmpty())
    return;
  // Use the itinerary for the underlying instruction to reserve FU's
  // in the scoreboard at the appropriate future cycles.
  const MCInstrDesc *MCID = &(MI->getDesc());
  assert(MCID && "The scheduler must filter non-machineinstrs");
  if (TII->isZeroCost(MCID->Opcode))
    return;
  ++IssueCount;
  
  unsigned cycle = 0;
  unsigned idx = MCID->getSchedClass();
  for (const InstrStage *IS = ItinData->beginStage(idx), *E = ItinData->endStage(idx); IS != E; ++IS)
  {
    // We must reserve one of the stage's units for every cycle the
    // stage is occupied. note it would be more accurate to reserve
    // the same unit free in all the cycles.
    for (unsigned int i = 0; i < IS->getCycles(); ++i) {
      assert(((cycle + i) < RequiredScoreboard.getDepth()) &&
             "Scoreboard depth exceeded!");
      unsigned long long freeUnits = IS->getUnits();
      switch (IS->getReservationKind()) {
      case InstrStage::Required:
        // Required FUs conflict with both reserved and required ones
        freeUnits &= ~ReservedScoreboard[cycle + i];
        LLVM_FALLTHROUGH;
      case InstrStage::Reserved:
        // Reserved FUs can conflict only with required ones.
        freeUnits &= ~RequiredScoreboard[cycle + i];
        break;
      }
      // reduce to a single unit
      unsigned long long freeUnit = 0;
      do {
        freeUnit = freeUnits;
        freeUnits = freeUnit & (freeUnit - 1);
      } while (freeUnits);
      if (IS->getReservationKind() == InstrStage::Required)
        RequiredScoreboard[cycle + i] |= freeUnit;
      else
        ReservedScoreboard[cycle + i] |= freeUnit;
    }
    // Advance the cycle to the next stage.
    cycle += IS->getNextCycles();
  }
  
  // Add data hazards (assuming writes in the last cycle for now)
  if (!MCID->isCall()) {
    // note: actually use operand latencies later
    unsigned lat = TII->getInstrLatency(ItinData, *MI);
    if (lat) {
    // - get writes
      for (unsigned i = 0; i < MI->getNumOperands(); ++i) {
        const MachineOperand &op = MI->getOperand(i);
        if (op.isReg() && op.isDef()) {
          unsigned reg = op.getReg();
          Registers.addReg(lat - 1, reg);
        }
      }
    }
  } 
  LLVM_DEBUG(std::cerr << MCID->Opcode << ":\n");
  LLVM_DEBUG(ReservedScoreboard.dump());
  LLVM_DEBUG(RequiredScoreboard.dump());
  LLVM_DEBUG(Registers.dump());
  LLVM_DEBUG(dbgs() << "-----------------\n");
}

