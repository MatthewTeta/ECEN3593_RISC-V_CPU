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
 * \author  Codasip (c) source generator
 * \version 9.1.1-1255
 */
#ifndef LLVM_CODASIPGENTTIIMPL_0_H_
#define LLVM_CODASIPGENTTIIMPL_0_H_

#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/CodeGen/CostTable.h"
#include "llvm/IR/Function.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

/**
 *  \class  CodasipGenTTIImpl
 */
class CodasipGenTTIImpl : public BasicTTIImplBase<CodasipGenTTIImpl>
 {
protected:
    typedef BasicTTIImplBase<CodasipGenTTIImpl> BaseT;
    friend BaseT;
    const TargetSubtargetInfo* ST;
    const TargetLowering* TLI;
private:
    const TargetSubtargetInfo* getST() const ;
    const TargetLoweringBase* getTLI() const ;
public:
    /**
     *  \brief  CodasipGenTTIImpl
     */
    CodasipGenTTIImpl(const TargetMachine *TM, const Function &F);
    /**
     *  \brief  getNumberOfRegisters
     */
    unsigned getNumberOfRegisters(bool Vector);
    /**
     *  \brief  getRegisterBitWidth
     */
    unsigned getRegisterBitWidth(bool Vector) const ;
    /**
     *  \brief  getArithmeticInstrCost
     */
    unsigned getArithmeticInstrCost(unsigned Opcode, Type * Ty, TargetTransformInfo::OperandValueKind Opd1Info = TargetTransformInfo::OK_AnyValue, TargetTransformInfo::OperandValueKind Opd2Info = TargetTransformInfo::OK_AnyValue, TargetTransformInfo::OperandValueProperties Opd1PropInfo = TargetTransformInfo::OP_None, TargetTransformInfo::OperandValueProperties Opd2PropInfo = TargetTransformInfo::OP_None, ArrayRef<const Value *> Args = ArrayRef<const Value *>());
    /**
     *  \brief  getMemoryOpCost
     */
    unsigned getMemoryOpCost(unsigned Opcode, Type * Src, unsigned Alignment, unsigned AddressSpace, const Instruction * I = nullptr);
    /**
     *  \brief  getCmpSelInstrCost
     */
    unsigned getCmpSelInstrCost(unsigned Opcode, Type * ValTy, Type * CondTy, const Instruction * I);
    /**
     *  \brief  getOperationCost
     */
    unsigned getOperationCost(unsigned Opcode, Type * Ty, Type * OpTy);
    /**
     *  \brief  getCastInstrCost
     */
    unsigned getCastInstrCost(unsigned Opcode, Type * Dst, Type * Src, const Instruction * I = nullptr);
    /**
     *  \brief  areInlineCompatible
     */
    bool areInlineCompatible(const Function * Caller, const Function * Callee) const ;
    /**
     *  \brief  getInliningThresholdMultiplier
     */
    unsigned getInliningThresholdMultiplier();
    /**
     *  \brief  getVectorInstrCost
     */
    unsigned getVectorInstrCost(unsigned Opcode, Type * Val, unsigned Index);
    /**
     *  \brief  getShuffleCost
     */
    unsigned getShuffleCost(TargetTransformInfo::ShuffleKind Kind, Type * Tp, int Index, Type * SubTp);
    /**
     *  \brief  enableInterleavedAccessVectorization
     */
    bool enableInterleavedAccessVectorization();
    /**
     *  \brief  getMaxInterleaveFactor
     */
    unsigned getMaxInterleaveFactor(unsigned VF);
    /**
     *  \brief  hasDivRemOp
     */
    bool hasDivRemOp(Type * DataType, bool IsSigned);
};
} // namespace llvm

#endif // LLVM_CODASIPGENTTIIMPL_0_H_
