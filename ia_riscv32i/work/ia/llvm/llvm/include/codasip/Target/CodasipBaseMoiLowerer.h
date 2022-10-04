/**
 * Codasip Ltd
 *
 * Copyright 2016 Codasip Ltd
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this file, may be use, copied, modified, or distributed
 * except in accordance with the terms contained in Codasip license agreement
 * under which you obtained this file.
 *
 * \file    CodasipBaseMoiLowerer.h
 * \date    26. 1. 2016
 * \author  Stanislav Melo
 * \version 5.5.0.
 * \brief   Base class for MoiLowerer
 */

#ifndef INCLUDE_CODASIP_TARGET_CODASIPBASEMOILOWERER_H_
#define INCLUDE_CODASIP_TARGET_CODASIPBASEMOILOWERER_H_

#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include <list>
#include <map>
#include <vector>

namespace llvm {

/// A map of opcodes and their count in pattern
typedef std::map<unsigned, unsigned> OpcodeCountMap;
/// A list of nodes
typedef std::list<SDNode *> NodeList;
/// A map of opcodes and found possible root nodes in CurDAG
typedef std::map<unsigned, NodeList> RootMap;
/// A list of nodelists
typedef std::list<NodeList> Node2List;
/// A map of opcodes and all possible mappings of corresponding model roots
typedef std::map<unsigned, Node2List> Mappingmap;
/// Group -> "has all operands covered by regs"
typedef std::pair<int, bool> GroupInfo;
// typedef std::map<SDNode*, SDNode*> Map2Node;
typedef std::map<SDValue, SDValue> Map2Val;
typedef std::vector<SDValue> ValueVec;

// structure that holds info about immediate operand
struct ImmInfo {
  int width;
  bool sign;
  int trunc;
};

/// Represents a multi-root pattern.
class BaseDagPattern {
protected:
  bool m_rootIsOp;
  const MCInstrDesc &m_insDesc;
  const TargetRegisterInfo *m_RegInfo;
  /// map of pattern roots opcodes of and their count
  OpcodeCountMap m_RootOpcodes;
  /// successfuly matched DAG roots that will be replaced
  NodeList m_FoundRoots;
  /// Opcode of a resulting instruction, if successfully matched.
  unsigned icode;
  /// Selection dag representing the semantics
  SelectionDAG *Pattern;
  // roots of pattern
  ValueVec m_PatternRoots;
  // must all operands be registers?
  bool allOpRegs;
  // map of pattern nodes matched to real nodes
  Map2Val m_globalPattToReal;
  // map of real nodes matched to pattern nodes
  Map2Val m_globalRealToPatt;
  /// Encountered operands.
  ValueVec m_FoundOperands;

private:
  bool IsInOutIn(SDNode *Nu);
  // check if nodes of trees, that overlap in pattern, overlap in real dag
  bool CheckRequiredDuplicities(Map2Val &patToReal);
  // check that nodes of trees, that don't overlap in pattern, don't overlap in
  // real dag
  bool CheckBadDuplicities(Map2Val patToReal);
  // update m_globalPattToReal and m_globalRealToPatt maps according to found
  // nodes
  void AddFoundNodes(Map2Val patToReal);
  // add new found operands to m_FoundOperands
  void AddOperands(ValueVec operands);
  // check if operands of found pattern satisfy conditions for operands of moi
  bool CheckOperands();
  /// clears data in pattern so pattern can be reused
  void ReusePattern();
  /// Gets a map of "bijections" from the DAG.
  /// Actually, it's a bijection minus R-totalness.
  /// For each opcode - generates possible combinations of nodes that may be
  /// roots
  Mappingmap GetMappings(SelectionDAG *DAG);
  /// checks if node is matched
  bool IsMatched(SDNode *N);
  /// checks if matched nodes generate convex set
  bool FoundIllegalDataMemDep();
  /// checks if node has any uses outside of matched nodes (it is root)
  bool IsRoot(SDNode *root);
  /// check if node is operand of new matched instruction
  bool IsOperand(SDNode *N);
  /// check if node is used outside of already matched pattern
  /// operands of pattern are considered to be outside of pattern
  bool IsUsedOutside(SDNode *root);
  /// returns vector of return types of new node
  void GetReturnType(std::vector<EVT> &returnVec);
  /// reshuffle return values accordingly
  void SortReturnNodes();
  /// replaces all uses of matched nodes with new node
  void PlaceNewValue(SDValue newVal, SelectionDAG *DAG);
  /// function for replacing matched nodes with one new node
  void ReplaceNN(SelectionDAG *DAG);
  // return true if node is operand of root
  bool IsOperandOfRoot(SDNode *N);
  // change operands of commutative root to see if it matches pattern then
  bool TryCommutativityWrapper(Map2Val &patToReal, ValueVec &operands,
                               SelectionDAG *DAG);
  // check if node can be found multiple times as operand of a pattern
  bool isUsedMultipleTimesInPatt(SDNode *pattOp);
  // check if const operands of pattern satisfy conditions for imm operands of
  // moi
  bool CheckImmProperties(SDValue operand, int opIndex);
  // check if register operands of pattern satisfy conditions for register
  // operands of moi
  bool CheckRegProperties(SDValue operand, int opIndex);
  bool TryComutativity(Map2Val &patToReal, bool isInStruct, SDValue patParent,
                       SDValue patFixOp, ValueVec &operands);
  bool HasType(const TargetRegisterClass *TRC, MVT nodeType) const;
  bool IsOnlyMemOp(SDNode *root);

public:
  // remove unnecessary nodes from roots of pattern
  static void GetRoots(ValueVec &roots);
  // match part of pattern that starts from one root
  static bool CheckTree(SDValue rootPatt, SDValue rootReal, Map2Val &patToReal,
                        ValueVec &operands);
  // match part of pattern that starts from one root
  static bool CheckTree(SDValue rootPatt, SDValue rootReal) {
    Map2Val a = Map2Val();
    ValueVec b = ValueVec();
    return CheckTree(rootPatt, rootReal, a, b);
  }
  bool FindMatch(NodeList nodelist, unsigned opcode, SelectionDAG *DAG);
  /// program continued to next group, push all group element on stack
  void PushAllVariationsOfGroupOnStack(Node2List &stack, Node2List *group);
  /// program backtracked one level, it updates structures of matched nodes
  /// accordingly
  void UpdateMatchedNodes(std::vector<ValueVec> &operandsStack,
                          std::vector<Map2Val> &nodesRTPStack,
                          std::vector<Map2Val> &nodesPTRStack,
                          Node2List &rootsStack);
  /// Try to find a match.
  bool BaseTryMatch(SelectionDAG *DAG);
  /// fill rootOpcodes map for use in TryMatch and GetMappings
  void PrepareMeta();
  BaseDagPattern(SelectionDAG *DAG, int *pattInfo, const TargetMachine &TM,
                 ValueVec &roots);

  virtual ~BaseDagPattern() {
    m_RootOpcodes.clear();
    m_FoundRoots.clear();
    m_PatternRoots.clear();
    m_globalPattToReal.clear();
    m_globalRealToPatt.clear();
    m_FoundOperands.clear();
  }
  // get various info from specific target
  virtual bool CheckImmWidth(int64_t val, int width, bool sign, int trunc) {
    return false;
  }
  virtual const TargetRegisterClass *GetRegClass(int rc) { return nullptr; }
  virtual ImmInfo GetImmInfo(unsigned opcode, unsigned opNum) {
    ImmInfo a = {0, false, 0};
    return a;
  }
};

} // namespace llvm

#endif /* INCLUDE_CODASIP_TARGET_CODASIPBASEMOILOWERER_H_ */
