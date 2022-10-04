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


//===----------------------------------------------------------------------===//
/// \file
/// This file implements a TargetTransformInfo analysis pass specific to the
/// Codasip target machine. It uses the target's detailed information to provide
/// more precise answers to certain TTI queries, while letting the target
/// independent and default TTI implementations handle the rest.
///
//===----------------------------------------------------------------------===//


#include "CodasipTargetTransformInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/CodeGen/CostTable.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Support/Debug.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
using namespace llvm;

#define DEBUG_TYPE "codasiptti"

//===----------------------------------------------------------------------===//
//
// Codasip cost model.
//
//===----------------------------------------------------------------------===//

extern cl::opt<unsigned> EnableNest;

cl::opt<bool>
    EnableHWLoops("enable-hwloops", cl::Hidden, cl::init(false),
                  cl::desc("Disable the generation of hardware loops"),
                  cl::ZeroOrMore);

bool CodasipTTIImpl::isHardwareLoopProfitable(Loop *L, ScalarEvolution &SE,
                              AssumptionCache &AC,
                              TargetLibraryInfo *LibInfo,
                              HardwareLoopInfo &HWLoopInfo) {
  if (!EnableHWLoops) {
    LLVM_DEBUG(dbgs() << "HWLoops disabled.\n";);
    return false;
  }

  // check whether the target has hwloop instructions at all
  const CodasipInstrInfo *TII =
      static_cast<const CodasipInstrInfo *>(getST()->getInstrInfo());
  std::vector<int> Opcodes;
  TII->getHWLoopOpc(Opcodes);
  if (Opcodes.empty()) {
    LLVM_DEBUG(dbgs() << "HWLoops are not supported on this architecture.\n";);
    return false;
  }

  if (findStringMetadataForLoop(L, "codasip.hwloop.disable")) {
    LLVM_DEBUG(
        dbgs() << "HWLoops disabled by pragma codasip.hwloop.disable\n";);
    return false;
  }

  if (!SE.hasLoopInvariantBackedgeTakenCount(L)) {
    return false;
  }

  const SCEV *BackedgeTakenCount = SE.getBackedgeTakenCount(L);
  if (isa<SCEVCouldNotCompute>(BackedgeTakenCount)) {
    return false;
  }
  
  auto IsHardwareLoopDec = [](Instruction &I) {
    if (auto *Call = dyn_cast<IntrinsicInst>(&I))
      return Call->getIntrinsicID() == Intrinsic::loop_decrement ||
          Call->getIntrinsicID() == Intrinsic::loop_decrement_reg;
    return false;
  };

  auto MaybeCall = [this](Instruction &I) {
    const CodasipTargetLowering *TLI = getTLI();
    unsigned ISD = TLI->InstructionOpcodeToISD(I.getOpcode());
    EVT VT = TLI->getValueType(DL, I.getType(), true);
    if (TLI->getOperationAction(ISD, VT) == TargetLowering::LibCall)
      return true;

    // Check if an intrinsic will be lowered to a call.
    if (auto *Call = dyn_cast<CallInst>(&I)) {
      if (isa<IntrinsicInst>(Call)) {
        if (const Function *F = Call->getCalledFunction())
          return isLoweredToCall(F);
      }
      return true;
    }
    return false;
  };

  // map the hwloop instrs already found. We don't want to disable parallel 
  // inner loops or accidentally count the instrs from inner loops.
  std::vector<Instruction *> FoundDecrements;

  std::function<unsigned(Loop *)> GetDeepestLevelOfHWLoop =
      [&](Loop *L) -> unsigned {
    unsigned LocalDepth = 0;
    bool isHWLoop = 0;
    for (const auto &Inner : L->getSubLoops()) {
      unsigned InnerDepth = GetDeepestLevelOfHWLoop(Inner);
      if (InnerDepth > LocalDepth)
        LocalDepth = InnerDepth;
    }

    for (auto *BB : L->getBlocks()) {
      for (auto &I : *BB) {
        if (IsHardwareLoopDec(I) && !is_contained(FoundDecrements, &I)) {
          FoundDecrements.push_back(&I);
          isHWLoop = true;
        }
      }
    }
    return LocalDepth + isHWLoop;
  };

  // Scan the instructions to see if there's any that we know will turn into a
  // call or if this loop is already a low-overhead loop.
  auto ScanLoop = [&](Loop *L) {
    for (auto *BB : L->getBlocks()) {
      for (auto &I : *BB) {
        if (MaybeCall(I)) {
          LLVM_DEBUG(dbgs() << "HWLoops: Bad instruction: " << I << "\n");
          return false;
        }
      }
    }
    return true;
  };

  // Visit inner loops.
  for (auto Inner : *L) {
    if (!ScanLoop(Inner)) {
        LLVM_DEBUG(dbgs() << "HWLoops: Inner loop contains an instruction "
                             "unsupported by HWLoop.\n";);
      return false;
    }
  }

  if (!ScanLoop(L)) {
    LLVM_DEBUG(dbgs() << "HWLoops: Loop contains an instruction unsupported by "
                    "HWLoop.\n";);
    return false;
  }

  FoundDecrements.clear();
  unsigned MaxDepth = GetDeepestLevelOfHWLoop(L);
  if (MaxDepth > EnableNest) {
    LLVM_DEBUG(dbgs() << "HWLoops: Nesting level exceeded.\n";);
    return false;
  }

  LLVM_DEBUG(dbgs() << "HWLoops: Loop deemed profitable for transformation by "
                       "the target.\n";);
  LLVMContext &C = L->getHeader()->getContext();
  // Updated through phi, so that it can be easily reverted to SUB 1;
  HWLoopInfo.CounterInReg = true;
  // This is now always true, as we're checking for nesting levels above and
  // if found to be deeper than enabled nesting, the check won't get here.
  HWLoopInfo.IsNestingLegal = true;
  // Our hwloop instr. does not check whether loop count is zero:
  HWLoopInfo.PerformEntryTest = false;
  HWLoopInfo.CountType = Type::getInt32Ty(C);
  HWLoopInfo.LoopDecrement = ConstantInt::get(HWLoopInfo.CountType, 1);
  return true;
}
