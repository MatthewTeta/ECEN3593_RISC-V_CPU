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
#include "codasip/misc/CodasipBaseJumpInfo.h"
#include "codasip/misc/utils.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "double-jump"

using namespace llvm;

namespace {

struct DoubleJumpPass : public MachineFunctionPass {
  static char ID;
  LTOFileInfo *LtoFile = nullptr;
  bool CommonMBB = true;
  bool HasBundles = 1 > 1;
  const CodasipInstrInfo *CII;
  MachineFunction *MF = nullptr;

  DoubleJumpPass() : MachineFunctionPass(ID), CII(nullptr) {}
  DoubleJumpPass(CodasipTargetMachine &tm);
  ~DoubleJumpPass();

  bool runOnMachineFunction(MachineFunction &F) override;
  bool runPass(MachineBasicBlock *mbb);

  bool canOptimize(const CodasipJumpInfo &condJumpInfo,
                   const CodasipJumpInfo &uncondJumpInfo,
                   const CodasipJumpInfo &invJumpInfo);
  void replaceCondJump(MachineInstr *oldJump,
                       const CodasipJumpInfo &oldJumpInfo,
                       const CodasipJumpInfo &newJumpInfo);
  void resetSuccessors(MachineBasicBlock *mbb);
  MachineInstr *getConditionalJumpCommon(MachineBasicBlock *mbb);
  MachineInstr *getConditionalJumpSeparate(MachineBasicBlock *mbb);
  MachineInstr *getUnconditionalJump(MachineBasicBlock *mbb);
};

} // end anonymous namespace

char DoubleJumpPass::ID = 0;
char &DoubleJumpPassID = DoubleJumpPass::ID;

static RegisterPass<DoubleJumpPass> X("double-jump", "Codasip double jump pass",
                                      false /* Only looks at CFG */,
                                      false /* Analysis Pass */);

DoubleJumpPass::DoubleJumpPass(CodasipTargetMachine &tm)
    : MachineFunctionPass(ID), CII(tm.getInstrInfo()) {
  LtoFile = new LTOFileInfo();
}

DoubleJumpPass::~DoubleJumpPass() { delete LtoFile; }

bool DoubleJumpPass::runOnMachineFunction(MachineFunction &F) {
  MF = &F;
  LLVM_DEBUG(dbgs() << "jumps in common BB: "
                    << (CommonMBB ? "true " : "false ") << "\n";);
  bool change = true;
  while (change) {
    change = false;
    for (MachineBasicBlock &mbb : *MF) {
      change |= runPass(&mbb);
    }
  }
  CommonMBB = false;
  LLVM_DEBUG(dbgs() << "jumps in common BB: "
                    << (CommonMBB ? "true " : "false ") << "\n";);
  change = true;
  while (change) {
    change = false;
    for (MachineBasicBlock &mbb : *MF) {
      change |= runPass(&mbb);
    }
  }
  return false;
}

bool DoubleJumpPass::canOptimize(const CodasipJumpInfo &condJumpInfo,
                                 const CodasipJumpInfo &uncondJumpInfo,
                                 const CodasipJumpInfo &invJumpInfo) {
  if (!condJumpInfo.getDestination()->isMBB() ||
      !uncondJumpInfo.getDestination()->isMBB() ||
      !invJumpInfo.getDestination()->isMBB()) {
    return false;
  }
  if (HasBundles) {
    return false;
  }
  if (uncondJumpInfo.hasDelaySlots() || condJumpInfo.hasDelaySlots() ||
      invJumpInfo.hasDelaySlots()) {
    return false;
  }
  if (!invJumpInfo.getOpcode()) {
    return false;
  }
  MachineFunction::iterator it = condJumpInfo.getMBBPosition();
  unsigned i = 0;
  do {
    ++i;
    ++it;
    if (it == MF->end()) {
      return false;
    }
  } while (CommonMBB ? i < 1 : i < 2);
  MachineBasicBlock *condDest = &(*it);
  if (condJumpInfo.getDestination()->getMBB() != condDest) {
    return false;
  }
  if (!invJumpInfo.canJumpToDestination(invJumpInfo.getDestination(), true,
                                        LtoFile)) {
    return false;
  }
  return true;
}

void DoubleJumpPass::replaceCondJump(MachineInstr *oldJump,
                                     const CodasipJumpInfo &oldJumpInfo,
                                     const CodasipJumpInfo &newJumpInfo) {
  MachineInstrBuilder mib =
      BuildMI(*newJumpInfo.getMBBPosition(), newJumpInfo.getPosition(),
              oldJump->getDebugLoc(), CII->get(newJumpInfo.getOpcode()));
  for (auto &mo : oldJump->operands()) {
    if (mo.isIdenticalTo(*oldJumpInfo.getDestination())) {
      mib.add(*newJumpInfo.getDestination());
      continue;
    }
    mib.add(mo);
  }
  oldJump->removeFromParent();
}

void DoubleJumpPass::resetSuccessors(MachineBasicBlock *mbb) {
  if (mbb == nullptr) {
    return;
  }
  for (auto *succ : mbb->successors()) {
    mbb->removeSuccessor(succ);
  }
  for (auto &mi : mbb->instrs()) {
    // If it is not a simple branch, we are in a table somewhere.
    if (!mi.isBranch()) {
      continue;
    }
    MachineOperand *dest = getJumpCallDest(mi);
    if (dest == nullptr) {
      continue;
    }
    if (!dest->isMBB()) {
      continue;
    }
    mbb->addSuccessorWithoutProb(dest->getMBB());
  }
  if (mbb->getNextNode()) {
    mbb->addSuccessorWithoutProb(mbb->getNextNode());
  }
}

MachineInstr *DoubleJumpPass::getUnconditionalJump(MachineBasicBlock *mbb) {
  if (mbb == nullptr) {
    return nullptr;
  }
  if (mbb->empty()) {
    return nullptr;
  }
  // can't use getFirstTerminator() because of DummyVariableOps
  // note: no longer a problem, DummyVariableOps was removed. Can this be
  // changed?
  MachineBasicBlock::reverse_iterator rit = mbb->rbegin();
  while (rit != mbb->rend()) {
    if (rit->isUnconditionalBranch()) {
      break;
    }
    if (!rit->isDebugInstr()) {
      return nullptr;
    }
    ++rit;
  }
  if (rit == mbb->rend()) {
    return nullptr;
  }
  MachineInstr *lastJump = &(*rit);
  if (!lastJump->isUnconditionalBranch()) {
    return nullptr;
  }
  if (CommonMBB) {
    return lastJump;
  }
  if (&(*mbb->begin()) != lastJump) {
    return nullptr;
  }
  if (mbb->pred_size() != 1) {
    return nullptr;
  }
  if (*mbb->pred_begin() != mbb->getPrevNode()) {
    return nullptr;
  }
  return lastJump;
}

MachineInstr *DoubleJumpPass::getConditionalJumpCommon(MachineBasicBlock *mbb) {
  if (mbb == nullptr) {
    return nullptr;
  }
  if (mbb->empty()) {
    return nullptr;
  }
  // check the number of jump instructions - only 2 allowed
  // one conditional, one unconditional
  int jmpCount = 0;
  for (auto &mi : mbb->instrs()) {
    if (!mi.isBranch()) {
      continue;
    } else {
      ++jmpCount;
    }
  }
  if (jmpCount != 2) {
    return nullptr;
  }
  // can't use getFirstTerminator() because of DummyVariableOps
  // note: the same as above
  MachineBasicBlock::reverse_iterator rit = mbb->rbegin();
  while (rit != mbb->rend()) {
    if (rit->isConditionalBranch()) {
      return &(*rit);
    }
    if (!rit->isDebugInstr() && !rit->isUnconditionalBranch()) {
      return nullptr;
    }
    ++rit;
  }
  return nullptr;
}

MachineInstr *
DoubleJumpPass::getConditionalJumpSeparate(MachineBasicBlock *mbb) {
  if (mbb == nullptr) {
    return nullptr;
  }
  if (mbb->empty()) {
    return nullptr;
  }
  // check the number of jump instructions - only 1 allowed
  // one conditional
  int jmpCount = 0;
  for (auto &mi : mbb->instrs()) {
    if (!mi.isBranch()) {
      continue;
    } else {
      ++jmpCount;
    }
  }
  if (jmpCount != 1) {
    return nullptr;
  }
  // can't use getFirstTerminator() because of DummyVariableOps
  // note: the same as above
  MachineBasicBlock::reverse_iterator rit = mbb->rbegin();
  while (rit != mbb->rend()) {
    if (rit->isConditionalBranch()) {
      break;
    }
    if (!rit->isDebugInstr()) {
      return nullptr;
    }
    ++rit;
  }
  if (rit == mbb->rend() || !rit->isConditionalBranch()) {
    return nullptr;
  }
  if (mbb->succ_size() != 2) {
    return nullptr;
  }
  if (!mbb->getNextNode() || !mbb->getNextNode()->getNextNode()) {
    return nullptr;
  }
  if (!mbb->isSuccessor(mbb->getNextNode()) ||
      !mbb->isSuccessor(mbb->getNextNode()->getNextNode())) {
    return nullptr;
  }
  return &(*rit);
}

bool DoubleJumpPass::runPass(MachineBasicBlock *mbb) {
  LLVM_DEBUG({
    dbgs() << "Before: \n";
    mbb->dump();
  });
  MachineInstr *condJump = CommonMBB ? getConditionalJumpCommon(mbb)
                                     : getConditionalJumpSeparate(mbb);
  MachineInstr *uncondJump =
      getUnconditionalJump(CommonMBB ? mbb : mbb->getNextNode());
  if (!condJump || !uncondJump) {
    return false;
  }
  LLVM_DEBUG({
    dbgs() << "conditional jump: ";
    condJump->dump();
    dbgs() << "unconditional jump: ";
    uncondJump->dump();
  });
  CodasipJumpInfo condJumpInfo = CodasipJumpInfo(condJump, CII);
  CodasipJumpInfo uncondJumpInfo = CodasipJumpInfo(uncondJump, CII);
  CodasipJumpInfo invJumpInfo = CodasipJumpInfo(
      condJumpInfo.getInvertJumpOpcode(CII), uncondJump->getIterator(),
      uncondJump->getParent()->getIterator(), MF,
      uncondJumpInfo.getDestination(), CII);
  if (canOptimize(condJumpInfo, uncondJumpInfo, invJumpInfo)) {
    invJumpInfo = CodasipJumpInfo(condJumpInfo.getInvertJumpOpcode(CII),
                                  condJump->getParent()->instr_end(),
                                  condJump->getParent()->getIterator(), MF,
                                  uncondJumpInfo.getDestination(), CII);
    replaceCondJump(condJump, condJumpInfo, invJumpInfo);
    if (CommonMBB) {
      uncondJump->removeFromParent();
    } else {
      uncondJump->getParent()->removeFromParent();
    }

    resetSuccessors(mbb);
    LLVM_DEBUG(dbgs() << "FOUND \n";);
    return true;
  }
  LLVM_DEBUG(dbgs() << "can't optimize \n";);
  return false;
}

FunctionPass *llvm::createCodasipDoubleJumpPass(CodasipTargetMachine &tm) {
  return new DoubleJumpPass(tm);
}