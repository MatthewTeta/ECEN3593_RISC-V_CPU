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


// You can create your own implementations here.

#include "Codasip.h"
#include "CodasipInstrInfo.h"
#include "CodasipTargetMachine.h"
#include "CodasipSubtarget.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/ScheduleDAG.h"
#include "llvm/CodeGen/ScoreboardHazardRecognizer.h"
#include "llvm/CodeGen/DFAPacketizer.h"

#include <cstdio>
#include <iostream>
#include <vector>

llvm::CodasipInstrInfo::CodasipInstrInfo(CodasipTargetMachine &TM): CodasipGenInstrInfo2(TM) {}

void llvm::CodasipInstrInfo::copyPhysReg(MachineBasicBlock &MB,
                                         MachineBasicBlock::iterator II,
                                         const DebugLoc& DL,
                                         unsigned DestReg,
                                         unsigned SrcReg,
                                         bool KillSrc) const
{
  CodasipGenInstrInfo2::copyPhysReg(MB,II,DL,DestReg,SrcReg,KillSrc);
}

void llvm::CodasipInstrInfo::storeRegToStackSlot(MachineBasicBlock &MB,
                                                 MachineBasicBlock::iterator II,
                                                 unsigned Reg,
                                                 bool isKill,
                                                 int FrameIndex,
                                                 const TargetRegisterClass *RC,
                                                 const TargetRegisterInfo *TRI) const
{
  CodasipGenInstrInfo2::storeRegToStackSlot(MB,II,Reg,isKill,FrameIndex,RC,TRI);
}

void llvm::CodasipInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MB,
                                                  MachineBasicBlock::iterator II,
                                                  unsigned Reg,
                                                  int FrameIndex,
                                                  const TargetRegisterClass *RC,
                                                  const TargetRegisterInfo *TRI) const
{
  CodasipGenInstrInfo2::loadRegFromStackSlot(MB,II,Reg,FrameIndex,RC,TRI);
}

// Use this to add/override pseudo insertions
bool llvm::CodasipInstrInfo::ExpandDummiesImpl(MachineInstr *MIp, MachineBasicBlock* &BB, const bool postRA) const
{
  return CodasipGenInstrInfo2::ExpandDummiesImpl(MIp,BB,postRA);
}

// Edit this if you are compiling for an environment which can cause unpredicable hazards (Linux with I/O interrupts)
// If you simply return true and leave TBB, FBB and Cond unedited, no advanced BB reorganisation will be performed
bool llvm::CodasipInstrInfo::analyzeBranch(MachineBasicBlock &MBB,
                                           MachineBasicBlock *&TBB,
                                           MachineBasicBlock *&FBB,
                                           SmallVectorImpl<MachineOperand> &Cond,
                                           bool AllowModify) const
{
  return CodasipGenInstrInfo2::analyzeBranch(MBB,TBB,FBB,Cond,AllowModify);
}

bool llvm::CodasipInstrInfo::reverseBranchCondition(SmallVectorImpl<MachineOperand> &Cond) const
{
  return CodasipGenInstrInfo2::reverseBranchCondition(Cond);
}

unsigned llvm::CodasipInstrInfo::getEquivalentCondOpcode(ArrayRef<MachineOperand> Cond, int RegPos) const
{
  return CodasipGenInstrInfo2::getEquivalentCondOpcode(Cond, RegPos);
}
