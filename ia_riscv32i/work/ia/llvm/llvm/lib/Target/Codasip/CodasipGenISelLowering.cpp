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


#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/CodeGen/PseudoSourceValue.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/Analysis/MemorySSA.h"
#include "codasip/Target/CodasipBaseMoiLowerer.h"

#include "Codasip.h"
#include "CodasipGenISelLowering.h"
#include "CodasipMachineFunction.h"
#include "CodasipTargetMachine.h"
#include "CodasipTargetObjectFile.h"
#include "CodasipGenRegisterInfo.h"
#include "CodasipInstructionSemantics.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace llvm;

#include "CodasipGenCallingConv.inc"

// init legalities
CodasipGenTargetLowering::CodasipGenTargetLowering(CodasipTargetMachine &TM)
: CodasipBaseTargetLowering(TM)
{
  const CodasipSubtarget& CST = *TM.getSubtargetImpl();
  // custom libcalls
  setLibcallName(RTLIB::FPTOSINT_F16_I32, "__fixhfsi");
  setLibcallName(RTLIB::FPTOSINT_F16_I64, "__fixhfdi");
  setLibcallName(RTLIB::FPTOUINT_F16_I32, "__fixhfui");
  setLibcallName(RTLIB::FPTOUINT_F16_I64, "__fixhfdu");
  setLibcallName(RTLIB::SINTTOFP_I32_F16, "__floatsihf");
  setLibcallName(RTLIB::SINTTOFP_I64_F16, "__floatdihf");
  setLibcallName(RTLIB::UINTTOFP_I64_F16, "__floatduhf");
  // set these to expand by default (would be legal otherwise)
  static_assert(sizeof(LegalizeAction)==1,"");
  memset(LoadExtActions, ((Expand<<4)|Expand), sizeof(LoadExtActions));
  memset(TruncStoreActions, Expand, sizeof(TruncStoreActions));
  // set legal actions
  addRegisterClass(MVT::i32, &Codasip::xpr_generalRegClass);

  setOperationAction(ISD::Constant, MVT::i32, Legal);
  setOperationAction(ISD::ADD, MVT::i32, Legal);
  setOperationAction(ISD::SUB, MVT::i32, Legal);
  setOperationAction(ISD::MUL, MVT::i32, Expand);
  setOperationAction(ISD::SDIV, MVT::i32, Expand);
  setOperationAction(ISD::UDIV, MVT::i32, Expand);
  setOperationAction(ISD::SREM, MVT::i32, Expand);
  setOperationAction(ISD::UREM, MVT::i32, Expand);
  setOperationAction(ISD::SMUL_LOHI, MVT::i32, Expand);
  setOperationAction(ISD::UMUL_LOHI, MVT::i32, Expand);
  setOperationAction(ISD::SDIVREM, MVT::i32, Expand);
  setOperationAction(ISD::UDIVREM, MVT::i32, Expand);
  setOperationAction(ISD::ADDC, MVT::i32, Expand);
  setOperationAction(ISD::SUBC, MVT::i32, Expand);
  setOperationAction(ISD::ADDE, MVT::i32, Expand);
  setOperationAction(ISD::SUBE, MVT::i32, Expand);
  setOperationAction(ISD::SADDO, MVT::i32, Expand);
  setOperationAction(ISD::UADDO, MVT::i32, Expand);
  setOperationAction(ISD::SSUBO, MVT::i32, Expand);
  setOperationAction(ISD::USUBO, MVT::i32, Expand);
  setOperationAction(ISD::SMULO, MVT::i32, Expand);
  setOperationAction(ISD::UMULO, MVT::i32, Expand);
  setOperationAction(ISD::SADDSAT, MVT::i32, Expand);
  setOperationAction(ISD::UADDSAT, MVT::i32, Expand);
  setOperationAction(ISD::SSUBSAT, MVT::i32, Expand);
  setOperationAction(ISD::USUBSAT, MVT::i32, Expand);
  setOperationAction(ISD::SMULFIX, MVT::i32, Expand);
  setOperationAction(ISD::UMULFIX, MVT::i32, Expand);
  setOperationAction(ISD::SMULFIXSAT, MVT::i32, Expand);
  setOperationAction(ISD::FADD, MVT::i32, Expand);
  setOperationAction(ISD::FSUB, MVT::i32, Expand);
  setOperationAction(ISD::FMUL, MVT::i32, Expand);
  setOperationAction(ISD::FDIV, MVT::i32, Expand);
  setOperationAction(ISD::FREM, MVT::i32, Expand);
  setOperationAction(ISD::FMA, MVT::i32, Expand);
  setOperationAction(ISD::INSERT_VECTOR_ELT, MVT::i32, Expand);
  setOperationAction(ISD::EXTRACT_VECTOR_ELT, MVT::i32, Expand);
  setOperationAction(ISD::INSERT_SUBVECTOR, MVT::i32, Expand);
  setOperationAction(ISD::EXTRACT_SUBVECTOR, MVT::i32, Expand);
  setOperationAction(ISD::VECTOR_SHUFFLE, MVT::i32, Expand);
  setOperationAction(ISD::MULHU, MVT::i32, Expand);
  setOperationAction(ISD::MULHS, MVT::i32, Expand);
  setOperationAction(ISD::AND, MVT::i32, Legal);
  setOperationAction(ISD::OR, MVT::i32, Legal);
  setOperationAction(ISD::XOR, MVT::i32, Legal);
  setOperationAction(ISD::SHL, MVT::i32, Legal);
  setOperationAction(ISD::SRA, MVT::i32, Legal);
  setOperationAction(ISD::SRL, MVT::i32, Legal);
  setOperationAction(ISD::ROTL, MVT::i32, Expand);
  setOperationAction(ISD::ROTR, MVT::i32, Expand);
  setOperationAction(ISD::FSHL, MVT::i32, Expand);
  setOperationAction(ISD::FSHR, MVT::i32, Expand);
  setOperationAction(ISD::BSWAP, MVT::i32, Expand);
  setOperationAction(ISD::CTTZ, MVT::i32, Expand);
  setOperationAction(ISD::CTLZ, MVT::i32, Expand);
  setOperationAction(ISD::CTPOP, MVT::i32, Expand);
  setOperationAction(ISD::BITREVERSE, MVT::i32, Expand);
  setOperationAction(ISD::VSELECT, MVT::i32, Expand);
  setOperationAction(ISD::SIGN_EXTEND, MVT::i32, Expand);
  setOperationAction(ISD::ZERO_EXTEND, MVT::i32, Expand);
  setOperationAction(ISD::ANY_EXTEND, MVT::i32, Expand);
  setOperationAction(ISD::TRUNCATE, MVT::i32, Expand);
  setOperationAction(ISD::SINT_TO_FP, MVT::i32, Expand);
  setOperationAction(ISD::UINT_TO_FP, MVT::i32, Expand);
  setOperationAction(ISD::FP_TO_SINT, MVT::i32, Expand);
  setOperationAction(ISD::FP_TO_UINT, MVT::i32, Expand);
  setOperationAction(ISD::FP_ROUND, MVT::i32, Expand);
  setOperationAction(ISD::FLT_ROUNDS_, MVT::i32, Expand);
  setOperationAction(ISD::FP_ROUND_INREG, MVT::i32, Expand);
  setOperationAction(ISD::FP_EXTEND, MVT::i32, Expand);
  setOperationAction(ISD::BITCAST, MVT::i32, Expand);
  setOperationAction(ISD::FP16_TO_FP, MVT::i32, Expand);
  setOperationAction(ISD::FP_TO_FP16, MVT::i32, Expand);
  setOperationAction(ISD::FNEG, MVT::i32, Expand);
  setOperationAction(ISD::FABS, MVT::i32, Expand);
  setOperationAction(ISD::FSQRT, MVT::i32, Expand);
  setOperationAction(ISD::FCBRT, MVT::i32, Expand);
  setOperationAction(ISD::FSIN, MVT::i32, Expand);
  setOperationAction(ISD::FCOS, MVT::i32, Expand);
  setOperationAction(ISD::FPOWI, MVT::i32, Expand);
  setOperationAction(ISD::FPOW, MVT::i32, Expand);
  setOperationAction(ISD::FLOG, MVT::i32, Expand);
  setOperationAction(ISD::FLOG2, MVT::i32, Expand);
  setOperationAction(ISD::FLOG10, MVT::i32, Expand);
  setOperationAction(ISD::FEXP, MVT::i32, Expand);
  setOperationAction(ISD::FEXP2, MVT::i32, Expand);
  setOperationAction(ISD::FCEIL, MVT::i32, Expand);
  setOperationAction(ISD::FTRUNC, MVT::i32, Expand);
  setOperationAction(ISD::FRINT, MVT::i32, Expand);
  setOperationAction(ISD::FNEARBYINT, MVT::i32, Expand);
  setOperationAction(ISD::FFLOOR, MVT::i32, Expand);
  setOperationAction(ISD::LROUND, MVT::i32, Expand);
  setOperationAction(ISD::LLROUND, MVT::i32, Expand);
  setOperationAction(ISD::LRINT, MVT::i32, Expand);
  setOperationAction(ISD::LLRINT, MVT::i32, Expand);
  setOperationAction(ISD::BR, MVT::Other, Legal);
  setOperationAction(ISD::BR, MVT::i32, Expand);
  setOperationAction(ISD::BRIND, MVT::Other, Legal);
  setOperationAction(ISD::BRIND, MVT::i32, Legal);

  setTruncStoreAction(MVT::i32, MVT::i8, Legal);
  setTruncStoreAction(MVT::i32, MVT::i16, Legal);

  setLoadExtAction(ISD::EXTLOAD, MVT::i8, MVT::i1, Promote);
  setLoadExtAction(ISD::EXTLOAD, MVT::i16, MVT::i1, Promote);
  setLoadExtAction(ISD::EXTLOAD, MVT::i32, MVT::i1, Promote);
  setLoadExtAction(ISD::EXTLOAD, MVT::i32, MVT::i8, Legal);
  setLoadExtAction(ISD::EXTLOAD, MVT::i32, MVT::i16, Legal);
  setLoadExtAction(ISD::EXTLOAD, MVT::i64, MVT::i1, Promote);
  setLoadExtAction(ISD::SEXTLOAD, MVT::i8, MVT::i1, Promote);
  setLoadExtAction(ISD::SEXTLOAD, MVT::i16, MVT::i1, Promote);
  setLoadExtAction(ISD::SEXTLOAD, MVT::i32, MVT::i1, Promote);
  setLoadExtAction(ISD::SEXTLOAD, MVT::i32, MVT::i8, Legal);
  setLoadExtAction(ISD::SEXTLOAD, MVT::i32, MVT::i16, Legal);
  setLoadExtAction(ISD::SEXTLOAD, MVT::i64, MVT::i1, Promote);
  setLoadExtAction(ISD::ZEXTLOAD, MVT::i8, MVT::i1, Promote);
  setLoadExtAction(ISD::ZEXTLOAD, MVT::i16, MVT::i1, Promote);
  setLoadExtAction(ISD::ZEXTLOAD, MVT::i32, MVT::i1, Promote);
  setLoadExtAction(ISD::ZEXTLOAD, MVT::i32, MVT::i8, Legal);
  setLoadExtAction(ISD::ZEXTLOAD, MVT::i32, MVT::i16, Legal);
  setLoadExtAction(ISD::ZEXTLOAD, MVT::i64, MVT::i1, Promote);


  // (read by getStackPointerRegisterToSaveRestore)
  // Note: see x86 back-end - they are setting this for SP, not BP.
  auto CRI = static_cast<const CodasipRegisterInfo*>(TM.getRegisterInfo());
  setStackPointerRegisterToSaveRestore(CRI->GetSP(0));
  // we handle these always the same way
  for (int i=0; i<MVT::LAST_VALUETYPE; ++i)
  {
    // all global symbols need to be wrapped
    setOperationAction(ISD::GlobalAddress, MVT::SimpleValueType(i), Custom);
    setOperationAction(ISD::GlobalTLSAddress, MVT::SimpleValueType(i), Custom);
    setOperationAction(ISD::ExternalSymbol, MVT::SimpleValueType(i), Custom);
    setOperationAction(ISD::JumpTable, MVT::SimpleValueType(i), Custom);
    setOperationAction(ISD::ConstantPool, MVT::SimpleValueType(i), Custom);
    setOperationAction(ISD::BlockAddress, MVT::SimpleValueType(i), Custom);
    // br_jt always expand
    setOperationAction(ISD::BR_JT, MVT::SimpleValueType(i), Expand);
    // we don't use br_cc and sel_cc
    setOperationAction(ISD::BR_CC, MVT::SimpleValueType(i), Expand);
    setOperationAction(ISD::SELECT_CC, MVT::SimpleValueType(i), Expand);
    // frame & return addr.
    setOperationAction(ISD::FRAMEADDR, MVT::SimpleValueType(i), Custom);
    setOperationAction(ISD::RETURNADDR, MVT::SimpleValueType(i), Custom);
    // "op_parts" operations are implicitly expanded
    setOperationAction(ISD::SHL_PARTS, MVT::SimpleValueType(i), Expand);
    setOperationAction(ISD::SRA_PARTS, MVT::SimpleValueType(i), Expand);
    setOperationAction(ISD::SRL_PARTS, MVT::SimpleValueType(i), Expand);
    // dynamic stack allocation (-> stacksave&stackrestore)
    setOperationAction(ISD::DYNAMIC_STACKALLOC, MVT::SimpleValueType(i), Expand );
    setOperationAction(ISD::STACKSAVE, MVT::SimpleValueType(i), Expand);
    setOperationAction(ISD::STACKRESTORE, MVT::SimpleValueType(i), Expand);
    // exceptions - not allowed
    setOperationAction(ISD::FRAME_TO_ARGS_OFFSET, MVT::SimpleValueType(i), Custom);
    setOperationAction(ISD::EH_RETURN, MVT::SimpleValueType(i), Custom);
    setOperationAction(ISD::EH_SJLJ_SETJMP, MVT::SimpleValueType(i), Custom);
    setOperationAction(ISD::EH_SJLJ_LONGJMP, MVT::SimpleValueType(i), Custom);
    if (TM.Options.ExceptionModel == ExceptionHandling::SjLj)
      setLibcallName(RTLIB::UNWIND_RESUME, "_Unwind_SjLj_Resume");
    // zero undef variant of ctlz & cttz
    setOperationAction(ISD::CTLZ_ZERO_UNDEF, MVT::SimpleValueType(i), Expand);
    setOperationAction(ISD::CTTZ_ZERO_UNDEF, MVT::SimpleValueType(i), Expand);
    // implicitly set inregs to expand, can be set to legal later
    setOperationAction(ISD::SIGN_EXTEND_INREG, MVT::SimpleValueType(i), Expand);
    // vector ops
    setOperationAction(ISD::SCALAR_TO_VECTOR, MVT::SimpleValueType(i), Expand);
    // - this even can't be legal
    setOperationAction(ISD::BUILD_VECTOR, MVT::SimpleValueType(i), Expand);
    // more imlicit expands
    setOperationAction(ISD::FCOPYSIGN, MVT::SimpleValueType(i), Expand);
    setOperationAction(ISD::FGETSIGN, MVT::SimpleValueType(i), Expand);
    // this is only for lowering
    setOperationAction(ISD::BUILD_PAIR, MVT::SimpleValueType(i), Expand);
    // this one is left on legal in TargetLoweringBase::initActions()
    setOperationAction(ISD::FSINCOS, MVT::SimpleValueType(i), Expand);
  }
  setOperationAction(ISD::EH_SJLJ_SETUP_DISPATCH, MVT::Other, Custom);
  // more error catching
  for (int i=MVT::FIRST_FP_VALUETYPE; i<MVT::LAST_FP_VALUETYPE; ++i)
  {
    for (int j=MVT::FIRST_FP_VALUETYPE; j<i; ++j)
    {
      setTruncStoreAction(MVT::SimpleValueType(i),MVT::SimpleValueType(j),Custom);
    }
  }
  // inreg sexts
  
  // bool content settings
  setBooleanContents(ZeroOrOneBooleanContent, ZeroOrOneBooleanContent);
setBooleanVectorContents(ZeroOrOneBooleanContent);
  // we need to pre-prepare intrins with varargs
  setOperationAction(ISD::INTRINSIC_WO_CHAIN,MVT::Other,Custom);
  setOperationAction(ISD::INTRINSIC_W_CHAIN,MVT::Other,Custom);
  setOperationAction(ISD::INTRINSIC_VOID,MVT::Other,Custom);
  // varargs, stacksave/restore
  setOperationAction(ISD::VASTART,MVT::Other,Custom);
  setOperationAction(ISD::VAEND,MVT::Other,Expand);
  setOperationAction(ISD::VAARG,MVT::Other,Expand);
  setOperationAction(ISD::VACOPY,MVT::Other,Expand);
  setOperationAction(ISD::STACKSAVE, MVT::Other, Expand); //(required)
  setOperationAction(ISD::STACKRESTORE, MVT::Other, Expand);
  // mem ops
  MaxStoresPerMemset = 32;
  MaxStoresPerMemsetOptSize = 4;
  MaxStoresPerMemcpy = 32;
  MaxStoresPerMemcpyOptSize = 4;
  MaxStoresPerMemmove = 32;
  MaxStoresPerMemmoveOptSize = 4;
  // custom finer grained info for indexed ops
  InitIndOffsetInfo();
  // tail calls allowed by default
  DisableTailCalls = false;
  // min argument align - corresponds with the generated call conv
  // note: the documentation says that the argument should be log2(n) but that's wrong
  setMinStackArgumentAlignment( 4 );
  // note: setTargetDAGCombine
  
  // disable libcalls available only on 64-bit architectures
  setLibcallName(RTLIB::SHL_I128, nullptr);
  setLibcallName(RTLIB::SRL_I128, nullptr);
  setLibcallName(RTLIB::SRA_I128, nullptr);
  setLibcallName(RTLIB::MUL_I128, nullptr);
  //setLibcallName(RTLIB::SDIV_I128, nullptr);
  //setLibcallName(RTLIB::UDIV_I128, nullptr);
  setLibcallName(RTLIB::SREM_I128, nullptr);
  setLibcallName(RTLIB::UREM_I128, nullptr);
  
  // for inline asm and clobbers
  NameMap.insert(std::make_pair("rf_xpr_0", RcAndReg(Codasip::rf_xpr_0, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_1", RcAndReg(Codasip::rf_xpr_1, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_2", RcAndReg(Codasip::rf_xpr_2, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_3", RcAndReg(Codasip::rf_xpr_3, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_4", RcAndReg(Codasip::rf_xpr_4, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_5", RcAndReg(Codasip::rf_xpr_5, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_6", RcAndReg(Codasip::rf_xpr_6, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_7", RcAndReg(Codasip::rf_xpr_7, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_8", RcAndReg(Codasip::rf_xpr_8, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_9", RcAndReg(Codasip::rf_xpr_9, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_10", RcAndReg(Codasip::rf_xpr_10, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_11", RcAndReg(Codasip::rf_xpr_11, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_12", RcAndReg(Codasip::rf_xpr_12, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_13", RcAndReg(Codasip::rf_xpr_13, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_14", RcAndReg(Codasip::rf_xpr_14, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_15", RcAndReg(Codasip::rf_xpr_15, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_16", RcAndReg(Codasip::rf_xpr_16, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_17", RcAndReg(Codasip::rf_xpr_17, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_18", RcAndReg(Codasip::rf_xpr_18, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_19", RcAndReg(Codasip::rf_xpr_19, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_20", RcAndReg(Codasip::rf_xpr_20, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_21", RcAndReg(Codasip::rf_xpr_21, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_22", RcAndReg(Codasip::rf_xpr_22, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_23", RcAndReg(Codasip::rf_xpr_23, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_24", RcAndReg(Codasip::rf_xpr_24, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_25", RcAndReg(Codasip::rf_xpr_25, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_26", RcAndReg(Codasip::rf_xpr_26, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_27", RcAndReg(Codasip::rf_xpr_27, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_28", RcAndReg(Codasip::rf_xpr_28, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_29", RcAndReg(Codasip::rf_xpr_29, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_30", RcAndReg(Codasip::rf_xpr_30, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("rf_xpr_31", RcAndReg(Codasip::rf_xpr_31, &Codasip::rf_xprRegClass)));
  NameMap.insert(std::make_pair("xpr_general", RcAndReg(0, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x1", RcAndReg(Codasip::rf_xpr_1, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("ra", RcAndReg(Codasip::rf_xpr_1, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x2", RcAndReg(Codasip::rf_xpr_2, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("sp", RcAndReg(Codasip::rf_xpr_2, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x3", RcAndReg(Codasip::rf_xpr_3, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("gp", RcAndReg(Codasip::rf_xpr_3, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x4", RcAndReg(Codasip::rf_xpr_4, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("tp", RcAndReg(Codasip::rf_xpr_4, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x5", RcAndReg(Codasip::rf_xpr_5, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("t0", RcAndReg(Codasip::rf_xpr_5, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x6", RcAndReg(Codasip::rf_xpr_6, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("t1", RcAndReg(Codasip::rf_xpr_6, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x7", RcAndReg(Codasip::rf_xpr_7, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("t2", RcAndReg(Codasip::rf_xpr_7, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x8", RcAndReg(Codasip::rf_xpr_8, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("fp", RcAndReg(Codasip::rf_xpr_8, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s0", RcAndReg(Codasip::rf_xpr_8, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x9", RcAndReg(Codasip::rf_xpr_9, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s1", RcAndReg(Codasip::rf_xpr_9, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x10", RcAndReg(Codasip::rf_xpr_10, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("a0", RcAndReg(Codasip::rf_xpr_10, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x11", RcAndReg(Codasip::rf_xpr_11, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("a1", RcAndReg(Codasip::rf_xpr_11, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x12", RcAndReg(Codasip::rf_xpr_12, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("a2", RcAndReg(Codasip::rf_xpr_12, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x13", RcAndReg(Codasip::rf_xpr_13, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("a3", RcAndReg(Codasip::rf_xpr_13, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x14", RcAndReg(Codasip::rf_xpr_14, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("a4", RcAndReg(Codasip::rf_xpr_14, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x15", RcAndReg(Codasip::rf_xpr_15, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("a5", RcAndReg(Codasip::rf_xpr_15, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x16", RcAndReg(Codasip::rf_xpr_16, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("a6", RcAndReg(Codasip::rf_xpr_16, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x17", RcAndReg(Codasip::rf_xpr_17, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("a7", RcAndReg(Codasip::rf_xpr_17, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x18", RcAndReg(Codasip::rf_xpr_18, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s2", RcAndReg(Codasip::rf_xpr_18, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x19", RcAndReg(Codasip::rf_xpr_19, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s3", RcAndReg(Codasip::rf_xpr_19, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x20", RcAndReg(Codasip::rf_xpr_20, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s4", RcAndReg(Codasip::rf_xpr_20, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x21", RcAndReg(Codasip::rf_xpr_21, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s5", RcAndReg(Codasip::rf_xpr_21, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x22", RcAndReg(Codasip::rf_xpr_22, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s6", RcAndReg(Codasip::rf_xpr_22, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x23", RcAndReg(Codasip::rf_xpr_23, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s7", RcAndReg(Codasip::rf_xpr_23, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x24", RcAndReg(Codasip::rf_xpr_24, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s8", RcAndReg(Codasip::rf_xpr_24, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x25", RcAndReg(Codasip::rf_xpr_25, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s9", RcAndReg(Codasip::rf_xpr_25, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x26", RcAndReg(Codasip::rf_xpr_26, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s10", RcAndReg(Codasip::rf_xpr_26, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x27", RcAndReg(Codasip::rf_xpr_27, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("s11", RcAndReg(Codasip::rf_xpr_27, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x28", RcAndReg(Codasip::rf_xpr_28, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("t3", RcAndReg(Codasip::rf_xpr_28, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x29", RcAndReg(Codasip::rf_xpr_29, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("t4", RcAndReg(Codasip::rf_xpr_29, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x30", RcAndReg(Codasip::rf_xpr_30, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("t5", RcAndReg(Codasip::rf_xpr_30, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("x31", RcAndReg(Codasip::rf_xpr_31, &Codasip::xpr_generalRegClass)));
  NameMap.insert(std::make_pair("t6", RcAndReg(Codasip::rf_xpr_31, &Codasip::xpr_generalRegClass)));
  
}

SDValue CodasipGenTargetLowering::
LowerCall(TargetLowering::CallLoweringInfo &CLI, SmallVectorImpl<SDValue> &InVals) const
{
  // load the info
  SelectionDAG &DAG                     = CLI.DAG;
  SDLoc &dl                             = CLI.DL;
  SmallVector<ISD::OutputArg, 32> &Outs = CLI.Outs;
  SmallVector<SDValue, 32> &OutVals     = CLI.OutVals;
  SmallVector<ISD::InputArg, 32> &Ins   = CLI.Ins;
  SDValue Chain                         = CLI.Chain;
  SDValue Callee                        = CLI.Callee;
  bool &isTailCall                      = CLI.IsTailCall;
  CallingConv::ID CallConv              = CLI.CallConv;
  bool isVarArg                         = CLI.IsVarArg;
  // get various metainfo
  LLVMContext &cont = *DAG.getContext();
  MachineFunction &MF = DAG.getMachineFunction();
  SmallVector<CCValAssign,16> ArgLocs;
  CCState CCInfo(CallConv, isVarArg, MF, ArgLocs, cont);
  CCInfo.AnalyzeCallOperands(Outs, CC_Codasip);
  SDValue InFlag;
  MachineFrameInfo *MFI = &MF.getFrameInfo();
  const DataLayout &td = getTargetMachine().getDataLayout();
  CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  // get call frame size in bytes (aligned to stack align)
  const unsigned stackAlign = td.getStackAlignment();
  unsigned stackParamSize = CCInfo.getNextStackOffset();
  stackParamSize += ((stackAlign-(stackParamSize%stackAlign))%stackAlign);
  // analyse tail call eligibility
  do if (isTailCall)
  {
    // explicitly disabled?
    if (DisableTailCalls) {
      isTailCall = false;
      break;
    }
    // optim level
    if (getTargetMachine().getOptLevel()==CodeGenOpt::None) {
      isTailCall = false;
      break;
    }
    // do not allow indirect
    if (Callee.getOpcode()!=ISD::GlobalAddress) {
      isTailCall = false;
      break;
    }
    // do not allow any varargs
    if (isVarArg || finfo->ArgsInfo.StackFI) {
      isTailCall = false;
      break;
    }
    // disable if either the callee or caller has a byval argument.
    const unsigned callerByValRegs = CCInfo.getInRegsParamsCount();
    if (callerByValRegs>0) {
      isTailCall = false;
      break;
    }
    for (unsigned i=0; i<Outs.size(); ++i) {
      ISD::ArgFlagsTy Flags = Outs[i].Flags;
      if (Flags.isByVal()) {
        isTailCall = false;
        break;
      }
    }
    if (!isTailCall) break;
    // no mem args either
    for (unsigned i=0; i < ArgLocs.size(); ++i)
    {
      if (ArgLocs[i].isMemLoc()) {
        isTailCall = false;
        break;
      }
    }
    if (!isTailCall) break;
    // is callee's argument area larger than the caller's?
    assert(finfo->ArgsInfo.StackOff >= 0);
    if (stackParamSize > unsigned(finfo->ArgsInfo.StackOff)) {
      isTailCall = false;
      break;
    }
    // don't tailcall functions inside interrupt routine
    if (MF.getFunction().hasFnAttribute("interrupt")) {
      isTailCall = false;
      break;
    }
  } while(false);
  // check MustTailCall
  if (!isTailCall && CLI.CS && CLI.CS.isMustTailCall()) {
    report_fatal_error("failed to perform tail call elimination on a call site marked musttail");
  }
  // deal with byvals before doing anything else
  for (unsigned i=0; i<ArgLocs.size(); ++i)
  {
    // manual handling without TD
    // caller side only - invisible for callee
    SDValue &Arg = OutVals[i];
    ISD::ArgFlagsTy Flags = Outs[i].Flags;
    if (Flags.isByVal()) {
      assert(!isTailCall);
      // make place
      unsigned align = Flags.getByValAlign();
      unsigned size = Flags.getByValSize();
      if (size) {
        int FI = MFI->CreateStackObject(size,align,false);
        SDValue PtrDst = DAG.getFrameIndex(FI,getPointerTy(td,0)); //that 0 is addres space
        
        // determine address space
        EVT vt = Arg.getValueType();
        unsigned addressSpace = GetSpace4Vt(vt);
        MFI->setStackID(FI, addressSpace);
        // copy
        SDValue Size = DAG.getConstant(size,dl,getPointerTy(td,0),false,false);
        MachinePointerInfo dstInfo = MachinePointerInfo::getFixedStack(MF,FI);
        MachinePointerInfo srcInfo = MachinePointerInfo();
        Chain = DAG.getMemcpy(Chain,dl,PtrDst,Arg,Size,align,false,false,false,dstInfo,srcInfo);
        // replace Arg
        Arg.setNode(PtrDst.getNode());
      }
    }
  }
  // how many bytes are to be pushed on the stack?
  // callee pushes nothing
  if (!isTailCall) {
    Chain = DAG.getCALLSEQ_START(Chain,stackParamSize,0,dl);
  }
  // operands of the call (the first two slots empty for now, we'll fill later with chain and callee)
  SmallVector<SDValue,8> Ops;
  Ops.push_back(SDValue()); Ops.push_back(SDValue());
  // deal with stack passes first
  for (int i=ArgLocs.size()-1; i>=0; --i)
  {
    SDValue Arg = OutVals[i];
    CCValAssign& VA = ArgLocs[i];
    assert(!VA.isUpperBitsInLoc());
    // is it a stack pass?
    if (VA.isMemLoc())
    {
      // memory requirements (alignment considered)
      EVT vt = Arg.getValueType();
      assert(vt.getSimpleVT()==VA.getValVT());
      Type *ty = vt.getTypeForEVT(cont);
      unsigned ArgSize = td.getTypeAllocSize(ty);
      assert(vt.isByteSized());
      // determine address space
      unsigned addressSpace = GetSpace4Vt(vt);
      // pass on stack
      if (isTailCall) {
        assert(false && "stack params not supported for tail calls");
      }
      else {
        // get index  -note: negative
        int FI = MFI->CreateFixedObject(ArgSize,VA.getLocMemOffset(),true);
        SDValue PtrOff = DAG.getFrameIndex(FI,getPointerTy(td,0));
        // mark it as out param
        finfo->MarkOutFI(FI);
        MFI->setStackID(FI, addressSpace);
        // "dummy" IR value (for MachinePointerInfo)
        FixedStackPseudoSourceValue *fspsv = new FixedStackPseudoSourceValue(FI,*CTM.getInstrInfo());
        // store
        Chain = DAG.getStore(Chain,dl,Arg,PtrOff,MachinePointerInfo(fspsv));
      }
    }
    // reg pass otherwise
    else {
      assert(VA.isRegLoc());
      assert(!isVarArg && "not allowed");
    }
  }
  // now deal with registers (in natural order)
  for (unsigned i=0; i<ArgLocs.size(); ++i)
  {
    SDValue Arg = OutVals[i];
    CCValAssign &VA = ArgLocs[i];
    // unprocessed yet?
    if (VA.isRegLoc()) {
      // from now on, everything has to flagged
      Chain = DAG.getCopyToReg(Chain,dl, VA.getLocReg(),Arg,InFlag);
      InFlag = Chain.getValue(1);
      // add to ops (to keep alive)
      Ops.push_back(DAG.getRegister(VA.getLocReg(),Arg.getValueType()));
    }
  }
  // these regs are not changed, the rest is invalidated (copied from riscV)
  if (!isTailCall) {
    // Add a register mask operand representing the call-preserved registers.
    const TargetRegisterInfo *TRI = CTM.getRegisterInfo();
    const uint32_t *Mask = TRI->getCallPreservedMask(MF, CallConv);
    assert(Mask && "Missing call preserved mask for calling convention");
    Ops.push_back(DAG.getRegisterMask(Mask));
  }
  // insert the call itself
  SDVTList NodeTys = DAG.getVTList(MVT::Other,MVT::Glue);
  Ops[0] = Chain;
  Ops[1] = Callee;
  if (InFlag.getNode()) Ops.push_back(InFlag);
  ArrayRef<SDValue> aref(&Ops[0],Ops.size());
  if (isTailCall) {
    Chain = DAG.getNode(CodasipISD::TailCall,dl,NodeTys,aref);
    // don't do anything else
    return Chain;
  }
  Chain = DAG.getNode(CodasipISD::Call,dl,NodeTys,aref);
  InFlag = Chain.getValue(1);
  // see CALLSEQ_START above
  Chain = DAG.getCALLSEQ_END(Chain, DAG.getIntPtrConstant(stackParamSize,dl,true), DAG.getIntPtrConstant(0,dl,true), InFlag, dl);
  InFlag = Chain.getValue(1);
  // ============= lower call result
  SmallVector<CCValAssign,16> RVLocs;
  CCState CCInfo2(CallConv, isVarArg, MF, RVLocs, cont);
  auto conv = (CLI.RetZExt||CLI.RetSExt? RetCC_Codasip_Ext: RetCC_Codasip);
  CCInfo2.AnalyzeCallResult(Ins,conv);
  // If this is the first return lowered for this function,
  // add the regs to the livein set for the function.
  if (MF.getRegInfo().livein_empty())
  {
    for (unsigned i=0; i<RVLocs.size(); ++i) {
      assert(RVLocs[i].isRegLoc());
      MF.getRegInfo().addLiveIn(RVLocs[i].getLocReg());
    }
  }
  // copy the result value from register to the target
  for (unsigned i=0; i<RVLocs.size(); ++i)
  {
    assert(RVLocs[i].isRegLoc());
    Chain = DAG.getCopyFromReg(Chain,dl, RVLocs[i].getLocReg(), RVLocs[i].getLocVT(), InFlag).getValue(1);
    InFlag = Chain.getValue(2);
    SDValue val = Chain.getValue(0);
    if (RVLocs[i].getLocVT() != RVLocs[i].getValVT())
    {
      // truncate
      assert(RVLocs[i].getLocVT() > RVLocs[i].getValVT() && "not a truncate");
      val = DAG.getAnyExtOrTrunc(val, dl, RVLocs[i].getValVT());
    }
    InVals.push_back(val);
  }
  return Chain;
}

static unsigned GetHwCl(unsigned id)
{
  switch (id)
  {
    case Codasip::xpr_generalRegClassID:
      return Codasip::rf_xprRegClassID;
    
    default:
      assert(false);
  }
  return 0;
}

SDValue CodasipGenTargetLowering::LowerFormalArguments(SDValue Chain,
                                                       CallingConv::ID CallConv,
                                                       bool isVarArg,
                                                       const SmallVectorImpl<ISD::InputArg> &Ins,
                                                       const SDLoc &dl,
                                                       SelectionDAG &DAG,
                                                       SmallVectorImpl<SDValue> &InVals) const
{
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  MachineFunction &MF = DAG.getMachineFunction();
  const Function &func = MF.getFunction();
  MachineFrameInfo *MFI = &MF.getFrameInfo();
  MachineRegisterInfo &MRI = MF.getRegInfo();
  const TargetRegisterInfo *TRI = CTM.getRegisterInfo();
  CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  const DataLayout &td = getTargetMachine().getDataLayout();
  LLVMContext &cont = *DAG.getContext();
  // Assign locations to all of the incoming arguments.
  SmallVector<CCValAssign,16> ArgLocs;
  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(), ArgLocs, cont);
  CCInfo.AnalyzeFormalArguments(Ins, CC_Codasip);
  // init StackOff
  finfo->ArgsInfo.StackOff = finfo->StackShift;
  finfo->ArgsInfo.StackFI = 0;
  // take all params
  for (unsigned i=0, e=ArgLocs.size(); i!=e; ++i)
  {
    CCValAssign &VA = ArgLocs[i];
    EVT vt = VA.getValVT();
    assert(vt.isSimple());
    // reg params
    if (VA.isRegLoc())
    {
      // for now
      assert(!isVarArg && "not supported yet");
      // should be always full
      assert(VA.getLocInfo()==CCValAssign::Full && "my assumption was faulty");
      // add the reg as a live in (direct use wouldn't always work)
      unsigned FReg = VA.getLocReg();
      assert(TRI->isPhysicalRegister(FReg));
      assert(TRI->isInAllocatableClass(FReg));
      // get a suitable allocatable class
      const TargetRegisterClass* RC = NULL;
      for (unsigned j=0; j<TRI->getNumRegClasses(); ++j)
      {
        const TargetRegisterClass* rc = TRI->getRegClass(j);
        if (!rc->isAllocatable()) continue;
        if (!rc->contains(FReg)) continue;
        if (TRI->isTypeLegalForClass(*rc,vt.getSimpleVT())) {
          RC = rc;
          break;
        }
      }
      assert(RC);
      unsigned VReg = MRI.createVirtualRegister(RC);
      MRI.addLiveIn(FReg,VReg);
      InVals.push_back(DAG.getCopyFromReg(Chain,dl,VReg,vt));
    }
    // mem params
    else if (VA.isMemLoc())
    {
      // memory requirements (alignment considered)
      unsigned ArgSize = td.getTypeAllocSize(vt.getTypeForEVT(cont));
      // note: (if the stack grows down) the offset is positive
      int off = VA.getLocMemOffset();
      int FI = MFI->CreateFixedObject(ArgSize,off,true);
      finfo->ArgsInfo.StackOff = off+ArgSize;
      // determine address space
      unsigned addressSpace = GetSpace4Vt(vt);
      MFI->setStackID(FI, addressSpace);
      // Create load nodes to retrieve arguments from the stack
      SDValue FIN = DAG.getFrameIndex(FI,getPointerTy(td,0));
      InVals.push_back(DAG.getLoad(vt,dl,Chain,FIN,MachinePointerInfo::getFixedStack(MF,FI)));
    }
    else
    {
      assert(false && "unreachable");
    }
  }
  // make dummy object for vastart
  if (isVarArg)
  {
      int FI = MFI->CreateFixedObject( 4 , finfo->ArgsInfo.StackOff, true);
      finfo->ArgsInfo.StackFI = FI;
      // space and mapping?
  }
  // are we returning a structure?
  if (func.hasStructRetAttr())
  {
    if (!finfo->StrctRetReg) {
      // use general register class (if the default is not)
      finfo->StrctRetReg = MRI.createVirtualRegister(TRI->getPointerRegClass(MF,true));
      assert(finfo->StrctRetReg);
    }
    SDValue Copy = DAG.getCopyToReg(DAG.getEntryNode(), dl, finfo->StrctRetReg, InVals[0]);
    Chain = DAG.getNode(ISD::TokenFactor, dl, MVT::Other, Copy, Chain);
  }
  return Chain;
}

SDValue CodasipGenTargetLowering::LowerReturn(SDValue Chain,
                                              CallingConv::ID CallConv,
                                              bool isVarArg,
                                              const SmallVectorImpl<ISD::OutputArg> &Outs,
                                              const SmallVectorImpl<SDValue> &OutVals,
                                              const SDLoc &dl, SelectionDAG &DAG) const
{
  // std rutine
  SmallVector<CCValAssign, 16> RVLocs;
  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(), RVLocs,
                 *DAG.getContext());
  CCInfo.AnalyzeReturn(Outs, RetCC_Codasip);
  MachineFunction &MF = DAG.getMachineFunction();
  const Function &Func = MF.getFunction();
  CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  const DataLayout &td = getTargetMachine().getDataLayout();
  SmallVector<SDValue, 8> Ops;
  Ops.push_back(SDValue());
  // store values in regs, also store meta
  SDValue Flag;
  finfo->RetRegs.reserve(RVLocs.size());
  for (unsigned i = 0; i < RVLocs.size(); ++i) {
    assert(!MF.getFunction().hasStructRetAttr());
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");
    Chain = DAG.getCopyToReg(Chain, dl, VA.getLocReg(), OutVals[i], Flag);
    Flag = Chain.getValue(1);
    finfo->RetRegs.push_back(VA.getLocReg());
    Ops.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }
  // are we returning a structure?
  if (Func.hasStructRetAttr()) {
    assert(RVLocs.empty());
    assert(finfo->StrctRetReg && "should have been set");
    Ops.push_back(DAG.getRegister(finfo->StrctRetReg, getPointerTy(td, 0)));
  }
  // chain and flag
  Ops[0] = Chain;
  if (Flag.getNode()) {
    Ops.push_back(Flag);
  }
  // prepare operands of the return
  ArrayRef<SDValue> aref(&Ops[0], Ops.size());
  // return from interrupts
  if (Func.hasFnAttribute("interrupt")) {
    if (!Func.getReturnType()->isVoidTy())
      report_fatal_error(
          "Functions with the interrupt attribute must have void return type!");
    MachineFunction &MF = DAG.getMachineFunction();
    StringRef Kind =
        MF.getFunction().getFnAttribute("interrupt").getValueAsString();
    unsigned RetOpc = 0;
    if (Kind == "user") {
      RetOpc = CodasipISD::URET;
    } else if (Kind == "supervisor") {
      RetOpc = CodasipISD::SRET;
    } else if (Kind == "machine") {
      RetOpc = CodasipISD::MRET;
    } else {
      report_fatal_error("Unknown interrupt type");
    }
    return DAG.getNode(RetOpc, dl, MVT::Other, aref);
  }
  // normal return
  return DAG.getNode(CodasipISD::Ret, dl, MVT::Other, aref);
}

bool CodasipGenTargetLowering::CanLowerReturn(CallingConv::ID CallConv,
                                              MachineFunction &MF,
                                              bool isVarArg,
                                              const SmallVectorImpl<ISD::OutputArg> &Outs,
                                              LLVMContext &Context) const
{
  SmallVector<CCValAssign,16> RVLocs;
  CCState CCInfo(CallConv, isVarArg, MF, RVLocs, Context);
  return CCInfo.CheckReturn(Outs, RetCC_Codasip);
}

static inline unsigned GetSpaceFromNode(SDNode* node)
{
  SDValue val(node,0);
  if (!val.hasOneUse()) {
    return 0;
  }
  auto it = node->use_begin();
  while (!it.atEnd())
  {
    if (it.getUse().getResNo()==0) {
      break;
    }
    ++it;
  }
  assert(!it.atEnd());
  node = *it;
  if (node->getOpcode() != ISD::ADDRSPACECAST) {
    return 0;
  }
  auto asc = cast<AddrSpaceCastSDNode>(node);
  return asc->getDestAddressSpace();
}

unsigned CodasipGenTargetLowering::GetSpForAS(SDNode* Node) const
{
  const CodasipTargetMachine& ctm = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const CodasipRegisterInfo* cri = static_cast<const CodasipRegisterInfo*>(ctm.getRegisterInfo());
  unsigned space = GetSpaceFromNode(Node);
  return cri->GetSP(space);
}

// from SelectionDAGLegalize::ExpandDYNAMIC_STACKALLOC
// edited, commented, or added lines are marked by X
SDValue CodasipGenTargetLowering::ExpandDYNAMIC_STACKALLOC(SDNode* Node, SelectionDAG& DAG) const
{
  unsigned SPReg = GetSpForAS(Node); //X
  //unsigned SPReg = TLI.getStackPointerRegisterToSaveRestore(); //X
  assert(SPReg && "Target cannot require DYNAMIC_STACKALLOC expansion and"
          " not tell us which reg is the stack pointer!");
  SDLoc dl(Node);
  EVT VT = Node->getValueType(0);
  SDValue Tmp1 = SDValue(Node, 0);
  SDValue Tmp2 = SDValue(Node, 1);
  SDValue Tmp3 = Node->getOperand(2);
  SDValue Chain = Tmp1.getOperand(0);

  // Chain the dynamic stack allocation so that it doesn't modify the stack
  // pointer when other instructions are using the stack.
  Chain = DAG.getCALLSEQ_START(Chain, 0, 0, dl);

  SDValue Size  = Tmp2.getOperand(1);
  SDValue SP = DAG.getCopyFromReg(Chain, dl, SPReg, VT);
  Chain = SP.getValue(1);
  unsigned Align = cast<ConstantSDNode>(Tmp3)->getZExtValue();
  unsigned StackAlign =
      DAG.getSubtarget().getFrameLowering()->getStackAlignment();
  Tmp1 = DAG.getNode(ISD::SUB, dl, VT, SP, Size);       // Value
  if (Align > StackAlign)
    Tmp1 = DAG.getNode(ISD::AND, dl, VT, Tmp1,
                       DAG.getConstant(-(uint64_t)Align, dl, VT));
  Chain = DAG.getCopyToReg(Chain, dl, SPReg, Tmp1);     // Output chain

  Tmp2 = DAG.getCALLSEQ_END(Chain, DAG.getIntPtrConstant(0, dl, true),
                            DAG.getIntPtrConstant(0, dl, true), SDValue(), dl);

  //Results.push_back(Tmp1); //X
  //Results.push_back(Tmp2); //X
  SDValue Ops[2] = {Tmp1,Tmp2}; //X
  return DAG.getMergeValues(Ops,dl); //X
}

SDValue CodasipGenTargetLowering::LowerOperation(SDValue Op, SelectionDAG &DAG) const
{
  SDLoc dl(Op);
  MachineFunction &MF = DAG.getMachineFunction();
  CodasipFunctionInfo *FuncInfo = MF.getInfo<CodasipFunctionInfo>();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  const DataLayout &td = getTargetMachine().getDataLayout();
  const TargetRegisterInfo *RI = MF.getSubtarget().getRegisterInfo();
  const TargetFrameLowering *FL = MF.getSubtarget().getFrameLowering();
  SDValue res;
  switch (Op.getOpcode())
  {
    case ISD::GlobalAddress:
    {
      // make a copy of the GA (target version)
      GlobalAddressSDNode *ga = cast<GlobalAddressSDNode>(Op);
      SDValue tga = DAG.getTargetGlobalAddress(ga->getGlobal(), dl, MVT::i32, ga->getOffset());
      // lower the original (will be done in the caller method) to wrapper, use the copy (tga) as an operand
      res = DAG.getNode(CodasipISD::GAWrap, dl, MVT::i32, tga);
      break;
    }
    case ISD::ExternalSymbol:
    {
      // same as above
      ExternalSymbolSDNode *es = cast<ExternalSymbolSDNode>(Op);
      assert(es->getSymbol() && "an unsupported call generated");
      SDValue tes = DAG.getTargetExternalSymbol(es->getSymbol(), MVT::i32, es->getTargetFlags());
      res = DAG.getNode(CodasipISD::GAWrap, dl, MVT::i32, tes);
      break;
    }
    case ISD::JumpTable:
    {
      JumpTableSDNode *jt = cast<JumpTableSDNode>(Op);
      SDValue tjt = DAG.getTargetJumpTable(jt->getIndex(), MVT::i32);
      res = DAG.getNode(CodasipISD::GAWrap, dl, MVT::i32, tjt);
      break;
    }
    case ISD::ConstantPool:
    {
      ConstantPoolSDNode *cp = cast<ConstantPoolSDNode>(Op);
      assert(cp);
      assert(!cp->isMachineConstantPoolEntry());
      SDValue tcp = DAG.getTargetConstantPool(cp->getConstVal(), Op.getValueType(), cp->getAlignment(), cp->getOffset());
      res = DAG.getNode(CodasipISD::GAWrap, dl, MVT::i32, tcp);
      break;
    }
    case ISD::BlockAddress:
    {
      BlockAddressSDNode *ba = cast<BlockAddressSDNode>(Op);
      assert(ba);
      SDValue tba = DAG.getBlockAddress(ba->getBlockAddress(), Op.getValueType(), ba->getOffset(), true);
      res = DAG.getNode(CodasipISD::GAWrap, dl, MVT::i32, tba);
      break;
    }
    case ISD::GlobalTLSAddress:
    {
      errs() << "Warning: thread local global variables aren't supported.\n";
      GlobalAddressSDNode *ga = cast<GlobalAddressSDNode>(Op);
      const GlobalVariable *gv = static_cast<const GlobalVariable*>(ga->getGlobal());
      const_cast<GlobalVariable*>(gv)->setThreadLocal(false);
      SDValue tga = DAG.getTargetGlobalAddress(gv, dl, MVT::i32, ga->getOffset());
      res = DAG.getNode(CodasipISD::GAWrap, dl, MVT::i32, tga);
      break;
    }
    // frame and return address
    case ISD::FRAMEADDR:
    case ISD::RETURNADDR:
    {
      // check the operand - only 0 is accepted
      const SDValue &op = Op.getOperand(0);
      assert(op.getOpcode()==ISD::Constant && "Invalid return/frame address usage.");
      const ConstantSDNode *hlp = static_cast<const ConstantSDNode*>(op.getNode());
      if (hlp->getZExtValue()) {
        errs() << "Builtin return/frame address can be only used with parameter 0.\n";
        exit(1);
      }
      // ptr mvt
      const MVT ptrT = MVT::i32;
      // continue
      if (Op.getOpcode()==ISD::FRAMEADDR) {
        MFI.setFrameAddressIsTaken(true);
        // a simple copy from the corresponging reg
        // (should be BP, see getFrameRegister)
        assert(FL->hasFP(MF));
        res = DAG.getCopyFromReg(DAG.getEntryNode(), dl, RI->getFrameRegister(MF), ptrT);
      }
      else {
      
        MFI.setReturnAddressIsTaken(true);
        unsigned Reg = MF.addLiveIn(RI->getRARegister(), getRegClassFor(ptrT));
        res = DAG.getCopyFromReg(DAG.getEntryNode(), dl, Reg, ptrT);
      
      }
      break;
    }
    // varargs
    case ISD::VASTART:
    {
      SDValue FI = DAG.getFrameIndex(FuncInfo->ArgsInfo.StackFI, getPointerTy(td,0));
      // vastart just stores the address of the VarArgsFrameIndex slot into the memory location argument.
      const Value *SV = cast<SrcValueSDNode>(Op.getOperand(2))->getValue();
      res = DAG.getStore(Op.getOperand(0),dl,FI,Op.getOperand(1),MachinePointerInfo(SV));
      break;
    }
    // multi-stack dynalloc
    case ISD::DYNAMIC_STACKALLOC:
      return ExpandDYNAMIC_STACKALLOC(Op.getNode(),DAG);
      break;
    // exceptions
    case ISD::EH_SJLJ_SETJMP:
                
        return DAG.getNode(CodasipISD::EH_SJLJ_SETJMP, dl,
                           DAG.getVTList(MVT::i32, MVT::Other),
                           Op.getOperand(0), Op.getOperand(1));
        break;
        
    case ISD::EH_SJLJ_LONGJMP:
                
        return DAG.getNode(CodasipISD::EH_SJLJ_LONGJMP, dl, MVT::Other,
                           Op.getOperand(0), Op.getOperand(1));
        break;
        
    case ISD::FRAME_TO_ARGS_OFFSET:
        errs() << "FRAME_TO_ARGS_OFFSET is not supported at this moment.\n";
        exit(1);
    case ISD::EH_RETURN:
        errs() << "FRAME_TO_ARGS_OFFSET is not supported at this moment.\n";
        exit(1);
        break;
    case ISD::EH_SJLJ_SETUP_DISPATCH:
        
        return DAG.getNode(CodasipISD::EH_SJLJ_SETUP_DISPATCH,
                           dl, MVT::Other, Op.getOperand(0), Op.getOperand(1));
        break;
        
    case ISD::EH_DWARF_CFA:
        errs() << "EH_DWARF_CFA is not supported at this moment. \n";
        exit(1);
    case ISD::EH_LABEL:
      errs() << "EH_LABEL is not supported at this moment. \n";
      exit(1);
    // Error message for non-legal (trunc/ext)store/load
    case ISD::STORE:
    case ISD::LOAD:
      errs() << "This program requires an unimplemented load/store operation (see the log from backendgen).\n";
      errs() << "Please do implement custom lowering in CodasipTargetLowering::LowerOperation.\n";
      exit(1);
    // intrinsics
    case ISD::INTRINSIC_VOID:
    case ISD::INTRINSIC_W_CHAIN:
    case ISD::INTRINSIC_WO_CHAIN:
      return LowerIntrinsic(Op,DAG);
    default:
      assert(false && "LowerOperation");
  }
  return res;
}

// remove this completely
SDValue CodasipGenTargetLowering::HandleExtToCust(SDValue Op, SelectionDAG &DAG) const
{
  return CodasipGenTargetLowering::LowerOperation(Op,DAG);
}

void CodasipGenTargetLowering::ReplaceNodeResults
(SDNode *N, SmallVectorImpl<SDValue> &Results, SelectionDAG &DAG) const
{
  switch (N->getOpcode())
  {
    // skip exts
    case ISD::ANY_EXTEND:
    case ISD::ZERO_EXTEND:
    case ISD::SIGN_EXTEND:
      break;
    // exceptions
    case ISD::FRAME_TO_ARGS_OFFSET:
    case ISD::EH_RETURN:
      errs() << "This operations is not supported at this moment.\n";
      exit(1);
    default:
      assert(false && "ReplaceNodeResults");
  }
}

EVT CodasipGenTargetLowering::getSetCCResultType(const DataLayout &DL, LLVMContext &Context, EVT VT) const
{
  if (VT.isVector()) {
    return VT.changeVectorElementTypeToInteger();
  }
  if (VT.isInteger()) {
    return MVT::i32;
  }
  if (VT.isFloatingPoint()) {
    return MVT::i32;
  }
  // canonical setcc result (VT is Other if this is reached)
  return MVT::i32;
}

// compiler-rt returns uintptr_t
MVT::SimpleValueType CodasipGenTargetLowering::getCmpLibcallReturnType() const
{
  return MVT::i32;
}

// users can reimplement this
bool CodasipGenTargetLowering::isShuffleMaskLegal(ArrayRef<int> m, EVT t) const
{
  // this is called from build_vector expansion
  // -> treatment of actual shuffles is determined by normal legality
  // check for implicit support
  
  // nothing matched
  return false;
}

const char* CodasipGenTargetLowering::getTargetNodeName(unsigned Opcode) const
{
  switch (Opcode)
  {
    case CodasipISD::Call:
      return "CodasipISD::Call";
    case CodasipISD::Ret:
      return "CodasipISD::Ret";
    case CodasipISD::TailCall:
      return "CodasipISD::TailCall";
    case CodasipISD::GAWrap:
      return "CodasipISD::GAWrap";
    case CodasipISD::EH_SJLJ_SETJMP:
      return "CodasipISD::EH_SJLJ_SETJMP";
    case CodasipISD::EH_SJLJ_LONGJMP:
      return "CodasipISD::EH_SJLJ_LONGJMP";
    case CodasipISD::EH_SJLJ_SETUP_DISPATCH:
      return "CodasipISD::EH_SJLJ_SETUP_DISPATCH";
    
    
    // this may appear in instruction semantics
    case CodasipISD::GET_PC:
      return "CodasipISD::GET_PC";
    case CodasipISD::MRET:
      return "CodasipISD::MRET";
    case CodasipISD::SRET:
      return "CodasipISD::SRET";
    case CodasipISD::URET:
      return "CodasipISD::URET";
    default:
      assert(false);
  }
}

std::pair<unsigned, const TargetRegisterClass*>
CodasipGenTargetLowering::getRegForInlineAsmConstraint(
  const TargetRegisterInfo *TRI,
  StringRef Constraint,
  MVT VT) const
{
  RcAndReg p;
  // can be empty
  if (Constraint.empty())
  {
    return TargetLowering::getRegForInlineAsmConstraint(TRI,Constraint,VT);
  }
  // operands
  if (Constraint.size() == 1)
  {
    switch (Constraint[0])
    {
      // a general operand (a concrete register/class is not specified)
      case 'r':
        if (VT==MVT::i1) {
          p.second = &Codasip::xpr_generalRegClass;
        }
        else if (VT==MVT::i8) {
          p.second = &Codasip::xpr_generalRegClass;
        }
        else if (VT==MVT::i16) {
          p.second = &Codasip::xpr_generalRegClass;
        }
        else if (VT==MVT::i32) {
          p.second = &Codasip::xpr_generalRegClass;
        }
        else {
          p.second = NULL;
        }
        p.first = 0;
        break;
      // label or imm
      case 'X':
      case 'i':
        // do nothing
        return p;
      default:
        break;
    }
  }
  // a concrete register/class (e.g. in a clobber)
  // (using custom impl rather than TargetLowering::getRegForInlineAsmConstraint)
  else if (Constraint[0] == '{')
  {
    assert(Constraint.size() >= 2);
    assert(*(Constraint.end()-1) == '}' && "Not a brace enclosed constraint?");
    StringRef RegName(Constraint.data()+1, Constraint.size()-2);
    if (RegName=="memory") {
      return p;
    }
    p = GetRegAndClassByName(RegName,VT);
  }
  // check
  if (!p.second)
  {
    errs() << "Invalid/unsupported inline-asm constraint: " << Constraint << ".\n";
    errs() << "Note: It's possible that this constraint was allowed in Clang but failed in finer analysis.\n";
  }
  return p;
}

unsigned CodasipGenTargetLowering::getInlineAsmMemConstraint(StringRef ConstraintCode) const
{
  if (ConstraintCode == "o") {
    return InlineAsm::Constraint_o;
  }
  if (ConstraintCode == "V") {
    return InlineAsm::Constraint_v;
  }
  return TargetLowering::getInlineAsmMemConstraint(ConstraintCode);
}

unsigned CodasipGenTargetLowering::getRegisterByName(const char *RegName, EVT VT, SelectionDAG &DAG) const
{
  RcAndReg p = GetRegAndClassByName(RegName,VT);
  const unsigned reg = p.first;
  // nothing?
  if (reg==0) {
    errs() << "Register " << RegName << " doesn't exist.\n";
    report_fatal_error("Invalid register name used in global variable constraint.");
  }
  // get reserveds
  auto &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  MachineFunction &MF = DAG.getMachineFunction();
  BitVector res = CTM.getRegisterInfo()->getReservedRegs(MF);
  // warning if not reserved
  if (!res[reg]) {
    errs() << "Register " << RegName << " is not reserved but is used for register-bound global variable.\n";
  }
  return reg;
}

unsigned CodasipGenTargetLowering::getRegisterByName(const char *RegName) const
{
  RcAndReg p = GetRegAndClassByName(RegName, MVT::Other);
  // caller will check
  return p.first;
}

bool CodasipGenTargetLowering::StrCaseInsensitive::operator() (const StringRef left, const StringRef right) const
{
  return left.compare_lower(right) < 0;
}

// the type is left unused for now
// VT may be Other
// note: this can be improved further
CodasipGenTargetLowering::RcAndReg CodasipGenTargetLowering::GetRegAndClassByName(StringRef RegName, EVT VT) const
{
  auto &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const TargetRegisterInfo *TRI = CTM.getRegisterInfo();
  // c++ pair
  auto range = NameMap.equal_range(RegName);
  // nothing? (redundant)
  if (range.first == range.second)
  {
    return RcAndReg(0,nullptr);
  }
  // is other?
  if (VT != MVT::Other)
  {
    // llvm range
    auto llvmRange = make_range(range);
    // find one with corresponding type
    if (VT.isSimple())
    {
      for (const auto &item: llvmRange)
      {
        const RcAndReg &ret = item.second;
        if (TRI->isTypeLegalForClass(*ret.second, VT.getSimpleVT()))
        {
          return ret;
        }
      }
    }
    // if failed, return same width
    // note: this will just fail later - catch now?
    for (const auto& item: llvmRange)
    {
      const RcAndReg &ret = item.second;
      if (TRI->getRegSizeInBits(*ret.second))
      {
        return ret;
      }
    }
  }
  // if failed again, return the last one
  // - this was the original functionality
  // note: c++11 keeps order of insertion
  auto it = range.first;
  unsigned cnt = NameMap.count(RegName);
  std::advance(it, cnt-1);
  return it->second;
}

// Replace fake instructions with a valid machine code.
// Note: disallow Codasip::KILL in here?
MachineBasicBlock* CodasipGenTargetLowering::EmitInstrWithCustomInserter(MachineInstr &MI, MachineBasicBlock *BB) const
{
  switch (MI.getOpcode()) {
    
    case Codasip::EH_SjLj_SetJmp:
      return emitEHSjLjSetJmp(MI, BB);
    case Codasip::EH_SjLj_LongJmp:
      return emitEHSjLjLongJmp(MI, BB);
    case Codasip::EH_SJLJ_SETUP_DISPATCH:
      return emitEHSjLjDispatchBlock(MI, BB);
    
    default:
      break;
  }
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const CodasipInstrInfo &TII = *CTM.getInstrInfo();
  bool check = TII.ExpandDummiesImpl(&MI,BB,false);
  if (!check) {
    assert(false && "failed to expand pseudo instruction in EmitInstrWithCustomInserter");
    return NULL;
  }
  // result must not be an empty BB
  assert(!BB->empty());
  return BB;
}

// copyed from TargetLoweringBase.cpp
static unsigned getVectorTypeBreakdownMVT(MVT VT, MVT &IntermediateVT,
                                          unsigned &NumIntermediates,
                                          MVT &RegisterVT,
                                          TargetLoweringBase *TLI)
{
  // Figure out the right, legal destination reg to copy into.
  unsigned NumElts = VT.getVectorNumElements();
  MVT EltTy = VT.getVectorElementType();

  unsigned NumVectorRegs = 1;

  // FIXME: We don't support non-power-of-2-sized vectors for now.  Ideally we
  // could break down into LHS/RHS like LegalizeDAG does.
  if (!isPowerOf2_32(NumElts)) {
    NumVectorRegs = NumElts;
    NumElts = 1;
  }

  // Divide the input until we get to a supported size.  This will always
  // end with a scalar if the target doesn't support vectors.
  while (NumElts > 1 && !TLI->isTypeLegal(MVT::getVectorVT(EltTy, NumElts))) {
    NumElts >>= 1;
    NumVectorRegs <<= 1;
  }

  NumIntermediates = NumVectorRegs;

  MVT NewVT = MVT::getVectorVT(EltTy, NumElts);
  if (!TLI->isTypeLegal(NewVT))
    NewVT = EltTy;
  IntermediateVT = NewVT;

  unsigned NewVTSize = NewVT.getSizeInBits();

  // Convert sizes such as i33 to i64.
  if (!isPowerOf2_32(NewVTSize))
    NewVTSize = NextPowerOf2(NewVTSize);

  MVT DestVT = TLI->getRegisterType(NewVT);
  RegisterVT = DestVT;
  if (EVT(DestVT).bitsLT(NewVT))    // Value is expanded, e.g. i64 -> i16.
    return NumVectorRegs*(NewVTSize/DestVT.getSizeInBits());

  // Otherwise, promotion or legal types use the same number of registers as
  // the vector decimated to the appropriate level.
  return NumVectorRegs;
}

/* Our custom types can't be left as legal.
 * -> The previous two actions need to be repeated for customs.
 * They also need to be computed a wee bit differently.
 * Note: Every type needs to be transformed into a smaller type (of half the size ideally, but no smaller than that) */
void CodasipGenTargetLowering::computeRegisterProperties(const TargetRegisterInfo *TRI)
{
  LLVMContext Context;
  // this needs to be ran first
  TargetLowering::computeRegisterProperties(TRI);
  // this is copy-pasted from the supermethod:
  // Find the largest integer register class.
  unsigned LargestIntReg = MVT::LAST_INTEGER_VALUETYPE;
  for (; RegClassForVT[LargestIntReg] == nullptr; --LargestIntReg)
    assert(LargestIntReg != MVT::i1 && "No integer registers defined!");
  // a new implementation of properties - everything is expand
  // note: default value of TransformToType[N] = N
  for (unsigned i=MVT::FIRST_CUSTOM_INTEGER_VALUETYPE; i<=MVT::LAST_CUSTOM_INTEGER_VALUETYPE; ++i)
  {
    MVT t = (MVT::SimpleValueType)i;
    // legal
    // note: big ints are never leagal, so this won't happen
    if (isTypeLegal(t))
    {
      // leave default values
    }
    // non-legal
    else
    {
      // non-simple types are(/were) implicitly Expand - it should work like that again
      ValueTypeActions.setTypeAction(t,TypeExpandInteger);
      // like "larger than max" types in the supermethod
      // note: i256 isn't after i128 - computation needed
      MVT tMax = MVT::SimpleValueType(LargestIntReg);
      MVT tHalf = MVT::getIntegerVT(t.getSizeInBits()/2);
      RegisterTypeForVT[i] = tMax;
      TransformToType[i] = tHalf;
      NumRegistersForVT[i] = NumRegistersForVT[tHalf.SimpleTy]*2;
    }
  }
  // new vectors
  for (unsigned i=MVT::FIRST_CUSTOM_INTEGER_VECTOR_VALUETYPE; i<=MVT::LAST_CUSTOM_INTEGER_VECTOR_VALUETYPE; ++i)
  {
    //=========== copied from TargetLoweringBase.cpp, changes marked
    MVT VT = (MVT::SimpleValueType) i;
    if (isTypeLegal(VT))
      continue;

    MVT EltVT = VT.getVectorElementType();
    unsigned NElts = VT.getVectorNumElements();
    bool IsLegalWiderType = false;
    LegalizeTypeAction PreferredAction = getPreferredVectorAction(VT);
    switch (PreferredAction) {
    case TypePromoteInteger:
      // Try to promote the elements of integer vectors. If no legal
      // promotion was found, fall through to the widen-vector method.
      //                  ======== CODASIP ==================
      for (unsigned nVT = MVT::FIRST_INTEGER_VECTOR_VALUETYPE; nVT <= MVT::LAST_INTEGER_VECTOR_VALUETYPE; ++nVT) {
        MVT SVT = (MVT::SimpleValueType) nVT;
        // Promote vectors of integers to vectors with the same number
        // of elements, with a wider element type.
        if (SVT.getScalarSizeInBits() > EltVT.getSizeInBits() &&
            SVT.getVectorNumElements() == NElts && isTypeLegal(SVT)) {
          TransformToType[i] = SVT;
          RegisterTypeForVT[i] = SVT;
          NumRegistersForVT[i] = 1;
          ValueTypeActions.setTypeAction(VT, TypePromoteInteger);
          IsLegalWiderType = true;
          break;
        }
      }
      if (IsLegalWiderType)
        break;
      LLVM_FALLTHROUGH;

    case TypeWidenVector:
      // Try to widen the vector.
      //                  ======== CODASIP ==================
      for (unsigned nVT = MVT::FIRST_INTEGER_VECTOR_VALUETYPE; nVT <= MVT::LAST_VECTOR_VALUETYPE; ++nVT) {
        MVT SVT = (MVT::SimpleValueType) nVT;
        if (SVT.getVectorElementType() == EltVT
            && SVT.getVectorNumElements() > NElts && isTypeLegal(SVT)) {
          TransformToType[i] = SVT;
          RegisterTypeForVT[i] = SVT;
          NumRegistersForVT[i] = 1;
          ValueTypeActions.setTypeAction(VT, TypeWidenVector);
          IsLegalWiderType = true;
          break;
        }
      }
      if (IsLegalWiderType)
        break;
      LLVM_FALLTHROUGH;

    case TypeSplitVector:
    case TypeScalarizeVector: {
      MVT IntermediateVT;
      MVT RegisterVT;
      unsigned NumIntermediates;
      NumRegistersForVT[i] = getVectorTypeBreakdownMVT(VT, IntermediateVT,
          NumIntermediates, RegisterVT, this);
      RegisterTypeForVT[i] = RegisterVT;

      MVT NVT = VT.getPow2VectorType();
      if (NVT == VT) {
        // Type is already a power of 2.  The default action is to split.
        TransformToType[i] = MVT::Other;
        if (PreferredAction == TypeScalarizeVector)
          ValueTypeActions.setTypeAction(VT, TypeScalarizeVector);
        else if (PreferredAction == TypeSplitVector)
          ValueTypeActions.setTypeAction(VT, TypeSplitVector);
        else
          // Set type action according to the number of elements.
          ValueTypeActions.setTypeAction(VT, NElts == 1 ? TypeScalarizeVector
                                                        : TypeSplitVector);
      } else {
        TransformToType[i] = NVT;
        ValueTypeActions.setTypeAction(VT, TypeWidenVector);
      }
      break;
    }
    default:
      llvm_unreachable("Unknown vector legalization action!");
    }
    //==================================
    //assert(NumRegistersForVT[i]>0);
  }
  // we can't call the supermethod again -> copy&paste of its tail
  for (unsigned i = 0; i != MVT::LAST_VALUETYPE; ++i) {
    const TargetRegisterClass* RRC;
    uint8_t Cost;
    std::tie(RRC,Cost) = findRepresentativeClass(TRI,(MVT::SimpleValueType)i);
    RepRegClassForVT[i] = RRC;
    RepRegClassCostForVT[i] = Cost;
  }
}

const TargetRegisterClass* CodasipGenTargetLowering::getRegClassFor(MVT t, bool) const
{
  if (t==MVT::i32) return &Codasip::xpr_generalRegClass;
  if (t==MVT::i32) return &Codasip::rf_xprRegClass;
  
  errs() << "Type " << EVT(t).getEVTString() << " is not supported. Implement CodasipTargetLowering::getRegClassFor.\n";
  exit(1);
  return TargetLowering::getRegClassFor(t);
}

const TargetRegisterClass* CodasipGenTargetLowering::getRepRegClassFor(MVT t) const
{
  if (t==MVT::i32) return &Codasip::xpr_generalRegClass;
  if (t==MVT::i32) return &Codasip::rf_xprRegClass;
  
  errs() << "Type " << EVT(t).getEVTString() << " is not supported. Implement CodasipTargetLowering::getRepRegClassFor.\n";
  exit(1);
  return TargetLowering::getRepRegClassFor(t);
}

bool CodasipGenTargetLowering::getTgtMemIntrinsic(IntrinsicInfo &ret, const CallInst &inst, MachineFunction &MF, unsigned mainCode) const
{
  // is this from "inlines.h" (but not nomem)?
  if (!IsCodasipMemIntrin(mainCode))
  {
    return false;
  }
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const CodasipInstrInfo *CII = CTM.getInstrInfo();
  // use normal intrin nodes (same as nomem intrins)
  ret.opc = (inst.getType()->isVoidTy()? ISD::INTRINSIC_VOID : ISD::INTRINSIC_W_CHAIN);
  // get subcode
  assert(inst.getNumOperands());
  Value *v = inst.getOperand(0);
  assert(ConstantInt::classof(v));
  ConstantInt* c = cast<ConstantInt>(v);
  const int subcode = c->getSExtValue();
  // get instr and examine it
  BuiltinInfo bInfo = CII->GetBuiltinInfo(subcode);
  std::vector<SDValue> dummy;
  SelectionDAG *sem = GetCodasipPattern(CTM, MF, bInfo.InstrID, dummy);
  assert(ret.size==0);
  for (const SDNode &n : sem->allnodes())
  {
    if (n.getOpcode()==ISD::LOAD || n.getOpcode()==ISD::STORE)
    {
      // there's only one
      assert(ret.size==0 && "multiple memory ops");
      const MemSDNode& mn = cast<MemSDNode>(n);
      // this is correct (if the semantic is correct)
      ret.size = mn.getMemoryVT().getSizeInBits();
      ret.flags = (n.getOpcode()==ISD::LOAD ? MachineMemOperand::MOLoad : MachineMemOperand::MOStore);
      // an estimate - the information in the semantics probably says 1
      ret.align = ret.size;
      // an estimate - may be f32 instead of i32
      ret.memVT = mn.getMemoryVT();
    }
  }
  assert(ret.size && "memory op not found");
  // note: get ptrVal from IR?
  return true;
}

// for getTgtMemIntrinsic and LowerIntrinsic
struct AuxIntrinInfo
{
  /// llvm intrinsic code
  unsigned IntrOpcode;
  /// where is codasip intrinsic (sub)code?
  unsigned SubcodeIndex;
};

static AuxIntrinInfo GetAuxIntrinInfo(SDValue Op)
{
  AuxIntrinInfo ret;
  switch (Op.getOpcode())
  {
    case ISD::INTRINSIC_WO_CHAIN:
      ret.IntrOpcode = Op.getConstantOperandVal(0);
      ret.SubcodeIndex = 1;
      break;
    case ISD::INTRINSIC_VOID:
    case ISD::INTRINSIC_W_CHAIN:
      ret.IntrOpcode = Op.getConstantOperandVal(1);
      ret.SubcodeIndex = 2;
      break;
    default:
      llvm_unreachable("not an intrinsic node");
  }
  return ret;
}

SDValue CodasipGenTargetLowering::LowerIntrinsic(SDValue Op, SelectionDAG &DAG) const
{
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const CodasipInstrInfo *CII = CTM.getInstrInfo();
  MachineFunction &MF = DAG.getMachineFunction();
  // loc
  const SDLoc dl(Op);
  // for exceptions and security features
  switch (Op.getOpcode())
  {
    case ISD::INTRINSIC_WO_CHAIN:
      if (cast<ConstantSDNode>(Op.getOperand(0))->getZExtValue() == Intrinsic::eh_sjlj_lsda) {
        const TargetLowering &TLI = DAG.getTargetLoweringInfo();
        MVT PtrVT = TLI.getPointerTy(DAG.getDataLayout());
        auto &Context = MF.getMMI().getContext();
        MCSymbol *S = Context.getOrCreateSymbol(Twine("GCC_except_table") +
                                                Twine(MF.getFunctionNumber()));
        return DAG.getNode(CodasipISD::GAWrap, dl, Op.getSimpleValueType(),
                          DAG.getMCSymbol(S, PtrVT));
      }
      break;
    case ISD::INTRINSIC_VOID:
      if (Op.getNumOperands() > 1 &&
           cast<ConstantSDNode>(Op.getOperand(1))->getZExtValue() == Intrinsic::codasip_lower_jump) {
        std::vector<SDValue> Ops;
        SDVTList NodeTys = DAG.getVTList(MVT::Other,MVT::Glue);
        Ops.push_back(Op.getOperand(0));
        Ops.push_back(Op.getOperand(2));
        ArrayRef<SDValue> aref(&Ops[0],Ops.size());
        return DAG.getNode(CodasipISD::TailCall,dl,NodeTys,aref);
      }
      break;
    default: ;
  }
  // aux info
  AuxIntrinInfo auxInfo = GetAuxIntrinInfo(Op);
  // is it our builtin?
  if (!IsCodasipIntrin(auxInfo.IntrOpcode)) {
    return SDValue();
  }
  // subcode
  const int subcode = Op.getConstantOperandVal(auxInfo.SubcodeIndex);
  // get new node code and oper type info
  BuiltinInfo info = CII->GetBuiltinInfo(subcode);
  unsigned newOpc = info.NodeID;
  std::vector<MVT> inputInfo = info.InputInfo;
  // result type array
  SDVTList resTypes = Op->getVTList();
  // inputs
  std::vector<SDValue> ops;
  ops.reserve(Op.getNumOperands());
  // - chain
  if (Op.getOpcode()!=ISD::INTRINSIC_WO_CHAIN) ops.push_back(Op.getOperand(0));
  // - input data
  for (unsigned i=auxInfo.SubcodeIndex+1, j=0; i<Op.getNumOperands(); ++i, ++j)
  {
    SDValue input = Op.getOperand(i);
    // add bitcast first?
    assert(j<inputInfo.size());
    if (inputInfo[j].isFloatingPoint()) {
      input = DAG.getNode(ISD::BITCAST,dl,inputInfo[j],input);
    }
    ops.push_back(input);
  }
  ArrayRef<SDValue> opsRef(ops);
  // make result node
  // note: first valid codasip mem opcode is the one after
  if (newOpc >= CodasipISD::FIRST_TARGET_MEMORY_OPCODE)
  {
    assert(MemSDNode::classof(Op.getNode()));
    const MemSDNode *mn = cast<MemSDNode>(Op.getNode());
    // make mem node
    EVT memVT = mn->getMemoryVT();
    MachineMemOperand *MMO = mn->getMemOperand();
    return GetCodasipMemSDNode(DAG,newOpc,resTypes,opsRef,dl,memVT,MMO);
  }
  return DAG.getNode(newOpc,dl,resTypes,opsRef);
}

// custom memsd classes, they differ just by the opcode


SDValue CodasipGenTargetLowering::GetCodasipMemSDNode(SelectionDAG &DAG, int Opcode,
                                                      SDVTList VTs, ArrayRef<SDValue> Ops,
                                                      const SDLoc &dl, EVT MemVT,
                                                      MachineMemOperand *MMO) const
{
  switch (Opcode)
  {
    
    default:
      llvm_unreachable("unknown target node");
  }
  return SDValue();
}

unsigned CodasipGenTargetLowering::GetSpace4Vt(EVT vt) const
{
  return llvm::GetSpace4Vt(vt);
}

bool CodasipGenTargetLowering::isOffsetFoldingLegal(const GlobalAddressSDNode* GA) const
{
  return false;
}

// taken from SelectionDAGBuilder::visitGetElementPtr
// edits marked superficially, some left unmarked
// note: note the hardcoded i32
bool CodasipGenTargetLowering::EmittArrayAccess(SelectionDAG& DAG, const User &I, Type* indexedType, const Value* Idx, SDValue IdxN, SDValue& N, const SDLoc &dl) const
{
  
  return false;
  
  // Normalize Vector GEP - all scalar operands should be converted to the
  // splat vector.
  unsigned VectorWidth = I.getType()->isVectorTy() ?
    cast<VectorType>(I.getType())->getVectorNumElements() : 0;
  const DataLayout *DL = &getTargetMachine().getDataLayout();
  MVT PtrTy = MVT::i32;
  unsigned PtrSize = PtrTy.getSizeInBits();
  APInt ElementSize(PtrSize, DL->getTypeAllocSize(indexedType));
  // If this is a scalar constant or a splat vector of constants,
  // handle it quickly.
  const auto *CI = dyn_cast<ConstantInt>(Idx);
  if (!CI && isa<ConstantDataVector>(Idx) &&
      cast<ConstantDataVector>(Idx)->getSplatValue())
    CI = cast<ConstantInt>(cast<ConstantDataVector>(Idx)->getSplatValue());
  if (CI) {
    return false; //codasip
  }
  // N = N + Idx * ElementSize;
  //SDValue IdxN = getValue(Idx); //already in param
  if (!IdxN.getValueType().isVector() && VectorWidth) {
    MVT VT = MVT::getVectorVT(IdxN.getValueType().getSimpleVT(), VectorWidth);
    IdxN = DAG.getSplatBuildVector(VT, dl, IdxN);
  }
  // If the index is smaller or larger than <i32>, truncate or extend it.
  IdxN = DAG.getSExtOrTrunc(IdxN, dl, MVT::i32);
  // If this is a multiply by a power of two, turn it into a shl
  // immediately.  This is a very common case.
  if (ElementSize != 1) {
    if (ElementSize.isPowerOf2()) {
      unsigned Amt = ElementSize.logBase2();
      IdxN = DAG.getNode(ISD::SHL, dl, MVT::i32, IdxN, DAG.getConstant(Amt, dl, IdxN.getValueType())); //codasip
    } else {
      SDValue Scale = DAG.getConstant(ElementSize, dl, IdxN.getValueType());
      IdxN = DAG.getNode(ISD::MUL, dl, MVT::i32, IdxN, Scale); //codasip
    }
  }
  IdxN = DAG.getSExtOrTrunc(IdxN, dl, N.getValueType()); //codasip
  N = DAG.getNode(ISD::ADD, dl, N.getValueType(), N, IdxN);
  return true;
}

std::pair<SDValue,SDValue> CodasipGenTargetLowering::ExpandCustomUnalignedLoad(LoadSDNode* LD, SelectionDAG& DAG) const
{
  EVT LoadedVT = LD->getMemoryVT();
  if (LoadedVT.isOriginal()) {
    return std::make_pair(SDValue(),SDValue());
  }
  
  errs() << "Unaligned packed custom int load: not implemented for little-endians\n";
  abort();
  
  SDLoc dl(LD);
  unsigned NumBits = LoadedVT.getSizeInBits();
  SDValue Chain = LD->getChain();
  SDValue Ptr = LD->getBasePtr();
  EVT VT = LD->getValueType(0);
  const unsigned BYTE_SIZE = 8;
  EVT NewLoadedVT = EVT::getIntegerVT(*DAG.getContext(), BYTE_SIZE);
  SDValue ShiftAmount = DAG.getConstant(BYTE_SIZE, dl, getShiftAmountTy(VT, DAG.getDataLayout()));
  ISD::LoadExtType HiExtType = LD->getExtensionType();
  if (HiExtType == ISD::NON_EXTLOAD) HiExtType = ISD::ZEXTLOAD;
  SmallVector<SDValue, 8> Ops;
  // the NumBits again
  NumBits = LoadedVT.getSizeInBits();
  SDValue Result;
  for (unsigned i=0; i*BYTE_SIZE < NumBits; ++i)
  {
    ISD::LoadExtType ExtType = (i? HiExtType: ISD::ZEXTLOAD);
    SDValue load = DAG.getExtLoad(ExtType, dl, VT, Chain, Ptr, LD->getPointerInfo().getWithOffset(i), NewLoadedVT, BYTE_SIZE, LD->getMemOperand()->getFlags(), LD->getAAInfo());
    Ops.push_back(load.getValue(1));
    if (i) {
      Result = DAG.getNode(ISD::SHL, dl, VT, Result, ShiftAmount);
      Result = DAG.getNode(ISD::OR, dl, VT, Result, load);
    }
    else {
      Result = load;
    }
    Ptr = DAG.getNode(ISD::ADD, dl, Ptr.getValueType(), Ptr, DAG.getConstant(1, dl, Ptr.getValueType()));
  }
  SDValue TF = DAG.getNode(ISD::TokenFactor, dl, MVT::Other, Ops);
  return std::make_pair(Result, TF);
}

SDValue CodasipGenTargetLowering::ExpandCustomUnalignedStore(StoreSDNode* ST, SelectionDAG& DAG) const
{
  EVT StoredVT = ST->getMemoryVT();
  if (StoredVT.isOriginal()) {
    return SDValue();
  }
  
  errs() << "Unaligned packed custom int store: not implemented for little-endians\n";
  abort();
  
  SDLoc dl(ST);
  SDValue Chain = ST->getChain();
  SDValue Ptr = ST->getBasePtr();
  SDValue Val = ST->getValue();
  EVT VT = Val.getValueType();
  int Alignment = ST->getAlignment();
  unsigned NumBits = StoredVT.getSizeInBits();
  const unsigned BYTE_SIZE = 8;
  EVT NewStoredVT = EVT::getIntegerVT(*DAG.getContext(), BYTE_SIZE);
  SmallVector<SDValue, 8> Ops;
  unsigned NumBytes = NumBits/BYTE_SIZE;
  if (NumBits%BYTE_SIZE) ++NumBytes;
  // the NumBits again
  NumBits = StoredVT.getSizeInBits();
  for (unsigned i=0; i*BYTE_SIZE < NumBits; ++i)
  {
    SDValue ShiftAmount = DAG.getConstant((NumBytes-i-1)*BYTE_SIZE, dl, getShiftAmountTy(VT, DAG.getDataLayout()));
    SDValue Value = DAG.getNode(ISD::SRL, dl, VT, Val, ShiftAmount);
    SDValue store = DAG.getTruncStore(Chain, dl, Value, Ptr, ST->getPointerInfo().getWithOffset(i), NewStoredVT, Alignment, ST->getMemOperand()->getFlags());
    Ops.push_back(store);
    Ptr = DAG.getNode(ISD::ADD, dl, Ptr.getValueType(), Ptr, DAG.getConstant(1, dl, Ptr.getValueType()));
  }
  return DAG.getNode(ISD::TokenFactor, dl, MVT::Other, Ops);
}

void CodasipGenTargetLowering::InitIndOffsetInfo()
{
IndOffsetInfo[0].at(ISD::PRE_INC).fill(false);
IndOffsetInfo[0].at(ISD::PRE_DEC).fill(false);
IndOffsetInfo[0].at(ISD::POST_INC).fill(false);
IndOffsetInfo[0].at(ISD::POST_DEC).fill(false);
IndOffsetInfo[1].at(ISD::PRE_INC).fill(false);
IndOffsetInfo[1].at(ISD::PRE_DEC).fill(false);
IndOffsetInfo[1].at(ISD::POST_INC).fill(false);
IndOffsetInfo[1].at(ISD::POST_DEC).fill(false);


}

// it's just like with MOI groups
// returns true, if supports any input
bool CodasipGenTargetLowering::CheckIndexedOffsetLegal(
    LSBaseSDNode *N, const ISD::MemIndexedMode AM, const SDValue &Offset,
    MachineFunction &MF) const {
  EVT Vt = N->getMemoryVT();
  MVT Mvt = Vt.getSimpleVT();
  // it's either load or store (checked in CheckIndexedLegal already)
  const unsigned Load = (N->getOpcode() == ISD::LOAD ? 1 : 0);
  if (IndOffsetInfo[Load].at(AM).at(Mvt.SimpleTy)) {
    return true;
  }
  // check of operand types from moi lowerer
  const std::vector<unsigned> &Patts = IndInstructionsMap[Load].at(AM);
  SDValue PattOffset;
  SDNode *MemNode = nullptr;
  for (const unsigned CandidateOpcode : Patts) {
    SelectionDAG *Dag = nullptr;
    {
      std::vector<SDValue> Roots;
      Dag = GetCodasipPattern(TM, MF, CandidateOpcode, Roots);
    }
    // get memnode (there can be only one)
    for (SDNode &Node : Dag->allnodes()) {
      if (Node.getOpcode() == ISD::LOAD || Node.getOpcode() == ISD::STORE) {
        MemNode = &Node;
        break;
      }
    }
    // shouldn't happen
    if (MemNode == nullptr) {
      return false;
    }
    // if we create this indexed load/store, can we then match it in isel?
    // doesn't it have to be truncstore or extendload? This checks it
    if (MemNode->getOpcode() == ISD::LOAD) {
      LoadSDNode *realNode = cast<LoadSDNode>(N);
      LoadSDNode *pattNode = cast<LoadSDNode>(MemNode);
      if (realNode->getExtensionType() != pattNode->getExtensionType())
        continue;
    } else if (MemNode->getOpcode() == ISD::STORE) {
      StoreSDNode *PattNode = cast<StoreSDNode>(MemNode);
      StoreSDNode *RealNode = cast<StoreSDNode>(N);
      if (PattNode->isTruncatingStore() != RealNode->isTruncatingStore() ||
          PattNode->getMemoryVT().getSimpleVT() !=
              RealNode->getMemoryVT().getSimpleVT())
        continue;
    } else {
      assert(false && "neither store nor load node");
    }
    PattOffset = cast<LSBaseSDNode>(MemNode)->getOffset();
    // for now check that both offset nodes are leafs and are of compatible type
    const CodasipTargetMachine &CTM =
        static_cast<const CodasipTargetMachine &>(this->getTargetMachine());
    const TargetRegisterInfo *TRI = CTM.getRegisterInfo();
    const CodasipInstrInfo *CII = CTM.getInstrInfo();
    const unsigned InstrOffsetOpcode = PattOffset->getOpcode();
    const unsigned RealOffsetOpcode = Offset->getOpcode();
    // for now we suppose instruction has constant or register operand
    const bool InstrOffsetIsLeaf = (InstrOffsetOpcode == ISD::Register ||
                                    InstrOffsetOpcode == ISD::Constant);
    // program contains constant offset...
    const bool RealOffsetIsLeaf = RealOffsetOpcode == ISD::Constant;
    // if some offset node is not leaf just continue
    if (!InstrOffsetIsLeaf || !RealOffsetIsLeaf) {
      continue;
    }
    // ok both offsets are leafs...
    // there is constant in program, get its value
    const int64_t ConstRealOffsetValue =
        cast<ConstantSDNode>(Offset)->getSExtValue();
    // check if instruction contains constant
    if (InstrOffsetOpcode == ISD::Constant) {
      // yes, it just has to be the same as in-program constant
      const int64_t ConstInstrOffsetValue =
          cast<ConstantSDNode>(PattOffset)->getSExtValue();
      if (ConstRealOffsetValue == ConstInstrOffsetValue) {
        return true;
      } else {
        continue;
      }
    }
    // check if instruction has register operand. It might be immediate, virtual
    // or physical register
    if (InstrOffsetOpcode == ISD::Register) {
      // check register operand type
      const RegisterSDNode *RegInstrOffset = cast<RegisterSDNode>(PattOffset);
      unsigned RegNumber = RegInstrOffset->getReg();
      bool IsPhysicalRegister = TRI->isPhysicalRegister(RegNumber);
      if (IsPhysicalRegister) {
        // this won't happen, this case should have been already matched
        return true;
      }
      // get instruction description
      const MCInstrDesc &InstrDescription = CII->get(CandidateOpcode);
      // convert virtual register number to operand index
      unsigned OperandIndex = TRI->virtReg2Index(RegNumber);
      // better check its validity
      assert(InstrDescription.getNumOperands() > OperandIndex &&
             "Illegal operand index.");
      // get operand info
      const MCOperandInfo &InstrOperandInfo =
          InstrDescription.OpInfo[OperandIndex];
      // check register type
      if (InstrOperandInfo.OperandType == MCOI::OperandType::OPERAND_REGISTER) {
        // again, this won't happen, register operand should have been matched
        return true;
      } else if (InstrOperandInfo.OperandType ==
                 MCOI::OperandType::OPERAND_IMMEDIATE) {
        // this case is expected, operand is immediate, check that program
        // constant fits into it prepare outputs
        int ImmWidth = -1;
        bool ImmSigned = false;
        int ImmTrunc = -1;
        // read instruction immediate operand properties
        CII->GetImmProperties(CandidateOpcode, OperandIndex, ImmWidth,
                              ImmSigned, ImmTrunc);
        // check that value fits into immediate
        bool ValueFits = CheckImmImpl(ConstRealOffsetValue, ImmWidth, ImmSigned,
                                      ImmTrunc);
        if (ValueFits) {
          return true;
        } else {
          continue;
        }
      } else {
        continue;
      }
    }
    // TBD - check general pattern match
    // bool match = BaseDagPattern::CheckTree(PattOffset, Offset);
    // if (match)
    // {
    //   return true;
    // }
  }
  return false;
}

// this checks coarse grained legality and address space
bool CodasipGenTargetLowering::CheckIndexedLegal(LSBaseSDNode* N, ISD::MemIndexedMode AM) const
{
  EVT vt = N->getMemoryVT();
  if (N->getOpcode()==ISD::LOAD)
  {
    if (!isIndexedLoadLegal(AM,vt))
    {
      return false;
    }
  }
  else if (N->getOpcode()==ISD::STORE)
  {
    if (!isIndexedStoreLegal(AM,vt))
    {
      return false;
    }
  }
  else
  {
    llvm_unreachable("Neither a load nor a store");
  }
  
  // all ok
  return true;
}

bool CodasipGenTargetLowering::getPreIndexedAddressParts(SDNode* Node, SDValue& BasePtr, SDValue& Offset, ISD::MemIndexedMode& AM, SelectionDAG& DAG) const
{
  LSBaseSDNode* lsb = dyn_cast<LSBaseSDNode>(Node);
  assert(lsb && lsb->isUnindexed() && "not an unindexed mem op");
  // look at the ptr
  SDValue ptr = lsb->getBasePtr();
  assert(ptr.getOpcode()==ISD::ADD || ptr.getOpcode()==ISD::SUB);
  AM = (ptr.getOpcode()==ISD::ADD? ISD::PRE_INC: ISD::PRE_DEC);
  // check legality
  // (this is neccessary, llvm doesn't differentiate between INC and DEC)
  if (!CheckIndexedLegal(lsb,AM)) {
    return false;
  }
  // mark inputs
  assert(ptr.getNumOperands()==2);
  BasePtr = ptr.getOperand(0);
  Offset  = ptr.getOperand(1);
  bool swaped = false;
  if (isa<ConstantSDNode>(BasePtr) && !isa<ConstantSDNode>(Offset)) {
    std::swap(BasePtr, Offset);
    swaped = true;
  }
  // one last check
  if (!CheckIndexedOffsetLegal(lsb,AM,Offset,DAG.getMachineFunction())) {
    return false;
  }
  // llvm also swaps it
  if (swaped) {
    std::swap(BasePtr, Offset);
  }
  // all ok
  return true;
}

bool CodasipGenTargetLowering::getPostIndexedAddressParts(SDNode* Node, SDNode* Op, SDValue& BasePtr, SDValue& Offset, ISD::MemIndexedMode& AM, SelectionDAG& DAG) const
{
  LSBaseSDNode* lsb = dyn_cast<LSBaseSDNode>(Node);
  assert(lsb && lsb->isUnindexed() && "not an unindexed mem op");
  // the ptr
  SDValue ptr = lsb->getBasePtr();
  // look at the operator
  assert(Op->getNumOperands()==2);
  assert(Op->getOpcode()==ISD::ADD || Op->getOpcode()==ISD::SUB);
  AM = (Op->getOpcode()==ISD::ADD? ISD::POST_INC: ISD::POST_DEC);
  // check legality
  if (!CheckIndexedLegal(lsb,AM)) {
    return false;
  }
  // mark inputs
  BasePtr = ptr;
  if (Op->getOperand(0)==ptr) {
    Offset = Op->getOperand(1);
  }
  else if (Op->getOperand(1)==ptr) {
    Offset = Op->getOperand(0);
  }
  else {
    return false;
  }    
  if (!CheckIndexedOffsetLegal(lsb,AM,Offset,DAG.getMachineFunction())) {
    return false;
  }
  // all ok
  return true;
}

// note: supermethod just returns true
bool CodasipGenTargetLowering::canMergeStoresTo(unsigned AS, EVT MemVT, const SelectionDAG&) const
{
  // nothing bigger than i64 (would cause an assert later)
  if (MemVT.getSizeInBits() > 64) {
    return false;
  }
  // address spaces
  unsigned AS2 = GetSpace4Vt(MemVT);
  return AS==AS2;
}

// note: t is scalar integer
MVT CodasipGenTargetLowering::getScalarShiftAmountTy(const DataLayout &DL, EVT t) const
{
  /*if (t.isSimple()) {
    return t.getSimpleVT();
  }*/
  return TargetLowering::getScalarShiftAmountTy(DL,t);
}

bool CodasipGenTargetLowering::isLegalAddressingMode(const DataLayout &DL,
    const AddrMode &AM,
    Type *Ty,
    unsigned AS,
    Instruction *I) const
{
  bool def = TargetLoweringBase::isLegalAddressingMode(DL,AM,Ty,AS,I);
  if (!def) return false;
  
  if (AM.BaseOffs <= -(1LL << 12) || AM.BaseOffs >= (1LL << 12)-1) {
    return false;
  }
  
  // all checks ok
  return true;
}

bool CodasipGenTargetLowering::isLegalICmpImmediate(int64_t imm) const
{
  return !( imm <= -(1LL << 12) || imm >= (1LL << 12)-1 );
}

bool CodasipGenTargetLowering::isLegalAddImmediate(int64_t imm) const
{
  return !( imm <= -(1LL << 12) || imm >= (1LL << 12)-1 );
}

bool CodasipGenTargetLowering::isZExtFree(SDValue Val, EVT VT2) const
{
  // Zexts are free if they can be combined with a load.
  if (Val.getOpcode() != ISD::LOAD) return false;
  auto* LD = dyn_cast<LoadSDNode>(Val);
  assert(LD);
  EVT MemVT = LD->getMemoryVT();
  return getLoadExtAction(ISD::ZEXTLOAD,VT2,MemVT)==Legal;
}

bool CodasipGenTargetLowering::enableAggressiveFMAFusion(EVT VT) const
{
  return isOperationLegal(ISD::FMA,VT);
}

bool CodasipGenTargetLowering::isFMAFasterThanFMulAndFAdd(EVT VT) const
{
  return enableAggressiveFMAFusion(VT);
}


void CodasipGenTargetLowering::EmitEssentialLoad(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL,
                                                 const CodasipInstrInfo &CII, unsigned Dst, unsigned Src, int64_t Imm) const
{
  SmallVector<MachineOperand,3> ops;

  MachineOperand InstrDst = MachineOperand::CreateReg(Dst, true);
  MachineOperand InstrSrc = MachineOperand::CreateReg(Src, false);
  MachineOperand InstrVal = MachineOperand::CreateImm(Imm);
  ops.push_back(InstrDst);
  ops.push_back(InstrSrc);
  ops.push_back(InstrVal);
  CII.EmitEssentialInstr(MBB, MBBI, DL, ISD::LOAD, ops);
  ops.clear();
}

void CodasipGenTargetLowering::EmitEssentialStore(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL,
                                                 const CodasipInstrInfo &CII, unsigned Data, unsigned Addr, int64_t Imm) const
{
  SmallVector<MachineOperand,3> ops;

  MachineOperand InstrData = MachineOperand::CreateReg(Data, false);
  MachineOperand InstrAddr = MachineOperand::CreateReg(Addr, false);
  MachineOperand InstrVal = MachineOperand::CreateImm(Imm);
  ops.push_back(InstrData);
  ops.push_back(InstrAddr);
  ops.push_back(InstrVal);
  CII.EmitEssentialInstr(MBB, MBBI, DL, ISD::STORE, ops);
  ops.clear();
}

void CodasipGenTargetLowering::EmitEssentialAdd(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL,
                                                 const CodasipInstrInfo &CII, unsigned Dst, unsigned Src, unsigned Src2) const
{
  SmallVector<MachineOperand,3> ops;

  MachineOperand InstrDst = MachineOperand::CreateReg(Dst, true);
  MachineOperand InstrSrc = MachineOperand::CreateReg(Src, false);
  MachineOperand InstrSrc2 = MachineOperand::CreateReg(Src2, false);
  ops.push_back(InstrDst);
  ops.push_back(InstrSrc);
  ops.push_back(InstrSrc2);
  CII.EmitEssentialInstr(MBB, MBBI, DL, ISD::ADD, ops);
  ops.clear();
}

void CodasipGenTargetLowering::EmitIndirectJump(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL,
                                                  const CodasipTargetMachine &CTM, unsigned Target) const
{
  const CodasipInstrInfo &TII = *CTM.getInstrInfo();
  const CodasipInstrInfo &CII = static_cast<const CodasipInstrInfo&>(TII);
  MVT PVT = getPointerTy(MBB.getParent()->getDataLayout());
  const int RCId = (int)getRegClassFor(PVT)->getID();
  
  std::vector<int> JmpOps;
  CII.getCodasipInstr(JmpOps, ISD::BRIND, getPointerTy(MBB.getParent()->getDataLayout()));
  for (std::vector<int>::iterator it = JmpOps.begin(); it != JmpOps.end(); ++it) {
    const MCInstrDesc &JumpOp = TII.get(*it);
    if (JumpOp.getNumOperands() == 1) {
      BuildMI(MBB, MBBI, DL, JumpOp).addReg(Target);
      return;
    }
    if (JumpOp.getNumOperands() == 2 && JumpOp.OpInfo[0].OperandType == MCOI::OPERAND_IMMEDIATE
      && JumpOp.OpInfo[1].RegClass == RCId) {
      BuildMI(MBB, MBBI, DL, JumpOp)
        .addReg(Target)
        .addImm(0);
      return;
    }
  }
  llvm_unreachable("Unknown Indirect jump!");
}

void CodasipGenTargetLowering::EmitLoad32(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL, unsigned Target, int Source, int Imm, bool FI) const
{
  MachineFunction *MF = MBB.getParent();
  MachineRegisterInfo *MRI = &MF->getRegInfo();
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const CodasipInstrInfo &TII = *CTM.getInstrInfo();
  const CodasipInstrInfo &CII = static_cast<const CodasipInstrInfo&>(TII);
  const TargetRegisterInfo *TRI = CTM.getRegisterInfo();

  MVT PVT = getPointerTy(MF->getDataLayout());
  const TargetRegisterClass *RC = getRegClassFor(PVT);

  if (PVT == MVT::i64) {
    const TargetRegisterClass* RC32 = getRegClassFor(MVT::i32);
    unsigned IReg32 = MRI->createVirtualRegister(RC32);
    std::vector<int> LoadOps;
    CII.getCodasipInstr(LoadOps, ISD::LOAD, MVT::i32);
    for (std::vector<int>::iterator it = LoadOps.begin(); it != LoadOps.end(); ++it) {
      const MCInstrDesc &LoadOp = TII.get(*it);
      if (LoadOp.OpInfo[2].OperandType == MCOI::OPERAND_IMMEDIATE && LoadOp.OpInfo[0].RegClass == (int)RC32->getID()) {
        MachineInstrBuilder MIB = BuildMI(MBB, MBBI, DL, LoadOp, IReg32);
        if (FI)
          MIB.addFrameIndex(Source);  
        else
          MIB.addReg(Source);
        MIB.addImm(Imm);
        
        SuperRegClassIterator RCI(MRI->getRegClass(IReg32), TRI);
        assert(RCI.isValid());
        unsigned superRegIdx = RCI.getSubReg();
        
        BuildMI(MBB, MBBI, DL, TII.get(TargetOpcode::SUBREG_TO_REG), Target)
          .addImm(0)
          .addReg(IReg32)
          .addImm(superRegIdx);
        return;
      }
    }
    llvm_unreachable("Unknown loadw variant, there should be rf32 = loadw fi, imm!");
  } else {
    if (FI) {
      unsigned Tmp = MRI->createVirtualRegister(RC);
      EmitEssentialLoad(MBB, MBB.end(), DL, CII, Target, Tmp, Imm);
      for (auto it =  MBB.instr_back().operands_end() ; it !=  MBB.instr_back().operands_begin() + 1; ) {
          MBB.instr_back().RemoveOperand(MBB.instr_back().getOperandNo(--it));
      }
      MBB.instr_back().addOperand(MachineOperand::CreateFI(Source));
      MBB.instr_back().addOperand(MachineOperand::CreateImm(Imm));
      return;
    }
    EmitEssentialLoad(MBB, MBB.end(), DL, CII, Target, Source, Imm);
  }
}

void CodasipGenTargetLowering::EmitLoadImm32(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL, unsigned Dst, int Imm) const
{
  MachineFunction *MF = MBB.getParent();
  MachineRegisterInfo *MRI = &MF->getRegInfo();
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const CodasipInstrInfo &TII = *CTM.getInstrInfo();
  const TargetRegisterInfo *TRI = CTM.getRegisterInfo();
  MVT PVT = getPointerTy(MF->getDataLayout());

  if (PVT == MVT::i64) {
    const TargetRegisterClass *RC = getRegClassFor(PVT);
    unsigned Dst64 = MRI->createVirtualRegister(RC);
    
    SuperRegClassIterator RCI(MRI->getRegClass(Dst), TRI);
    assert(RCI.isValid());
    unsigned superRegIdx = RCI.getSubReg();
    
    BuildMI(MBB, MBBI, DL, TII.get(Codasip::e_movi32__), Dst64).addImm(Imm);
    BuildMI(MBB, MBBI, DL, TII.get(TargetOpcode::EXTRACT_SUBREG), Dst)
              .addReg(Dst64)
              .addImm(superRegIdx);
  } else {
    BuildMI(MBB, MBBI, DL, TII.get(Codasip::e_movi32__), Dst).addImm(Imm);
  }
}

// Based on PowerPC
MachineBasicBlock *CodasipGenTargetLowering::emitEHSjLjLongJmp(MachineInstr &MI, MachineBasicBlock *MBB) const
{
  DebugLoc dl = MI.getDebugLoc();
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const CodasipInstrInfo &TII = *CTM.getInstrInfo();
  const CodasipInstrInfo &CII = static_cast<const CodasipInstrInfo&>(TII);


  MachineFunction *MF = MBB->getParent();
  MachineRegisterInfo &MRI = MF->getRegInfo();

  MVT PVT = getPointerTy(MF->getDataLayout());
  assert((PVT == MVT::i64 || PVT == MVT::i32) &&
          "Invalid Pointer Size!");

  const TargetRegisterClass *RC = getRegClassFor(PVT);

  unsigned IP = MRI.createVirtualRegister(RC);
  unsigned FP = TII.getRegisterInfo().GetBP(0);
  unsigned SP  = TII.getRegisterInfo().GetSP(0);

  const int64_t LabelOffset = 1 * PVT.getStoreSize();
  const int64_t SPOffset    = 2 * PVT.getStoreSize();

  unsigned BufReg = MI.getOperand(0).getReg();
  // Reload FP (the jumped-to function may not have had a
  // frame pointer, and if so, then its r31 will be restored
  // as necessary).
  EmitEssentialLoad(*MBB, MI.getIterator(), dl, CII, FP, BufReg, 0);

  // Reload IP
  EmitEssentialLoad(*MBB, MI.getIterator(), dl, CII, IP, BufReg, LabelOffset);
  // Reload SP
  EmitEssentialLoad(*MBB, MI.getIterator(), dl, CII, SP, BufReg, SPOffset);

  // Jump
  EmitIndirectJump(*MBB, MI.getIterator(), dl, CTM, IP);

  MI.eraseFromParent();
  return MBB;
}

MachineBasicBlock *CodasipGenTargetLowering::emitEHSjLjSetJmp(MachineInstr &MI, MachineBasicBlock *MBB) const
{
  DebugLoc dl = MI.getDebugLoc();
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const CodasipInstrInfo &TII = *CTM.getInstrInfo();
  const TargetRegisterInfo *TRI = CTM.getRegisterInfo();

  const CodasipInstrInfo &CII = static_cast<const CodasipInstrInfo&>(TII);

  MachineFunction *MF = MBB->getParent();
  MachineRegisterInfo &MRI = MF->getRegInfo();

  const BasicBlock *BB = MBB->getBasicBlock();
  MachineFunction::iterator I = ++MBB->getIterator();

  unsigned DstReg = MI.getOperand(0).getReg();
  const TargetRegisterClass *RC = MRI.getRegClass(DstReg);
  assert(TRI->isTypeLegalForClass(*RC, MVT::i32) && "Invalid destination!");
  unsigned mainDstReg = MRI.createVirtualRegister(RC);
  unsigned restoreDstReg = MRI.createVirtualRegister(RC);

  MVT PVT = getPointerTy(MF->getDataLayout());
  assert((PVT == MVT::i64 || PVT == MVT::i32) &&
	     "Invalid Pointer Size!");
  // For v = setjmp(buf), we generate
  //
  // thisMBB:
  //  SjLjSetup mainMBB
  //  bl mainMBB
  //  v_restore = 1
  //  b sinkMBB
  //
  // mainMBB:
  //  buf[LabelOffset] = LR
  //  v_main = 0
  //
  // sinkMBB:
  //  v = phi(main, restore)
  //

  MachineBasicBlock *thisMBB = MBB;
  MachineBasicBlock *mainMBB = MF->CreateMachineBasicBlock(BB);
  mainMBB->setIsEHPad(true);
  mainMBB->setHasAddressTaken();
  MachineBasicBlock *sinkMBB = MF->CreateMachineBasicBlock(BB);
  
  MF->insert(I, mainMBB);
  MF->insert(I, sinkMBB);

  MachineInstrBuilder MIB;

  // Transfer the remainder of BB and its successor edges to sinkMBB.
  sinkMBB->splice(sinkMBB->begin(), MBB,
				  std::next(MachineBasicBlock::iterator(MI)), MBB->end());
  sinkMBB->transferSuccessorsAndUpdatePHIs(MBB);

  // Note that the structure of the jmp_buf used here is not compatible
  // with that used by libc, and is not designed to be. Specifically, it
  // stores only those 'reserved' registers that LLVM does not otherwise
  // understand how to spill. Also, by convention, by the time this
  // intrinsic is called, Clang has already stored the frame address in the
  // first slot of the buffer and stack address in the third. Following the
  // X86 target code, we'll store the jump address in the second slot. We also
  // need to save the TOC pointer (R2) to handle jumps between shared
  // libraries, and that will be stored in the fourth slot. The thread
  // identifier (R13) is not affected.

  // thisMBB:
  const int64_t LabelOffset = 1 * PVT.getStoreSize();

  // Prepare IP either in reg.
  unsigned LabelReg = TII.getRegisterInfo().getRARegister();
  unsigned BufReg = MI.getOperand(1).getReg();

  // Setup
  //FIXME: Jump + getNoPreservedMask
  std::vector<int> JmpOps;
  CII.getCodasipInstr(JmpOps, CodasipBaseISD::Call, PVT);
  for (std::vector<int>::iterator it = JmpOps.begin(); it != JmpOps.end(); ++it) {
    const MCInstrDesc &JumpOp = TII.get(*it);
    if (JumpOp.OpInfo[0].OperandType == MCOI::OPERAND_IMMEDIATE) {
      MIB = BuildMI(*thisMBB, MI, dl, JumpOp);
      break;
    } 
  }
  assert((MIB.getInstr() != nullptr) && "There is no valid call instruction");

  for (auto it = MIB.getInstr()->operands_end() ; it != MIB.getInstr()->operands_begin(); ) {
      MIB.getInstr()->RemoveOperand(MIB.getInstr()->getOperandNo(--it));
  }

  MIB.addMBB(mainMBB);
  MIB.getInstr()->addRegisterDefined(LabelReg, TRI);
  MIB.addRegMask(TRI->getNoPreservedMask());
  MF->getFrameInfo().setHasCalls(true);

  EmitLoadImm32(*thisMBB, MI, dl, restoreDstReg, 1);

  BuildMI(*thisMBB, MI, dl, TII.get(getLongJumpOpcodeStatic())).addMBB(sinkMBB);

  thisMBB->addSuccessor(mainMBB, BranchProbability::getZero());
  thisMBB->addSuccessor(sinkMBB, BranchProbability::getOne());

  mainMBB->addLiveIn(LabelReg);
  // Store IP
  EmitEssentialStore(*mainMBB, mainMBB->begin(), dl, CII, LabelReg, BufReg, LabelOffset);
  EmitLoadImm32(*mainMBB, mainMBB->end(), dl, mainDstReg, 0);

  mainMBB->addSuccessor(sinkMBB);
  // sinkMBB:
  BuildMI(*sinkMBB, sinkMBB->begin(), dl,
		  TII.get(Codasip::PHI), DstReg)
    .addReg(mainDstReg).addMBB(mainMBB)
    .addReg(restoreDstReg).addMBB(thisMBB);

  MI.eraseFromParent();
  return sinkMBB;
}


const MCExpr *
CodasipGenTargetLowering::LowerCustomJumpTableEntry(const MachineJumpTableInfo *MJTI,
                                                    const MachineBasicBlock *MBB,
                                                    unsigned uid,MCContext &Ctx) const
{
  assert(isPositionIndependent());
  // In 32-bit ELF systems, our jump table entries are formed with @GOTOFF
  // entries.
  return MCSymbolRefExpr::create(MBB->getSymbol(), MCSymbolRefExpr::VK_GOTOFF, Ctx);
}


/// Return the entry encoding for a jump table in the
/// current function.  The returned value is a member of the
/// MachineJumpTableInfo::JTEntryKind enum.
unsigned CodasipGenTargetLowering::getJumpTableEncoding() const {
  return TargetLowering::getJumpTableEncoding();
}

void CodasipGenTargetLowering::SetupEntryBlockForSjLj(MachineInstr &MI,
                                                      MachineBasicBlock *MBB,
                                                      MachineBasicBlock *DispatchBB,
                                                      int FI) const
{
  DebugLoc DL = MI.getDebugLoc();
  MachineFunction *MF = MBB->getParent();
  MachineRegisterInfo *MRI = &MF->getRegInfo();
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const TargetInstrInfo &TII = *CTM.getInstrInfo();
  const CodasipInstrInfo &CII = static_cast<const CodasipInstrInfo&>(TII);

  MVT PVT = getPointerTy(MF->getDataLayout());
  assert((PVT == MVT::i64 || PVT == MVT::i32) && "Invalid Pointer Size!");
  const TargetRegisterClass *RC = getRegClassFor(PVT);
  unsigned VR = MRI->createVirtualRegister(RC);
  unsigned Tmp = MRI->createVirtualRegister(RC);
  // Offset points to jbuf in SjLj_Function_Context structure
  // https://opensource.apple.com/source/gcc_jaguar/gcc_jaguar-1257/gcc/unwind-sjlj.c.auto.html
  unsigned Imm = getPointerTy(MF->getDataLayout()) == MVT::i64 ? 56 : 36;
  BuildMI(*MBB, MI, DL, TII.get(Codasip::e_movi32__), VR)
      .addMBB(DispatchBB);
  EmitEssentialStore(*MBB, MI, DL, CII, VR, Tmp, Imm);
  
  MachineBasicBlock::iterator StoreInstr = std::prev(MachineBasicBlock::iterator(MI));
  for (auto it =  StoreInstr->operands_end(); it !=  StoreInstr->operands_begin()+1; ) {
       StoreInstr->RemoveOperand(StoreInstr->getOperandNo(--it));
  }
  StoreInstr->addOperand(MachineOperand::CreateFI(FI));
  StoreInstr->addOperand(MachineOperand::CreateImm(Imm));
}

MachineBasicBlock *CodasipGenTargetLowering::emitEHSjLjDispatchBlock(MachineInstr &MI,
                                                                     MachineBasicBlock *BB) const
{
  DebugLoc dl = MI.getDebugLoc();
  MachineFunction *MF = BB->getParent();
  MachineFrameInfo &MFI = MF->getFrameInfo();
  MachineRegisterInfo *MRI = &MF->getRegInfo();
  const CodasipTargetMachine &CTM = static_cast<const CodasipTargetMachine&>(getTargetMachine());
  const CodasipInstrInfo &TII = *CTM.getInstrInfo();
  const CodasipInstrInfo &CII = static_cast<const CodasipInstrInfo&>(TII);
  int FI = MFI.getFunctionContextIndex();
  MVT PVT = getPointerTy(MF->getDataLayout());
  const int RCId = (int)getRegClassFor(PVT)->getID();

  assert((PVT == MVT::i64 || PVT == MVT::i32) && "Invalid Pointer Size!");
  const TargetRegisterClass *RC = getRegClassFor(PVT);

  // Get a mapping of the call site numbers to all of the landing pads they're
  // associated with.
  DenseMap<unsigned, SmallVector<MachineBasicBlock *, 2>> CallSiteNumToLPad;
  unsigned MaxCSNum = 0;
  for (auto &MBB : *MF) {
    if (!MBB.isEHPad())
      continue;

    MCSymbol *Sym = nullptr;
    for (const auto &MI : MBB) {
      if (MI.isDebugInstr())
        continue;

      assert(MI.isEHLabel() && "expected EH_LABEL");
      Sym = MI.getOperand(0).getMCSymbol();
      break;
    }

    if (!MF->hasCallSiteLandingPad(Sym))
      continue;

    for (unsigned CSI : MF->getCallSiteLandingPad(Sym)) {
      CallSiteNumToLPad[CSI].push_back(&MBB);
      MaxCSNum = std::max(MaxCSNum, CSI);
    }
  }

  // Get an ordered list of the machine basic blocks for the jump table.
  std::vector<MachineBasicBlock *> LPadList;
  SmallPtrSet<MachineBasicBlock *, 32> InvokeBBs;
  LPadList.reserve(CallSiteNumToLPad.size());

  for (unsigned CSI = 1; CSI <= MaxCSNum; ++CSI) {
    for (auto &LP : CallSiteNumToLPad[CSI]) {
      LPadList.push_back(LP);
      InvokeBBs.insert(LP->pred_begin(), LP->pred_end());
    }
  }

  assert(!LPadList.empty() &&
         "No landing pad destinations for the dispatch jump table!");

  // Create the MBBs for the dispatch code.

  // Shove the dispatch's address into the return slot in the function context.
  MachineBasicBlock *DispatchBB = MF->CreateMachineBasicBlock(BB->getBasicBlock());
  DispatchBB->setIsEHPad(true);

  MachineBasicBlock *TrapBB = MF->CreateMachineBasicBlock(BB->getBasicBlock());
  // FIXME: Trap instruction
  // Generates an invalid opcode. 
  // This instruction is provided for software testing to explicitly generate an invalid opcode.
  // The opcode for this instruction is reserved for this purpose. 
  BuildMI(TrapBB, dl, TII.get(getLongJumpOpcodeStatic()))
  .addExternalSymbol("abort");
  DispatchBB->addSuccessor(TrapBB);

  MachineBasicBlock *DispContBB = MF->CreateMachineBasicBlock(BB->getBasicBlock());
  DispatchBB->addSuccessor(DispContBB);

  // Insert MBBs.
  MF->push_back(DispatchBB);
  MF->push_back(DispContBB);
  MF->push_back(TrapBB);

  // Insert code into the entry block that creates and registers the function
  // context.
  SetupEntryBlockForSjLj(MI, BB, DispatchBB, FI);

  // Create the jump table and associated information
  // FIXME: Override getJumpTableEncoding()
  unsigned JTE = getJumpTableEncoding();
  MachineJumpTableInfo *JTI = MF->getOrCreateJumpTableInfo(JTE);
  unsigned MJTI = JTI->createJumpTableIndex(LPadList);

  const CodasipRegisterInfo &RI = TII.getRegisterInfo();
  
  CII.insertNoopOnPos(*DispatchBB, DispatchBB->end(), /* position */ 0);
  DispatchBB->instr_back().addOperand(*MF, 
    MachineOperand::CreateRegMask(RI.getNoPreservedMask()));

  // IReg is used as an index in a memory operand and therefore can't be SP
  unsigned IReg = MRI->createVirtualRegister(RC);
  unsigned Imm = getPointerTy(MF->getDataLayout()) == MVT::i64 ? 8 : 4;
  EmitLoad32(*DispatchBB, DispatchBB->end(), dl, IReg, FI, Imm, true);

  unsigned VRImm = MRI->createVirtualRegister(RC);
  BuildMI(DispatchBB, dl, TII.get(Codasip::e_movi32__), VRImm)
    .addImm(LPadList.size());

  std::vector<int> CondJumpOps;
  MachineInstrBuilder MIB;

  CII.getCondBranchOpc(CondJumpOps, ISD::CondCode::SETLE);

  for (std::vector<int>::iterator it = CondJumpOps.begin(); it != CondJumpOps.end(); ++it) {
    const MCInstrDesc &CondJumpOp = TII.get(*it);
    if (CondJumpOp.getNumOperands() == 3 && CondJumpOp.OpInfo[0].RegClass == RCId
        && CondJumpOp.OpInfo[1].RegClass == RCId
        && CondJumpOp.OpInfo[2].OperandType == MCOI::OPERAND_IMMEDIATE) {
      MIB = BuildMI(DispatchBB, dl, CondJumpOp)
        .addReg(VRImm)
        .addReg(IReg)
        .addMBB(TrapBB);
      break;
    }
  }
  assert((MIB.getInstr() != nullptr) && "There is no valid conditional jump instruction with SETLE variant");

  // FIXME: Relative or Abs?
  unsigned MJTIAddr = MRI->createVirtualRegister(RC);
  unsigned JumpTargetAddr = MRI->createVirtualRegister(RC);
  unsigned JumpTarget = MRI->createVirtualRegister(RC);
  unsigned Offset  = MRI->createVirtualRegister(RC);
  BuildMI(DispContBB, dl, TII.get(Codasip::e_movi32__), MJTIAddr)
    .addJumpTableIndex(MJTI);

  MIB = MachineInstrBuilder();
  std::vector<int> Shift;
  CII.getCodasipInstr(Shift, ISD::SHL, getPointerTy(MF->getDataLayout()));
  unsigned shiftSize = (PVT == MVT::i64 && JTE == MachineJumpTableInfo::EK_BlockAddress) ? 3 : 2;

  for (std::vector<int>::iterator it = Shift.begin(); it != Shift.end(); ++it) {
    const MCInstrDesc &ShiftOp = TII.get(*it);

    if (ShiftOp.getNumOperands() == 3 && ShiftOp.OpInfo[0].RegClass == RCId
      && ShiftOp.OpInfo[1].RegClass == RCId
      && ShiftOp.OpInfo[2].OperandType == MCOI::OPERAND_IMMEDIATE) {
      MIB = BuildMI(DispContBB, dl, ShiftOp, Offset)
        .addReg(IReg)
        .addImm(shiftSize);
      break;
    } else if (ShiftOp.getNumOperands() == 3 && ShiftOp.OpInfo[0].RegClass == RCId
      && ShiftOp.OpInfo[1].RegClass == RCId && ShiftOp.OpInfo[2].RegClass == RCId) {
      unsigned SizeReg  = MRI->createVirtualRegister(RC);
      // FIXME: Get offset in JT: Probably should be IReg*4
      MIB = BuildMI(DispContBB, dl, TII.get(Codasip::e_movi32__), SizeReg)
        .addImm(shiftSize);
      MIB = BuildMI(DispContBB, dl, ShiftOp, Offset)
        .addReg(IReg)
        .addReg(SizeReg);
      break;
    }
  }

  assert((MIB.getInstr() != nullptr) && "There is no valid shift left instruction");

  EmitEssentialAdd(*DispContBB, DispContBB->end(), dl, CII, JumpTargetAddr, MJTIAddr, Offset);

  EmitLoad32(*DispContBB, DispContBB->end(), dl, JumpTarget, JumpTargetAddr, 0);

  switch (JTE) {
    case MachineJumpTableInfo::EK_BlockAddress:
      EmitIndirectJump(*DispContBB, DispContBB->end(), dl, CTM, JumpTarget);
      break;
    case MachineJumpTableInfo::EK_LabelDifference32: {
      unsigned RelAddr  = MRI->createVirtualRegister(RC);
      EmitEssentialAdd(*DispContBB, DispContBB->end(), dl, CII, RelAddr, JumpTarget, MJTIAddr);
      EmitIndirectJump(*DispContBB, DispContBB->end(), dl, CTM, RelAddr);
      break;
    }
    default:
      llvm_unreachable("Unexpected jump table encoding");
  }

  // Add the jump table entries as successors to the MBB.
  SmallPtrSet<MachineBasicBlock *, 8> SeenMBBs;
  for (auto &LP : LPadList)
    if (SeenMBBs.insert(LP).second)
      DispContBB->addSuccessor(LP);

  // N.B. the order the invoke BBs are processed in doesn't matter here.
  SmallVector<MachineBasicBlock *, 64> MBBLPads;
  const MCPhysReg *SavedRegs = MF->getRegInfo().getCalleeSavedRegs();
  for (MachineBasicBlock *MBB : InvokeBBs) {
    // Remove the landing pad successor from the invoke block and replace it
    // with the new dispatch block.
    // Keep a copy of Successors since it's modified inside the loop.
    SmallVector<MachineBasicBlock *, 8> Successors(MBB->succ_rbegin(),
                                                   MBB->succ_rend());
    // FIXME: Avoid quadratic complexity.
    for (auto MBBS : Successors) {
      if (MBBS->isEHPad()) {
        MBB->removeSuccessor(MBBS);
        MBBLPads.push_back(MBBS);
      }
    }

    MBB->addSuccessor(DispatchBB);

    // Find the invoke call and mark all of the callee-saved registers as
    // 'implicit defined' so that they're spilled.  This prevents code from
    // moving instructions to before the EH block, where they will never be
    // executed.
    for (auto &II : reverse(*MBB)) {
      if (!II.isCall())
        continue;

      DenseMap<unsigned, bool> DefRegs;
      for (auto &MOp : II.operands())
        if (MOp.isReg())
          DefRegs[MOp.getReg()] = true;

      MachineInstrBuilder MIB(*MF, &II);
      for (unsigned RI = 0; SavedRegs[RI]; ++RI) {
        unsigned Reg = SavedRegs[RI];
        if (!DefRegs[Reg])
          MIB.addReg(Reg, RegState::ImplicitDefine | RegState::Dead);
      }

      break;
    }
  }

  // The instruction is gone now.
  MI.eraseFromParent();
  return BB;
}

unsigned CodasipGenTargetLowering::getExceptionPointerRegister(const Constant *PersonalityFn) const
{
  return Codasip::rf_xpr_10;
}

unsigned CodasipGenTargetLowering::getExceptionSelectorRegister(const Constant *PersonalityFn) const
{
  return Codasip::rf_xpr_11;
}



Value *CodasipGenTargetLowering::getSafeStackPointerLocation(IRBuilder<> &IRB) const
{
  return getDefaultSafeStackPointerLocation(IRB, /*ThreadLocalStorage*/false);
}
