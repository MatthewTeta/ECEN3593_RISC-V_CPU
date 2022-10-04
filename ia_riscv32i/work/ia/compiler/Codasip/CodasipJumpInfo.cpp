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


#include "CodasipJumpInfo.h"

namespace llvm {

CodasipJumpInfo::CodasipJumpInfo(unsigned opc, InstrIt pos,
                                 MachineFunction::iterator posMBB,
                                 MachineFunction *mf,
                                 const MachineOperand *dest,
                                 const CodasipInstrInfo *cii)
    : BaseJumpInfo(dest), CII(cii) {
  Opcode = opc;
  Position = pos;
  PositionMF = mf;
  PositionMBB = posMBB;
  DelaySlots = getInsDelaySlots(cii, mf);
  cii->getAllPosInBundle(Opcode, BundlePosition);
  NumInsInBundle = 1;
  BitWidth = CII->GetJumpInfo(Opcode).Length;
  IsAbsolute = CII->GetJumpInfo(Opcode).IsAbsolute;
  setJmpDirection(Opcode);
  // When no bundle positions are defined, treat it as unbundled instruction.
  // This may happen if instruction is emulation, or it is defined in
  // user_semantics.sem like in bb700.
  if (BundlePosition.empty()) {
    BundlePosition.resize(1);
    BundlePosition[0].resize(NumInsInBundle, 0);
  }
}

void CodasipJumpInfo::setJmpDirection(unsigned opcode) {
  char dir = CII->GetJumpInfo(opcode).Direction;
  if (dir == 0) {
    Direction = BOTH;
  } else if (dir < 0) {
    Direction = BACK;
  } else if (dir > 0) {
    Direction = FORWARD;
  }
}

bool CodasipJumpInfo::immediateFits(int64_t imm, int width, bool sign,
                                    int trunc) const {
  return CheckImmImpl(imm, width, sign, trunc);
}

unsigned CodasipJumpInfo::computeDistance(MachineFunction &F,
                                          MachineFunction::iterator FI,
                                          InstrIt I,
                                          MachineBasicBlock *dest) const {
  return ComputeDistance(F, FI, I, dest);
}

} // namespace llvm