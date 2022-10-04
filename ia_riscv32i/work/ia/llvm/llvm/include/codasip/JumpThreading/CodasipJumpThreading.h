/**
 * Codasip Ltd
 *
 * CONFIDENTIAL
 *
 * Copyright 2018 Codasip Ltd
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the
 * property of Codasip Ltd and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and
 * proprietary to Codasip Ltd and are protected by trade secret and copyright
 * law.  In addition, elements of the technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this file, may be use, copied, modified, or distributed
 * except in accordance with the terms contained in Codasip license agreement
 * under which you obtained this file.
 *
 *  \file
 *  \author Martin Ministr
 *  \date   7. 9. 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_CODASIP_JUMPTHREADING_CODASIPJUMPTHREADING_H_
#define INCLUDE_CODASIP_JUMPTHREADING_CODASIPJUMPTHREADING_H_

#include <memory>
#include <utility>

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/BlockFrequencyInfo.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/IR/ValueHandle.h"

namespace llvm {

class BasicBlock;
class BinaryOperator;
class BranchInst;
class CmpInst;
class Constant;
class Function;
class Instruction;
class IntrinsicInst;
class LazyValueInfo;
class LoadInst;
class PHINode;
class TargetLibraryInfo;
class Value;

/// This pass performs 'jump threading', which looks at blocks that have
/// multiple predecessors and multiple successors.  If one or more of the
/// predecessors of the block can be proven to always jump to one of the
/// successors, we forward the edge from the predecessor to the successor by
/// duplicating the contents of this block.
///
/// An example of when this can occur is code like this:
///
///   if () { ...
///     X = 4;
///   }
///   if (X < 3) {
///
/// In this case, the unconditional branch at the end of the first if can be
/// revectored to the false side of the second if.
class CodasipJumpThreadingPass
    : public PassInfoMixin<CodasipJumpThreadingPass> {
  TargetLibraryInfo *TLI;
  LazyValueInfo *LVI;

public:
  CodasipJumpThreadingPass();
};

} // end namespace llvm

#endif // INCLUDE_CODASIP_JUMPTHREADING_CODASIPJUMPTHREADING_H_
