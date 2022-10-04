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


#ifndef CODASIPGENISELLOWERING_H
#define CODASIPGENISELLOWERING_H

#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "codasip/Target/CodasipBaseLowering.h"
#include "codasip/Target/CodasipBaseTargetInstrInfo.h"
#include "CodasipInstrInfo.h"
#include "Codasip.h"

#include <bitset>
#include <vector>
#include <array>

namespace llvm {

namespace CodasipISD
{
  /// Internal subcodes for intrinsic calls
  enum IntrinsicsSubcodes
  {
    
    IntrinsicsSubcodes_stopper
  };
  /// Extra node types that are used for creation of abstract operations (generally used for all targets)
  enum NodeType
  {
    FIRST_NUMBER = CodasipBaseISD::CODASIP_OP_END,
    Call, Ret, TailCall,
    /// machine interrupt return
    MRET,
    /// user interrupt return
    URET,
    /// supervisor interrupt return
    SRET,
    /// wrapper of global symbols adressed through pointer type imm
    GAWrap,
    // nodes for lowering of builtins
    
    // nodes for lowering of MOIs
    
    // exceptions
    EH_SJLJ_SETJMP,
    EH_SJLJ_LONGJMP,
    EH_SJLJ_SETUP_DISPATCH,
    /// This is only for GetCodasipPattern
    GET_PC,
    /// mark of the end of normal generated opcodes, custom and memory afterwards
    LAST_NUMBER,
    /// memory only from this point on
    FIRST_TARGET_MEMORY_OPCODE = ISD::FIRST_TARGET_MEMORY_OPCODE,
    // memory nodes for lowering of builtins
    
    // memory nodes for lowering of MOIs
    
    /// mark
    LAST_MEMORY_NUMBER
  };
}

class CodasipGenTargetLowering: public CodasipBaseTargetLowering
{
  // for getRegForInlineAsmConstraint and getRegisterByName
  typedef std::pair<unsigned, const TargetRegisterClass*> RcAndReg;

public:
  explicit CodasipGenTargetLowering(CodasipTargetMachine &TM);
  SDValue LowerFormalArguments(SDValue Chain,
                               CallingConv::ID CallConv,
                               bool isVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               const SDLoc &dl,
                               SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals) const override;
  SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI, SmallVectorImpl<SDValue> &InVals) const override;
  SDValue LowerReturn(SDValue Chain,
                      CallingConv::ID CallConv,
                      bool isVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      const SmallVectorImpl<SDValue> &OutVals,
                      const SDLoc &dl,
                      SelectionDAG &DAG) const override;
  bool CanLowerReturn(CallingConv::ID CallConv,
                      MachineFunction &MF,
                      bool isVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      LLVMContext &Context) const override;
  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;
  void ReplaceNodeResults(SDNode *N, SmallVectorImpl<SDValue> &Results, SelectionDAG &DAG) const override;
  /// Handles extends from illegal original types to attypical integers
  SDValue HandleExtToCust(SDValue Op, SelectionDAG &DAG) const;
  EVT getSetCCResultType(const DataLayout &DL, LLVMContext &Context, EVT VT) const override;
  MVT::SimpleValueType getCmpLibcallReturnType() const override;
  bool isShuffleMaskLegal(ArrayRef<int> m, EVT t) const override;
  const char* getTargetNodeName(unsigned Opcode) const override;
  RcAndReg getRegForInlineAsmConstraint(const TargetRegisterInfo *TRI, StringRef Constraint, MVT VT) const override;
  unsigned getInlineAsmMemConstraint(StringRef ConstraintCode) const override;
  unsigned getRegisterByName(const char *RegName, EVT VT, SelectionDAG &DAG) const override;
  // for reserved-regs cmdline arg
  unsigned getRegisterByName(const char *RegName) const;
  // handles exceptions, calls ExpandDummiesImpl
  MachineBasicBlock* EmitInstrWithCustomInserter(MachineInstr &MI, MachineBasicBlock *BB) const override;
  // For semi-general registers of illegal types
  const TargetRegisterClass* getRepRegClassFor(MVT t) const override;
  const TargetRegisterClass* getRegClassFor(MVT t, bool isDivergent = false) const override;
  // Type leg. info for custom vectors
  // (it's not virtual but it doesn't have to be)
  void computeRegisterProperties(const TargetRegisterInfo *TRI);
  /// From CodasipBaseTargetLowering
  unsigned GetSpace4Vt(EVT vt) const override;
  /// Always true for now
  bool isOffsetFoldingLegal(const GlobalAddressSDNode* GA) const override;
  // Auto shifts
  bool getPreIndexedAddressParts(SDNode* Node, SDValue& BasePtr, SDValue& Offset, ISD::MemIndexedMode& AM, SelectionDAG& DAG) const override;
  bool getPostIndexedAddressParts(SDNode* Node, SDNode* Op, SDValue& BasePtr, SDValue& Offset, ISD::MemIndexedMode& AM, SelectionDAG& DAG) const override;
  /** Hook for accessing arrays.
   * \return False, if normal implementation should be used. */
  bool EmittArrayAccess(SelectionDAG& DAG, const User &I, Type* indexedType, const Value* Idx, SDValue IdxN, SDValue& N, const SDLoc &dl) const override;
  /// Handle custom unaligned ints in loads
  std::pair<SDValue,SDValue> ExpandCustomUnalignedLoad(LoadSDNode* LD, SelectionDAG& DAG) const override;
  /// Handle custom unaligned ints in stores
  SDValue ExpandCustomUnalignedStore(StoreSDNode* ST, SelectionDAG& DAG) const override;
  /// Check address spaces
  bool canMergeStoresTo(unsigned AS, EVT MemVT, const SelectionDAG &DAG) const override;
  /// Default implementation returns PTR, this returns t
  MVT getScalarShiftAmountTy(const DataLayout &DL, EVT t) const override;
  /// FMA usage
  bool enableAggressiveFMAFusion(EVT VT) const override;
  bool isFMAFasterThanFMulAndFAdd(EVT VT) const override;
  // optimisation hooks
  bool isLegalAddressingMode(const DataLayout &DL, const AddrMode &AM, Type *Ty, unsigned AS, Instruction *I) const override;
  bool isLegalICmpImmediate(int64_t imm) const override;
  bool isLegalAddImmediate(int64_t imm) const override;
  bool isZExtFree(SDValue Val, EVT VT2) const override;
  // Exceptions handling
  
  MachineBasicBlock *emitEHSjLjSetJmp(MachineInstr &MI,
                                      MachineBasicBlock *MBB) const;
  MachineBasicBlock *emitEHSjLjLongJmp(MachineInstr &MI,
                                       MachineBasicBlock *MBB) const;
  MachineBasicBlock *emitEHSjLjDispatchBlock(MachineInstr &MI,
                                             MachineBasicBlock *MBB) const;
  void SetupEntryBlockForSjLj(MachineInstr &MI, MachineBasicBlock *MBB,
                              MachineBasicBlock *DispatchBB, int FI) const;
  const MCExpr *LowerCustomJumpTableEntry(const MachineJumpTableInfo *MJTI,
                                          const MachineBasicBlock *MBB,
                                          unsigned uid,
                                          MCContext &Ctx) const override;
  unsigned getJumpTableEncoding() const override;
  // If a physical register, this returns the register that receives the
  // exception address on entry to an EH pad.
  unsigned getExceptionPointerRegister(const Constant *PersonalityFn) const override;
  // If a physical register, this returns the register that receives the
  // exception typeid on entry to a landing pad.
  unsigned getExceptionSelectorRegister(const Constant *PersonalityFn) const override;
  
  // SafeStack
  Value *getSafeStackPointerLocation(IRBuilder<> &IRB) const override;
  // memory intrins
  bool getTgtMemIntrinsic(IntrinsicInfo &intInfo, const CallInst &inst, MachineFunction &MF, unsigned intrin) const override;
  // codasip mem nodes
  SDValue GetCodasipMemSDNode(SelectionDAG &DAG, int Opcode,
                              SDVTList VTs, ArrayRef<SDValue> Ops,
                              const SDLoc &dl, EVT MemVT,
                              MachineMemOperand *MMO) const override;

protected:
  /// Offset info for one indexed mode
  typedef std::array<bool, MVT::LAST_VALUETYPE> OffsetInfo;
  /// Address space legalities for one indexed mode
  typedef std::array<std::bitset<STACK_COUNT>, MVT::LAST_VALUETYPE> AsInfo;
  
  RcAndReg GetRegAndClassByName(StringRef Constraint, EVT VT) const;
  // Handle builtins
  virtual SDValue LowerIntrinsic(SDValue Op, SelectionDAG &DAG) const;
  // Auxs for getPreIndexedAddressParts/getPostIndexedAddressParts
  bool CheckIndexedLegal(LSBaseSDNode* N, ISD::MemIndexedMode AM) const;
  virtual bool CheckIndexedOffsetLegal(LSBaseSDNode* N, const ISD::MemIndexedMode AM, const SDValue& Offset, MachineFunction &MF) const;
  // inits IndOffsetInfo
  void InitIndOffsetInfo();
  /// For multistacks
  SDValue ExpandDYNAMIC_STACKALLOC(SDNode* Node, SelectionDAG& DAG) const;
  /// Aux for ExpandDYNAMIC_STACKALLOC
  unsigned GetSpForAS(SDNode* Node) const;

  // finer grained info for indexed ops
  std::array<OffsetInfo, ISD::LAST_INDEXED_MODE> IndOffsetInfo[2];
  
  // for optim - which instructions?
  std::array<std::vector<unsigned>, ISD::LAST_INDEXED_MODE> IndInstructionsMap[2];
  // disable tail calls?
  bool DisableTailCalls;

private:
  void EmitEssentialLoad(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL,
                         const CodasipInstrInfo &CII, unsigned DST, unsigned SRC, int64_t IMM) const;
  void EmitLoad32(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL, unsigned Target, int Source,
                  int Imm, bool FI = false) const;
  void EmitLoadImm32(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL, unsigned Dst, int Imm) const;
  void EmitEssentialStore(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL,
                          const CodasipInstrInfo &CII, unsigned Data, unsigned Addr, int64_t Imm) const;
  void EmitEssentialAdd(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL,
                        const CodasipInstrInfo &CII, unsigned Dst, unsigned Src, unsigned Src2) const;
  void EmitIndirectJump(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, DebugLoc& DL,
                        const CodasipTargetMachine &CTM, unsigned Target) const;
  // for regs in inline asm & clobbers
  struct StrCaseInsensitive {
    bool operator() (const StringRef left, const StringRef right) const;
  };
  typedef std::multimap<std::string,RcAndReg,StrCaseInsensitive> NameMapT;
  NameMapT NameMap;
};

}

#endif
