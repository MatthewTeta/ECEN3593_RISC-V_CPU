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


#ifndef CODASIP_GEN_FRAMEINFO_H
#define CODASIP_GEN_FRAMEINFO_H

#include "Codasip.h"
#include "CodasipInstrInfo.h"
#include "CodasipRegisterInfo.h"

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class CodasipGenFrameLowering: public TargetFrameLowering
{
public:
  // note: remove implicit value of realig when moving to next llvm
  explicit CodasipGenFrameLowering(const CodasipTargetMachine &tm, bool realig=false);
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void determineCalleeSaves(MachineFunction &MF, BitVector &SavedRegs, RegScavenger *RS) const override;
  bool hasFP(const MachineFunction &MF) const override;
  bool hasReservedCallFrame(const MachineFunction &MF) const override;
  MachineBasicBlock::iterator eliminateCallFramePseudoInstr(MachineFunction &MF,
                                                            MachineBasicBlock &MBB,
                                                            MachineBasicBlock::iterator MI) const override;
  int getFrameIndexReference(const MachineFunction &MF, int FI, unsigned &FrameReg) const override;
  int getInitialCFAOffset(const MachineFunction &MF) const override;
  unsigned getInitialCFARegister(const MachineFunction &MF) const override;
  void processFunctionBeforeFrameFinalized(MachineFunction &MF, RegScavenger *RS) const override;
  /// Is lib cs supported?
  bool LibCSSupported() const;
  // Shrink-wrapping support (reads from finfo)
  bool enableShrinkWrapping(const MachineFunction &MF) const override;
  // Enabled by default in Codasip
  bool enableCalleeSaveSkip(const MachineFunction &MF) const override;

protected:
  /** Aux method for general shifting of SP(s).
   * \param II Current position.
   * \param dir Prologue or epilogue? */
  void StackAlloc(MachineFunction &MF, MachineBasicBlock &MB, MachineBasicBlock::iterator II, bool dir) const;
  /** Auxiliary for StackAlloc
   * \param space For which stack?
   * \param noShiftExpl Explicitly ban making extra space for BP(s) */
  int64_t GetStackShift(const MachineFunction &MF, unsigned space, bool noShiftExpl=false) const;
  /// Auxiliary for GetStackShift and getFrameIndexOffset
  bool NeedsNoShift(const MachineFunction &MF, unsigned space) const;
  /// Aux method for getFrameIndexReference
  int getFrameIndexOffset(const MachineFunction &MF, int FI) const;
  virtual const char* getCSLibCallName(MachineFunction &MF,
                                       const std::vector<CalleeSavedInfo> &CSI,
                                       bool spill) const;
  bool spillCalleeSavedRegisters(MachineBasicBlock &MBB,
                                 MachineBasicBlock::iterator MI,
                                 const std::vector<CalleeSavedInfo> &CSI,
                                 const TargetRegisterInfo *TRI) const override;
  bool restoreCalleeSavedRegisters(MachineBasicBlock &MBB,
                                   MachineBasicBlock::iterator MI,
                                   std::vector<CalleeSavedInfo> &CSI,
                                   const TargetRegisterInfo *TRI) const override;
  virtual bool SpillRestoreImpl(MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator MI,
                                const std::vector<CalleeSavedInfo> &CSI,
                                bool spill) const;
  // for lib CS regs save/restore, prints a warning
  void LibSaveRestoreCheck(MachineFunction &MF, BitVector &SavedRegs) const;
  // called from determineCalleeSaves
  void CreateEmergencySpillSlot(MachineFunction &MF, RegScavenger *RS) const;
  void HandleLibSaveRestore(MachineFunction &MF, BitVector &SavedRegs) const;

  const CodasipInstrInfo &TII;
  const CodasipRegisterInfo &TRI;
  /// Check lib cs for "holes"?
  bool CheckLibCalleeSaves;
};

} // End llvm namespace

#endif
