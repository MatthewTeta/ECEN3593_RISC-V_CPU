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


#ifndef CODASIPGENMACHINEFUNCTIONINFO_H
#define CODASIPGENMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"

#include <map>
#include <set>
#include <vector>

#define STACK_COUNT 1

namespace llvm {

/// A set of FIs
typedef std::set<int> FISet;

class CodasipGenFunctionInfo: public MachineFunctionInfo
{
public:
  CodasipGenFunctionInfo(MachineFunction &MF);
  /// Mark outgoing call param
  void MarkOutFI(int FI);
  /// Is outgoing call param?
  bool IsOutFI(int FI) const;
  /// Either normal or custom stack size.
  unsigned GetStackSize(unsigned space) const;
  /** Performs final processing of stack objects.
   * (Meant for usage in processFunctionBeforeFrameFinalized) */
  void ProcessFunctionBeforeFrameFinalized();
  /// Uses lib save/restore?
  bool HasLibSaveRestoreCS() const;
  /** Unset usage of lib CS.
   * To be used in determineCalleeSaves. */
  void UnsetLibSaveRestoreCS();
  /** Set shrink wrapper on or off.
   * Must be unknown, rewriting not allowed. */
  void SetShrinkWrapEnabled(bool v);
  /** Read shrink wrapper setting.
   * Must be set, will assert otherwise.
   * DO NOT use this directly (only through enableShrinkWrapping)! */
  bool GetShrinkWrapEnabled() const;

  /** Metainfo for varargs.
   * Created during analysis of formal arguments.
   * Intented for usage in prologue emition - va_start needs this in constants. */
  struct ArgsInfo {
    /// The last fixed arg on the stack.
    int StackOff;
    int StackFI;
  } ArgsInfo;
  /** A stack shift (in bytes) made on stack in prologue "out of system".
   * (For registers such as BP.) */
  const int StackShift;
  /** SRetReturnReg - Some subtargets require that sret lowering includes
   * returning the value of the returned struct in a register. This field
   * holds the virtual register into which the sret argument is passed. */
  unsigned StrctRetReg;
  /** Metainfo for return value.
   * Registers used for return (if it isn't struct ret). */
  std::vector<unsigned> RetRegs;

protected:
  // aux
  void CalculateFrameObjectOffsets(unsigned space);
  
  /// Frame info from the MF in the constructor
  MachineFrameInfo& MFI;
  /// A set of FIs belonging to outgoing call params.
  FISet FI_Outs;
  /// Stack sizes (MFI stores only for 0)
  typedef std::vector<unsigned> FrameSizesT;
  FrameSizesT FrameSizes;
  /// Enabling/disabling of shrink wrapper
  int ShrinkWrapEnabled;
  /// Storage for HasLibSaveRestoreCSI
  bool HasLibSaveRestoreCS_;
};

// aux
inline bool HasCall(const MachineFunction &MF)
{
  return MF.getFrameInfo().hasCalls();
}

inline void CodasipGenFunctionInfo::MarkOutFI(int FI)
{
  FI_Outs.insert(FI);
}
inline bool CodasipGenFunctionInfo::IsOutFI(int FI) const
{
  return FI_Outs.count(FI);
}

inline bool CodasipGenFunctionInfo::HasLibSaveRestoreCS() const
{
  return HasLibSaveRestoreCS_;
}
inline void CodasipGenFunctionInfo::UnsetLibSaveRestoreCS()
{
  HasLibSaveRestoreCS_ = false;
}

}//namespace llvm

#endif
