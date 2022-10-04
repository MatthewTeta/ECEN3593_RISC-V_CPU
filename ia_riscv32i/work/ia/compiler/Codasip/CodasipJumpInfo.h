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


#ifndef CODASIPJUMPINFO_H
#define CODASIPJUMPINFO_H

#include "Codasip.h"
#include "CodasipInstrInfo.h"
#include "codasip/Target/CodasipBaseTargetInstrInfo.h"
#include "codasip/misc/CodasipBaseJumpInfo.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

namespace llvm {

class CodasipJumpInfo : public BaseJumpInfo {
  const CodasipInstrInfo *CII;

public:
  CodasipJumpInfo(const MachineOperand *dest)
      : BaseJumpInfo(dest), CII(nullptr) {}
  CodasipJumpInfo(unsigned opc, InstrIt pos, MachineFunction::iterator posMBB,
                  MachineFunction *mf, const MachineOperand *dest,
                  const CodasipInstrInfo *cii);
  CodasipJumpInfo(MachineInstr *ins, const CodasipInstrInfo *cii)
      : CodasipJumpInfo(ins->getOpcode(), ins->getIterator(),
                        ins->getParent()->getIterator(),
                        ins->getParent()->getParent(), getJumpCallDest(*ins),
                        cii) {}
  CodasipJumpInfo(unsigned opc, MachineInstr *ins, const MachineOperand *dest,
                  const CodasipInstrInfo *cii)
      : CodasipJumpInfo(opc, ins->getIterator(),
                        ins->getParent()->getIterator(),
                        ins->getParent()->getParent(), dest, cii) {}
  ~CodasipJumpInfo() override { BundlePosition.clear(); }

private:
  void setJmpDirection(unsigned opcode);
  bool immediateFits(int64_t imm, int width, bool sign,
                     int trunc) const override;
  unsigned computeDistance(MachineFunction &F, MachineFunction::iterator FI,
                           InstrIt I, MachineBasicBlock *dest) const override;
};

} // end namespace llvm

#endif // CODASIPJUMPINFO_H