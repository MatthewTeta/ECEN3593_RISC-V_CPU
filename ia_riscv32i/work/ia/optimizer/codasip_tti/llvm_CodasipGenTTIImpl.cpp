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
#include "llvm_CodasipGenTTIImpl.h"

namespace llvm {

/**
 *  \brief  getST
 */
const TargetSubtargetInfo* CodasipGenTTIImpl::getST() const 
{
    return ST;
}
/**
 *  \brief  getTLI
 */
const TargetLoweringBase* CodasipGenTTIImpl::getTLI() const 
{
    return TLI;
}
CodasipGenTTIImpl::CodasipGenTTIImpl(const TargetMachine *TM, const Function &F)
 :  BaseT(TM, TM->getDataLayout())
{
    ST = TM->getSubtargetImpl(F);
    TLI = ST->getTargetLowering();

}
unsigned CodasipGenTTIImpl::getNumberOfRegisters(bool Vector)
{
    return Vector ? 0 : 31;
}
unsigned CodasipGenTTIImpl::getRegisterBitWidth(bool Vector) const 
{
    return Vector ? 0 : 32;
}
unsigned CodasipGenTTIImpl::getArithmeticInstrCost(unsigned Opcode, Type * Ty, TargetTransformInfo::OperandValueKind Opd1Info, TargetTransformInfo::OperandValueKind Opd2Info, TargetTransformInfo::OperandValueProperties Opd1PropInfo, TargetTransformInfo::OperandValueProperties Opd2PropInfo, ArrayRef<const Value *> Args)
{
    std::pair<int, MVT> LT = TLI->getTypeLegalizationCost(DL, Ty);
    int ISD = TLI->InstructionOpcodeToISD(Opcode);

    static const CostTblEntry CostTable[] = {
        { ISD::ADD, MVT::i32, 1 },
        { ISD::ADD, MVT::i16, 1 },
        { ISD::ADD, MVT::i8, 1 },
        { ISD::ADD, MVT::i1, 1 },
        { ISD::SUB, MVT::i32, 1 },
        { ISD::SUB, MVT::i16, 1 },
        { ISD::SUB, MVT::i8, 1 },
        { ISD::SUB, MVT::i1, 1 },
        { ISD::AND, MVT::i32, 1 },
        { ISD::AND, MVT::i16, 1 },
        { ISD::AND, MVT::i8, 1 },
        { ISD::AND, MVT::i1, 1 },
        { ISD::OR, MVT::i32, 1 },
        { ISD::OR, MVT::i16, 1 },
        { ISD::OR, MVT::i8, 1 },
        { ISD::OR, MVT::i1, 1 },
        { ISD::XOR, MVT::i32, 1 },
        { ISD::XOR, MVT::i16, 1 },
        { ISD::XOR, MVT::i8, 1 },
        { ISD::XOR, MVT::i1, 1 },
        { ISD::SHL, MVT::i32, 1 },
        { ISD::SHL, MVT::i16, 1 },
        { ISD::SHL, MVT::i8, 1 },
        { ISD::SHL, MVT::i1, 1 },
        { ISD::SRA, MVT::i32, 1 },
        { ISD::SRA, MVT::i16, 1 },
        { ISD::SRA, MVT::i8, 1 },
        { ISD::SRA, MVT::i1, 1 },
        { ISD::SRL, MVT::i32, 1 },
        { ISD::SRL, MVT::i16, 1 },
        { ISD::SRL, MVT::i8, 1 },
        { ISD::SRL, MVT::i1, 1 },
    };

    if (const auto *Entry = CostTableLookup(CostTable, ISD, LT.second))
        return LT.first * Entry->Cost;

    return BaseT::getArithmeticInstrCost(Opcode, Ty, Opd1Info, Opd2Info, Opd1PropInfo, Opd2PropInfo, Args);
}
unsigned CodasipGenTTIImpl::getMemoryOpCost(unsigned Opcode, Type * Src, unsigned Alignment, unsigned AddressSpace, const Instruction * I)
{
    std::pair<int, MVT> LT = TLI->getTypeLegalizationCost(DL, Src);
    int ISD = TLI->InstructionOpcodeToISD(Opcode);

    // Make vector reads/writes with unsupported alignment extremely expensive.
    if (Src->isVectorTy() && Alignment % DL.getABITypeAlignment(Src) != 0)
        return LT.first * 1000 * Src->getVectorNumElements();

    return BaseT::getMemoryOpCost(Opcode, Src, Alignment, AddressSpace, I);
}
unsigned CodasipGenTTIImpl::getCmpSelInstrCost(unsigned Opcode, Type * ValTy, Type * CondTy, const Instruction * I)
{
    std::pair<int, MVT> LT = TLI->getTypeLegalizationCost(DL, ValTy);
    int ISD = TLI->InstructionOpcodeToISD(Opcode);

    static const CostTblEntry CostTable[] = {
        { ISD::SETCC, MVT::i32, 1 },
        { ISD::SETCC, MVT::i16, 1 },
        { ISD::SETCC, MVT::i8, 1 },
        { ISD::SETCC, MVT::i1, 1 },
        { ISD::SELECT, MVT::i32, 1 },
        { ISD::SELECT, MVT::i16, 1 },
        { ISD::SELECT, MVT::i8, 1 },
        { ISD::SELECT, MVT::i1, 1 },
    };

    if (const auto *Entry = CostTableLookup(CostTable, ISD, LT.second))
        return LT.first * Entry->Cost;

    return BaseT::getCmpSelInstrCost(Opcode, ValTy, CondTy, I);
}
unsigned CodasipGenTTIImpl::getOperationCost(unsigned Opcode, Type * Ty, Type * OpTy)
{
    // llvm::EVT::getEVT() cannot be used on vector of pointers
    if (Ty->isPtrOrPtrVectorTy() && Ty->isVectorTy())
        return BaseT::getOperationCost(Opcode, Ty, OpTy);

    if (llvm::EVT::getEVT(Ty, /*HandleUnknown=*/true) == llvm::MVT::Other)
        return BaseT::getOperationCost(Opcode, Ty, OpTy);

    if (Opcode == Instruction::Br)
        return 1;

    std::pair<int, MVT> LT = TLI->getTypeLegalizationCost(DL, Ty);
    int ISD = TLI->InstructionOpcodeToISD(Opcode);

    static const CostTblEntry CostTable[] = {
        { ISD::ADD, MVT::i32, 1 },
        { ISD::ADD, MVT::i16, 1 },
        { ISD::ADD, MVT::i8, 1 },
        { ISD::ADD, MVT::i1, 1 },
        { ISD::SUB, MVT::i32, 1 },
        { ISD::SUB, MVT::i16, 1 },
        { ISD::SUB, MVT::i8, 1 },
        { ISD::SUB, MVT::i1, 1 },
        { ISD::AND, MVT::i32, 1 },
        { ISD::AND, MVT::i16, 1 },
        { ISD::AND, MVT::i8, 1 },
        { ISD::AND, MVT::i1, 1 },
        { ISD::OR, MVT::i32, 1 },
        { ISD::OR, MVT::i16, 1 },
        { ISD::OR, MVT::i8, 1 },
        { ISD::OR, MVT::i1, 1 },
        { ISD::XOR, MVT::i32, 1 },
        { ISD::XOR, MVT::i16, 1 },
        { ISD::XOR, MVT::i8, 1 },
        { ISD::XOR, MVT::i1, 1 },
        { ISD::SHL, MVT::i32, 1 },
        { ISD::SHL, MVT::i16, 1 },
        { ISD::SHL, MVT::i8, 1 },
        { ISD::SHL, MVT::i1, 1 },
        { ISD::SRA, MVT::i32, 1 },
        { ISD::SRA, MVT::i16, 1 },
        { ISD::SRA, MVT::i8, 1 },
        { ISD::SRA, MVT::i1, 1 },
        { ISD::SRL, MVT::i32, 1 },
        { ISD::SRL, MVT::i16, 1 },
        { ISD::SRL, MVT::i8, 1 },
        { ISD::SRL, MVT::i1, 1 },
        { ISD::SETCC, MVT::i32, 1 },
        { ISD::SETCC, MVT::i16, 1 },
        { ISD::SETCC, MVT::i8, 1 },
        { ISD::SETCC, MVT::i1, 1 },
        { ISD::SELECT, MVT::i32, 1 },
        { ISD::SELECT, MVT::i16, 1 },
        { ISD::SELECT, MVT::i8, 1 },
        { ISD::SELECT, MVT::i1, 1 },
        { ISD::TRUNCATE, MVT::i32, 0 },
        { ISD::TRUNCATE, MVT::i16, 0 },
        { ISD::TRUNCATE, MVT::i8, 0 },
        { ISD::TRUNCATE, MVT::i1, 0 },
    };

    if (const auto *Entry = CostTableLookup(CostTable, ISD, LT.second))
        return LT.first * Entry->Cost;

    return BaseT::getOperationCost(Opcode, Ty, OpTy);
}
unsigned CodasipGenTTIImpl::getCastInstrCost(unsigned Opcode, Type * Dst, Type * Src, const Instruction * I)
{
    return BaseT::getCastInstrCost(Opcode, Dst, Src, I);
}
bool CodasipGenTTIImpl::areInlineCompatible(const Function * Caller, const Function * Callee) const 
{
    const TargetMachine &TM = getTLI()->getTargetMachine();
    const FeatureBitset &CallerBits = TM.getSubtargetImpl(*Caller)->getFeatureBits();
    const FeatureBitset &CalleeBits = TM.getSubtargetImpl(*Callee)->getFeatureBits();
    return (CallerBits & CalleeBits) == CalleeBits;
}
unsigned CodasipGenTTIImpl::getInliningThresholdMultiplier()
{
    return BaseT::getInliningThresholdMultiplier();
}
unsigned CodasipGenTTIImpl::getVectorInstrCost(unsigned Opcode, Type * Val, unsigned Index)
{
    return BaseT::getVectorInstrCost(Opcode, Val, Index);
}
unsigned CodasipGenTTIImpl::getShuffleCost(TargetTransformInfo::ShuffleKind Kind, Type * Tp, int Index, Type * SubTp)
{
    return BaseT::getShuffleCost(Kind, Tp, Index, SubTp);
}
bool CodasipGenTTIImpl::enableInterleavedAccessVectorization()
{
    return BaseT::enableInterleavedAccessVectorization();
}
unsigned CodasipGenTTIImpl::getMaxInterleaveFactor(unsigned VF)
{
    return BaseT::getMaxInterleaveFactor(VF);
}
bool CodasipGenTTIImpl::hasDivRemOp(Type * DataType, bool IsSigned)
{
    return false;
}
} // namespace llvm
