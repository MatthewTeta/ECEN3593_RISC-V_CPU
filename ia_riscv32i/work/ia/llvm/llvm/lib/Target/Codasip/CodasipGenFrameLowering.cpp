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


#include "Codasip.h"
#include "CodasipGenFrameLowering.h"
#include "CodasipInstrInfo.h"
#include "CodasipMachineFunction.h"
#include "CodasipTargetMachine.h"

#include "llvm/IR/Function.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/ADT/Twine.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "codasip/misc/utils.h"

#define DEBUG_TYPE "frame-lowering"

using namespace llvm;

CodasipGenFrameLowering::CodasipGenFrameLowering(const CodasipTargetMachine &tm, bool realig)
: TargetFrameLowering(StackGrowsDown,8,0,8,realig), TII(*tm.getInstrInfo()), TRI(TII.getRegisterInfo())
{
  CheckLibCalleeSaves = true;
}

bool CodasipGenFrameLowering::LibCSSupported() const
{
  return TII.LibCSSupported();
}

// Warning: hasCalls is unknown during instruction selection - do not use it here
// note: hasVarSizedObjects is set before selection so it's safe to use
bool CodasipGenFrameLowering::hasFP(const MachineFunction &MF) const
{
  // has frameadr built-in
  if (MF.getFrameInfo().isFrameAddressTaken()) return true;
  // compiled with -fno-omit-frame-pointer?
  if (MF.getTarget().Options.DisableFramePointerElim(MF)) return true;
  // VarSizedObjects
  return MF.getFrameInfo().hasVarSizedObjects();
}

bool CodasipGenFrameLowering::hasReservedCallFrame(const MachineFunction &MF) const
{
  // this will merely return !hasFP(MF)
  return TargetFrameLowering::hasReservedCallFrame(MF);
}

// can we skip prologue/epilogue?
static inline bool CanForgoProEpi(const MachineFunction &MF)
{
  // optimlevel?
  const TargetMachine &TM = MF.getTarget();
  if (TM.getOptLevel()==CodeGenOpt::None) return false;
  // calls or local space?
  // note: this will cover contents of hasFP (or should there be a check here?)
  return !HasCall(MF) && !MF.getFunction().isVarArg() && !MF.getFrameInfo().hasStackObjects();
}

// warning: this assumes that the user doesn't want any "holes"
void CodasipGenFrameLowering::LibSaveRestoreCheck(MachineFunction &MF, BitVector &SavedRegs) const
{
  CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  if (!finfo->HasLibSaveRestoreCS())
  {
    return;
  }
  if (!CheckLibCalleeSaves)
  {
    return;
  }
  // go through the callee saves
  // (may or may not include BP, see CodasipGen2RegisterInfo::getCalleeSavedRegs)
  const MCPhysReg *CSRegs = MF.getRegInfo().getCalleeSavedRegs();
  assert(CSRegs && "getCalleeSavedRegs() returned null");
  // determine max index
  unsigned N = 0;
  for (unsigned i=0; CSRegs[i]; ++i)
  {
    N = i;
  }
  // go from the end (BP is set in SavedRegs at this point)
  bool firstHit = false;
  for (int i=N; i>=0; --i)
  {
    const unsigned reg = CSRegs[i];
    // skip if BP or RAR
    // (BPs are stored always if lib cs)
    bool isBP = false;
    for (unsigned space=0; space<STACK_COUNT; ++space)
    {
      if (reg==TRI.GetBP(space))
      {
        isBP = true;
      }
      else if (reg==TRI.getRARegister())
      {
        isBP = true;
      }
    }
    if (isBP)
    {
      continue;
    }
    // set?
    if (SavedRegs.test(reg))
    {
      firstHit = true;
    }
    // not set
    else
    {
      // check
      if (firstHit)
      {
        // set
        SavedRegs.set(reg);
      }
    }
  }
}

void CodasipGenFrameLowering::HandleLibSaveRestore(MachineFunction &MF, BitVector &SavedRegs) const
{
  CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  if (finfo->HasLibSaveRestoreCS())
  {
    // anything at all?
    if (SavedRegs.none())
    {
      finfo->UnsetLibSaveRestoreCS();
    }
  }
  // more checks, if still lib cs
  if (finfo->HasLibSaveRestoreCS())
  {
    // if any, set all BPs and RAR
    // note: they may or may not be set at this point
    if (SavedRegs.any())
    {
      for (unsigned space=0; space<STACK_COUNT; ++space)
      {
        SavedRegs.set(TRI.GetBP(space));
      }
      if (TRI.getRARegister())
      {
        SavedRegs.set(TRI.getRARegister());
      }
    }
  }
  // check the result for "holes"
  // note: this isn't needed under normal circumstances
  LibSaveRestoreCheck(MF, SavedRegs);
}

void CodasipGenFrameLowering::CreateEmergencySpillSlot(MachineFunction &MF, RegScavenger *RS) const
{
  if (MF.getFrameInfo().getNumObjects() > 0)
  {
    const TargetRegisterClass *RC = TRI.getRegClass(TII.get(Codasip::e_movi32__).OpInfo[0].RegClass);
    unsigned size = TRI.getSpillSize(*RC);
    unsigned align = TRI.getSpillAlignment(*RC);
    // In the worst case, we need as many spill slots as the max stack operands per instruction:
    unsigned MaxFIOperands = findMaxFIOperands(MF);
    for (unsigned i = 0; i < MaxFIOperands; ++i) {
      RS->addScavengingFrameIndex(MF.getFrameInfo().CreateStackObject(size,align,false));
    }
  }
}

// this is the first method called in the process, edit finfo here if needed
void CodasipGenFrameLowering::determineCalleeSaves(MachineFunction &MF, BitVector &SavedRegs, RegScavenger *RS) const
{
  // call parent first
  TargetFrameLowering::determineCalleeSaves(MF, SavedRegs, RS);
  // interrupt handlers
  MachineFrameInfo &MFI = MF.getFrameInfo();
  if (MF.getFunction().hasFnAttribute("interrupt")) {
    
    MF.setAlignment(2);
    
    if (MFI.hasCalls()) {
      const MCPhysReg *saveds = TRI.getCalleeSavedRegs(&MF);
      for (unsigned i = 0; saveds[i]; ++i)
        SavedRegs.set(saveds[i]);
    }
  }
  // check the result, unset if no CS
  HandleLibSaveRestore(MF, SavedRegs);
  // note: this is here because it's convenient
  CreateEmergencySpillSlot(MF, RS);
}

bool CodasipGenFrameLowering::NeedsNoShift(const MachineFunction &MF, unsigned space) const
{
  const CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  return space || !hasFP(MF) || finfo->HasLibSaveRestoreCS();
}

// note1: this is absolute value
// note2: this is overall shift as computed by llvm (lib cs included)
int64_t CodasipGenFrameLowering::GetStackShift(const MachineFunction &MF, unsigned space, bool noShiftExpl) const
{
  const CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  int64_t Offset = finfo->GetStackSize(space);
  assert(Offset>=0);
  // determine, whether manual shift is needed
  // HasLibSaveRestoreCS() here and in StackAlloc has diffrent meaning
  // (libsave will store BP even if not neccessary)
  const bool noShift = noShiftExpl || NeedsNoShift(MF,space);
  // add offset for BP, if needed AND requested
  if (!noShift)
  {
    Offset += finfo->StackShift;
  }
  return Offset;
}

// note: all of this expects downward growth of the stack
void CodasipGenFrameLowering::StackAlloc(MachineFunction &MF, MachineBasicBlock &MB, MachineBasicBlock::iterator II, bool dir) const
{
  MachineBasicBlock::iterator BuildI;
  const CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  // lib CS s/r supports only one AS
  assert(STACK_COUNT==1 || !finfo->HasLibSaveRestoreCS());
  // flags to be used by instructions emitted here
  MachineInstr::MIFlag miflag(dir? MachineInstr::FrameDestroy: MachineInstr::FrameSetup);
  for (unsigned space=0; space < STACK_COUNT; ++space)
  {
    DebugLoc dl;
    if (II != MB.end()) {
      dl = II->getDebugLoc();
    }
    // account for RAR&BP in lib save/restore right away
    // - however, space for BP will be allocated in lib save, if lib save used
    int64_t Offset = GetStackShift(MF, space, finfo->HasLibSaveRestoreCS());
    // allocate space?
    if (Offset==0) continue;
    // are cs regs saved in lib save/restore?
    if (finfo->HasLibSaveRestoreCS())
    {
      // how much was shifted by lib save/restore?
      const std::vector<CalleeSavedInfo> &CSI = MF.getFrameInfo().getCalleeSavedInfo();
      int64_t CSLibShift = 0;
      for (const CalleeSavedInfo& item: CSI)
      {
        assert(!item.isSpilledToReg());
        int64_t off = -(MF.getFrameInfo().getObjectOffset(item.getFrameIdx()));
        assert(off>=0);
        if (CSLibShift < off)
        {
          CSLibShift = off;
        }
      }
      // note: CSLibShift should be, at this point, a sum of sizes of all cs regs
      // print it for debug purposes
      if (!dir)
      {
        LLVM_DEBUG(dbgs() << "Function " << MF.getName() << " uses library CS-save/restore which shifts SP by "
                          << CSLibShift << "\n");
      }
      // detract it from the normal offset
      Offset -= CSLibShift;
    }
    // check again
    // note: it would be better if there was only this one
    if (Offset==0) continue;
    // - should be positive, see GetStackShift
    assert(Offset>0);
    // emit
    MachineOperand SP_R = MachineOperand::CreateReg(TRI.GetSP(space),false);
    MachineOperand SP_W = MachineOperand::CreateReg(TRI.GetSP(space),true);
    SmallVector<MachineOperand,3> stackShiftOps;
    stackShiftOps.push_back(SP_W);
    stackShiftOps.push_back(SP_R);
    MachineOperand off = MachineOperand::CreateImm(dir? Offset: -Offset);
    stackShiftOps.push_back(off);
    TII.EmitEssentialInstr(MB,II,dl,ISD::ADD,stackShiftOps);
    BuildI = std::prev(II);
    BuildI->setFlag(miflag);
  }
}

bool CodasipGenFrameLowering::enableShrinkWrapping(const MachineFunction& MF) const
{
  const CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  return finfo->GetShrinkWrapEnabled();
}

bool CodasipGenFrameLowering::enableCalleeSaveSkip(const MachineFunction &MF) const
{
  // exploit the assert checks in the parrent, drop the return value
  TargetFrameLowering::enableCalleeSaveSkip(MF);
  // is there a case when we wouldn't want this?
  // (llvm already does all the neccessary deductions)
  return true;
}

// note: certain basic&invariable cfi was left here
// WARNING: spill/restore libcall is supposed to handle RAR and BP as well!!
void CodasipGenFrameLowering::emitPrologue(MachineFunction &MF, MachineBasicBlock &MB) const
{
  const CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  MachineBasicBlock::iterator II = MB.begin();
  MachineBasicBlock::iterator BuildI;
  DebugLoc dl;
  bool hasCall = HasCall(MF);
  (void)hasCall;
  unsigned CFIIndex = -1;
  // add initial cfa
  // (cfa is a value of SP upon entering a function and never changes)
  // insert initial .cfi_def_cfa directive
  
  MCCFIInstruction defCfa0 = MCCFIInstruction::createDefCfa(nullptr, TRI.getDwarfRegNum(TRI.GetSP(0),0), 0);
  
  CFIIndex = MF.addFrameInst(defCfa0);
  BuildMI(MB,II,dl, TII.get(TargetOpcode::CFI_INSTRUCTION)).addCFIIndex(CFIIndex).setMIFlag(MachineInstr::FrameSetup);
  // skip completely?
  // note: SP still points at the "top" of the stack!
  if (CanForgoProEpi(MF)) {
    return;
  }
  // skip past lib-spill, if any
  if (finfo->HasLibSaveRestoreCS())
  {
    while (II != MB.end() && II->getFlag(MachineInstr::FrameSetup))
    {
      ++II;
    }
  }
  // allocate space (if anything to allocate)
  StackAlloc(MF,MB,II,false);
  // go through each space and store BPs and such
  // note: all BPs are stored on stack 0
  for (unsigned space=0; space < STACK_COUNT; ++space)
  {
    // prepare operands
    MachineOperand SP_R = MachineOperand::CreateReg(TRI.GetSP(space),false);
    MachineOperand BP_R = MachineOperand::CreateReg(TRI.GetBP(space),false);
    MachineOperand BP_W = MachineOperand::CreateReg(TRI.GetBP(space),true);
    MachineOperand SP0_R = MachineOperand::CreateReg(TRI.GetSP(0),false);
    // how was SP of this stack shifted in StackAlloc
    const int64_t Offset0 = GetStackShift(MF,0);
    // operations for space 0 only
    if (space==0)
    {
      
      if (hasCall && !finfo->HasLibSaveRestoreCS())
      {
        if (MF.getFunction().hasFnAttribute(Attribute::ShadowCallStack))
        {
          
          errs() << "There is no Shadow Call Stack pointer register specified! Shadow call stack won't be used.\n";
          
        }
      }
      
    }
    // using BP?
    if (!hasFP(MF)) {
      continue;
    }
    // note: this can be ommitted even if there are calls
    // save BP
    if (!finfo->HasLibSaveRestoreCS())
    {
      const int BP_off = space * 4 - finfo->StackShift;
      MachineOperand off = MachineOperand::CreateImm(BP_off + Offset0);
      SmallVector<MachineOperand,3> ops;
      ops.push_back(BP_R);
      ops.push_back(SP0_R);
      ops.push_back(off);
      TII.EmitEssentialInstr(MB,II,dl,ISD::STORE,ops);
      BuildI = std::prev(II);
      BuildI->setFlag(MachineInstr::FrameSetup);
    }
    // set a new one
    const int64_t Offset2 = GetStackShift(MF,space,true);
    SmallVector<MachineOperand,3> ops2;
    ops2.push_back(BP_W);
    ops2.push_back(SP_R);
    ops2.push_back(MachineOperand::CreateImm(Offset2));
    TII.EmitEssentialInstr(MB,II,dl,ISD::ADD,ops2);
    BuildI = std::prev(II);
    BuildI->setFlag(MachineInstr::FrameSetup);
  }
}

// note: certain basic&invariable cfi was left here
void CodasipGenFrameLowering::emitEpilogue(MachineFunction &MF, MachineBasicBlock &MB) const
{
  const CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  unsigned CFIIndex = -1;
  bool hasCall = HasCall(MF);
  (void)hasCall;
  MachineOperand SP0_R = MachineOperand::CreateReg(TRI.GetSP(0),false);
  // skip completely?
  if (CanForgoProEpi(MF)) return;
  // determine insertion point (MB may not have any terminator)
  MachineBasicBlock::iterator II = MB.end();
  if (!MB.empty())
  {
    II = MB.getFirstTerminator();
    // no terminator
    if (II == MB.end())
    {
      // first debug instr or end
      II = MB.getLastNonDebugInstr();
      assert(II != MB.end());
      ++II;
    }
  }
  // return before lib-restore, if any
  if (finfo->HasLibSaveRestoreCS())
  {
    while (II != MB.begin() && std::prev(II)->getFlag(MachineInstr::FrameDestroy))
    {
      --II;
    }
  }
  // copy debug info
  DebugLoc dl;
  if (II != MB.end())
  {
    dl = II->getDebugLoc();
  }
  // restore BPs and such
  for (unsigned space=0; space < STACK_COUNT; ++space)
  {
    // prepare ops
    MachineOperand BP_W = MachineOperand::CreateReg(TRI.GetBP(space),true);
    // partially restore SP from BP, if BP
    if (hasFP(MF))
    {
      TII.copyPhysReg(MB, II, dl, TRI.GetSP(space), TRI.GetBP(space), false);
      std::prev(II)->setFlag(MachineInstr::FrameDestroy);
    }
    // libcall used?
    if (finfo->HasLibSaveRestoreCS())
    {
      continue;
    }
    // restore BP (and RAR) - see prologue
    
    if (hasCall && space==0)
    {
      
    }
    
    if (hasFP(MF))
    {
      const int BP_off = space * 4;
      MachineOperand off = MachineOperand::CreateImm(BP_off);
      SmallVector<MachineOperand,3> ops;
      ops.push_back(BP_W);
      ops.push_back(SP0_R);
      ops.push_back(off);
      TII.EmitEssentialInstr(MB,II,dl,ISD::LOAD,ops);
      std::prev(II)->setFlag(MachineInstr::FrameDestroy);
    }
  }
  // shift SP0, if BP
  if (hasFP(MF))
  {
    MachineOperand off = MachineOperand::CreateImm(finfo->StackShift);
    SmallVector<MachineOperand,3> ops;
    MachineOperand SP0_W = MachineOperand::CreateReg(TRI.GetSP(0),true);
    ops.push_back(SP0_W);
    ops.push_back(SP0_R);
    ops.push_back(off);
    TII.EmitEssentialInstr(MB,II,dl,ISD::ADD,ops);
    std::prev(II)->setFlag(MachineInstr::FrameDestroy);
  }
  // restore old SPs by shifts, if no BP
  else
  {
    StackAlloc(MF,MB,II,true);
  }
  // final cfi
  CFIIndex = MF.addFrameInst(MCCFIInstruction::createDefCfa(nullptr, TRI.getDwarfRegNum(TRI.GetSP(0),0), 0));
  BuildMI(MB,II,dl, TII.get(TargetOpcode::CFI_INSTRUCTION)).addCFIIndex(CFIIndex).setMIFlag(MachineInstr::FrameDestroy);
}

const char* CodasipGenFrameLowering::getCSLibCallName(MachineFunction &MF,
                                                      const std::vector<CalleeSavedInfo> &CSI,
                                                      bool save) const
{
  // get least allocatable spilled reg (the last one but before BP(s))
  // see determineCalleeSaves - regs are stored in CSI in same order as getCalleeSavedRegs gives them
  assert(!CSI.empty());
  unsigned topReg = 0;
  bool hasBP = false;
  for (auto it=CSI.rbegin(); it!=CSI.rend(); ++it)
  {
    // skip if a BP
    bool isBP = false;
    for (unsigned space=0; space<STACK_COUNT; ++space)
    {
      if (it->getReg()==TRI.GetBP(space))
      {
        isBP = true;
        hasBP = true;
      }
    }
    if (isBP) continue;
    topReg = it->getReg();
    break;
  }
  switch (topReg)
  {
    case Codasip::rf_xpr_9:
return save?"__codasip_libcs_save_rf_xpr_9":"__codasip_libcs_restore_rf_xpr_9";
case Codasip::rf_xpr_18:
return save?"__codasip_libcs_save_rf_xpr_18":"__codasip_libcs_restore_rf_xpr_18";
case Codasip::rf_xpr_19:
return save?"__codasip_libcs_save_rf_xpr_19":"__codasip_libcs_restore_rf_xpr_19";
case Codasip::rf_xpr_20:
return save?"__codasip_libcs_save_rf_xpr_20":"__codasip_libcs_restore_rf_xpr_20";
case Codasip::rf_xpr_21:
return save?"__codasip_libcs_save_rf_xpr_21":"__codasip_libcs_restore_rf_xpr_21";
case Codasip::rf_xpr_22:
return save?"__codasip_libcs_save_rf_xpr_22":"__codasip_libcs_restore_rf_xpr_22";
case Codasip::rf_xpr_23:
return save?"__codasip_libcs_save_rf_xpr_23":"__codasip_libcs_restore_rf_xpr_23";
case Codasip::rf_xpr_24:
return save?"__codasip_libcs_save_rf_xpr_24":"__codasip_libcs_restore_rf_xpr_24";
case Codasip::rf_xpr_25:
return save?"__codasip_libcs_save_rf_xpr_25":"__codasip_libcs_restore_rf_xpr_25";
case Codasip::rf_xpr_26:
return save?"__codasip_libcs_save_rf_xpr_26":"__codasip_libcs_restore_rf_xpr_26";
case Codasip::rf_xpr_27:
return save?"__codasip_libcs_save_rf_xpr_27":"__codasip_libcs_restore_rf_xpr_27";

  }
  // only BP(s)?
  if (hasBP)
  {
    return save?"__codasip_libcs_save_BPs":"__codasip_libcs_restore_BPs";
  }
  // shouldn't happen, is detected earlier
  return nullptr;
}

bool CodasipGenFrameLowering::SpillRestoreImpl(MachineBasicBlock &MB,
                                               MachineBasicBlock::iterator MI,
                                               const std::vector<CalleeSavedInfo> &CSI,
                                               bool spill) const
{
  MachineFunction *MF = MB.getParent();
  const CodasipFunctionInfo *finfo = MF->getInfo<CodasipFunctionInfo>();
  if (!finfo->HasLibSaveRestoreCS()) {
    return false;
  }
  // CSI is never empty here
  assert(!CSI.empty());
  // use libcall instead of manual spill
  DebugLoc DL;
  if (MI != MB.end() && !MI->isDebugInstr())
    DL = MI->getDebugLoc();
  // Insert a call with altenative link register
  const char *LibCall = getCSLibCallName(*MF, CSI, spill);
  assert(LibCall);
  auto MIB = BuildMI(MB, MI, DL, TII.get(TII.GetLibCSSpillInstr()), TII.GetLibCSSpillReg());
  auto flag = (spill? MachineInstr::FrameSetup: MachineInstr::FrameDestroy);
  MIB.addExternalSymbol(LibCall).setMIFlag(flag);
  // changes the auxiliary RAR
  MIB.add(MachineOperand::CreateReg(TII.GetLibCSSpillReg(), true, true));
  // shifts SP
  MIB.add(MachineOperand::CreateReg(TRI.GetSP(0), true, true));
  // Add CSI and RAR as implicit use to prevent premature overwrite
  if (spill)
  {
    for (auto &CS: CSI)
    {
      MIB.add(MachineOperand::CreateReg(CS.getReg(), false, true));
    }
  }
  // handled manually
  return true;
}

bool CodasipGenFrameLowering::spillCalleeSavedRegisters(MachineBasicBlock &MB,
                                                        MachineBasicBlock::iterator MI,
                                                        const std::vector<CalleeSavedInfo> &CSI,
                                                        const TargetRegisterInfo *TRI) const
{
  bool handled = SpillRestoreImpl(MB,MI,CSI,true);
  if (!handled) return false;
  // Add CSI as liveins
  // note: shrink wrap disabled, MB is entry
  // fixme: RAR may have been added aready
  for (auto &CS: CSI)
  {
    MB.addLiveIn(CS.getReg());
  }
  return true;
}

bool CodasipGenFrameLowering::restoreCalleeSavedRegisters(MachineBasicBlock &MB,
                                                          MachineBasicBlock::iterator MI,
                                                          std::vector<CalleeSavedInfo> &CSI,
                                                          const TargetRegisterInfo *TRI) const
{
  return SpillRestoreImpl(MB,MI,CSI,false);
}

// note: see eliminateFrameIndex
int CodasipGenFrameLowering::getFrameIndexOffset(const MachineFunction &MF, int FrameIndex) const
{
  const CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  // address space
  const unsigned space = MFI.getStackID(FrameIndex);
  // only valid if no variable sized things!
  const int StackSize = finfo->GetStackSize(space);
  // offset
  int Offset = MF.getFrameInfo().getObjectOffset(FrameIndex);
  // has calls?
  bool hasCall = HasCall(MF);
  (void)hasCall;
  // is this an outgoing stack parameter?
  const bool callParam = finfo->IsOutFI(FrameIndex);
  // fixed objects (we created them in the lowering for passing and receiving of arguments)
  if (FrameIndex<0)
  {
    // outgoing argument (placed at the end of the caller's space)
    if (callParam) {
      // no action
    }
    // shift incomming arguments, account for leaf opti
    // note: BPs are stored only on stack 0
    else {
      if (!CanForgoProEpi(MF) && !NeedsNoShift(MF,space)) {
        Offset += finfo->StackShift;
      }
      // shift even more, if stores RA on stack
      
      // FP shift?
      if (!hasFP(MF)) {
        Offset += StackSize;
      }
    }
  }
  // normal objects
  else
  {
    // should be negative (if the stack grows down)
    assert(Offset<0);
    // flip?
    if (!hasFP(MF)) {
      Offset = StackSize+Offset;
    }
  }
  return Offset;
}

// like default but added address spaces
// note: this is used only for debug purposes
int CodasipGenFrameLowering::getFrameIndexReference(const MachineFunction &MF, int FI, unsigned &freg) const
{
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  int as = MFI.getStackID(FI);
  freg = TRI.getFrameRegister(MF,as);
  return getFrameIndexOffset(MF,FI);
}

// eliminate call start/end (and other things)
MachineBasicBlock::iterator CodasipGenFrameLowering::eliminateCallFramePseudoInstr
(MachineFunction &MF, MachineBasicBlock &MB, MachineBasicBlock::iterator II) const
{
  assert(II->getOpcode()==Codasip::CALLSTART || II->getOpcode()==Codasip::CALLEND);
  const unsigned space = 0;
  if (!hasReservedCallFrame(MF))
  {
    DebugLoc dl = II->getDebugLoc();
    // is it start or end?
    bool is_start = II->getOpcode()==Codasip::CALLSTART;
    // get stack offset
    assert(II->getOperand(0).isImm());
    int off = II->getOperand(0).getImm();
    assert(off>=0);
    if (off)
    {
      if (is_start) off = -off;
      // adjust SP register
      MachineOperand SP_R = MachineOperand::CreateReg(TRI.GetSP(space), false);
      MachineOperand SP_W = MachineOperand::CreateReg(TRI.GetSP(space), true);
      MachineOperand shift = MachineOperand::CreateImm(off);
      SmallVector<MachineOperand,3> shiftOps;
      shiftOps.push_back(SP_W);
      shiftOps.push_back(SP_R);
      shiftOps.push_back(shift);
      TII.EmitEssentialInstr(MB,II,dl,ISD::ADD,shiftOps);
    }
  }
  // erase in any case
  return MB.erase(II);
}

int CodasipGenFrameLowering::getInitialCFAOffset(const MachineFunction &MF) const {
  
  return 0;
  
}

unsigned CodasipGenFrameLowering::getInitialCFARegister(const MachineFunction &MF) const {
  return TRI.getDwarfRegNum(TRI.GetSP(0), 0);
}

void CodasipGenFrameLowering::processFunctionBeforeFrameFinalized(MachineFunction &MF, RegScavenger*) const
{
  CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  finfo->ProcessFunctionBeforeFrameFinalized();
}

