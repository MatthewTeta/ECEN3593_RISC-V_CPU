/**
 * Codasip Ltd
 *
 * CONFIDENTIAL
 *
 * Copyright 2016 Codasip Ltd
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
 *  \author jan
 *  \date   27 Apr 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef CODASIPBASELOWERING_H_
#define CODASIPBASELOWERING_H_

#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLowering.h"

#include <utility>

namespace llvm {

struct CodasipBaseTargetLowering : public TargetLowering {
  // just relay the TM
  CodasipBaseTargetLowering(TargetMachine &TM) : TargetLowering(TM) {}
  /// For multi-stack architectures
  virtual unsigned GetSpace4Vt(EVT vt) const = 0;
  /// Hook for custom array access.
  virtual bool EmittArrayAccess(SelectionDAG &DAG, const User &I,
                                Type *indexedType, const Value *Idx,
                                SDValue IdxN, SDValue &N,
                                const SDLoc &dl) const = 0;
  // Hooks for handling of unaligned load&store
  virtual std::pair<SDValue, SDValue>
  ExpandCustomUnalignedLoad(LoadSDNode *LD, SelectionDAG &DAG) const = 0;
  virtual SDValue ExpandCustomUnalignedStore(StoreSDNode *ST,
                                             SelectionDAG &DAG) const = 0;
  /** Creates MOI/intrinsic node with the given opcode.
   * \return The new value. */
  virtual SDValue GetCodasipMemSDNode(SelectionDAG &DAG, int Opcode,
                                      SDVTList VTs, ArrayRef<SDValue> Ops,
                                      const SDLoc &dl, EVT MemVT,
                                      MachineMemOperand *MMO) const = 0;
};

} // namespace llvm

#endif // CODASIPBASELOWERING_H_
