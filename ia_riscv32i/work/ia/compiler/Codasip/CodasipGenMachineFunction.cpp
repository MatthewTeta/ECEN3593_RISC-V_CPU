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


#include "CodasipGenMachineFunction.h"
#include "CodasipTargetMachine.h"

#include "llvm/ADT/IndexedMap.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/MachineDominators.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineLoopInfo.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/StackProtector.h"
#include "llvm/CodeGen/WinEHFuncInfo.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm
{

static cl::opt<bool> EnableSaveRestore("enable-save-restore", cl::init(false),
  cl::desc("Enable save/restore of callee-saved registers via libcalls"));

// alignments of stacks - not used for anything at the moment
static const unsigned AlignmentsData[ 1 ] = { 8 };

/// Settings of shrink wrapper - unknown is invalid
enum ShrinkWrapValue
{
  SW_UNKNOWN, SW_OFF, SW_ON
};

// doing work in constructor - no better place for it without hacking LLVM core
CodasipGenFunctionInfo::CodasipGenFunctionInfo(MachineFunction &MF)
: StackShift(8), StrctRetReg(0), MFI(MF.getFrameInfo())
{
  // init sizes
  // note: 0 will remain unused
  FrameSizes.resize(STACK_COUNT,0);
  // is there going to be lib save/restore?
  HasLibSaveRestoreCS_ = false;
  if (EnableSaveRestore)
  {
    const CodasipTargetMachine& CTM = static_cast<const CodasipTargetMachine&>(MF.getTarget());
    const CodasipFrameLowering* CFL = CTM.getFrameLowering();
    // check support
    if (!CFL->LibCSSupported())
    {
      errs() << "Libcall save/restore of callee saved registers was requested but there's no support.\n";
      abort();
    }
    // store
    HasLibSaveRestoreCS_ = true;
    // no dynloc
    // note: call hasFP instead?
    if (MF.getFrameInfo().hasVarSizedObjects())
    {
      HasLibSaveRestoreCS_ = false;
    }
    // not supported for interrupts
    if (MF.getFunction().hasFnAttribute("interrupt"))
    {
      HasLibSaveRestoreCS_ = false;
    }
  }
  
  // initialize shrink wrapper to default
  ShrinkWrapEnabled = SW_UNKNOWN;
  // at the moment, disabled only if lib cs enabled (not compatible)
  // - move and change this later? (if possible)
  SetShrinkWrapEnabled(!HasLibSaveRestoreCS());
  
}

unsigned CodasipGenFunctionInfo::GetStackSize(unsigned space) const
{
  assert(space < STACK_COUNT);
  if (space==0)
  {
    return MFI.getStackSize();
  }
  return FrameSizes.at(space);
}

// Was supposed to reflect calculateFrameObjectOffsets (in PrologEpilogInserter.cpp)
// but it didn't work so it needed to be dumbed down
void CodasipGenFunctionInfo::CalculateFrameObjectOffsets(unsigned space)
{
  uint64_t size = 0;
  for (int i = MFI.getObjectIndexBegin(); i < MFI.getObjectIndexEnd(); ++i)
  {
    if (MFI.isDeadObjectIndex(i)) {
      continue;
    }
    if (MFI.getStackID(i) != space) {
      continue;
    }
    unsigned os = MFI.getObjectSize(i);
    // checks
    assert(!MFI.isVariableSizedObjectIndex(i) && "doesn't work for variable sized objects");
    assert(os); //checked by above
    // incremenet and store
    size += os;
    MFI.setObjectOffset(i,-size);
  }
  FrameSizes.at(space) = size;
}

void CodasipGenFunctionInfo::ProcessFunctionBeforeFrameFinalized()
{
  // compute offsets for custom address spaces
  for (unsigned i=1; i<STACK_COUNT; ++i)
  {
    CalculateFrameObjectOffsets(i);
  }
}

void CodasipGenFunctionInfo::SetShrinkWrapEnabled(bool v)
{
  assert(ShrinkWrapEnabled == SW_UNKNOWN && "this was called already for this function");
  ShrinkWrapEnabled = (v? SW_ON: SW_OFF);
}

bool CodasipGenFunctionInfo::GetShrinkWrapEnabled() const
{
  assert(ShrinkWrapEnabled != SW_UNKNOWN && "not set yet for this function");
  return ShrinkWrapEnabled == SW_ON;
}

}//namespace llvm
