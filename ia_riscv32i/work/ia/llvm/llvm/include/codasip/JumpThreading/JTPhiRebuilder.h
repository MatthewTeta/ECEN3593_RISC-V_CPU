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
 *  \date   4. 10. 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_CODASIP_JUMPTHREADING_JTPHIREBUILDER_H_
#define INCLUDE_CODASIP_JUMPTHREADING_JTPHIREBUILDER_H_

#include <map>
#include <set>

#include "llvm/Transforms/Utils/ValueMapper.h"

#include "Ir/JTGraph.h"

namespace llvm {

// Forward declaration.
class Instruction;
class Value;

namespace jumpthreading {

// Forward declaration.
class JTBuilder;

/**
 *  \brief  This class computes dominating definitions to fix old PHI nodes
 *          and creates new ones when needed.
 */
class JTPhiRebuilder {
public:
  /**
   *  \brief  Rebuilds PHI nodes and creates new ones when needed.
   *  \param[in, out] Blocks Reachable blocks, only them could be processed
   *  \param[in, out] G Graph
   *  \param[in, out] Builder JT IR Builder
   *  \param[in]  Duplicate2Original Mapping from duplicate to original
   * instruction
   */
  static void run(JTGraph::JTBlocks &Blocks, JTGraph &G, JTBuilder &Builder,
                  ValueToValueMapTy &Duplicate2Original);

private:
  /// Dominating def cache
  typedef std::map<JTBlock *, Value *> DDCache;
  /// Node -> Dominating def cache
  typedef std::map<Value *, DDCache *> DominatingDefs;
  /// Set to determine whether LLVM Value was visited already
  typedef std::set<Value *> VisitedValues;

  JTPhiRebuilder(JTGraph &G, JTBuilder &Builder,
                 ValueToValueMapTy &Duplicate2Original);

  ~JTPhiRebuilder();

  void operator()(JTGraph::JTBlocks &Blocks);
  void rebuildInstruction(Instruction &I, const size_t Indent);
  static size_t getPositionFromBack(Instruction &I);
  Value *getDominatingDefinition(Instruction &I, const size_t StartPositionBack,
                                 JTBlock *Block, DDCache *DominatingDefCache,
                                 const size_t Indent);
  Instruction &getOriginal(Instruction &I);
  DDCache *getDDCache(Value &V);
  Value *getCachedDominatingDefinition(JTBlock &Block, DDCache &Cache);
  bool isVisitedElseMark(Value &V);

  /// Processed graph
  JTGraph &G;
  /// JT IR Builder
  JTBuilder &Builder;
  /// Initialized by createDuplicateMap
  ValueToValueMapTy &Duplicate2Original;
  /// Dominating definition caches
  DominatingDefs DDCaches;
  /// Determines whether LLVM Value is visited by PhiRebuilder
  VisitedValues Visited;
};

} // namespace jumpthreading
} // namespace llvm

#endif // INCLUDE_CODASIP_JUMPTHREADING_JTPHIREBUILDER_H_
