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
 *  \date   29. 6. 2017
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INSTRSET_SEMPARSERL_ISD_OPCODES_H_
#define INSTRSET_SEMPARSERL_ISD_OPCODES_H_

#include "llvm/CodeGen/ISDOpcodes.h"

namespace codasip {
namespace semantics {
namespace ISD {

enum NodeType {
  FIRST_NUMBER = llvm::ISD::BUILTIN_OP_END,
  // writes/reads
  REGOP_READ,
  REG_READ,
  REGOP_WRITE,
  REG_WRITE,
  IMMOP_READ,
  MEM_READ,
  MEM_WRITE,
  // operations
  CARRY_ADD,
  CARRY_ADDC,
  CARRY_SUB,
  CARRY_SUBC,
  OVERFLOW_ADD,
  OVERFLOW_ADDC,
  OVERFLOW_SUB,
  OVERFLOW_SUBC,
  FLAG_COMPARE,
  HW_LOOP,
  HAS_SIDE_EFFECTS,
  // vector shuffle
  SHUFFLE,
  // fixed-point operations
  FP_TO_FX,
  FX_TO_FP,
  INT_TO_FX,
  FX_TO_INT,
  FX_MUL,
  FX_DIV,
  // meta-operations
  PREDICATE_TRUE,
  PREDICATE_FALSE,
  // system
  GET_PC,
  JUMP,
  NOP,
  HALT,
  SYSCALL,
  SUBINSTRUCTION,
  // every instruction needs this
  RET,
  LAST_NUMBER
};

} // namespace ISD
} // namespace semantics
} // namespace codasip

#endif // INSTRSET_SEMPARSERL_ISD_OPCODES_H_
