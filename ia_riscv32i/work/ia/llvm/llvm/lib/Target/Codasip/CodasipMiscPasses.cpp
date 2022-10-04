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


#define DEBUG_TYPE "jump-length-checker"

#include "Codasip.h"
#include "CodasipTargetMachine.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineInstrBundle.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/LiveIntervals.h"
#include "llvm/CodeGen/SlotIndexes.h"

using namespace llvm;

namespace {

/// Expands any dummy instructions which are still left
struct Expander: public MachineFunctionPass
{
  Expander(CodasipTargetMachine& TM): MachineFunctionPass(ID), CII(TM.getInstrInfo()) {}
  StringRef getPassName() const {return "Codasip dummy instructions expander";}
  bool runOnMachineFunction(MachineFunction& MF);
  static char ID;
  const CodasipInstrInfo* CII;
};

/// Handles repeated usage of a virt reg in inline asm with 'p'
class AsmPairer: public MachineFunctionPass
{
public:
  AsmPairer(CodasipTargetMachine& TM): MachineFunctionPass(ID), CII(TM.getInstrInfo()) {}
  StringRef getPassName() const {return "Codasip inline asm reg pairs handler";}
  bool runOnMachineFunction(MachineFunction& MF);
  void getAnalysisUsage(AnalysisUsage &AU) const override;
  static char ID;
private:
  void HandleAsmPair(MachineInstr& MI);
  const CodasipInstrInfo* CII;
  bool Changed = false;
  /// Pre-RA or in RA?
  const bool PreRA = true;
};

/// Fast regalloc for inline asm with 'p'
class AsmFastAlloc: public MachineFunctionPass
{
public:
  AsmFastAlloc(CodasipTargetMachine& TM);
  StringRef getPassName() const {return "Codasip inline asm fast reg pre-allocator";}
  bool runOnMachineFunction(MachineFunction& MF);
  void getAnalysisUsage(AnalysisUsage &AU) const override;
  static char ID;
private:
  void HandleAsmPair(MachineInstr& MI);
  const CodasipRegisterInfo* CRI;
  const CodasipInstrInfo* CII;
  bool Changed = false;
};

} // end of anonymous namespace

char Expander::ID = 0;

bool Expander::runOnMachineFunction(MachineFunction &F)
{
  bool changed = false;
  // aux function
  auto AuxHandle = [this,&changed](MachineBasicBlock::iterator I, MachineBasicBlock* BB) -> bool
  {
    MachineInstr& MI = *I;
    // leave unexpanded if vliw?
    if (MI.isBundled()) return false;
    // perform the actual expansion
    bool check = CII->ExpandDummiesImpl(&MI,BB,true);
    if (check) {
      changed = true;
    }
    return check;
  };
  // go through blocks
  for (MachineFunction::iterator FI=F.begin(); FI!=F.end(); ++FI)
  {
    MachineBasicBlock* BB = &*FI;
    // first instr
    if (FI->empty()) continue;
    while (AuxHandle(FI->begin(),BB)) ;
    // remaining instrs
    MachineBasicBlock::iterator I = FI->begin();
    MachineBasicBlock::iterator J = I;
    ++I;
    for (; I != FI->end(); ++I)
    {
      if (AuxHandle(I,BB)) {
        I = J;
      }
    }
  }
  return changed;
}

//----------------------------------------------------------

// Map of inline-asm operand indexes and associated data
typedef std::map<unsigned, std::vector<const MachineOperand*> > InlineAsmRegPairs;

// note: $ character will appear as $$
static InlineAsmRegPairs GetCodasipInlineAsmPairsAux(const MachineInstr& MI)
{
  InlineAsmRegPairs ret;
  // is inline asm
  if (!MI.isInlineAsm())
  {
    return ret;
  }
  // FSA states
  enum
  {
    S_START,
    // $
    S_S1,
    // ${ - there will be modifier
    // read numbers
    S_M1,
    // : has been just read
    S_M2,
    // p (don't care otherwise)
    S_MP
    // (and then back to START)
  } s = S_START;
  // aux for tmp storage of current index
  std::string indStr;
  indStr.reserve(4);
  // empty vector
  const InlineAsmRegPairs::mapped_type emptyV;
  // the asm string
  const MachineOperand& firstMO = MI.getOperand(0);
  assert(firstMO.isSymbol());
  const char* const asmStr = firstMO.getSymbolName();
  assert(asmStr);
  for (const char* p=asmStr; *p; ++p)
  {
    const char c = *p;
    switch (s)
    {
      case S_START:
        // clear
        indStr.clear();
        // process
        if (c=='$')
        {
          s = S_S1;
        }
        break;
      case S_S1:
        if (c=='{')
        {
          s = S_M1;
        }
        // either $ or index
        // (no check, assuming the string to be correct)
        else
        {
          s = S_START;
        }
        break;
      case S_M1:
        // number
        if (c>='0' && c<='9')
        {
          indStr.push_back(c);
        }
        // end of the number
        else if (c==':')
        {
          s = S_M2;
        }
        // shouldn't happen
        else
        {
          s = S_START;
        }
        break;
      case S_M2:
        // is it 'p'?
        if (c=='p')
        {
          s = S_MP;
        }
        // don't care otherwise
        else
        {
          s = S_START;
        }
        break;
      case S_MP:
        if (c=='}')
        {
          assert(!indStr.empty());
          unsigned ind = std::stoul(indStr);
          ret.insert(std::make_pair(ind,emptyV));
        }
        // back to the beginning either way
        s = S_START;
        break;
      default:
        llvm_unreachable("unknown state");
    };
  }
  return ret;
}

static InlineAsmRegPairs GetCodasipInlineAsmPairs(const MachineInstr& MI)
{
  InlineAsmRegPairs ret = GetCodasipInlineAsmPairsAux(MI);
  if (ret.empty())
  {
    return ret;
  }
  // empty ret data for fail
  InlineAsmRegPairs fret;
  // FSA states
  enum
  {
    // expecting asm string
    S_START,
    // expecting inline asm meta (before any operands)
    S_PREMETA,
    // expecting operand meta
    S_BEGIN,
    // expecting op
    S_OP,
    // a register was read
    S_REG,
    // a bound operand, possibly a pair
    S_BOUND,
    // no more operands
    S_END
  } s = S_START;
  // counter of operands
  unsigned ind = -1;
  // storage for operand pairs
  InlineAsmRegPairs::mapped_type regOps;
  regOps.reserve(2);
  // go through operands
  for (const MachineOperand& MO : MI.operands())
  {
    switch (s)
    {
      // sauce (eat first two operands)
      case S_START:
        s = S_PREMETA;
        break;
      case S_PREMETA:
        assert(MO.isImm());
        s = S_BEGIN;
        break;
      // actual operand data loop
      case S_BOUND:
        if (MO.isReg())
        {
          s = S_BEGIN;
          break;
        }
        // epsilon edge
        LLVM_FALLTHROUGH;
      case S_BEGIN:
        // meta before op
        if (MO.isImm())
        {
          s = S_OP;
        }
        // the end
        else if (MO.isMetadata())
        {
          s = S_END;
        }
        // unexpected reg
        else if (MO.isReg())
        {
          MI.emitError("Faulty usage of 'p' in inline asm (long data used without 'p')");
          return fret;
        }
        // something unexpected
        else
        {
          // 'p' was used somewhere, this won't happen for normal inline asm
          MI.emitError("Failed to process register pairs in inline asm");
          return fret;
        }
        // raise counter
        ++ind;
        break;
      case S_OP:
        // is in the map?
        if (ret.count(ind))
        {
          // must be reg
          if (!MO.isReg())
          {
            MI.emitError("Faulty usage of 'p' in inline asm (was used with wrong data)");
            return fret;
          }
          // store directly in the map instead?
          assert(regOps.empty());
          regOps.push_back(&MO);
          // expect another reg
          s = S_REG;
        }
        // bound (input)?
        // expects the ouput index to be in the asm string
        else if (MO.isReg() && MO.isTied() && MO.isUse())
        {
          // it may be single, it may be a pair
          s = S_BOUND;
        }
        // is a normal reg or something else
        else
        {
          s = S_BEGIN;
        }
        break;
      case S_REG:
        // must be reg again
        if (!MO.isReg())
        {
          MI.emitError("Faulty usage of 'p' in inline asm (was used with short data)");
          return fret;
        }
        // store
        regOps.push_back(&MO);
        assert(ret.count(ind));
        assert(ret.at(ind).empty());
        ret.at(ind).swap(regOps);
        // expecting meta again
        s = S_BEGIN;
        break;
      // errors
      case S_END:
        MI.emitError("Failed to process register pairs in inline asm");
        return fret;
      default:
        llvm_unreachable("unknown state");
    }
  }
  return ret;
}

//----------------------------------------------------------

char AsmPairer::ID = 0;

void AsmPairer::HandleAsmPair(MachineInstr& MI)
{
  auto inds = GetCodasipInlineAsmPairsAux(MI);
  if (inds.empty())
  {
    return;
  }
  // used virt regs
  std::set<unsigned> virtRegs;
  // go through ops
  // note: do for all or use GetCodasipInlineAsmPairs instead?
  for (MachineOperand& MO : MI.operands())
  {
    if (!MO.isReg()) continue;
    if (!MO.getReg().isVirtual()) continue;
    // was handled already
    if (!PreRA)
    {
      if (MO.isTied() && MO.isUse()) continue;
    }
    // used already?
    auto vr = MO.getReg();
    if (virtRegs.count(vr)==0)
    {
      virtRegs.insert(vr);
      continue;
    }
    // handle
    MachineBasicBlock* MB = MI.getParent();
    MachineRegisterInfo& MRI = MB->getParent()->getRegInfo();
    auto nvr = MRI.cloneVirtualRegister(vr);
    BuildMI(*MB, MI, MI.getDebugLoc(), CII->get(Codasip::COPY), nvr).addUse(vr);
    MO.setReg(nvr);
    // (no need to mark this new one)
    Changed = true;
  }
}

bool AsmPairer::runOnMachineFunction(MachineFunction& MF)
{
  Changed = false;
  for (MachineBasicBlock& MB : MF)
  {
    for (MachineInstr& MI : MB)
    {
      HandleAsmPair(MI);
    }
  }
  return Changed;
}

void AsmPairer::getAnalysisUsage(AnalysisUsage &AU) const
{
  MachineFunctionPass::getAnalysisUsage(AU);
  AU.setPreservesCFG();
}

//----------------------------------------------------------

char AsmFastAlloc::ID = 0;

AsmFastAlloc::AsmFastAlloc(CodasipTargetMachine& TM)
: MachineFunctionPass(ID), CII(TM.getInstrInfo())
{
  CRI = static_cast<const CodasipRegisterInfo*>(TM.getRegisterInfo());
}

// note: greedy allocator doesn't always listen to getRegAllocationHints (even if hard hint)

// refac this
void AsmFastAlloc::HandleAsmPair(MachineInstr& MI)
{
  auto opMap = GetCodasipInlineAsmPairs(MI);
  if (opMap.empty())
  {
    return;
  }
  MachineBasicBlock& MB = *MI.getParent();
  MachineFunction& MF = *MI.getMF();
  MachineRegisterInfo& MRI = MF.getRegInfo();
  // check that everything is the same class
  const TargetRegisterClass* RC = nullptr;
  // counter of regs (contemplating one class only)
  unsigned ind = 0;
  // map of virtual regs and intended physical regs
  std::map<unsigned,unsigned> regmap;
  // go through virt regs and prepare a map
  for (const auto &item : opMap)
  {
    for (const MachineOperand* MO : item.second)
    {
      assert(MO->isReg());
      if (!MO->getReg().isVirtual()) continue;
      if (MO->isTied() && MO->isUse()) continue;
      const unsigned vr = MO->getReg();
      if (RC)
      {
        assert(RC==MRI.getRegClass(vr));
      }
      else
      {
        RC = MRI.getRegClass(vr);
      }
      // get reg
      ArrayRef<MCPhysReg> Order = CRI->getPairOrder(RC,MF);
      const MCPhysReg fr = Order[ind];
      // store
      regmap.insert(std::make_pair(vr,fr));
      // raise count
      ++ind;
    }
  }
  // replace only in the asm
  for (auto repl: regmap)
  {
    const unsigned vr = repl.first;
    const unsigned fr = repl.second;
    // reads? writes (either fully or partially)?
    auto rw = MI.readsWritesVirtualRegister(vr);
    // insert copy before
    if (rw.first)
    {
      BuildMI(MB, MI, MI.getDebugLoc(), CII->get(Codasip::COPY), fr).addUse(vr);
    }
    // substitute
    for (MachineOperand& MO : MI.operands())
    {
      if (!MO.isReg()) continue;
      if (!MO.getReg().isVirtual()) continue;
      if (MO.getReg() != vr) continue;
      // (setReg would suffice too)
      MO.substPhysReg(fr,*CRI);
    }
    // insert copy after
    if (rw.second)
    {
      MachineBasicBlock::iterator it = MI;
      ++it;
      BuildMI(MB, it, MI.getDebugLoc(), CII->get(Codasip::COPY), vr).addUse(fr);
    }
    Changed = true;
  }
}

bool AsmFastAlloc::runOnMachineFunction(MachineFunction& MF)
{
  Changed = false;
  for (MachineBasicBlock& MB : MF)
  {
    for (MachineInstr& MI : MB)
    {
      HandleAsmPair(MI);
    }
  }
  return Changed;
}

void AsmFastAlloc::getAnalysisUsage(AnalysisUsage &AU) const
{
  MachineFunctionPass::getAnalysisUsage(AU);
  AU.setPreservesCFG();
  AU.addPreserved<LiveIntervals>();
  AU.addPreserved<SlotIndexes>();
}

//----------------------------------------------------------

FunctionPass* llvm::createCodasipCallCompletionPass(CodasipTargetMachine& tm)
{
  return new Expander(tm);
}

FunctionPass* llvm::createCodasipInlineAsmRegPairsPass(CodasipTargetMachine& tm)
{
  return new AsmPairer(tm);
}

FunctionPass* llvm::createCodasipInlineAsmFastRegAlloc(CodasipTargetMachine& tm)
{
  return new AsmFastAlloc(tm);
}
