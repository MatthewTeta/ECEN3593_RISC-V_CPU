/**
 * Codasip Ltd
 *
 * CONFIDENTIAL
 *
 * Copyright 2017 Codasip Ltd
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
 *  \date   3. 8. 2017
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_CODASIP_MISC_SELECTION_DAG_PRINTER_H_
#define INCLUDE_CODASIP_MISC_SELECTION_DAG_PRINTER_H_

#include "codasip/Semantics/isd_opcodes.h"

#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/Support/raw_ostream.h"

namespace llvm {

/**
 * \brief Auxiliary function to generate white spaces.
 * \param indent count of white spaces
 */
inline std::string getIndent(const int Indent) {
  return std::string(4 * (Indent > 0 ? Indent : 0), ' ');
}

/**
 * \brief Determines whether Value has REGOP_WRITE or REG_WRITE SDNode with zero
 * condition. \param[in] Value
 */
inline bool hasUselessRegisterWrite(const SDValue &Value) {
  const SDNode *Node = Value.getNode();
  assert(Node);

  if (Node->getOpcode() == codasip::semantics::ISD::REGOP_WRITE ||
      Node->getOpcode() == codasip::semantics::ISD::REG_WRITE) {
    const unsigned N = Node->getNumOperands();
    assert(N > 2);
    SDValue Condition = Node->getOperand(N - 1);

    // constant zero condition is not printed
    if (Condition.getOpcode() == ISD::Constant &&
        Node->getConstantOperandVal(N - 1) == 0) {
      return true;
    }
  }

  for (unsigned i = 0; i < Node->getNumOperands(); i++) {
    if (hasUselessRegisterWrite(Node->getOperand(i))) {
      return true;
    }
  }

  return false;
}

/**
 * \brief Prints value and operands recursively with given indentation.
 *        Created for automatic testing purposes now.
 * \param[out] Out
 * \param[in] Value
 * \param[in] DAG
 * \param[in] Indent
 * \param[in] IsTestingMode skips some constructs when set on true
 */
inline void printValue(raw_ostream &Out, const SDValue &Value,
                       SelectionDAG *DAG, const int Indent,
                       const bool IsTestingMode) {
  const SDNode *Node = Value.getNode();
  assert(Node);

  if (hasUselessRegisterWrite(Value)) {
    // TODO should be constants at least, better print some dummy DAG
    Out << getIndent(Indent) << "m0: ch = ret m1\n"
        << getIndent(Indent + 1) << "m1: ch = EntryToken\n";
    return;
  }

  Out << getIndent(Indent);
  Node->print(Out, DAG);
  Out << "\n";
  for (unsigned i = 0; i < Node->getNumOperands(); i++) {
    // skip only problematic constants, not all because it could hide some
    // problems
    if (IsTestingMode &&
        ((Node->getOpcode() == codasip::semantics::ISD::MEM_READ && i == 2) ||
         (Node->getOpcode() == codasip::semantics::ISD::MEM_WRITE && i == 3) ||
         (Node->getOpcode() == codasip::semantics::ISD::REG_WRITE && i == 1))) {
      continue;
    }

    printValue(Out, Node->getOperand(i), DAG, Indent + 1, IsTestingMode);
  }
}

} // namespace llvm

#endif // INCLUDE_CODASIP_MISC_SELECTION_DAG_PRINTER_H_
