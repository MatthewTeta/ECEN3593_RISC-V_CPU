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


#include "Codasip.h"
#include "CodasipGenInstrInfo.h"
#include "CodasipTargetMachine.h"
#include "CodasipSubtarget.h"
#include "CodasipMachineFunction.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/ScheduleDAG.h"
#include "llvm/CodeGen/ScoreboardHazardRecognizer.h"
#include "llvm/CodeGen/DFAPacketizer.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/CodeGen/PseudoSourceValue.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "CodasipInstructionSemantics.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"

#define TargetInstrInfo CodasipBaseInstrInfo
#define GET_INSTRINFO_CTOR_DTOR
#define GET_INSTRMAP_INFO
#include "CodasipGenInstrInfo.inc"
#undef TargetInstrInfo
#include "CodasipGenRegisterInfo.inc"

#include <cstdio>
#include <iostream>
#include <vector>

#define DEBUG_TYPE "codasip-phi-optim"

namespace llvm {

CodasipGenInstrInfo2::CodasipGenInstrInfo2(CodasipTargetMachine &TM)
: CodasipGenInstrInfo(Codasip::CALLSTART,Codasip::CALLEND), RI(*this)
{
  UncondBrOpc = Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__;
  ExpandedInstrs = {Codasip::KILL, Codasip::COPY, Codasip::EXTRACT_SUBREG,
    Codasip::rule_SELECT_7,
Codasip::rule_SELECT_8,
Codasip::rule_SELECT_9,
Codasip::rule_SELECT_10,
Codasip::rule_SELECT_11,
Codasip::rule_SELECT_12,
Codasip::rule_SELECT_13,
Codasip::rule_SELECT_14,
Codasip::rule_SELECT_15,
Codasip::rule_SELECT_16,
Codasip::rule_SELECT_17,
Codasip::i_call_reg_alias__simm12__xpr_general__immspec_1_,
Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_,
Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__immspec_1_,
Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__,
Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__,
Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__,
Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__,
Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__0__,
Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__1__,
Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__0__,
Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__1__,
Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__immspec_1_,
Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__AEXT_CLONE_,
Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__AEXT_CLONE_,
Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_,
Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_,
Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__AEXT_CLONE_,
Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__AEXT_CLONE_,
Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_,
Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_,
Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__immspec_1_,
Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__AEXT_CLONE_,
Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__AEXT_CLONE_,
Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_,
Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_,
Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__AEXT_CLONE_,
Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__AEXT_CLONE_,
Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_,
Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_,
Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__immspec_1_,
Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__immspec_1_,
Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__swappedCmpClone0__,
Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__swappedCmpClone0__,
Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_,
Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_,
Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_,
Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__immspec_1_,
Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_,
Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__immspec_1_,
Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__immspec_1_,
Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__immspec_1_,
Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__immspec_1_,
Codasip::e_movi32__,
Codasip::e_movi32__GA,
Codasip::e_movi32__ES,
Codasip::e_movi32__MC,
Codasip::e_movi32__BA,
Codasip::e_movi32__JT,
Codasip::e_movi32__CP,
Codasip::i_ret_alias__TAILCALL_CLONE_,
Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_TAILCALL_CLONE_,
Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_,
Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES,
Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC,
Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA,
Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_,
Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES,
Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC,
Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA,
Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_,
Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES,
Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC,
Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA,
Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_,
Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES,
Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC,
Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA,
Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_,
Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES,
Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC,
Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA,
Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_,
Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_ES,
Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_MC,
Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_BA,
Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__i32_TRUNC_CLONE_,
Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__i32_TRUNC_CLONE_,
Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__i32_TRUNC_CLONE_,
Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__i32_TRUNC_CLONE_,
Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_,
Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_,
Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__0_REG_EMUL_,
Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__1_BIGIMM_EMUL_,
Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__2_REG_EMUL_,
Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__3_BIGIMM_EMUL_,
Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__4_BIGIMM_EMUL_,
Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__5_BIGIMM_EMUL_,
Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__6_BIGIMM_EMUL_,
Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__7_BIGIMM_EMUL_,
Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__8_BIGIMM_EMUL_,

  };
  LibCSSpillInstr = Codasip::i_jal_abs_calias__opc_jal__xpr_general__relative_addr20__;
  LibCSSpillReg = Codasip::rf_xpr_5;
}

// R2R moves
void CodasipGenInstrInfo2::copyPhysReg(MachineBasicBlock &MB,
                                       MachineBasicBlock::iterator II,
                                       const DebugLoc& DL,
                                       unsigned DestReg,
                                       unsigned SrcReg,
                                       bool KillSrc) const
{
  // should be physical
  assert(RI.isPhysicalRegister(DestReg));
  assert(RI.isPhysicalRegister(SrcReg));
  // check all supported combinations
  // this will cover logical classes with included register sets as well
  if ((Codasip::xpr_generalRegClass.contains(SrcReg)) && (Codasip::xpr_generalRegClass.contains(DestReg)))
  {
    BuildMI(MB,II,DL, get(Codasip::i_rtype_alu__opc_add__xpr_general__x_0__xpr_general__), DestReg).addReg(SrcReg,getKillRegState(KillSrc));
  }
  else 
  {
    errs() << "Copy from register " << RI.getName(SrcReg) << " to register " << RI.getName(DestReg) << " is unsupported. ";
    errs() << "Add handling manually to CodasipInstrInfo.cpp or avoid usage. ";
    errs() << "Implementing CodasipTargetLowering::getRegClassFor and getRepRegClassFor should be also taken into consideration.\n";
    assert(false && "It's impossible to perform this copy.");
  }
}

// R2S stores
// Note: Reg may be virtual
void CodasipGenInstrInfo2::storeRegToStackSlot(MachineBasicBlock &MB,
                                               MachineBasicBlock::iterator II,
                                               unsigned Reg,
                                               bool isKill,
                                               int FrameIndex,
                                               const TargetRegisterClass *RC,
                                               const TargetRegisterInfo *TRI) const
{
  DebugLoc dl;
  const TargetInstrInfo &TII = *this;
  MachineFunction &MF = *MB.getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  unsigned Align = MFI.getObjectAlignment(FrameIndex);
  auto FS = MachinePointerInfo::getFixedStack(MF,FrameIndex);
  MachineMemOperand *MMO = MF.getMachineMemOperand(FS, MachineMemOperand::MOStore, MFI.getObjectSize(FrameIndex), Align);
  if (II != MB.end()) dl = II->getDebugLoc();
  // determine and store address space
  const unsigned space = GetSpace4Rc(RC);
  MFI.setStackID(FrameIndex,space);
  // get FP
  unsigned FP = RI.getFrameRegister(MF,space);
  // check all supported registers
  // this will cover logical classes with included register sets as well
  if ((Codasip::xpr_generalRegClass.contains(Reg) || RC->getID()==Codasip::xpr_generalRegClass.getID()) && Codasip::xpr_generalRegClass.contains(FP) && space==0)
  {
    BuildMI(MB,II,dl, TII.get(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__)).add(MachineOperand::CreateReg(Reg,false,false,isKill)).add(MachineOperand::CreateFI(FrameIndex)).add(MachineOperand::CreateImm(0)).addMemOperand(MMO);
  }
  else 
  {
    errs() << "Spill of a register class " << RI.getRegClassName(RC) << " is unsupported. ";
    errs() << "Add handling manually to CodasipInstrInfo.cpp or avoid usage.\n"; 
    assert(false && "It's impossible to store this register.");
  }
}

// S2R loads
// Note: Reg may be virtual
void CodasipGenInstrInfo2::loadRegFromStackSlot(MachineBasicBlock &MB,
                                                MachineBasicBlock::iterator II,
                                                unsigned Reg,
                                                int FrameIndex,
                                                const TargetRegisterClass *RC,
                                                const TargetRegisterInfo *TRI) const
{
  DebugLoc dl;
  const TargetInstrInfo &TII = *this;
  MachineFunction &MF = *MB.getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  CodasipFunctionInfo *finfo = MF.getInfo<CodasipFunctionInfo>();
  unsigned Align = MFI.getObjectAlignment(FrameIndex);
  MachineMemOperand *MMO = MF.getMachineMemOperand(
                      MachinePointerInfo::getFixedStack(MF,FrameIndex),
                      MachineMemOperand::MOLoad, MFI.getObjectSize(FrameIndex), Align);
  if (II != MB.end()) dl = II->getDebugLoc();
  // determine and store address space
  // - kind of duplicit but this can be called before a store
  const unsigned space = GetSpace4Rc(RC);
  MFI.setStackID(FrameIndex,space);
  // get FP
  unsigned FP = RI.getFrameRegister(MF,space);
  // check all supported registers
  // this will cover logical classes with included register sets as well
  if ((Codasip::xpr_generalRegClass.contains(Reg) || RC->getID()==Codasip::xpr_generalRegClass.getID()) && Codasip::xpr_generalRegClass.contains(FP) && space==0)
  {
    BuildMI(MB,II,dl, TII.get(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__)).add(MachineOperand::CreateReg(Reg,true)).add(MachineOperand::CreateFI(FrameIndex)).add(MachineOperand::CreateImm(0)).addMemOperand(MMO);
  }
  else 
  {
    errs() << "Restore of a register class " << RI.getRegClassName(RC) << " is unsupported. ";
    errs() << "Add handling manually to CodasipInstrInfo.cpp or avoid usage.\n"; 
    assert(false && "It's impossible to load to this register.");
  }
}

// class for dummy nodes for printing
class SDNode4Print: public SDNode
{
public:
  SDNode4Print(unsigned Opc): SDNode(Opc,0,DebugLoc(),SDVTList()) {}
};

// Note: this is always post-RA
void CodasipGenInstrInfo2::EmitEssentialInstr(MachineBasicBlock &MB,
                                              MachineBasicBlock::iterator II,
                                              DebugLoc dl,
                                              ISD::NodeType Opc,
                                              SmallVectorImpl<MachineOperand> &Ops) const
{
  // expected by the generated code
  const CodasipGenInstrInfo2 &TII = *this;
  const CodasipRegisterInfo &TRI = RI;
  const MachineRegisterInfo &MRI = MB.getParent()->getRegInfo();
  // prepare operation name
  SDNode4Print dummy(Opc);
  std::string name = dummy.getOperationName();
  // try to emit
  switch (Opc)
  {
    case ISD::STORE:
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm() && CheckImmImpl(Ops[2].getImm(),12,1,0)) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm() && CheckImmImpl(Ops[2].getImm(),12,1,0)) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm()) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__1_BIGIMM_EMUL_)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm()) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__4_BIGIMM_EMUL_)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      break;
    case ISD::LOAD:
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm() && CheckImmImpl(Ops[2].getImm(),12,1,0)) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm() && CheckImmImpl(Ops[2].getImm(),12,1,0)) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm()) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__3_BIGIMM_EMUL_)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm()) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__5_BIGIMM_EMUL_)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      break;
    case ISD::ADD:
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm() && CheckImmImpl(Ops[2].getImm(),12,1,0)) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm() && CheckImmImpl(Ops[2].getImm(),12,1,0)) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm() && CheckImmImpl(Ops[2].getImm(),12,1,0)) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[2]).add(Ops[1]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[2]).add(Ops[1]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[2]).add(Ops[1]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[2]).add(Ops[1]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm()) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__6_BIGIMM_EMUL_)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm()) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__7_BIGIMM_EMUL_)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isImm()) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__8_BIGIMM_EMUL_)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      break;
    case ISD::SUB:
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_sub__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      if (Ops.size()==3 && Ops[0].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[0].getReg()) && Ops[1].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[1].getReg()) && Ops[2].isReg() && TRI.CheckRegClass(MRI, &Codasip::xpr_generalRegClass, Ops[2].getReg())) {
        BuildMI(MB,II,dl, TII.get(Codasip::i_rtype_alu__opc_sub__xpr_general__xpr_general__xpr_general__)).add(Ops[0]).add(Ops[1]).add(Ops[2]);
        return;
      }
      break;

    default:
      errs() << "Requesting unsupported opcode \"" << name << "\" from runtime emit of basic instructions.\n";
      abort();
  }
  errs() << "An essential instruction implementing operation \"" << name << "\" with these operands: {";
  for (unsigned i=0; i<Ops.size(); ++i)
  {
    if (i) errs() << ", ";
    Ops[i].print(errs(), &RI);
    if (Ops[i].isReg())
    {
      const auto reg = Ops[i].getReg();
      errs() << " in (";
      if (reg.isPhysical())
      {
        bool found = false;
        for (const TargetRegisterClass *RC: RI.regclasses())
        {
          if (RC->contains(reg))
          {
            if (found) errs() << ", ";
            errs() << RI.getRegClassName(RC);
            found = true;
          }
        }
      }
      else
      {
        const TargetRegisterClass *RC = MRI.getRegClass(reg);
        errs() << RI.getRegClassName(RC);
      }
      errs() << ")";
    }
  }
  errs() << "} requested for runtime emit is unsupported. See the backendgen log for more information.\n";
  abort();
}

unsigned CodasipGenInstrInfo2::getAnalyzableBrOpc(unsigned Opc) const
{
  // (not from mips)
  MCInstrDesc d = get(Opc);
  if (d.isBranch() && !d.isIndirectBranch()) {
    return Opc;
  }
  else {
    return 0;
  }
}

int CodasipGenInstrInfo2::ReverseBranchConditionOpc(int Opc) const
{
  switch (Opc)
  {
    case Codasip::i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_beq__xpr_general__x_0__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_blt__x_0__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__x_0__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_blt__xpr_general__x_0__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_blt__x_0__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_bge__x_0__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__x_0__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_bge__xpr_general__x_0__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bne__x_0__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bne__xpr_general__x_0__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__:
      Opc = Codasip::i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__;
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      Opc = Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__;
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      Opc = Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__;
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      Opc = Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__;
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      Opc = Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__;
      break;
    
    default:
      if (isPredicated(Opc))
      {
        if (isPredicatedTrue(Opc)) {
          Opc = Codasip::getFalsePredOpcode(Opc);
          break;
        }
        else {
          Opc = Codasip::getTruePredOpcode(Opc);
          break;
        }
      }
      Opc = 0;
  }
  return Opc;
}

void CodasipGenInstrInfo2::getCodasipInstr(std::vector<int> &Opcs, int Operation, MVT Type) const
{
  assert(Opcs.empty());
  switch (Operation)
  {
        case ISD::ADD:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(2);
          Opcs.push_back(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__);
          Opcs.push_back(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__);
          break;
        default: ;
      }
      break;
    case ISD::SUB:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(1);
          Opcs.push_back(Codasip::i_rtype_alu__opc_sub__xpr_general__xpr_general__xpr_general__);
          break;
        default: ;
      }
      break;
    case ISD::AND:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(2);
          Opcs.push_back(Codasip::i_itype_alu__opc_andi__xpr_general__xpr_general__simm12__);
          Opcs.push_back(Codasip::i_rtype_alu__opc_and__xpr_general__xpr_general__xpr_general__);
          break;
        default: ;
      }
      break;
    case ISD::OR:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(2);
          Opcs.push_back(Codasip::i_itype_alu__opc_ori__xpr_general__xpr_general__simm12__);
          Opcs.push_back(Codasip::i_rtype_alu__opc_or__xpr_general__xpr_general__xpr_general__);
          break;
        default: ;
      }
      break;
    case ISD::XOR:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(2);
          Opcs.push_back(Codasip::i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__);
          Opcs.push_back(Codasip::i_rtype_alu__opc_xor__xpr_general__xpr_general__xpr_general__);
          break;
        default: ;
      }
      break;
    case ISD::SHL:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(2);
          Opcs.push_back(Codasip::i_rtype_alu__opc_sll__xpr_general__xpr_general__xpr_general__);
          Opcs.push_back(Codasip::i_rtype_shift__opc_slli__xpr_general__xpr_general__uimm5__);
          break;
        default: ;
      }
      break;
    case ISD::SRA:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(2);
          Opcs.push_back(Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__);
          Opcs.push_back(Codasip::i_rtype_shift__opc_srai__xpr_general__xpr_general__uimm5__);
          break;
        default: ;
      }
      break;
    case ISD::SRL:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(2);
          Opcs.push_back(Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__);
          Opcs.push_back(Codasip::i_rtype_shift__opc_srli__xpr_general__xpr_general__uimm5__);
          break;
        default: ;
      }
      break;
    case ISD::LOAD:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(3);
          Opcs.push_back(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0__);
          Opcs.push_back(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__);
          Opcs.push_back(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__immspec_1_);
          break;
        default: ;
      }
      break;
    case ISD::BRIND:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(1);
          Opcs.push_back(Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_);
          break;
        default: ;
      }
      break;
    case CodasipBaseISD::Call:
      switch (Type.SimpleTy)
      {
        case MVT::i32:
          Opcs.reserve(11);
          Opcs.push_back(Codasip::i_call_reg_alias__simm12__xpr_general__immspec_1_);
          Opcs.push_back(Codasip::i_call_alias__relative_addr20__);
          Opcs.push_back(Codasip::i_call_reg_alias__simm12__x_0__);
          Opcs.push_back(Codasip::i_ret_alias__TAILCALL_CLONE_);
          Opcs.push_back(Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_TAILCALL_CLONE_);
          Opcs.push_back(Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_);
          Opcs.push_back(Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_);
          Opcs.push_back(Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_);
          Opcs.push_back(Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_);
          Opcs.push_back(Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_);
          Opcs.push_back(Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_);
          break;
        default: ;
      }
      break;

    case CodasipBaseISD::HW_LOOP_START:
      Opcs.push_back(Codasip::hwloop_set_loop_iterations);
      
      break;
    case CodasipBaseISD::HW_LOOP_DEC:
      Opcs.push_back(Codasip::hwloop_loop_decrement_reg);
      break;
    default: ;
  }
}

void CodasipGenInstrInfo2::getCondBranchOpc(std::vector<int>& Opcs, ISD::CondCode CC) const
{
  assert(Opcs.empty());
  switch (CC)
  {
    case ISD::SETUGT:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__);
 break;
case ISD::SETUGE:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__);
 break;
case ISD::SETULT:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__);
 break;
case ISD::SETULE:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__);
 break;
case ISD::SETEQ:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__);
 break;
case ISD::SETGT:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__);
 break;
case ISD::SETGE:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__);
 break;
case ISD::SETLT:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__);
 break;
case ISD::SETLE:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__);
 break;
case ISD::SETNE:
 Opcs.reserve(1);
 Opcs.push_back(Codasip::i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__);
 break;

    default: ;
  }
}

// based on mips but accounts for branches without an opposite
bool CodasipGenInstrInfo2::reverseBranchCondition(SmallVectorImpl<MachineOperand> &Cond) const
{ 
  assert((Cond.size() && Cond.size() <= 3) && "Unexpected condition vector");
  assert(Cond[0].getImm() && "Unexpected condition vector");
  // get opc and reverse
  int Opc = Cond[0].getImm();
  Opc = ReverseBranchConditionOpc(Opc);
  if (Opc==0) return true;
  Cond[0].setImm(Opc);
  assert(Cond[0].getImm() && "Unexpected condition vector");
  return false;
}

unsigned CodasipGenInstrInfo2::getEquivalentCondOpcode(ArrayRef<MachineOperand> Cond, int RegPos) const
{
  int JumpOpc = Cond[RegPos-1].getImm();
  int CondOpc = 0;
  if (!Cond.empty() && Cond[0].isImm() && (Cond[0].getImm() == 0))
  {
    JumpOpc = ReverseBranchConditionOpc(JumpOpc);
    if (!JumpOpc) {
      return 0;
    }
  }
  // determine the corresponding setcc instruction
  switch (JumpOpc)
  {
    case Codasip::i_btype_branches__opc_blt__x_0__xpr_general__relative_addr12__:
  CondOpc = Codasip::i_rtype_alu__opc_slt__xpr_general__x_0__xpr_general__;
  break;
case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__:
  CondOpc = Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__;
  break;
case Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__:
  CondOpc = Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0__xpr_general__;
  break;
case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__:
  CondOpc = Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__;
  break;
case Codasip::i_btype_branches__opc_bne__x_0__xpr_general__relative_addr12__:
  CondOpc = Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0__xpr_general__;
  break;
case Codasip::i_btype_branches__opc_bne__xpr_general__x_0__relative_addr12__:
  CondOpc = Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0__xpr_general__;
  break;
case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
  CondOpc = Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__swappedCmpClone0__;
  break;
case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
  CondOpc = Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__swappedCmpClone0__;
  break;

    default:
      CondOpc = 0;
  }
  return CondOpc;
}

bool CodasipGenInstrInfo2::analyzeCompare
(const MachineInstr &MI, unsigned &SrcReg, unsigned &SrcReg2, int &CmpMask, int &CmpValue) const
{
  CmpMask = ~0;
  SrcReg2 = 0;
  CmpValue = 0;
  switch (MI.getOpcode())
  {
    case Codasip::i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__:
SrcReg = MI.getOperand(1).getReg();
CmpValue = MI.getOperand(2).getImm();
return true;
case Codasip::i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__:
SrcReg = MI.getOperand(1).getReg();
CmpValue = MI.getOperand(2).getImm();
return true;
case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__:
SrcReg = MI.getOperand(1).getReg();
 SrcReg2 = MI.getOperand(2).getReg();
return true;
case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__:
SrcReg = MI.getOperand(1).getReg();
 SrcReg2 = MI.getOperand(2).getReg();
return true;
case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
SrcReg = MI.getOperand(1).getReg();
 SrcReg2 = MI.getOperand(2).getReg();
return true;
case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
SrcReg = MI.getOperand(1).getReg();
 SrcReg2 = MI.getOperand(2).getReg();
return true;

    default:
      return TargetInstrInfo::analyzeCompare(MI,SrcReg,SrcReg2,CmpMask,CmpValue);
  }
}

ISD::CondCode CodasipGenInstrInfo2::isCondWithSense(int opc) const
{
  switch(opc)
  {
    case Codasip::i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__:
return ISD::SETEQ;
case Codasip::i_btype_branches__opc_beq__xpr_general__x_0__relative_addr12__:
return ISD::SETEQ;
case Codasip::i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__:
return ISD::SETEQ;
case Codasip::i_btype_branches__opc_bge__x_0__xpr_general__relative_addr12__:
return ISD::SETLT;
case Codasip::i_btype_branches__opc_bge__xpr_general__x_0__relative_addr12__:
return ISD::SETGT;
case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__:
return ISD::SETGE;
case Codasip::i_btype_branches__opc_bgeu__x_0__xpr_general__relative_addr12__:
return ISD::SETEQ;
case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__:
return ISD::SETUGE;
case Codasip::i_btype_branches__opc_blt__x_0__xpr_general__relative_addr12__:
return ISD::SETGT;
case Codasip::i_btype_branches__opc_blt__xpr_general__x_0__relative_addr12__:
return ISD::SETLT;
case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__:
return ISD::SETLT;
case Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__:
return ISD::SETNE;
case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__:
return ISD::SETULT;
case Codasip::i_btype_branches__opc_bne__x_0__xpr_general__relative_addr12__:
return ISD::SETNE;
case Codasip::i_btype_branches__opc_bne__xpr_general__x_0__relative_addr12__:
return ISD::SETNE;
case Codasip::i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__:
return ISD::SETNE;
case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
return ISD::SETLE;
case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
return ISD::SETULE;
case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
return ISD::SETGT;
case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
return ISD::SETUGT;
case Codasip::i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__:
return ISD::SETLT;
case Codasip::i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__:
return ISD::SETULT;
case Codasip::i_rtype_alu__opc_slt__xpr_general__x_0__xpr_general__:
return ISD::SETGT;
case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__:
return ISD::SETLT;
case Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0__xpr_general__:
return ISD::SETNE;
case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__:
return ISD::SETULT;
case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
return ISD::SETGT;
case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
return ISD::SETUGT;

    default:
      return CodasipBaseInstrInfo::isCondWithSense(opc);
  }
}

// === methods for predicates ===

bool CodasipGenInstrInfo2::isPredicable(const MachineInstr& MI) const
{
  bool isPred = MI.getDesc().isPredicable();
  return isPred;   
}

bool CodasipGenInstrInfo2::isProfitableToIfCvt(MachineBasicBlock&, unsigned, unsigned, BranchProbability) const
{
  return true;
}

bool CodasipGenInstrInfo2::isProfitableToIfCvt(MachineBasicBlock&, unsigned, unsigned, MachineBasicBlock&, unsigned, unsigned, BranchProbability) const
{
  return true;
}

bool CodasipGenInstrInfo2::isPredicatedTrue(const MachineInstr& MI) const
{
  const uint64_t F = MI.getDesc().TSFlags;
  assert(isPredicated(MI));
  return (!((F >> 2) & 0x1));
}

bool CodasipGenInstrInfo2::isPredicatedTrue(unsigned Opcode) const
{
  const uint64_t F = get(Opcode).TSFlags;
  // Make sure that the instruction is predicated.
  assert((F>> 1) & 0x1);
  return (!((F >> 2) &0x1));
}

bool CodasipGenInstrInfo2::isPredicated(const MachineInstr& MI) const
{
  const uint64_t F = MI.getDesc().TSFlags;
  return ((F >> 1) & 0x1);
}


bool CodasipGenInstrInfo2::isProfitableToDupForIfCvt(MachineBasicBlock&, unsigned, BranchProbability) const
{
  return true;
}

bool CodasipGenInstrInfo2::isPredicated(unsigned Opcode) const
{
  const uint64_t F = get(Opcode).TSFlags;
  return ((F >> 1) & 0x1);
}

bool CodasipGenInstrInfo2::SubsumesPredicate(ArrayRef<MachineOperand> Pred1, ArrayRef<MachineOperand> Pred2) const
{
  return false;
}

bool CodasipGenInstrInfo2::DefinesPredicate(MachineInstr &MI, std::vector<MachineOperand> &Pred) const
{
  
  return false;
}

int CodasipGenInstrInfo2::getMatchingCondBranchOpcode(int Opc, bool invertPredicate) const
{
  enum Codasip::PredSense inPredSense;
  inPredSense = invertPredicate ? Codasip::PredSense_false :
                                  Codasip::PredSense_true;
  int CondOpcode = Codasip::getPredOpcode(Opc, inPredSense);
  if (CondOpcode >= 0) // Valid Conditional opcode/instruction
    return CondOpcode;
  llvm_unreachable("Unexpected predicable instruction");
}

bool CodasipGenInstrInfo2::isPredReg(const MachineOperand *PredMO) const
{
  bool Result = false; 
  
  return Result;
}

MachineBasicBlock::iterator CodasipGenInstrInfo2::identifyPositionInParentBlock(MachineInstr *PredMOSource) const
{
  MachineBasicBlock *ParentBlock = PredMOSource->getParent();
  if (ParentBlock == NULL) {
    return NULL;
  }
  for (MachineBasicBlock::iterator MBBIt=ParentBlock->begin(), MBBItE=ParentBlock->end(); MBBIt!=MBBItE; MBBIt++)
  {
     if (PredMOSource->isIdenticalTo(*MBBIt)) {
        return MBBIt;
     }
  }
  return ParentBlock->end();
}

bool CodasipGenInstrInfo2::isLiveInMBB(MachineInstr *ParentInstr, unsigned int Reg) const
{
  MachineBasicBlock *MBB = ParentInstr->getParent();
  // check liveins
  if (MBB->isLiveIn(Reg)) {
     return true;
  }
  // check instrs in block
  for (MachineBasicBlock::iterator MBBIt=MBB->begin(), MBBEIt=MBB->end(); MBBIt!=MBBEIt; MBBIt++)
  {
    for (unsigned i=0; i < MBBIt->getNumOperands(); i++)
    {
      //if we are already using this reg as an operand in any instruction in this block, then it's not safe
      if (MBBIt->getOperand(i).isReg() && MBBIt->getOperand(i).getReg()==Reg) {
        return true;
      }
    }
  }
  return false;
}

bool CodasipGenInstrInfo2::isPredicableBlock(MachineBasicBlock &MBB, SmallVectorImpl<MachineOperand> &Cond) const
{
  bool Result = false;
  
  return Result;
}

unsigned CodasipGenInstrInfo2::getPredReg(MachineInstr *MI) const
{
  unsigned Result = 0;
  if (!this->isPredicated(MI->getOpcode()) && MI->getNumOperands() != 0)
  {
    return Result;
  }
  for (int i = MI->getNumOperands()-1; i>=0; i--)
  {
    if (isPredReg(&MI->getOperand(i)))
    {
      Result = MI->getOperand(i).getReg();
      return Result;
    }
  }
  return Result;
}

bool CodasipGenInstrInfo2::getFreePredRegister(MachineInstr *ParentInstr, unsigned *FreePredReg) const
{  
  bool Result = false;
  
  return Result;
}

bool CodasipGenInstrInfo2::isThereSuitableCopy(MachineOperand *PredMO) const
{
  MachineInstr *ParentInstr = PredMO->getParent(); 
  DebugLoc DL;
  MachineBasicBlock::iterator PredBBIt = identifyPositionInParentBlock(ParentInstr);
  MachineBasicBlock *ParentMBB = PredBBIt->getParent();
  if (ParentMBB->begin() == PredBBIt)
  {
    return false;
  }
  PredBBIt--;
  if (PredBBIt->getNumOperands() == 2 && PredBBIt->getOperand(1).isReg() && PredBBIt->getOperand(1).getReg() == PredMO->getReg() && isPredReg(&PredBBIt->getOperand(0)))
  {
    *PredMO = PredBBIt->getOperand(0);
    return true;
  }
  return false;
}


bool CodasipGenInstrInfo2::copyCondToPredReg(MachineOperand *PredMO) const
{
  MachineInstr *ParentInstr = PredMO->getParent(); 
  DebugLoc DL;
  unsigned FreePredReg = 0;
  MachineBasicBlock::iterator PredBBIt = identifyPositionInParentBlock(ParentInstr);
  // get a free predicate register
  if (PredBBIt == ParentInstr->getParent()->end()  || !getFreePredRegister(ParentInstr, &FreePredReg))
  {
    return false;
  }
  // build r2r copy
  assert(PredMO->isReg());
  unsigned dstReg = PredMO->getReg();
  copyPhysReg(*(ParentInstr->getParent()), PredBBIt, DL, FreePredReg, dstReg, false);
  // make deep copy of the destination operand
  --PredBBIt;
  *PredMO = PredBBIt->getOperand(0);
  return true; 
}


llvm::ISD::CondCode CodasipGenInstrInfo2::getISDType(unsigned Opc, MachineFunction *MF) const
{
  std::vector<SDValue> RootsOpc;
  const TargetMachine *TM = &MF->getTarget();
  SelectionDAG *Pattern = GetCodasipPattern(*TM, *MF, Opc, RootsOpc);
  if (RootsOpc.size() == 0 || RootsOpc[0].getOpcode() != llvm::ISD::CopyToReg || Pattern == NULL)
  {
    return llvm::ISD::SETCC_INVALID ;
  }
  llvm::ISD::CondCode OpcType = llvm::ISD::SETCC_INVALID ;
  for (unsigned k = 0; k< RootsOpc[0].getNumOperands(); k++)
  {
    SDValue TargetOp = RootsOpc[0].getOperand(k);
    if (TargetOp.getOpcode() == llvm::ISD::SETCC && TargetOp.getNumOperands() == 3 && isa<CondCodeSDNode>(TargetOp.getOperand(2)))
    {
      OpcType = cast<CondCodeSDNode>(TargetOp.getOperand(2))->get();
      break;
    }
  }
  return OpcType;
}


bool CodasipGenInstrInfo2::isCondNegated(unsigned Opc, unsigned OpcNeg, MachineFunction *MF) const
{
  llvm::ISD::CondCode OpcNT = getISDType(Opc, MF);
  llvm::ISD::CondCode OpcNegNT = getISDType(OpcNeg, MF);
  if (getSetCCInverse(OpcNT,true) == OpcNegNT)
  {
    return true;
  }
  return false;
}

bool CodasipGenInstrInfo2::isThereSuitableCondEmul(ArrayRef<MachineOperand> Cond, int RegPos,  MachineOperand *PredMO, MachineInstr *PredInstr, bool &InvertJump) const
{
  // now we need to get our jump opc and check if there is some suitable operation which emulates jumps condition
  // emulation can _only_ be before first terminator of predecessor block
  DebugLoc DL;
  MachineBasicBlock *ParentMBB = PredInstr->getParent();
  MachineBasicBlock *PredMBB = *(ParentMBB->pred_begin()); //we have only one predecessor - confirmed sooner in isPredicableBlock()
  int EmulOpc = 0;
  EmulOpc = getEquivalentCondOpcode(Cond, RegPos);
  if (EmulOpc == 0 || PredMBB->empty() )
  {
     //no suitable emulation
     return false;
  }
  // first terminator
  MachineBasicBlock::iterator PredBBIt = PredMBB->getFirstTerminator();
  // look at instruction before the first terminator, thats the only place where emulCondToPredReg can put already existing emulation
  // there is one special case- codasip flag instruction
  bool AltPlace = false;
  while (1)
  {
    if (PredBBIt != PredMBB->end() && PredBBIt->getFlag(MachineInstr::CodasipFlag))
    {
      AltPlace = true;
      PredBBIt++;
      break;
    }
    if (PredBBIt == PredMBB->begin())
    {
      break;
    }
    PredBBIt--;
  }
  if (!AltPlace)
  {
    PredBBIt = PredMBB->getFirstTerminator();
  }
  if (PredBBIt != PredMBB->begin() && !AltPlace)
  {
    PredBBIt--;
  }
  // now we should have access to previous pred emulation _if_ this is a diamond and we need to negate
  unsigned AdjunctPredReg = 0;
  for (auto AdjunctMBB: PredMBB->successors())
  {
    if( AdjunctMBB == ParentMBB)
       continue;
    MachineInstr *TestInstr = NULL;
    if(AdjunctMBB->getFirstNonDebugInstr() != AdjunctMBB->end() ){
        TestInstr = &*AdjunctMBB->getFirstNonDebugInstr();
    }
    if(TestInstr != NULL &&    //even if jumps use predicates, they are not considered predicated //if we have use of predicate, in adjacent block, then we cannot safely use selected register
       this->isPredicated(TestInstr->getOpcode()) )
    {
     AdjunctPredReg = getPredReg(TestInstr);
     break;
    }
  }
  // if theres a diamond we now have predreg, check position if match occured
  if(PredBBIt != PredMBB->end() && (&*PredBBIt)->getNumOperands() != 0 && isPredReg(&((&*PredBBIt)->getOperand(0))) && (&*PredBBIt)->getOperand(0).getReg() == AdjunctPredReg && isCondNegated(EmulOpc, (&*PredBBIt)->getOpcode(), (&*PredBBIt)->getParent()->getParent()) )
  {
    // we have match, all we have to do is to inform rest that we need
    *PredMO = PredBBIt->getOperand(0);
    // adjunct block has negated condition
    InvertJump = true;
    return true;
  }
  if (PredBBIt != PredMBB->end() && (&*PredBBIt)->getOpcode() == (unsigned)EmulOpc && (&*PredBBIt)->getNumOperands() != 0 && //we have matching emulation opc and
      isPredReg( &((&*PredBBIt)->getOperand(0)) ) )  //we define predicate register
  {
    *PredMO = PredBBIt->getOperand(0);
    return true;
  }
  return false;
}

bool CodasipGenInstrInfo2::emulCondToPredReg(ArrayRef<MachineOperand> Cond, int RegPos,  MachineOperand *PredMO, MachineInstr *PredInstr ) const
{
  // get opc of 
  DebugLoc DL;
  unsigned FreePredReg = 0;
  MachineBasicBlock *ParentMBB = PredInstr->getParent();
  // build emulation of condition guarding jump
  int EmulOpc = 0;
  EmulOpc = getEquivalentCondOpcode(Cond, RegPos);
  if (EmulOpc == 0) {
    // no suitable emulation
    return false;
  }
  // get previous block
  MachineBasicBlock *PredMBB = *(ParentMBB->pred_begin()); //we have only one predecessor- already checked before
  MachineBasicBlock::iterator PredBBIt = PredMBB->getFirstTerminator();//where to put emulation? just place it before terminators, ifconversion _will_ coalesce basicblocks and rework these terminators
  if (!getFreePredRegister(PredInstr, &FreePredReg)) {  //abort if no free predreg
    return false;
  }
  bool AltPlace = false;
  while (1)
  {
    if (PredBBIt != PredMBB->end() && PredBBIt->getFlag(MachineInstr::CodasipFlag))
    {
      AltPlace = true;
      PredBBIt++;
      break;
    }
    if (PredBBIt == PredMBB->begin())
    {
      break;
    }
    PredBBIt--;
  }
  if (!AltPlace)
  {
    PredBBIt = PredMBB->getFirstTerminator();
  }
  const MCInstrDesc &MCID = get(EmulOpc);
  unsigned OperandsToCopy = Cond.size()-RegPos;
  // we can safely say that we will cover every operand in new instr.
  if ((MCID.getNumOperands()-1) == OperandsToCopy)
  {
    MachineInstrBuilder MIB = BuildMI(*(PredMBB), PredBBIt , DL, MCID, FreePredReg);
    //copy condition operands into emulation
    for (unsigned i = RegPos; i<Cond.size(); i++) {
      MIB.add(Cond[i]);
    }
  }
  else if (OperandsToCopy == 1 && MCID.getNumOperands() == 3 && MCID.OpInfo[2].OperandType == MCOI::OperandType::OPERAND_IMMEDIATE)
  {
    MachineInstrBuilder MIB = BuildMI(*(PredMBB), PredBBIt , DL, MCID, FreePredReg);
    for (unsigned i = RegPos; i<Cond.size(); i++) {
      MIB.add(Cond[i]);
    }
    MIB.addImm(0);
  }
  else {
    return false;
  }
  // make deep copy of the destination operand
  --PredBBIt;
  *PredMO = PredBBIt->getOperand(0);
  return true;
}

bool CodasipGenInstrInfo2::PredicateInstruction(MachineInstr &MI, ArrayRef<MachineOperand> Cond) const
{
  const int Opc = MI.getOpcode();
  assert(isPredicable(MI) && "Expected predicable instruction");
  bool invertJump = (!Cond.empty() && Cond[0].isImm() && (Cond[0].getImm() == 0));
  // This will change MI's opcode to its predicate version.
  // However, its operand list is still the old one, i.e. the
  // non-predicate one.
  int regPos = invertJump ? 2 : 1;
  MachineOperand PredMO = Cond[regPos];
  // single reg conditions (predreg class or something else)
  if (!( ((invertJump && Cond.size()==3) || (!invertJump && Cond.size() == 2)) && isPredReg( &PredMO) )) 
  {
    if (!isThereSuitableCondEmul(Cond,regPos, &PredMO, &MI, invertJump) && !emulCondToPredReg(Cond,regPos, &PredMO, &MI)) //handle complicated conditions
    {  
      return false;
    }
  }
  MI.setDesc(get(getMatchingCondBranchOpcode(Opc, invertJump)));
  MI.addOperand(MachineOperand::CreateReg(PredMO.getReg(), false));
  MachineRegisterInfo &RegInfo = MI.getParent()->getParent()->getRegInfo();
  RegInfo.clearKillFlags(PredMO.getReg());
  return true;
}

//adding NO-OP instruction to code
void CodasipGenInstrInfo2::insertNoop(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI) const
{
  DebugLoc DL;
  // created nops belong to previous instruction
  // otherwise debugg tests fail
  BuildMI(MBB, MI, DL, get(Codasip::i_nop_alias__));

}

//adding specific NO-OP instruction to code on specific position
void CodasipGenInstrInfo2::insertNoopOnPos(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, unsigned pos) const
{
  DebugLoc DL;
  switch (pos)
  {
     case 0:
  BuildMI(MBB,MI,DL,get(Codasip::i_nop_alias__)); break;


    default: insertNoop(MBB,MI);break;
  }
}

// turn of optimization on windows, too long function
#ifdef _WIN32
	#pragma optimize("", off)	// disable global optimization, this will increase compilation times 8x-10x
#endif
// return a vector with all positions, where the instruction can be
void CodasipGenInstrInfo2::getAllPosInBundleImpl(int opc, SlotData &vec)
{
  assert(vec.empty());
  switch (opc)
  {
    case Codasip::i_ret_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_call_reg_alias__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_call_alias__relative_addr20__:
    case Codasip::i_call_alias__relative_addr20__ES:
    case Codasip::i_call_alias__relative_addr20__MC:
    case Codasip::i_call_alias__relative_addr20__BA:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_jal_abs_calias__opc_jal__xpr_general__relative_addr20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_jtype_jlink__opc_jal__xpr_general__relative_addr20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_blt__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bne__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bne__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      vec.resize(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      vec.resize(0);
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      vec.resize(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      vec.resize(0);
      break;
    case Codasip::i_call_reg_alias__simm12__x_0__:
    case Codasip::i_call_reg_alias__simm12__x_0__ES:
    case Codasip::i_call_reg_alias__simm12__x_0__MC:
    case Codasip::i_call_reg_alias__simm12__x_0__BA:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_andi__xpr_general__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_ori__xpr_general__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_ori__xpr_general__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_xori__xpr_general__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_nop_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_slli__xpr_general__xpr_general__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srai__xpr_general__xpr_general__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srli__xpr_general__xpr_general__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__x_0__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__0__:
      vec.resize(0);
      break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__1__:
      vec.resize(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__0__:
      vec.resize(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__1__:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__AEXT_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__AEXT_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__AEXT_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__AEXT_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__AEXT_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__AEXT_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
      vec.resize(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
      vec.resize(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__immspec_1_:
      vec.resize(0);
      break;
    case Codasip::e_movi32__:
    case Codasip::e_movi32__GA:
    case Codasip::e_movi32__ES:
    case Codasip::e_movi32__MC:
    case Codasip::e_movi32__BA:
    case Codasip::e_movi32__JT:
    case Codasip::e_movi32__CP:
      vec.resize(0);
      break;
    case Codasip::i_ret_alias__TAILCALL_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_TAILCALL_CLONE_:
      vec.resize(0);
      break;
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_ES:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_MC:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_BA:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__i32_TRUNC_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__i32_TRUNC_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_:
      vec.resize(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_:
      vec.resize(0);
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__0_REG_EMUL_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__1_BIGIMM_EMUL_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__2_REG_EMUL_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__3_BIGIMM_EMUL_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__4_BIGIMM_EMUL_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__5_BIGIMM_EMUL_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__6_BIGIMM_EMUL_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__7_BIGIMM_EMUL_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__8_BIGIMM_EMUL_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_beqz_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_beqz_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_beqz_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgez_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgez_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgez_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgt_alias__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgt_alias__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgt_alias__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgt_alias__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgt_alias__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgt_alias__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgt_alias__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgt_alias__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgt_alias__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtu_alias__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtu_alias__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtu_alias__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtu_alias__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtu_alias__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtu_alias__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtu_alias__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtu_alias__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtu_alias__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtz_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtz_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bgtz_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_ble_alias__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_ble_alias__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_ble_alias__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_ble_alias__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_ble_alias__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_ble_alias__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_ble_alias__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_ble_alias__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_ble_alias__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bleu_alias__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bleu_alias__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bleu_alias__x_0__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bleu_alias__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bleu_alias__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bleu_alias__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bleu_alias__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bleu_alias__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bleu_alias__xpr_general__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_blez_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_blez_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_blez_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bltz_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bltz_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bltz_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bnez_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bnez_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_bnez_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_beq__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_blt__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_blt__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_blt__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_blt__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bne__x_0__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bne__x_0_alias__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bne__x_0_alias__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bne__x_0_alias__xpr_general__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bne__xpr_general__x_0_alias__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_call_reg_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_halt__opc_halt__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__x_0__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__x_0_alias__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__x_0_alias__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__x_0_alias__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_andi__x_0__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_andi__x_0_alias__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_andi__x_0_alias__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_andi__x_0_alias__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_andi__xpr_general__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_ori__x_0__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_ori__x_0_alias__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_ori__x_0_alias__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_ori__x_0_alias__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_ori__xpr_general__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__x_0__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__x_0_alias__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__x_0_alias__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__x_0_alias__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__x_0__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__x_0_alias__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__x_0_alias__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__x_0_alias__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_xori__x_0__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_xori__x_0_alias__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_xori__x_0_alias__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_xori__x_0_alias__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_xori__xpr_general__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0_alias__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__x_0_alias__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__x_0_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__x_0_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__x_0_alias__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__x_0_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__x_0_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__x_0_alias__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__x_0_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__x_0_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__x_0_alias__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__x_0_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__x_0_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__x_0_alias__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__x_0_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__x_0_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_j_alias__relative_addr20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_jr_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_jr_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_jr_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_jtype_jlink__opc_jal__x_0_alias__relative_addr20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_li_alias__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_li_alias__x_0_alias__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_li_alias__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_mv_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_mv_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_mv_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_mv_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_mv_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_mv_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_mv_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_mv_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_mv_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_neg_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_neg_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_neg_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_neg_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_neg_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_neg_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_neg_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_neg_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_neg_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_not_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_not_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_not_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_not_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_not_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_not_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_not_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_not_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_not_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_slli__x_0__x_0_alias__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_slli__x_0_alias__x_0__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_slli__x_0_alias__x_0_alias__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_slli__x_0_alias__xpr_general__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_slli__xpr_general__x_0_alias__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srai__x_0__x_0_alias__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srai__x_0_alias__x_0__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srai__x_0_alias__x_0_alias__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srai__x_0_alias__xpr_general__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srai__xpr_general__x_0_alias__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srli__x_0__x_0_alias__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srli__x_0_alias__x_0__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srli__x_0_alias__x_0_alias__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srli__x_0_alias__xpr_general__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srli__xpr_general__x_0_alias__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_seqz_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_seqz_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_seqz_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_seqz_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_seqz_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_seqz_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_seqz_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_seqz_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_seqz_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__x_0_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__xpr_general__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__xpr_general__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__xpr_general__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__xpr_general__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__xpr_general__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__xpr_general__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgt_alias__xpr_general__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgtz_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgtz_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgtz_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgtz_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgtz_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgtz_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgtz_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgtz_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sgtz_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sltz_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sltz_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sltz_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sltz_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sltz_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sltz_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sltz_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sltz_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_sltz_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_snez_alias__x_0__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_snez_alias__x_0__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_snez_alias__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_snez_alias__x_0_alias__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_snez_alias__x_0_alias__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_snez_alias__x_0_alias__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_snez_alias__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_snez_alias__xpr_general__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_snez_alias__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0_alias__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__x_0_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0_alias__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__x_0_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__x_0__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__x_0_alias__simm12__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__x_0_alias__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__x_0_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__x_0_alias__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_auipc__x_0_alias__uimm20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_lui__x_0_alias__uimm20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_blt__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_btype_branches__opc_bne__x_0__x_0__relative_addr12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_call_reg_alias__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__x_0__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_addi__x_0__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_andi__x_0__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_andi__x_0__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_andi__xpr_general__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_ori__x_0__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_ori__x_0__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__x_0__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_slti__x_0__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__x_0__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_sltiu__x_0__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_xori__x_0__x_0__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_alu__opc_xori__x_0__xpr_general__simm12__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__x_0__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__xpr_general__x_0__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__xpr_general__xpr_general__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_slli__x_0__x_0__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_slli__x_0__xpr_general__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_slli__xpr_general__x_0__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srai__x_0__x_0__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srai__x_0__xpr_general__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srai__xpr_general__x_0__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srli__x_0__x_0__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srli__x_0__xpr_general__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_rtype_shift__opc_srli__xpr_general__x_0__uimm5__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_auipc__x_0__uimm20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_lui__x_0__uimm20__:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__1_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__2_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__5_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__6_:
      vec.resize(1);
      vec[0].reserve(1);
      vec[0].push_back(0);
      break;
    
    default:
      /* no action */;
  }
}
// turn on optimizations back
#ifdef _WIN32
	#pragma optimize("", on)
#endif

void CodasipGenInstrInfo2::getAllPosInBundle(int opc, SlotData &vec) const
{
    getAllPosInBundleImpl(opc,vec);
}

bool CodasipGenInstrInfo2::isSchedulingBoundary(const MachineInstr &MI,
                                                const MachineBasicBlock *MBB,
                                                const MachineFunction &MF) const
{
  // Debug info is never a scheduling boundary. It's necessary to be explicit
  // due to the special treatment of IT instructions below, otherwise a
  // dbg_value followed by an IT will result in the IT instruction being
  // considered a scheduling hazard, which is wrong. It should be the actual
  // instruction preceding the dbg_value instruction(s), just like it is
  // when debug info is not present.
  if (MI.isDebugInstr())
    return false;
  // Terminators and labels can't be scheduled around.
  if (MI.getDesc().isTerminator() || MI.isLabel() || MI.isInlineAsm())
    return true;
  return TargetInstrInfo::isSchedulingBoundary(MI, MBB, MF);
}


// Auxiliary functions for custom inserters
namespace {

// creates successors for the given BB
void GetNextBB(MachineBasicBlock *BB, MachineBasicBlock *BBs[2], MachineInstr *MI)
{
  assert(MI->getParent()==BB);
  MachineFunction *F = BB->getParent();
  // create new basic blocks
  const BasicBlock *LLVM_BB = BB->getBasicBlock();
  MachineFunction::iterator It = BB->getIterator();
  ++It;
  BBs[0] = F->CreateMachineBasicBlock(LLVM_BB);
  BBs[1] = F->CreateMachineBasicBlock(LLVM_BB);
  F->insert(It,BBs[0]);
  F->insert(It,BBs[1]);
  // transfer the rest of the instructions
  BBs[1]->splice(BBs[1]->begin(), BB, std::next(MachineBasicBlock::iterator(MI)), BB->end());
  BBs[1]->transferSuccessorsAndUpdatePHIs(BB);
  // set successory
  BB->addSuccessor(BBs[0]);
  BB->addSuccessor(BBs[1]);
  BBs[0]->addSuccessor(BBs[1]);
}

typedef std::list<MachineInstr*> MachineInstrList;
typedef SmallVector<MachineInstr*,4> MachineInstrVec;
typedef SmallSet<unsigned,4> RegSet;

bool DestConflict(const MachineInstr& MI, const unsigned ind, const RegSet& dests)
{
  if (MI.getOperand(ind).isReg())
  {
    return dests.count(MI.getOperand(ind).getReg());
  }
  return false;
}

bool IsSame(const MachineOperand& a, const MachineOperand& b)
{
  if (!(a.isReg() && b.isReg()))
  {
    return false;
  }
  return a.getReg() == b.getReg();
}

// looks for more same selects
// MI - is always a select with a compare of two operands with lhs and rhs on ops 1 and 2
// selects - store any found instructions here
// return instruction after which to split BB
MachineInstr* CollectPseudoSelect(MachineInstr& MI,
                                  MachineBasicBlock* BB,
                                  MachineInstrList& selects,
                                  MachineInstrVec& debugVals,
                                  bool postRA)
{
  // this shouldn't happen
  if (postRA)
  {
    return &MI;
  }
  // no general support for now
  if (MI.getNumOperands() != 5)
  {
    return &MI;
  }
  const unsigned opc = MI.getOpcode();
  const MachineOperand& lhs = MI.getOperand(1);
  const MachineOperand& rhs = MI.getOperand(2);
  // a set of registers written into by the selects
  RegSet selectDests;
  // the first select itself
  selectDests.insert(MI.getOperand(0).getReg());
  // look ahead
  MachineBasicBlock::iterator MBI(MI);
  ++MBI;
  for (; MBI != BB->end(); ++MBI)
  {
    if (MBI->isDebugInstr()) continue;
    if (MBI->getOpcode() == opc)
    {
      if (!IsSame(MBI->getOperand(1),lhs)) break;
      if (!IsSame(MBI->getOperand(2),rhs)) break;
      if (DestConflict(*MBI,3,selectDests)) break;
      if (DestConflict(*MBI,4,selectDests)) break;
      selects.push_back(&*MBI);
      selectDests.insert(MBI->getOperand(0).getReg());
      MBI->collectDebugValues(debugVals);
    }
    else
    {
      if (MBI->hasUnmodeledSideEffects()) break;
      if (MBI->mayLoadOrStore()) break;
      auto pred = [&](MachineOperand &MO)
      {
        return MO.isReg() && MO.isUse() && selectDests.count(MO.getReg());
      };
      if (llvm::any_of(MBI->operands(), pred))
      {
        break;
      }
    }
  }
  if (!selects.empty())
  {
    LLVM_DEBUG(dbgs() << "\nPseudo-selects are going to be optimized:\n");
    LLVM_DEBUG(BB->dump());
    return selects.back();
  }
  return &MI;
}

void PhiDebugPrint(const SmallVector<MachineBasicBlock*,3>& BB)
{
  dbgs() << "\nPseudo-selects were optimized:\n";
  dbgs() << "Note: the first select wasn't removed yet.\n";
  BB[0]->dump();
  BB[2]->dump();
  dbgs() << "\n";
}

// inserts previously found same selects
void EmitAdditionalPhis(MachineInstrList& selects,
                        const MachineInstrVec& debugVals,
                        SmallVector<MachineBasicBlock*,3> BB,
                        const MCInstrDesc& phi)
{
  // make phis
  for (MachineInstr* MI: selects)
  {
    auto pos = BB[2]->begin();
    DebugLoc dl = MI->getDebugLoc();
    // this will reverse the order but riscv inserts the same way
    BuildMI(*BB[2], pos, dl, phi, MI->getOperand(0).getReg())
      .addReg(MI->getOperand(3).getReg()).addMBB(BB[0])
      .addReg(MI->getOperand(4).getReg()).addMBB(BB[1]);
    MI->eraseFromParent();
  }
  // insert any collected debug instrs
  for (MachineInstr* DI: debugVals)
  {
    if (DI->getParent()==BB[2])
    {
      continue;
    }
    // beyond any phis
    // (pos is invalidated every time)
    auto pos = BB[2]->getFirstNonPHI();
    BB[2]->insert(pos, DI->removeFromParent());
  }
  if (!selects.empty())
  {
    LLVM_DEBUG(PhiDebugPrint(BB));
  }
}

}//anonymous namespace

bool CodasipGenInstrInfo2::LowerExtractSubreg(MachineInstr* MIp, MachineBasicBlock* &BB) const
{
    MachineBasicBlock *MBB = MIp->getParent();
    assert((MIp->getOperand(0).isReg() && MIp->getOperand(0).isDef()) &&
           (MIp->getOperand(1).isReg() && MIp->getOperand(1).isUse()) &&
            MIp->getOperand(2).isImm() && "Invalid subreg_to_reg");

    unsigned DstReg  = MIp->getOperand(0).getReg();
    unsigned InsReg  = MIp->getOperand(1).getReg();
    assert(!MIp->getOperand(0).getSubReg() && "SubIdx on physreg?");
    unsigned SubIdx  = MIp->getOperand(2).getImm();
    assert(SubIdx != 0 && "Invalid index for insert_subreg");
    unsigned SrcSubReg = RI.getSubReg(InsReg, SubIdx);
    assert(CodasipRegisterInfo::isPhysicalRegister(DstReg) &&
           "Insert destination must be in a physical register");
    assert(CodasipRegisterInfo::isPhysicalRegister(SrcSubReg) &&
           "Inserted value must be in a physical register");

    if (MIp->allDefsAreDead())
    {
      MIp->setDesc(get(TargetOpcode::KILL));
      MIp->RemoveOperand(1); // SubIdx
      return true;
    }

    if (SrcSubReg == InsReg)
    {
      // No need to insert an identity copy instruction.
      // Watch out for case like this:
      // %rax = SUBREG_TO_REG 0, killed %eax, 3
      // We must leave %rax live.
      if (DstReg != InsReg)
      {
        MIp->setDesc(get(TargetOpcode::KILL));
        MIp->RemoveOperand(1);     // SubIdx
        return true;
      }
    }
    else
    {
      copyPhysReg(*MBB, MIp, MIp->getDebugLoc(), DstReg, SrcSubReg, MIp->getOperand(1).isKill());
      // Implicitly define DstReg for subsequent uses.
      MachineBasicBlock::iterator CopyMI = MIp;
      --CopyMI;
      CopyMI->addRegisterDefined(DstReg);
      MIp->dump();
      CopyMI->dump();
    }
    MBB->erase(MIp);
    return true;
}

// This is a merge of all possible expansions for all (three) places when such a thing can take place
bool CodasipGenInstrInfo2::ExpandDummiesImpl(MachineInstr* MIp, MachineBasicBlock* &BB, const bool postRA) const
{
  // skip this instruction?
  if (!ExpandedInstrs.count(MIp->getOpcode())) {
    return false;
  }
  assert(BB && MIp);
  // different regs on tied opers
  bool has2AdrConfl = false;
  // usable in post-RA only because of using an output operand (in L-side) as input (in R-side)
  bool postRaOnly = false;
  // no predicate suceeded?
  bool failed = false;
  MachineInstr &MI = *MIp;
  // this iterator will be overwritten if pseudo select
  MachineBasicBlock::instr_iterator MBI(MIp);
  MachineBasicBlock &MB = *BB;
  MachineFunction &MF = *MB.getParent();
  MachineRegisterInfo &MRI = MF.getRegInfo();
  DebugLoc dl = MI.getDebugLoc();
  const auto flags = MI.getFlags();
  // for subtarget features
  const CodasipSubtarget& CST = MF.getSubtarget<CodasipSubtarget>();
  // prepare register scavenger
  RegScavenger *RS = nullptr;
  RegScavenger RSInstance;
  if (postRA && MRI.tracksLiveness())
  {
    RS = &RSInstance;
    assert(&MI);
    // this is true for all post-ra cases
    assert(BB && BB==MI.getParent());
    RS->enterBasicBlockEnd(*BB);
    RS->backward(MI);
    // RA is forbidden (in any case)
    
    if (HasCall(*BB->getParent())) {
      RS->setRegUsed(Codasip::rf_xpr_1);
    }
    
    // if prologue/epilogue, block callee saved as well
    const unsigned frameFlags(MachineInstr::FrameSetup|MachineInstr::FrameDestroy);
    if (flags|frameFlags)
    {
      MachineFunction* MF = BB->getParent();
      assert(MF);
      const MCPhysReg* regs = RI.getCalleeSavedRegs(MF);
      while (*regs) {
        RS->setRegUsed(*regs);
        ++regs;
      }
    }
  }
  // mark start and stop
  bool wasStart = false;
  MachineBasicBlock::instr_iterator start(MBI);
  MachineBasicBlock::instr_iterator stop(start);
  if (start == MB.instr_begin()) {
    wasStart = true;
  }
  else {
    --start;
  }
  ++stop;
  // avoid warnings
  MRI.isSSA();
  // for PHI optim
  MachineInstrList selects;
  MachineInstrVec debugVals;
  // expand
  switch (MI.getOpcode())
  {
    case Codasip::EXTRACT_SUBREG:
      return LowerExtractSubreg(MIp, BB);
    case Codasip::KILL:
      MI.eraseFromParent();
      return true;
    case Codasip::COPY:
      if (MI.getOperand(0).isReg() && MI.getOperand(1).isReg()) {
        copyPhysReg(MB,MBI,dl, MI.getOperand(0).getReg(), MI.getOperand(1).getReg(),false);
      }
      break;
    case Codasip::rule_SELECT_7:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_8:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_9:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_10:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_11:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_12:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_13:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_14:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_15:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_16:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__)).addReg(MI.getOperand(1).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(3).getReg()).addMBB(BB).addReg(MI.getOperand(4).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    case Codasip::rule_SELECT_17:
    {
      auto* last = CollectPseudoSelect(MI,BB,selects,debugVals,postRA);
      MBI = MachineBasicBlock::instr_iterator(last);
      MachineBasicBlock *BBs[2];
      GetNextBB(BB,BBs,last);
      BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__)).addReg(MI.getOperand(1).getReg()).addMBB(BBs[1]);
      BuildMI(*BBs[1],BBs[1]->begin(), dl, get(Codasip::PHI), MI.getOperand(0).getReg()).addReg(MI.getOperand(2).getReg()).addMBB(BB).addReg(MI.getOperand(3).getReg()).addMBB(BBs[0]);
      EmitAdditionalPhis(selects, debugVals, {BB,BBs[0],BBs[1]}, get(Codasip::PHI));
      BB = BBs[1];
      break;
    }
    
    case Codasip::i_call_reg_alias__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_call_reg_alias__simm12__xpr_general__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(1);
MachineOperand op_1_1 = MI.getOperand(0);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__)).add(op_1_0).add(op_1_1).add(op_1_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(1);
MachineOperand op_1_1 = MI.getOperand(0);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__)).add(op_1_0).add(op_1_1).add(op_1_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(1);
MachineOperand op_1_1 = MI.getOperand(0);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__)).add(op_1_0).add(op_1_1).add(op_1_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(1);
MachineOperand op_1_1 = MI.getOperand(0);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__)).add(op_1_0).add(op_1_1).add(op_1_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__0__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__1__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MachineOperand::CreateImm(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__0__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__1__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MachineOperand::CreateImm(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(2);
MachineOperand op_1_2 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(2);
MachineOperand op_1_2 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
MachineOperand op_1_2 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_2 = MachineOperand::CreateImm(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__immspec_1_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
BuildMI(MB,MBI,dl, get(Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::e_movi32__:
    case Codasip::e_movi32__GA:
    case Codasip::e_movi32__ES:
    case Codasip::e_movi32__MC:
    case Codasip::e_movi32__BA:
    case Codasip::e_movi32__JT:
    case Codasip::e_movi32__CP:
    {
      if (postRA) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__1_)).add(op_1_0).add(op_1_1);
MachineOperand op_2_0 = MachineOperand::CreateReg(Codasip::rf_xpr_30,1);
MachineOperand op_2_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__2_)).add(op_2_0).add(op_2_1);
MachineOperand op_3_0 = MachineOperand::CreateReg(Codasip::rf_xpr_30,1);
MachineOperand op_3_1 = MachineOperand::CreateReg(Codasip::rf_xpr_30,0);
MachineOperand op_3_2 = MachineOperand::CreateImm(12);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_shift__opc_srli__xpr_general__xpr_general__uimm5__)).add(op_3_0).add(op_3_1).add(op_3_2);
MachineOperand op_4_0 = MI.getOperand(0);
MachineOperand op_4_2 = MachineOperand::CreateReg(MI.getOperand(0).getReg(),false);
postRaOnly = true;
MachineOperand op_4_1 = MachineOperand::CreateReg(Codasip::rf_xpr_30,0);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_or__xpr_general__xpr_general__xpr_general__)).add(op_4_0).add(op_4_1).add(op_4_2);
      }
      else if ((!(postRA))) {
unsigned virtreg_0 = MRI.createVirtualRegister(&Codasip::xpr_generalRegClass);
MachineOperand op_1_0 = MachineOperand::CreateReg(virtreg_0,1);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__5_)).add(op_1_0).add(op_1_1);
MachineOperand op_2_0 = MachineOperand::CreateReg(Codasip::rf_xpr_30,1);
MachineOperand op_2_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__6_)).add(op_2_0).add(op_2_1);
MachineOperand op_3_0 = MachineOperand::CreateReg(Codasip::rf_xpr_30,1);
MachineOperand op_3_1 = MachineOperand::CreateReg(Codasip::rf_xpr_30,0);
MachineOperand op_3_2 = MachineOperand::CreateImm(12);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_shift__opc_srli__xpr_general__xpr_general__uimm5__)).add(op_3_0).add(op_3_1).add(op_3_2);
MachineOperand op_4_0 = MI.getOperand(0);
MachineOperand op_4_2 = MachineOperand::CreateReg(virtreg_0,0);
MachineOperand op_4_1 = MachineOperand::CreateReg(Codasip::rf_xpr_30,0);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_or__xpr_general__xpr_general__xpr_general__)).add(op_4_0).add(op_4_1).add(op_4_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_ret_alias__TAILCALL_CLONE_:
    {
      if (true) {
BuildMI(MB,MBI,dl, get(Codasip::i_ret_alias__));
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_TAILCALL_CLONE_:
    {
      if (true) {
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1);
      }
      else failed=true;
      break;
    }
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__)).add(op_1_0);
      }
      else failed=true;
      break;
    }
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__)).add(op_1_0);
      }
      else failed=true;
      break;
    }
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__)).add(op_1_0);
      }
      else failed=true;
      break;
    }
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__)).add(op_1_0);
      }
      else failed=true;
      break;
    }
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__)).add(op_1_0);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_ES:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_MC:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_BA:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__)).add(op_1_0);
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__i32_TRUNC_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__)).add(op_1_0).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__i32_TRUNC_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__)).add(op_1_0).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
    {
      if (true) {
MachineOperand op_1_0 = MI.getOperand(0);
MachineOperand op_1_1 = MI.getOperand(1);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_:
    {
      if (true) {
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_:
    {
      if (true) {
MachineOperand op_1_1 = MachineOperand::CreateImm(0);
MachineOperand op_1_0 = MI.getOperand(0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__)).add(op_1_0).add(op_1_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__0_REG_EMUL_:
    {
      if ((postRA && true)) {
assert(RS);
unsigned auxreg_0 = RS->FindUnusedReg(&Codasip::xpr_generalRegClass);
assert(auxreg_0 && "failed to find an unused register");
RS->setRegUsed(auxreg_0);
MachineOperand op_1_0 = MachineOperand::CreateReg(auxreg_0,1);
MachineOperand op_1_2 = MI.getOperand(1);
MachineOperand op_1_1 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2);
MachineOperand op_2_0 = MI.getOperand(0);
MachineOperand op_2_1 = MachineOperand::CreateReg(auxreg_0,0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__immspec_1_)).add(op_2_0).add(op_2_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__1_BIGIMM_EMUL_:
    {
      if (postRA) {
assert(RS);
unsigned auxreg_0 = RS->FindUnusedReg(&Codasip::xpr_generalRegClass);
assert(auxreg_0 && "failed to find an unused register");
RS->setRegUsed(auxreg_0);
MachineOperand op_1_0 = MachineOperand::CreateReg(auxreg_0,1);
MachineOperand op_1_1 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::e_movi32__)).add(op_1_0).add(op_1_1);
MachineOperand op_2_0 = MI.getOperand(0);
MachineOperand op_2_1 = MI.getOperand(1);
MachineOperand op_2_2 = MachineOperand::CreateReg(auxreg_0,0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__0_REG_EMUL_)).add(op_2_0).add(op_2_1).add(op_2_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__2_REG_EMUL_:
    {
      if ((postRA && true)) {
assert(RS);
unsigned auxreg_0 = RS->FindUnusedReg(&Codasip::xpr_generalRegClass);
assert(auxreg_0 && "failed to find an unused register");
RS->setRegUsed(auxreg_0);
MachineOperand op_1_0 = MachineOperand::CreateReg(auxreg_0,1);
MachineOperand op_1_2 = MI.getOperand(1);
MachineOperand op_1_1 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(op_1_0).add(op_1_1).add(op_1_2);
MachineOperand op_2_0 = MI.getOperand(0);
MachineOperand op_2_1 = MachineOperand::CreateReg(auxreg_0,0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__immspec_1_)).add(op_2_0).add(op_2_1).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__3_BIGIMM_EMUL_:
    {
      if (postRA) {
assert(RS);
unsigned auxreg_0 = RS->FindUnusedReg(&Codasip::xpr_generalRegClass);
assert(auxreg_0 && "failed to find an unused register");
RS->setRegUsed(auxreg_0);
MachineOperand op_1_0 = MachineOperand::CreateReg(auxreg_0,1);
MachineOperand op_1_1 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::e_movi32__)).add(op_1_0).add(op_1_1);
MachineOperand op_2_0 = MI.getOperand(0);
MachineOperand op_2_1 = MI.getOperand(1);
MachineOperand op_2_2 = MachineOperand::CreateReg(auxreg_0,0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__2_REG_EMUL_)).add(op_2_0).add(op_2_1).add(op_2_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__4_BIGIMM_EMUL_:
    {
      if (postRA) {
assert(RS);
unsigned auxreg_0 = RS->FindUnusedReg(&Codasip::xpr_generalRegClass);
assert(auxreg_0 && "failed to find an unused register");
RS->setRegUsed(auxreg_0);
MachineOperand op_1_0 = MachineOperand::CreateReg(auxreg_0,1);
MachineOperand op_1_1 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::e_movi32__)).add(op_1_0).add(op_1_1);
MachineOperand op_2_0 = MI.getOperand(0);
MachineOperand op_2_1 = MI.getOperand(1);
MachineOperand op_2_2 = MachineOperand::CreateReg(auxreg_0,0);
BuildMI(MB,MBI,dl, get(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__0_REG_EMUL_)).add(op_2_0).add(op_2_1).add(op_2_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__5_BIGIMM_EMUL_:
    {
      if (postRA) {
assert(RS);
unsigned auxreg_0 = RS->FindUnusedReg(&Codasip::xpr_generalRegClass);
assert(auxreg_0 && "failed to find an unused register");
RS->setRegUsed(auxreg_0);
MachineOperand op_1_0 = MachineOperand::CreateReg(auxreg_0,1);
MachineOperand op_1_1 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::e_movi32__)).add(op_1_0).add(op_1_1);
MachineOperand op_2_0 = MI.getOperand(0);
MachineOperand op_2_1 = MI.getOperand(1);
MachineOperand op_2_2 = MachineOperand::CreateReg(auxreg_0,0);
BuildMI(MB,MBI,dl, get(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__2_REG_EMUL_)).add(op_2_0).add(op_2_1).add(op_2_2).setMemRefs(MI.memoperands());
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__6_BIGIMM_EMUL_:
    {
      if (postRA) {
assert(RS);
unsigned auxreg_0 = RS->FindUnusedReg(&Codasip::xpr_generalRegClass);
assert(auxreg_0 && "failed to find an unused register");
RS->setRegUsed(auxreg_0);
MachineOperand op_1_0 = MachineOperand::CreateReg(auxreg_0,1);
MachineOperand op_1_1 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::e_movi32__)).add(op_1_0).add(op_1_1);
MachineOperand op_2_0 = MI.getOperand(0);
MachineOperand op_2_1 = MI.getOperand(1);
MachineOperand op_2_2 = MachineOperand::CreateReg(auxreg_0,0);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(op_2_0).add(op_2_1).add(op_2_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__7_BIGIMM_EMUL_:
    {
      if (postRA) {
assert(RS);
unsigned auxreg_0 = RS->FindUnusedReg(&Codasip::xpr_generalRegClass);
assert(auxreg_0 && "failed to find an unused register");
RS->setRegUsed(auxreg_0);
MachineOperand op_1_0 = MachineOperand::CreateReg(auxreg_0,1);
MachineOperand op_1_1 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::e_movi32__)).add(op_1_0).add(op_1_1);
MachineOperand op_2_0 = MI.getOperand(0);
MachineOperand op_2_1 = MI.getOperand(1);
MachineOperand op_2_2 = MachineOperand::CreateReg(auxreg_0,0);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(op_2_0).add(op_2_1).add(op_2_2);
      }
      else failed=true;
      break;
    }
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__8_BIGIMM_EMUL_:
    {
      if (postRA) {
assert(RS);
unsigned auxreg_0 = RS->FindUnusedReg(&Codasip::xpr_generalRegClass);
assert(auxreg_0 && "failed to find an unused register");
RS->setRegUsed(auxreg_0);
MachineOperand op_1_0 = MachineOperand::CreateReg(auxreg_0,1);
MachineOperand op_1_1 = MI.getOperand(2);
BuildMI(MB,MBI,dl, get(Codasip::e_movi32__)).add(op_1_0).add(op_1_1);
MachineOperand op_2_0 = MI.getOperand(0);
MachineOperand op_2_1 = MI.getOperand(1);
MachineOperand op_2_2 = MachineOperand::CreateReg(auxreg_0,0);
BuildMI(MB,MBI,dl, get(Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__)).add(op_2_0).add(op_2_1).add(op_2_2);
      }
      else failed=true;
      break;
    }
    
    default:
      return false; // like in TargetInstrInfo::expandPostRAPseudo(MBI)
  }
  // at least one side succeeded?
  if (failed)
  {
    errs() << "An emulation occured where all predicates failed.\n";
    abort();
  }
  // copy variadic operands
  if (MI.isVariadic())
  {
    MachineBasicBlock::instr_iterator it = MBI;
    --it;
    const MCInstrDesc& dsc = MI.getDesc();
    for (unsigned i=dsc.getNumOperands(); i<MI.getNumOperands(); ++i)
    {
      MachineOperand op = MI.getOperand(i);
      // add register operands as implicit
      if (op.isReg())
      {
        op.setImplicit();
      }
      // note: if this is a call, a regmask is among these operands
      it->addOperand(op);
    }
  }
  // remove original
  MI.eraseFromParent();
  // checks for post-RA
  if (postRA)
  {
    // two-address conflicts
    if (has2AdrConfl) {
      errs() << "Usage of coflicting registers in tied operands not allowed in post-RA passes.\n";
      abort();
    }
    // check kills and edit them, if needed
    MachineBasicBlock::instr_iterator it;
    if (wasStart) {
      start = MB.instr_begin();
      it = MB.instr_begin();
    }
    else {
      it = start;
      ++it;
    }
    std::set<unsigned> kills;
    while (it != stop)
    {
      // no PHIs this late!
      assert(it != MB.instr_end() && "invalid operation in post-RA");
      for (const MachineOperand& mo: it->operands())
      {
        if (mo.isReg() && mo.isKill()) {
          assert(!mo.isDef());
          kills.insert(mo.getReg());
        }
      }
      // add frame flags
      it->setFlags(flags);
      ++it;
    }
    --it;
    do {
      for (MachineOperand& mo: it->operands())
      {
        if (mo.isReg() && !mo.isDef())
        {
          if (kills.count(mo.getReg())) {
            mo.setIsKill(true);
            kills.erase(mo.getReg());
          }
          else {
            mo.setIsKill(false);
          }
        }
      }
    }
    while (it-- != start);
  }
  // checks for pre-RA
  else
  {
    if (postRaOnly) {
      errs() << "Non-SSA emulations aren't allowed to be used in pre-RA";
      abort();
    }
  }
  return true;
}

// Note: TargetInstrInfo::expandPostRAPseudo just returns false
bool CodasipGenInstrInfo2::expandPostRAPseudo(MachineInstr& MI) const
{
  // skip?
  switch (MI.getOpcode())
  {
    case TargetOpcode::COPY:
    case TargetOpcode::DBG_VALUE:
      return false;
  }
  // mark positions
  MachineBasicBlock* BB = MI.getParent();
  bool wasBegin = false;
  MachineBasicBlock::instr_iterator start(&MI);
  MachineBasicBlock::instr_iterator stop = start;
  assert(stop != BB->instr_end());
  ++stop;
  if (start == BB->instr_begin())
  {
    wasBegin = true;
  }
  else
  {
    --start;
  }
  // replace
  bool check = ExpandDummiesImpl(&MI,BB,true);
  if (!check)
  {
    return TargetInstrInfo::expandPostRAPseudo(MI);
  }
  // recurse
  MachineBasicBlock::instr_iterator it;
  if (wasBegin)
  {
    it = BB->instr_begin();
  }
  else
  {
    it = start;
    ++it;
  }
  while (it != stop)
  {
    assert(it != BB->instr_end());
    MachineInstr& MI2 = *it;
    ++it;
    if (!MI2.isPseudo()) continue;
    expandPostRAPseudo(MI2);
  }
  return true;
}

JumpInfo CodasipGenInstrInfo2::GetJumpInfo(int op) const
{
  JumpInfo ret = {0,1,0};
  switch (op)
  {
    case Codasip::i_ret_alias__:
      ret.IsAbsolute = 1;
      ret.Length = 32;
      break;
    case Codasip::i_call_reg_alias__simm12__xpr_general__immspec_1_:
      ret.IsAbsolute = 1;
      ret.Length = 32;
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_:
      ret.IsAbsolute = 1;
      ret.Length = 32;
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__immspec_1_:
      ret.IsAbsolute = 1;
      ret.Length = 32;
      break;
    case Codasip::i_call_alias__relative_addr20__:
    case Codasip::i_call_alias__relative_addr20__ES:
    case Codasip::i_call_alias__relative_addr20__MC:
    case Codasip::i_call_alias__relative_addr20__BA:
      ret.IsAbsolute = 0;
      ret.Length = 21;
      ret.Direction = 0;
      break;
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__:
      ret.IsAbsolute = 1;
      ret.Length = 21;
      break;
    case Codasip::i_jal_abs_calias__opc_jal__xpr_general__relative_addr20__:
      ret.IsAbsolute = 1;
      ret.Length = 21;
      break;
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__:
      ret.IsAbsolute = 0;
      ret.Length = 21;
      ret.Direction = 0;
      break;
    case Codasip::i_jtype_jlink__opc_jal__xpr_general__relative_addr20__:
      ret.IsAbsolute = 0;
      ret.Length = 21;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_beq__xpr_general__x_0__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__x_0__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_blt__x_0__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__x_0__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bne__x_0__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bne__xpr_general__x_0__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_call_reg_alias__simm12__x_0__:
    case Codasip::i_call_reg_alias__simm12__x_0__ES:
    case Codasip::i_call_reg_alias__simm12__x_0__MC:
    case Codasip::i_call_reg_alias__simm12__x_0__BA:
      ret.IsAbsolute = 1;
      ret.Length = 12;
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__:
      ret.IsAbsolute = 1;
      ret.Length = 12;
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0__:
      ret.IsAbsolute = 1;
      ret.Length = 12;
      break;
    case Codasip::i_ret_alias__TAILCALL_CLONE_:
      ret.IsAbsolute = 1;
      ret.Length = 32;
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_TAILCALL_CLONE_:
      ret.IsAbsolute = 1;
      ret.Length = 32;
      break;
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA:
      ret.IsAbsolute = 1;
      ret.Length = 21;
      break;
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA:
      ret.IsAbsolute = 0;
      ret.Length = 21;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
      ret.IsAbsolute = 0;
      ret.Length = 13;
      ret.Direction = 0;
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_ES:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_MC:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_BA:
      ret.IsAbsolute = 1;
      ret.Length = 12;
      break;
    case Codasip::i_call_reg_alias__simm12__xpr_general__:
      ret.IsAbsolute = 1;
      ret.Length = 32;
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__:
      ret.IsAbsolute = 1;
      ret.Length = 32;
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__:
      ret.IsAbsolute = 1;
      ret.Length = 32;
      break;
    
    default: ;
  }
  return ret;
}

static inline unsigned computeDistanceDown(MachineFunction &F, MachineFunction::iterator FI, MachineBasicBlock::instr_iterator I, MachineBasicBlock *dest)
{
  // is it to the beginning of the current BB?
  if (&(*FI)==dest) return 0;
  // continue down
  unsigned dist = 0;
  while (FI != F.end())
  {
    // are we at the beginning of the target block?
    if (&(*FI)==dest) {
      assert(I==FI->instr_begin());
      return dist;
    }
    // iterate through the block
    for (; I != FI->instr_end(); ++I)
    {
      dist += GetEncodingSize(I);
    }
    // shift the iterators
    ++FI;
    if (FI != F.end()) {
      I = FI->instr_begin();
    }
  }
  // not found
  return 0;
}

static inline unsigned computeDistanceUp(MachineFunction &F, MachineFunction::iterator FI, MachineBasicBlock::instr_iterator II, MachineBasicBlock *dest)
{
  unsigned dist = 0;
  // compute the distance to the beginning of the current block
  for (MachineBasicBlock::instr_iterator I=FI->instr_begin(); I!=II; ++I)
  {
    assert(I != FI->instr_end());
    dist += GetEncodingSize(I);
  }
  // is this it?
  if (&(*FI)==dest) return dist;
  // compute the remaining blocks
  while (FI != F.begin())
  {
    // next block
    --FI;
    // sum this block
    for (MachineBasicBlock::instr_iterator I=FI->instr_begin(); I!=FI->instr_end(); ++I)
    {
      dist += GetEncodingSize(I);
    }
    // is this it?
    if (&(*FI)==dest) return dist;
  }
  return 0;
}

unsigned ComputeDistance(MachineFunction &F, MachineFunction::iterator FI, MachineBasicBlock::instr_iterator I, MachineBasicBlock *dest)
{
  unsigned l = 0;
  for (const MachineBasicBlock &mbb : F) {
    if (&mbb == &(*FI) && &mbb == dest) {
      l = computeDistanceUp(F,FI,I,dest);
      break;
    } else if (&mbb == &(*FI)) {
      l = computeDistanceDown(F,FI,I,dest);
      break;
    } else if (&mbb == dest) {
      l = computeDistanceUp(F,FI,I,dest);
      break;
    }
  }
  return l;
}

// Print warning - only once.
inline static void ZeroSizeWarning(const MachineBasicBlock::instr_iterator &I)
{
  // Was there a zero-sized instruction warning already?
  static bool visited = false;
  if (visited) return;
  // is this truly one of our instructions?
  if (!(I->getOpcode()>Codasip::CALLSTART && I->getOpcode()<Codasip::INSTRUCTION_LIST_END)) return;
  // mark
  visited = true;
  // Print warning.
  errs() << "Instructions without defined coding size encountered. Check of lengths of jumps won't be accurate.\n";
}

unsigned GetEncodingSize(const MachineBasicBlock::instr_iterator &I)
{
  const MCInstrDesc &dsc = I->getDesc();
  const unsigned maxEncSize = 4;
  // is this inline asm?
  if (I->getOpcode()==Codasip::INLINEASM)
  {
    const MachineOperand &op = I->getOperand(0);
    assert(op.getType()==MachineOperand::MO_ExternalSymbol);
    const char *text = op.getSymbolName();
    // count lines
    unsigned cnt = 1;
    for (unsigned i=0; text[i]; ++i)
    {
      if (text[i]=='\n') ++cnt;
    }
    return cnt*maxEncSize;
  }
  if (I->isCopy()) return maxEncSize;
  // continue normally
  if (!dsc.getSize()) ZeroSizeWarning(I); 
  return dsc.getSize();
}

void CodasipGenInstrInfo2::GetImmProperties(unsigned opCode, unsigned opNum, int& width, bool& sign, int& trunc) const
{
  switch (opCode)
  {
    case Codasip::i_itype_alu__opc_addi__xpr_general__x_0__simm12__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_andi__xpr_general__xpr_general__simm12__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_ori__xpr_general__x_0__simm12__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_ori__xpr_general__xpr_general__simm12__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_xori__xpr_general__x_0__simm12__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__x_0__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__x_0__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__xpr_general__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__x_0__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__x_0__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__xpr_general__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__x_0__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_rtype_shift__opc_slli__xpr_general__xpr_general__uimm5__:
    switch (opNum) {
    case 2: width = 5; sign = 0; trunc = 0; break;
    }
    break;
    case Codasip::i_rtype_shift__opc_srai__xpr_general__xpr_general__uimm5__:
    switch (opNum) {
    case 2: width = 5; sign = 0; trunc = 0; break;
    }
    break;
    case Codasip::i_rtype_shift__opc_srli__xpr_general__xpr_general__uimm5__:
    switch (opNum) {
    case 2: width = 5; sign = 0; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__x_0__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__x_0__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sw__x_0__simm12__x_0__:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__x_0__:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__:
    switch (opNum) {
    case 1: width = 32; sign = 0; trunc = 12; break;
    }
    break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__:
    switch (opNum) {
    case 1: width = 32; sign = 0; trunc = 12; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__AEXT_CLONE_:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__AEXT_CLONE_:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__AEXT_CLONE_:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__AEXT_CLONE_:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__AEXT_CLONE_:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__AEXT_CLONE_:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
    switch (opNum) {
    case 2: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::e_movi32__:
    switch (opNum) {
    }
    break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__i32_TRUNC_CLONE_:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__i32_TRUNC_CLONE_:
    switch (opNum) {
    case 0: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
    switch (opNum) {
    case 1: width = 12; sign = 1; trunc = 0; break;
    }
    break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__1_BIGIMM_EMUL_:
    switch (opNum) {
    }
    break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__3_BIGIMM_EMUL_:
    switch (opNum) {
    }
    break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__4_BIGIMM_EMUL_:
    switch (opNum) {
    }
    break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__5_BIGIMM_EMUL_:
    switch (opNum) {
    }
    break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__6_BIGIMM_EMUL_:
    switch (opNum) {
    }
    break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__7_BIGIMM_EMUL_:
    switch (opNum) {
    }
    break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__8_BIGIMM_EMUL_:
    switch (opNum) {
    }
    break;
    
    default: width = -1; sign = false; trunc = -1;
      break;
  }
}

BuiltinInfo CodasipGenInstrInfo2::GetBuiltinInfo(unsigned intrinCode) const
{
  BuiltinInfo ret;
  ret.NodeID = CodasipISD::LAST_NUMBER;
  switch (intrinCode)
  {
    
    default:
      assert(false && "unknown builtin");
  }
  return ret;
}

static bool IsCodasipIntrinImpl(unsigned intrinCode, bool mem)
{
  switch (intrinCode)
  {
    case Intrinsic::codasip_builtin:
    case Intrinsic::codasip_builtin_anyint:
    case Intrinsic::codasip_builtin_anyfloat:
    case Intrinsic::codasip_builtin_anyptr:
    case Intrinsic::codasip_builtin_anyvector:
    case Intrinsic::codasip_builtin_anyint_anyint:
    case Intrinsic::codasip_builtin_anyint_anyint_anyint:
    case Intrinsic::codasip_builtin_anyint_anyint_anyint_anyint:
    case Intrinsic::codasip_builtin_anyint_anyint_anyint_anyint_anyint:
      return true;
    case Intrinsic::codasip_builtin_nomem_anyint:
    case Intrinsic::codasip_builtin_nomem_anyfloat:
    case Intrinsic::codasip_builtin_nomem_anyptr:
    case Intrinsic::codasip_builtin_nomem_anyvector:
    case Intrinsic::codasip_builtin_nomem_anyint_anyint:
    case Intrinsic::codasip_builtin_nomem_anyint_anyint_anyint:
    case Intrinsic::codasip_builtin_nomem_anyint_anyint_anyint_anyint:
    case Intrinsic::codasip_builtin_nomem_anyint_anyint_anyint_anyint_anyint:
      return !mem;
    default:
      return false;
  }
}

bool IsCodasipIntrin(unsigned intrinCode)
{
  return IsCodasipIntrinImpl(intrinCode,false);
}

bool IsCodasipMemIntrin(unsigned intrinCode)
{
  return IsCodasipIntrinImpl(intrinCode,true);
}

/************************** MachineOutliner **************************/

#define ALT_CALL LibCSSpillInstr
#define ALT_RAR LibCSSpillReg
#define JUMP_DIRECT getLongJumpOpcode()
#define CALL_DIRECT getLongCallOpcode()
#define RAR_MV_SIZE 4
// ordinary return
#define RETURN Codasip::i_ret_alias__
// used as (alt)return
#define JUMP_INDIRECT Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_

unsigned CodasipGenInstrInfo2::getLongJumpOpcode() const
{
  return Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__;
}

unsigned CodasipGenInstrInfo2::getLongCallOpcode() const
{
  return Codasip::i_call_alias__relative_addr20__;
}

unsigned CodasipGenInstrInfo2::getShortCallOpcode() const
{
  return Codasip::i_call_reg_alias__simm12__x_0__;
}

unsigned CodasipGenInstrInfo2::getLongTailCallOpcode() const
{
  return Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_;
}

unsigned CodasipGenInstrInfo2::getShortTailCallOpcode() const
{
  return Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_;
}

bool CodasipGenInstrInfo2::LibCSSupported() const
{
  return LibCSSpillInstr && LibCSSpillReg;
}

// It's preferred to use alternative link reg if it's available, this will be
// generated based on existence of ALR and the call utilizing it.
inline bool CodasipGenInstrInfo2::useAlternativeLinkReg() const
{
  return LibCSSupported();
}

unsigned CodasipGenInstrInfo2::getInstSizeInBytes(const MachineInstr &MI) const
{
  switch (MI.getOpcode()) {
  case TargetOpcode::INLINEASM: { // Inline Asm: Variable size.
    const MachineFunction *MF = MI.getParent()->getParent();
    const char *AsmStr = MI.getOperand(0).getSymbolName();
    return getInlineAsmLength(AsmStr, *MF->getTarget().getMCAsmInfo());
  }
  // Add more cases here if necessary
  default:
    // Note that getSize() returns zero when it can't determine size, so
    // by default we should return some default instruction size, not 0.
    // This is unfortunate, because it returns 0 for both DEBUG (correctly) and
    // for unknowns (probably incorrectly). We currently rely on the fact that
    // our targets generate this information for every instruction.
    return MI.getDesc().getSize();
  }
}

// Enum values indicating how an outlined call should be constructed.
enum MachineOutlinerConstructionID
{
  // (Note: ALR == Alternative Link Register, ALT_RAR)
  // It's best to use ALR if available, so this is the default.
  // No terminator in the candidate, insert AltCall ALR Outlined_Fn;
  // return by ALR with indirect jump:
  MachineOutlinerDefault,
  // We don't have ALR or at least we don't have a call that can use it.
  // This is like default in that RA doesn't need to be saved.
  // Insert direct call to Outlined_Fn, return normally
  MachineOutlinerRA,
  // This candidate already has Return and we have to use RA.
  // jump to Outlined_Fn; no need to insert anything to outlined function.
  MachineOutlinerRATailCall,
  // Like MachineOutlinerRA, except RA needs to be saved in an available
  // register. This is the last resort, as it has a large cost.
  // Find available reg (e.g. x10), then insert:
  // x10 = RA; direct call Outlined_Fn; RA = x10
  // return normally just like in MachineOutlinerRA
  MachineOutlinerRARegSave
};

static bool isACalleeSavedRegister(unsigned reg,
                                   const TargetRegisterInfo &TRI,
                                   const MachineFunction &MF)
{
  const MCPhysReg *CSR = MF.getRegInfo().getCalleeSavedRegs();
  for (unsigned i = 0; CSR[i] != 0; ++i)
    if (TRI.regsOverlap(reg, CSR[i]))
      return true;
  return false;
}

unsigned CodasipGenInstrInfo2::findRegisterToSaveLRTo(const outliner::Candidate &C) const
{
  
  assert(C.LRUWasSet && "LRU wasn't set?");
  const MachineFunction *MF = C.getMF();
  const CodasipRegisterInfo *CRI = static_cast<const CodasipRegisterInfo *>(
      MF->getSubtarget().getRegisterInfo());
  const MachineRegisterInfo &MRI = MF->getRegInfo();
  // RAR and a class to copy it to
  unsigned RAReg = CRI->getRARegister();
  const auto &RARBackupClass = Codasip::xpr_generalRegClass;
  // Check if there is an available register across the sequence that we can use.
  for (unsigned Reg : RARBackupClass) {
    // Find an available register that is not reserved, caller-saved and unused:
    if (!MRI.isReserved(Reg) && !isACalleeSavedRegister(Reg, *CRI, *MF) &&
        Reg != RAReg && C.LRU.available(Reg) &&
        C.UsedInSequence.available(Reg)) {
      return Reg;
    }
  }
  
  // No suitable register.
  return 0u;
}

bool CodasipGenInstrInfo2::isFunctionSafeToOutlineFrom(MachineFunction &MF,
                                                       bool OutlineFromLinkOnceODRs) const
{
  const Function &F = MF.getFunction();
  // Can F be deduplicated by the linker? If it can, don't outline from it.
  if (!OutlineFromLinkOnceODRs && F.hasLinkOnceODRLinkage())
    return false;
  // Don't outline from functions with section markings; the program could
  // expect that all the code is in the named section.
  if (F.hasSection())
    return false;
  // Some passes such as Delay Slot Filler invalidate liveness, in that case
  // we can't safely outline anything.
  if (!MF.getRegInfo().tracksLiveness())
    return false;

  // Don't outline when hwloops are present.
  std::vector<int> HWLoopOpcs;
  getHWLoopOpc(HWLoopOpcs);
  for (const auto &MBB : MF) {
    if (any_of(MBB.instrs(), [&HWLoopOpcs](const MachineInstr &MI) {
          return is_contained(HWLoopOpcs, MI.getOpcode());
        }))
      return false;
  }

  return true;
}

bool CodasipGenInstrInfo2::isMBBSafeToOutlineFrom(MachineBasicBlock &MBB, unsigned &Flags) const
{
  // More accurate safety checking is done in getOutliningCandidateInfo.
  return true;
}

outliner::OutlinedFunction CodasipGenInstrInfo2::getOutliningCandidateInfo(
    std::vector<outliner::Candidate> &RepeatedSequenceLocs) const
{
  const CodasipRegisterInfo &CRI = getRegisterInfo();

  const unsigned CallUsed = useAlternativeLinkReg() ? ALT_CALL : CALL_DIRECT;
  const MCInstrDesc &CallDesc = get(CallUsed);
  SmallVector<Register, 4> CallDefs;
  if (CallDesc.getImplicitDefs())
    for (const MCPhysReg *ImpDef = CallDesc.getImplicitDefs(); *ImpDef; ++ImpDef) {
      // RA is accounted for.
      if (CRI.getRARegister() != *ImpDef)
        CallDefs.push_back(*ImpDef);
    }
  const unsigned RARegUsed = useAlternativeLinkReg() ? ALT_RAR : CRI.getRARegister();
  // Filter out candidates where RA/AltRA can't be used to setup the function call.
  auto CannotInsertCall = [&](outliner::Candidate &C) {
    C.initLRU(CRI);
    // TODO: improve this. RA can be used even when AltRA is unavailable but
    // allowed.

    // if any of the calldefs are unavailable here, we can't outline.
    if (any_of(CallDefs, [&](unsigned R) { return !C.LRU.available(R); })) {
      return true;
    }
    // Note that it's not enough to check for liveness of RA through LRU.
    // RA can be seen as "unused" when the candidate sequence is located between
    // an epilogue and a tailcall. This rarely happens e.g. on architectures
    // with load latency over 16 cycles, where sequences of instructions after
    // an epilogue can be outlined.
    // RA in this case looks like "unused", but is used later in the tailcalled
    // function's return.
    // This is problematic, because epilogue loads are exactly the sequences we
    // want outlined.
    // So don't outline after an epilogue if RA has already been restored:
    for (auto MBBIt = C.front(), E = C.getMBB()->begin(); MBBIt != E; MBBIt--) {
      if (MBBIt->getFlag(MachineInstr::FrameDestroy) &&
          MBBIt->modifiesRegister(RARegUsed, &CRI))
        return true;
    }

    // if RA is used, we can't outline either.
    return !C.LRU.available(RARegUsed);
  };

  RepeatedSequenceLocs.erase(std::remove_if(RepeatedSequenceLocs.begin(),
                                            RepeatedSequenceLocs.end(),
                                            CannotInsertCall),
                             RepeatedSequenceLocs.end());

  // If the sequence doesn't have enough candidates left, then we're done.
  if (RepeatedSequenceLocs.size() < 2) {
    LLVM_DEBUG(dbgs() << "Not enough repeated sequences.\n");
    return outliner::OutlinedFunction();
  }

  unsigned SequenceSize = 0;

  for (auto I = RepeatedSequenceLocs[0].front(), E = std::next(RepeatedSequenceLocs[0].back()); I != E; ++I) {
    SequenceSize += getInstSizeInBytes(*I);
  }

  // default
  auto ConstructID = MachineOutlinerDefault;
  unsigned FrameOverhead = 0;
  unsigned CallOverhead = get(CALL_DIRECT).getSize();
  auto LastInst = RepeatedSequenceLocs[0].back();
  while (LastInst->isPseudo() &&
      LastInst != RepeatedSequenceLocs[0].front()) { // dummy, debug, cfi
    LastInst--;
  }

  if (LastInst->isTerminator()) {
    ConstructID = MachineOutlinerRATailCall;
  } else if (LastInst->isCall()) {
    return outliner::OutlinedFunction();
  } else {
    if (useAlternativeLinkReg()) {
      ConstructID = MachineOutlinerDefault;
    } else if (std::all_of(RepeatedSequenceLocs.begin(),
                           RepeatedSequenceLocs.end(),
                           [&](outliner::Candidate &C) {
                             // !isReserved;
                             return !CRI.getReservedRegs(*(C.getMF()))
                                 .test(CRI.getRARegister());
                           })) {
      ConstructID = MachineOutlinerRA;
    } else if (std::all_of(RepeatedSequenceLocs.begin(),
                           RepeatedSequenceLocs.end(),
                           [this](outliner::Candidate &C) {
                             return findRegisterToSaveLRTo(C);
                           })) {
      ConstructID = MachineOutlinerRARegSave;
      // two moves are inserted to save and restore RA Reg:
      CallOverhead += 2*RAR_MV_SIZE;
    } else {
      LLVM_DEBUG(dbgs() << "No caller-saved reg available.\n");
      return outliner::OutlinedFunction();
    }
    unsigned JumpOpc = (useAlternativeLinkReg()) ? JUMP_INDIRECT : RETURN;
    FrameOverhead = get(JumpOpc).getSize();
  }
  for (auto &C : RepeatedSequenceLocs)
    C.setCallInfo(ConstructID, CallOverhead);

  return outliner::OutlinedFunction(RepeatedSequenceLocs, SequenceSize,
                                    FrameOverhead, ConstructID);
}

outliner::InstrType CodasipGenInstrInfo2::getOutliningType(MachineBasicBlock::iterator &MBBI,
                                                           unsigned Flags) const
{
  MachineInstr &MI = *MBBI;
  MachineBasicBlock *MBB = MI.getParent();
  const CodasipRegisterInfo &CRI = getRegisterInfo();

  if (MI.isDebugInstr() || MI.isIndirectDebugValue())
    return outliner::InstrType::Invisible;

  if (MI.isKill())
    return outliner::InstrType::Invisible;

  // Positions generally can't safely be outlined.
  if (MI.isPosition()) {
    // We can manually strip out CFI instructions later.
    if (MI.isCFIInstruction())
      return outliner::InstrType::Invisible;
    return outliner::InstrType::Illegal;
  }
  // Don't trust the user to write safe inline assembly.
  if (MI.isInlineAsm())
    return outliner::InstrType::Illegal;
  // We can't outline branches to other basic blocks.
  if (MI.isTerminator() && !MBB->succ_empty()) {
    return outliner::InstrType::Illegal;
  }

  if (isTailCall(MI) || (MI.isTerminator() && MI.getParent()->succ_empty()))
    return outliner::InstrType::Legal;

  // Don't allow modifying the AltRA register which we use for return addresses for
  // these outlined functions.
  if (useAlternativeLinkReg()) {
    if (MI.modifiesRegister(ALT_RAR, &CRI) ||
        MI.getDesc().hasImplicitDefOfPhysReg(ALT_RAR))
      return outliner::InstrType::Illegal;
  } else { // no ALR, so don't touch RA:
    // note that this part also disables calls, as they use RA implicitly.
    unsigned RAReg = CRI.getRARegister();
    if (MI.modifiesRegister(RAReg, &CRI) || MI.readsRegister(RAReg, &CRI) ||
        MI.getDesc().hasImplicitUseOfPhysReg(RAReg) ||
        MI.getDesc().hasImplicitDefOfPhysReg(RAReg)) {
      return outliner::InstrType::Illegal;
    }
  }

  // Make sure the operands don't reference something unsafe.
  for (const auto &MO : MI.operands()) {
    if (MO.isMBB() || MO.isBlockAddress() || MO.isCPI() || MO.isJTI() ||
        MO.isCFIIndex() || MO.isFI() || MO.isTargetIndex()) {
      return outliner::InstrType::Illegal;
    }
  }
  for (const auto &MMO : MI.memoperands()) {
    if (MMO->isVolatile()) {
      return outliner::InstrType::Illegal;
    }
  }
  // Don't allow instructions which won't be materialized to impact outlining
  // analysis.
  if (MI.isMetaInstruction())
    return outliner::InstrType::Invisible;

  return outliner::InstrType::Legal;
}

void CodasipGenInstrInfo2::buildOutlinedFrame(MachineBasicBlock &MBB,
                                              MachineFunction &MF,
                                              const outliner::OutlinedFunction &OF) const
{
  const CodasipRegisterInfo &CRI = getRegisterInfo();
  // Strip out any CFI instructions
  bool Changed = true;
  while (Changed) {
    Changed = false;
    auto I = MBB.begin();
    auto E = MBB.end();
    for (; I != E; ++I) {
      if (I->isCFIInstruction()) {
        I->removeFromParent();
        Changed = true;
        break;
      }
    }
  }

  switch (OF.FrameConstructionID) {
  case MachineOutlinerDefault:
    MBB.insert(MBB.end(),
               BuildMI(MF, DebugLoc(), get(JUMP_INDIRECT)).addReg(ALT_RAR));
    break;
  case MachineOutlinerRA:
    LLVM_FALLTHROUGH;
  case MachineOutlinerRARegSave:
    MBB.insert(MBB.end(), BuildMI(MF, DebugLoc(), get(RETURN))
                              .addReg(CRI.getRARegister()));
    break;
  case MachineOutlinerRATailCall:
    break; // already contains return, don't do anything.
  }
}

MachineBasicBlock::iterator CodasipGenInstrInfo2::insertOutlinedCall(Module &M,
                                                                     MachineBasicBlock &MBB,
                                                                     MachineBasicBlock::iterator &It,
                                                                     MachineFunction &MF,
                                                                     const outliner::Candidate &C) const
{
  const CodasipRegisterInfo &CRI = getRegisterInfo();
  unsigned RAReg = CRI.getRARegister();

  switch (C.CallConstructionID) {
  case MachineOutlinerDefault:
    It = MBB.insert(It, BuildMI(MF, DebugLoc(), get(ALT_CALL), ALT_RAR)
            .addGlobalAddress(M.getNamedValue(MF.getName())));
    return It;
  case MachineOutlinerRA:
    It = MBB.insert(It, BuildMI(MF, DebugLoc(), get(CALL_DIRECT))
        .addGlobalAddress(M.getNamedValue(MF.getName())));
    return It;
  case MachineOutlinerRATailCall:
    It = MBB.insert(It, BuildMI(MF, DebugLoc(), get(JUMP_DIRECT))
            .addGlobalAddress(M.getNamedValue(MF.getName())));

    return It;
  case MachineOutlinerRARegSave:
    // We want to return the spot where we inserted the call.
    MachineBasicBlock::iterator CallPt;
    unsigned Reg = findRegisterToSaveLRTo(C);
    assert(Reg != 0 && "No caller-saved register available?");
    DebugLoc dl;
    // Save and restore LR from that register.
    copyPhysReg(MBB,It,dl,Reg,RAReg,false);
    // Insert the call.
    It = MBB.insert(It, BuildMI(MF, DebugLoc(), get(CALL_DIRECT))
        .addGlobalAddress(M.getNamedValue(MF.getName())));
    CallPt = It;
    copyPhysReg(MBB,std::next(It),dl,RAReg,Reg,false);
    It++;
    return CallPt;
  }
  return It;
}

// run on -Os (optForSize) and -Oz (optForMinSize)
bool CodasipGenInstrInfo2::shouldOutlineFromFunctionByDefault(
    MachineFunction &MF) const
{
  return MF.getFunction().hasOptSize();
}

/*********************************************************************/

// our own tweaked recognizer for PostRA
class CodasipHazardRecognizer: public ScoreboardHazardRecognizer
{
public:
  CodasipHazardRecognizer(const InstrItineraryData *ItinData,
                          const ScheduleDAG *DAG,
                          const char *ParentDebugType)
  : ScoreboardHazardRecognizer(ItinData,DAG,ParentDebugType) {}
  // detect hazard type
  HazardType getHazardType(SUnit *m, int Stalls) override
  {
    HazardType ht = ScoreboardHazardRecognizer::getHazardType(m,Stalls);
    
    if (ht==Hazard) ht=NoopHazard;
    
    return ht;
  }
};

// needs to be enabled (-post-RA-scheduler or in the subtarget)
ScheduleHazardRecognizer* CodasipGenInstrInfo2::CreateTargetPostRAHazardRecognizer(
    const InstrItineraryData *II,
    const ScheduleDAG *DAG) const
{
  return new CodasipHazardRecognizer(II, DAG, "post-RA-sched");
}

}//namespace llvm
