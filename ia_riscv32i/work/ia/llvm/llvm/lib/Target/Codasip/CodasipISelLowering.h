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


// you can edit this file

#ifndef CODASIPISELLOWERING_H
#define CODASIPISELLOWERING_H

#include "CodasipGenISelLowering.h"

namespace llvm {

/// use this class to reimplement the generated lowerer
class CodasipTargetLowering: public CodasipGenTargetLowering
{
public:
  explicit CodasipTargetLowering(CodasipTargetMachine &TM);
  /// Handles instructions with "usesCustomInserter" flag.
  MachineBasicBlock* EmitInstrWithCustomInserter(MachineInstr &MI, MachineBasicBlock *BB) const override;
  /// Custom lowering
  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;
  // various meta-info
  EVT getSetCCResultType(const DataLayout &DL, LLVMContext &Context, EVT VT) const override;
  MVT::SimpleValueType getCmpLibcallReturnType() const override;
  bool isShuffleMaskLegal(ArrayRef<int> m, EVT t) const override;
  bool isOffsetFoldingLegal(const GlobalAddressSDNode* GA) const override;
  /** Performs finer grained checking of indexed load/store availability.
   * \param N  The load/store.
   * \param AM Intended indexing mode.
   * \param Offset  Shift operand.
   * \return True, if operation should be lowered. */
  bool CheckIndexedOffsetLegal(LSBaseSDNode* N, const ISD::MemIndexedMode AM, const SDValue& Offset, MachineFunction &MF) const override;
  MVT getScalarShiftAmountTy(const DataLayout &DL, EVT t) const override;
};

}

#endif
