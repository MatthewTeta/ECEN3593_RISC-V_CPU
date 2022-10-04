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
#include "CodasipJumpInfo.h"
#include "CodasipTargetMachine.h"
#include "codasip/Target/CodasipBaseJumplengthChecker.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include <fstream>
#include <sstream>
#include <string.h>

#define DEBUG_TYPE "jump-length-checker"

using namespace llvm;

namespace {

struct JumpLengthChecker : public BaseJumpLengthChecker {
  std::ifstream File;
  const CodasipInstrInfo *CII;

public:
  static char ID;
  JumpLengthChecker(CodasipTargetMachine &tm);
  // default ctor used only for the registration in the pass manager.
  JumpLengthChecker() : BaseJumpLengthChecker(), CII(nullptr) {}
  ~JumpLengthChecker() override { InstrsToExamine.clear(); };
  /// Allocates space on heap and calls constructors.
  std::shared_ptr<BaseJumpInfo>
  createJumpInfo(unsigned opc, MachineInstr *mi,
                 const MachineOperand *dest) override;
  std::shared_ptr<BaseJumpInfo>
  createJumpInfo(unsigned opc, MachineFunction::iterator posMBB,
                 const MachineOperand *dest) override;
  
  bool hasBundles() override { return false; }
  
  unsigned getLongJumpOpcode() override;
  unsigned getLongCallOpcode() override;
  unsigned getLongTailCallOpcode() override;
  bool checkImmFits(int64_t imm, int width, bool sign, int trunc) override;
};

} // end anonymous namespace


char JumpLengthChecker::ID = 0;
char &JumpLengthCheckerID = JumpLengthChecker::ID;

static RegisterPass<JumpLengthChecker> X("jmplen-check",
                                         "Codasip Jump Length Checker",
                                         false /* Only looks at CFG */,
                                         false /* Analysis Pass */);

JumpLengthChecker::JumpLengthChecker(CodasipTargetMachine &tm)
    : BaseJumpLengthChecker(tm, tm.getInstrInfo(), ID), CII(tm.getInstrInfo()) {
  IsVliw = 0;
}

std::shared_ptr<BaseJumpInfo>
JumpLengthChecker::createJumpInfo(unsigned opc, MachineInstr *mi,
                                  const MachineOperand *dest) {
  return std::make_shared<CodasipJumpInfo>(opc, mi, dest, CII);
}

std::shared_ptr<BaseJumpInfo>
JumpLengthChecker::createJumpInfo(unsigned opc,
                                  MachineFunction::iterator posMBB,
                                  const MachineOperand *dest) {
  assert(MF);
  return std::make_shared<CodasipJumpInfo>(opc, posMBB->instr_end(), posMBB, MF,
                                           dest, CII);
}

unsigned JumpLengthChecker::getLongJumpOpcode() {
  return CII->getLongJumpOpcode();
}

bool JumpLengthChecker::checkImmFits(int64_t imm, int width, bool sign,
                                     int trunc) {
  return CheckImmImpl(imm, width, sign, trunc);
}

unsigned JumpLengthChecker::getLongCallOpcode() {
  return CII->getLongCallOpcode();
}

unsigned JumpLengthChecker::getLongTailCallOpcode() {
  return Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_;
}

unsigned llvm::getLongJumpOpcodeStatic() { return Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__; }

FunctionPass *
llvm::createCodasipJumpLengthCheckerPass(CodasipTargetMachine &tm) {
  return new JumpLengthChecker(tm);
}