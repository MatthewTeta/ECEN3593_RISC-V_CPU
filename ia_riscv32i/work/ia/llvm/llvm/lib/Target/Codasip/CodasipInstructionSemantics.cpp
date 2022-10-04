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


#include "CodasipInstructionSemantics.h"
#include "CodasipGenInstrInfo.h"
#include "CodasipGenISelLowering.h"

#include "llvm/Analysis/OptimizationRemarkEmitter.h"

// turn of optimization on windows, too long function
#ifdef _WIN32
  #pragma optimize("", off)	// disable global optimization, this will increase compilation times 8x-10x
#endif

llvm::SelectionDAG* llvm::GetCodasipPattern(const TargetMachine &TM,
    MachineFunction &mf,
    unsigned icode,
    std::vector<SDValue>& roots,
    bool lowlevel)
{
  // hlp for memop
  MachinePointerInfo mpi;
  // resulting dag
  SelectionDAG* dag = new SelectionDAG(TM,CodeGenOpt::None);
  OptimizationRemarkEmitter ore(&mf.getFunction());
  dag->init(mf,ore,nullptr,nullptr,nullptr);
  // entry node
  SDValue entry = dag->getEntryNode();
  // dummy loc
  SDLoc dl;
  // building of nodes for each instruction
  switch (icode)
  {
    case Codasip::i_ret_alias__:
      if (lowlevel) {
SDValue node0x5da1fe0 = dag->getRegister(Codasip::rf_xpr_1, MVT::i32);
SDValue node0x5da1d30 = dag->getNode(ISD::BRIND, dl, MVT::Other, entry, node0x5da1fe0);
roots.reserve(1);
roots.push_back(node0x5da1d30);
dag->setRoot(node0x5da1d30);
      } else       {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_call_reg_alias__simm12__xpr_general__immspec_1_:
      if (lowlevel) {
SDValue node0x5ecbb00 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5ecbe30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eca3c0 = dag->getCopyToReg(entry, dl, dag->getRegister(Codasip::rf_xpr_1, MVT::i32), node0x5ecbb00, SDValue());
SDValue node0x5ecba50 = dag->getNode(ISD::BRIND, dl, MVT::Other, node0x5eca3c0, node0x5ecbe30);
roots.reserve(2);
roots.push_back(node0x5eca3c0);
roots.push_back(node0x5ecba50);
dag->setRoot(node0x5ecba50);
      } else       {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ecc8a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ecc450 = dag->getNode(ISD::BRIND, dl, MVT::Other, entry, node0x5ecc8a0);
roots.reserve(1);
roots.push_back(node0x5ecc450);
dag->setRoot(node0x5ecc450);
      }
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5eccd70 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5ecaf80 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5eccd70, SDValue());
SDValue node0x5ecd310 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ecd3e0 = dag->getNode(ISD::BRIND, dl, MVT::Other, node0x5ecaf80, node0x5ecd310);
roots.reserve(2);
roots.push_back(node0x5ecaf80);
roots.push_back(node0x5ecd3e0);
dag->setRoot(node0x5ecd3e0);
      }
      break;
    case Codasip::i_call_alias__relative_addr20__:
case Codasip::i_call_alias__relative_addr20__ES:
case Codasip::i_call_alias__relative_addr20__MC:
case Codasip::i_call_alias__relative_addr20__BA:
      if (lowlevel) {
SDValue node0x5beb930 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5beaef0 = dag->getCopyToReg(entry, dl, dag->getRegister(Codasip::rf_xpr_1, MVT::i32), node0x5beb930, SDValue());
SDValue node0x5bebd40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::Other);
SDValue node0x5bebf60 = dag->getNode(ISD::BR, dl, MVT::Other, node0x5beaef0, node0x5bebd40);
roots.reserve(2);
roots.push_back(node0x5beaef0);
roots.push_back(node0x5bebf60);
dag->setRoot(node0x5bebf60);
      } else       {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__:
      {
SDValue node0x5d92350 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::Other);
SDValue node0x5d92000 = dag->getNode(ISD::BR, dl, MVT::Other, entry, node0x5d92350);
roots.reserve(1);
roots.push_back(node0x5d92000);
dag->setRoot(node0x5d92000);
      }
      break;
    case Codasip::i_jal_abs_calias__opc_jal__xpr_general__relative_addr20__:
      {
SDValue node0x5d92b40 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5d91150 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d92b40, SDValue());
SDValue node0x5d92eb0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5d92b10 = dag->getNode(ISD::BR, dl, MVT::Other, node0x5d91150, node0x5d92eb0);
roots.reserve(2);
roots.push_back(node0x5d91150);
roots.push_back(node0x5d92b10);
dag->setRoot(node0x5d92b10);
      }
      break;
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__:
      {
SDValue node0x5d94900 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::Other);
SDValue node0x5d94ac0 = dag->getNode(ISD::BR, dl, MVT::Other, entry, node0x5d94900);
roots.reserve(1);
roots.push_back(node0x5d94ac0);
dag->setRoot(node0x5d94ac0);
      }
      break;
    case Codasip::i_jtype_jlink__opc_jal__xpr_general__relative_addr20__:
      {
SDValue node0x5d95710 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5d94be0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d95710, SDValue());
SDValue node0x5d95b20 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5d95d10 = dag->getNode(ISD::BR, dl, MVT::Other, node0x5d94be0, node0x5d95b20);
roots.reserve(2);
roots.push_back(node0x5d94be0);
roots.push_back(node0x5d95d10);
dag->setRoot(node0x5d95d10);
      }
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__:
      {
SDValue node0x5cfb450 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::Other);
SDValue node0x5bc4d70 = dag->getNode(ISD::BR, dl, MVT::Other, entry, node0x5cfb450);
roots.reserve(1);
roots.push_back(node0x5bc4d70);
dag->setRoot(node0x5bc4d70);
      }
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5bc5ff0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5bab2d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5bc6190 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5bc6230 = dag->getSetCC(dl, MVT::iAny, node0x5bab2d0, node0x5bc5ff0, ISD::SETEQ);
SDValue node0x5bc63a0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5bc6230, node0x5bc6190);
roots.reserve(1);
roots.push_back(node0x5bc63a0);
dag->setRoot(node0x5bc63a0);
      } else       {
SDValue node0x5bc5ff0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5bab2d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5bc6190 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5bc6230 = dag->getSetCC(dl, MVT::i32, node0x5bab2d0, node0x5bc5ff0, ISD::SETEQ);
SDValue node0x5bc63a0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5bc6230, node0x5bc6190);
roots.reserve(1);
roots.push_back(node0x5bc63a0);
dag->setRoot(node0x5bc63a0);
      }
      break;
    case Codasip::i_btype_branches__opc_beq__xpr_general__x_0__relative_addr12__:
      if (lowlevel) {
SDValue node0x5be4e50 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5cbbf60 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5be4ff0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5be5090 = dag->getSetCC(dl, MVT::iAny, node0x5cbbf60, node0x5be4e50, ISD::SETEQ);
SDValue node0x5be52e0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5be5090, node0x5be4ff0);
roots.reserve(1);
roots.push_back(node0x5be52e0);
dag->setRoot(node0x5be52e0);
      } else       {
SDValue node0x5be4e50 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5cbbf60 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5be4ff0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5be5090 = dag->getSetCC(dl, MVT::i32, node0x5cbbf60, node0x5be4e50, ISD::SETEQ);
SDValue node0x5be52e0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5be5090, node0x5be4ff0);
roots.reserve(1);
roots.push_back(node0x5be52e0);
dag->setRoot(node0x5be52e0);
      }
      break;
    case Codasip::i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5cc0650 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5cd5f00 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5bad650 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5bad6f0 = dag->getSetCC(dl, MVT::iAny, node0x5cd5f00, node0x5cc0650, ISD::SETEQ);
SDValue node0x5bad940 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5bad6f0, node0x5bad650);
roots.reserve(1);
roots.push_back(node0x5bad940);
dag->setRoot(node0x5bad940);
      } else       {
SDValue node0x5cc0650 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5cd5f00 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5bad650 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5bad6f0 = dag->getSetCC(dl, MVT::i32, node0x5cd5f00, node0x5cc0650, ISD::SETEQ);
SDValue node0x5bad940 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5bad6f0, node0x5bad650);
roots.reserve(1);
roots.push_back(node0x5bad940);
dag->setRoot(node0x5bad940);
      }
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__:
      {
SDValue node0x5bae8c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::Other);
SDValue node0x5cb8470 = dag->getNode(ISD::BR, dl, MVT::Other, entry, node0x5bae8c0);
roots.reserve(1);
roots.push_back(node0x5cb8470);
dag->setRoot(node0x5cb8470);
      }
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5cb9300 = dag->getConstant(1LL, dl, MVT::i32);
SDValue node0x5cd12a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5cb9680 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5cb9720 = dag->getSetCC(dl, MVT::iAny, node0x5cd12a0, node0x5cb9300, ISD::SETLT);
SDValue node0x5cb9970 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5cb9720, node0x5cb9680);
roots.reserve(1);
roots.push_back(node0x5cb9970);
dag->setRoot(node0x5cb9970);
      } else       {
SDValue node0x5cb9300 = dag->getConstant(1LL, dl, MVT::i32);
SDValue node0x5cd12a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5cb9680 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5cb9720 = dag->getSetCC(dl, MVT::i32, node0x5cd12a0, node0x5cb9300, ISD::SETLT);
SDValue node0x5cb9970 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5cb9720, node0x5cb9680);
roots.reserve(1);
roots.push_back(node0x5cb9970);
dag->setRoot(node0x5cb9970);
      }
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__x_0__relative_addr12__:
      if (lowlevel) {
SDValue node0x5f0ce10 = dag->getConstant(-1LL, dl, MVT::i32);
SDValue node0x5cc0a30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f0cf10 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f0cfb0 = dag->getSetCC(dl, MVT::iAny, node0x5cc0a30, node0x5f0ce10, ISD::SETGT);
SDValue node0x5f0d200 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f0cfb0, node0x5f0cf10);
roots.reserve(1);
roots.push_back(node0x5f0d200);
dag->setRoot(node0x5f0d200);
      } else       {
SDValue node0x5f0ce10 = dag->getConstant(-1LL, dl, MVT::i32);
SDValue node0x5cc0a30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f0cf10 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f0cfb0 = dag->getSetCC(dl, MVT::i32, node0x5cc0a30, node0x5f0ce10, ISD::SETGT);
SDValue node0x5f0d200 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f0cfb0, node0x5f0cf10);
roots.reserve(1);
roots.push_back(node0x5f0d200);
dag->setRoot(node0x5f0d200);
      }
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5cc6670 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5f0e920 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f0e9d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5f0ea70 = dag->getSetCC(dl, MVT::iAny, node0x5f0e920, node0x5cc6670, ISD::SETGE);
SDValue node0x5f0ecc0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f0ea70, node0x5f0e9d0);
roots.reserve(1);
roots.push_back(node0x5f0ecc0);
dag->setRoot(node0x5f0ecc0);
      } else       {
SDValue node0x5cc6670 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5f0e920 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f0e9d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5f0ea70 = dag->getSetCC(dl, MVT::i32, node0x5f0e920, node0x5cc6670, ISD::SETGE);
SDValue node0x5f0ecc0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f0ea70, node0x5f0e9d0);
roots.reserve(1);
roots.push_back(node0x5f0ecc0);
dag->setRoot(node0x5f0ecc0);
      }
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__:
      {
SDValue node0x5f0fbf0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::Other);
SDValue node0x5cbb4d0 = dag->getNode(ISD::BR, dl, MVT::Other, entry, node0x5f0fbf0);
roots.reserve(1);
roots.push_back(node0x5cbb4d0);
dag->setRoot(node0x5cbb4d0);
      }
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5cb5690 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5cb5810 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5cb58c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5cb5960 = dag->getSetCC(dl, MVT::iAny, node0x5cb5810, node0x5cb5690, ISD::SETEQ);
SDValue node0x5cb5bb0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5cb5960, node0x5cb58c0);
roots.reserve(1);
roots.push_back(node0x5cb5bb0);
dag->setRoot(node0x5cb5bb0);
      } else       {
SDValue node0x5cb5690 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5cb5810 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5cb58c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5cb5960 = dag->getSetCC(dl, MVT::i32, node0x5cb5810, node0x5cb5690, ISD::SETEQ);
SDValue node0x5cb5bb0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5cb5960, node0x5cb58c0);
roots.reserve(1);
roots.push_back(node0x5cb5bb0);
dag->setRoot(node0x5cb5bb0);
      }
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5f01bd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5f01c80 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f01d30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5f01dd0 = dag->getSetCC(dl, MVT::iAny, node0x5f01c80, node0x5f01bd0, ISD::SETUGE);
SDValue node0x5f02020 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f01dd0, node0x5f01d30);
roots.reserve(1);
roots.push_back(node0x5f02020);
dag->setRoot(node0x5f02020);
      } else       {
SDValue node0x5f01bd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5f01c80 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f01d30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5f01dd0 = dag->getSetCC(dl, MVT::i32, node0x5f01c80, node0x5f01bd0, ISD::SETUGE);
SDValue node0x5f02020 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f01dd0, node0x5f01d30);
roots.reserve(1);
roots.push_back(node0x5f02020);
dag->setRoot(node0x5f02020);
      }
      break;
    case Codasip::i_btype_branches__opc_blt__x_0__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5f03be0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f03d60 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f03e10 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f03eb0 = dag->getSetCC(dl, MVT::iAny, node0x5f03d60, node0x5f03be0, ISD::SETGT);
SDValue node0x5f04100 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f03eb0, node0x5f03e10);
roots.reserve(1);
roots.push_back(node0x5f04100);
dag->setRoot(node0x5f04100);
      } else       {
SDValue node0x5f03be0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f03d60 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f03e10 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f03eb0 = dag->getSetCC(dl, MVT::i32, node0x5f03d60, node0x5f03be0, ISD::SETGT);
SDValue node0x5f04100 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f03eb0, node0x5f03e10);
roots.reserve(1);
roots.push_back(node0x5f04100);
dag->setRoot(node0x5f04100);
      }
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__x_0__relative_addr12__:
      if (lowlevel) {
SDValue node0x5f11f70 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f120f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f121a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f12240 = dag->getSetCC(dl, MVT::iAny, node0x5f120f0, node0x5f11f70, ISD::SETLT);
SDValue node0x5f12490 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f12240, node0x5f121a0);
roots.reserve(1);
roots.push_back(node0x5f12490);
dag->setRoot(node0x5f12490);
      } else       {
SDValue node0x5f11f70 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f120f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f121a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f12240 = dag->getSetCC(dl, MVT::i32, node0x5f120f0, node0x5f11f70, ISD::SETLT);
SDValue node0x5f12490 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f12240, node0x5f121a0);
roots.reserve(1);
roots.push_back(node0x5f12490);
dag->setRoot(node0x5f12490);
      }
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5f13b90 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5f13c40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f13cf0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5f13d90 = dag->getSetCC(dl, MVT::iAny, node0x5f13c40, node0x5f13b90, ISD::SETLT);
SDValue node0x5f13fe0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f13d90, node0x5f13cf0);
roots.reserve(1);
roots.push_back(node0x5f13fe0);
dag->setRoot(node0x5f13fe0);
      } else       {
SDValue node0x5f13b90 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5f13c40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f13cf0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5f13d90 = dag->getSetCC(dl, MVT::i32, node0x5f13c40, node0x5f13b90, ISD::SETLT);
SDValue node0x5f13fe0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f13d90, node0x5f13cf0);
roots.reserve(1);
roots.push_back(node0x5f13fe0);
dag->setRoot(node0x5f13fe0);
      }
      break;
    case Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5f15b50 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f15cd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f15d80 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f15e20 = dag->getSetCC(dl, MVT::iAny, node0x5f15cd0, node0x5f15b50, ISD::SETNE);
SDValue node0x5f16070 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f15e20, node0x5f15d80);
roots.reserve(1);
roots.push_back(node0x5f16070);
dag->setRoot(node0x5f16070);
      } else       {
SDValue node0x5f15b50 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f15cd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f15d80 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f15e20 = dag->getSetCC(dl, MVT::i32, node0x5f15cd0, node0x5f15b50, ISD::SETNE);
SDValue node0x5f16070 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f15e20, node0x5f15d80);
roots.reserve(1);
roots.push_back(node0x5f16070);
dag->setRoot(node0x5f16070);
      }
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5f06be0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5f06c90 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f06d40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5f06de0 = dag->getSetCC(dl, MVT::iAny, node0x5f06c90, node0x5f06be0, ISD::SETULT);
SDValue node0x5f07030 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f06de0, node0x5f06d40);
roots.reserve(1);
roots.push_back(node0x5f07030);
dag->setRoot(node0x5f07030);
      } else       {
SDValue node0x5f06be0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5f06c90 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f06d40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5f06de0 = dag->getSetCC(dl, MVT::i32, node0x5f06c90, node0x5f06be0, ISD::SETULT);
SDValue node0x5f07030 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f06de0, node0x5f06d40);
roots.reserve(1);
roots.push_back(node0x5f07030);
dag->setRoot(node0x5f07030);
      }
      break;
    case Codasip::i_btype_branches__opc_bne__x_0__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5f08bf0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f08d70 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f08e20 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f08ec0 = dag->getSetCC(dl, MVT::iAny, node0x5f08d70, node0x5f08bf0, ISD::SETNE);
SDValue node0x5f09110 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f08ec0, node0x5f08e20);
roots.reserve(1);
roots.push_back(node0x5f09110);
dag->setRoot(node0x5f09110);
      } else       {
SDValue node0x5f08bf0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f08d70 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f08e20 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f08ec0 = dag->getSetCC(dl, MVT::i32, node0x5f08d70, node0x5f08bf0, ISD::SETNE);
SDValue node0x5f09110 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f08ec0, node0x5f08e20);
roots.reserve(1);
roots.push_back(node0x5f09110);
dag->setRoot(node0x5f09110);
      }
      break;
    case Codasip::i_btype_branches__opc_bne__xpr_general__x_0__relative_addr12__:
      if (lowlevel) {
SDValue node0x5f0b5e0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f0b760 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f0b810 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f0b8b0 = dag->getSetCC(dl, MVT::iAny, node0x5f0b760, node0x5f0b5e0, ISD::SETNE);
SDValue node0x5f0bb00 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f0b8b0, node0x5f0b810);
roots.reserve(1);
roots.push_back(node0x5f0bb00);
dag->setRoot(node0x5f0bb00);
      } else       {
SDValue node0x5f0b5e0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5f0b760 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f0b810 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5f0b8b0 = dag->getSetCC(dl, MVT::i32, node0x5f0b760, node0x5f0b5e0, ISD::SETNE);
SDValue node0x5f0bb00 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5f0b8b0, node0x5f0b810);
roots.reserve(1);
roots.push_back(node0x5f0bb00);
dag->setRoot(node0x5f0bb00);
      }
      break;
    case Codasip::i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__:
      if (lowlevel) {
SDValue node0x5bea980 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5beaa30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5beaae0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5beab80 = dag->getSetCC(dl, MVT::iAny, node0x5beaa30, node0x5bea980, ISD::SETNE);
SDValue node0x5beadd0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5beab80, node0x5beaae0);
roots.reserve(1);
roots.push_back(node0x5beadd0);
dag->setRoot(node0x5beadd0);
      } else       {
SDValue node0x5bea980 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5beaa30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5beaae0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5beab80 = dag->getSetCC(dl, MVT::i32, node0x5beaa30, node0x5bea980, ISD::SETNE);
SDValue node0x5beadd0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5beab80, node0x5beaae0);
roots.reserve(1);
roots.push_back(node0x5beadd0);
dag->setRoot(node0x5beadd0);
      }
      break;
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      if (lowlevel) {
SDValue node0x5ebb340 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5eba420 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ebb4e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ebb590 = dag->getSetCC(dl, MVT::iAny, node0x5eba420, node0x5ebb4e0, ISD::SETLE);
SDValue node0x5ebb660 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5ebb590, node0x5ebb340);
roots.reserve(1);
roots.push_back(node0x5ebb660);
dag->setRoot(node0x5ebb660);
      } else       {
SDValue node0x5ebb340 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5eba420 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ebb4e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ebb590 = dag->getSetCC(dl, MVT::i32, node0x5eba420, node0x5ebb4e0, ISD::SETLE);
SDValue node0x5ebb660 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5ebb590, node0x5ebb340);
roots.reserve(1);
roots.push_back(node0x5ebb660);
dag->setRoot(node0x5ebb660);
      }
      break;
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      if (lowlevel) {
SDValue node0x5ebbff0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5ebc280 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ebc330 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ebc3e0 = dag->getSetCC(dl, MVT::iAny, node0x5ebc280, node0x5ebc330, ISD::SETULE);
SDValue node0x5ebc4b0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5ebc3e0, node0x5ebbff0);
roots.reserve(1);
roots.push_back(node0x5ebc4b0);
dag->setRoot(node0x5ebc4b0);
      } else       {
SDValue node0x5ebbff0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5ebc280 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ebc330 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ebc3e0 = dag->getSetCC(dl, MVT::i32, node0x5ebc280, node0x5ebc330, ISD::SETULE);
SDValue node0x5ebc4b0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5ebc3e0, node0x5ebbff0);
roots.reserve(1);
roots.push_back(node0x5ebc4b0);
dag->setRoot(node0x5ebc4b0);
      }
      break;
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      if (lowlevel) {
SDValue node0x5ebce40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5ebd0d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ebd180 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ebd230 = dag->getSetCC(dl, MVT::iAny, node0x5ebd0d0, node0x5ebd180, ISD::SETGT);
SDValue node0x5ebd300 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5ebd230, node0x5ebce40);
roots.reserve(1);
roots.push_back(node0x5ebd300);
dag->setRoot(node0x5ebd300);
      } else       {
SDValue node0x5ebce40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5ebd0d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ebd180 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ebd230 = dag->getSetCC(dl, MVT::i32, node0x5ebd0d0, node0x5ebd180, ISD::SETGT);
SDValue node0x5ebd300 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5ebd230, node0x5ebce40);
roots.reserve(1);
roots.push_back(node0x5ebd300);
dag->setRoot(node0x5ebd300);
      }
      break;
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__swappedCmpClone0__:
      if (lowlevel) {
SDValue node0x5ebdd30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5ebdfc0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ebe070 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ebe120 = dag->getSetCC(dl, MVT::iAny, node0x5ebdfc0, node0x5ebe070, ISD::SETUGT);
SDValue node0x5ebe1f0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5ebe120, node0x5ebdd30);
roots.reserve(1);
roots.push_back(node0x5ebe1f0);
dag->setRoot(node0x5ebe1f0);
      } else       {
SDValue node0x5ebdd30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::Other);
SDValue node0x5ebdfc0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ebe070 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ebe120 = dag->getSetCC(dl, MVT::i32, node0x5ebdfc0, node0x5ebe070, ISD::SETUGT);
SDValue node0x5ebe1f0 = dag->getNode(ISD::BRCOND, dl, MVT::Other, entry, node0x5ebe120, node0x5ebdd30);
roots.reserve(1);
roots.push_back(node0x5ebe1f0);
dag->setRoot(node0x5ebe1f0);
      }
      break;
    case Codasip::i_call_reg_alias__simm12__x_0__:
case Codasip::i_call_reg_alias__simm12__x_0__ES:
case Codasip::i_call_reg_alias__simm12__x_0__MC:
case Codasip::i_call_reg_alias__simm12__x_0__BA:
      if (lowlevel) {
SDValue node0x5bec570 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5beaf40 = dag->getCopyToReg(entry, dl, dag->getRegister(Codasip::rf_xpr_1, MVT::i32), node0x5bec570, SDValue());
SDValue node0x5bec980 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::Other);
SDValue node0x5bec4f0 = dag->getNode(ISD::BR, dl, MVT::Other, node0x5beaf40, node0x5bec980);
roots.reserve(2);
roots.push_back(node0x5beaf40);
roots.push_back(node0x5bec4f0);
dag->setRoot(node0x5bec4f0);
      } else       {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__:
      {
SDValue node0x5d163d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::Other);
SDValue node0x5d16100 = dag->getNode(ISD::BR, dl, MVT::Other, entry, node0x5d163d0);
roots.reserve(1);
roots.push_back(node0x5d16100);
dag->setRoot(node0x5d16100);
      }
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0__:
      {
SDValue node0x5d18ae0 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5d18890 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d18ae0, SDValue());
SDValue node0x5d18e50 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::Other);
SDValue node0x5d18ab0 = dag->getNode(ISD::BR, dl, MVT::Other, node0x5d18890, node0x5d18e50);
roots.reserve(2);
roots.push_back(node0x5d18890);
roots.push_back(node0x5d18ab0);
dag->setRoot(node0x5d18ab0);
      }
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__x_0__simm12__:
      {
SDValue node0x5bf1450 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5beaf90 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5bf1450, SDValue());
roots.reserve(1);
roots.push_back(node0x5beaf90);
dag->setRoot(node0x5beaf90);
      }
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__:
      {
SDValue node0x5bf2620 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5bf26d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5bf2770 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5bf2620, node0x5bf26d0);
SDValue node0x5bf1580 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5bf2770, SDValue());
roots.reserve(1);
roots.push_back(node0x5bf1580);
dag->setRoot(node0x5bf1580);
      }
      break;
    case Codasip::i_itype_alu__opc_andi__xpr_general__xpr_general__simm12__:
      {
SDValue node0x5d02140 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d021f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d02290 = dag->getNode(ISD::AND, dl, MVT::i32, node0x5d02140, node0x5d021f0);
SDValue node0x5d00fd0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d02290, SDValue());
roots.reserve(1);
roots.push_back(node0x5d00fd0);
dag->setRoot(node0x5d00fd0);
      }
      break;
    case Codasip::i_itype_alu__opc_ori__xpr_general__x_0__simm12__:
      {
SDValue node0x5d05980 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d023b0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d05980, SDValue());
roots.reserve(1);
roots.push_back(node0x5d023b0);
dag->setRoot(node0x5d023b0);
      }
      break;
    case Codasip::i_itype_alu__opc_ori__xpr_general__xpr_general__simm12__:
      {
SDValue node0x5d06cf0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d06da0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d06e40 = dag->getNode(ISD::OR, dl, MVT::i32, node0x5d06cf0, node0x5d06da0);
SDValue node0x5d05ab0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d06e40, SDValue());
roots.reserve(1);
roots.push_back(node0x5d05ab0);
dag->setRoot(node0x5d05ab0);
      }
      break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__:
      {
SDValue node0x5d0a450 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5d0a530 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d0a5d0 = dag->getSetCC(dl, MVT::i32, node0x5d0a530, node0x5d0a450, ISD::SETGT);
SDValue node0x5d06f60 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d0a5d0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d06f60);
dag->setRoot(node0x5d06f60);
      }
      break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__:
      {
SDValue node0x5d0ba70 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d0bb20 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d0bbc0 = dag->getSetCC(dl, MVT::i32, node0x5d0ba70, node0x5d0bb20, ISD::SETLT);
SDValue node0x5d0a8a0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d0bbc0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d0a8a0);
dag->setRoot(node0x5d0a8a0);
      }
      break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__:
      {
SDValue node0x5d0f330 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5d0f410 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d0f4b0 = dag->getSetCC(dl, MVT::i32, node0x5d0f410, node0x5d0f330, ISD::SETNE);
SDValue node0x5d0ef20 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d0f4b0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d0ef20);
dag->setRoot(node0x5d0ef20);
      }
      break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__:
      {
SDValue node0x5d109a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d10a50 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d10af0 = dag->getSetCC(dl, MVT::i32, node0x5d109a0, node0x5d10a50, ISD::SETULT);
SDValue node0x5d0f690 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d10af0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d0f690);
dag->setRoot(node0x5d0f690);
      }
      break;
    case Codasip::i_itype_alu__opc_xori__xpr_general__x_0__simm12__:
      {
SDValue node0x5d14250 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d105e0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d14250, SDValue());
roots.reserve(1);
roots.push_back(node0x5d105e0);
dag->setRoot(node0x5d105e0);
      }
      break;
    case Codasip::i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__:
      {
SDValue node0x5d155c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d15670 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d15710 = dag->getNode(ISD::XOR, dl, MVT::i32, node0x5d155c0, node0x5d15670);
SDValue node0x5d14380 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d15710, SDValue());
roots.reserve(1);
roots.push_back(node0x5d14380);
dag->setRoot(node0x5d14380);
      }
      break;
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__:
      {
SDValue node0x5d1e6e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d1c580 = dag->getExtLoad(ISD::SEXTLOAD, dl, MVT::i32, entry, node0x5d1e6e0, mpi, MVT::i8, 1);
SDValue node0x5d1c6f0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d1c580, SDValue());
roots.reserve(1);
roots.push_back(node0x5d1c6f0);
dag->setRoot(node0x5d1c6f0);
      }
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__:
      {
SDValue node0x5d1fc70 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d1fd20 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d1fdc0 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5d1fc70, node0x5d1fd20);
SDValue node0x5d1b410 = dag->getExtLoad(ISD::SEXTLOAD, dl, MVT::i32, entry, node0x5d1fdc0, mpi, MVT::i8, 1);
SDValue node0x5d1ea30 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d1b410, SDValue());
roots.reserve(1);
roots.push_back(node0x5d1ea30);
dag->setRoot(node0x5d1ea30);
      }
      break;
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__xpr_general__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__:
      {
SDValue node0x5d24200 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d21fb0 = dag->getExtLoad(ISD::ZEXTLOAD, dl, MVT::i32, entry, node0x5d24200, mpi, MVT::i8, 1);
SDValue node0x5d23d10 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d21fb0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d23d10);
dag->setRoot(node0x5d23d10);
      }
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__:
      {
SDValue node0x5d25830 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d258e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d25980 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5d25830, node0x5d258e0);
SDValue node0x5d20df0 = dag->getExtLoad(ISD::ZEXTLOAD, dl, MVT::i32, entry, node0x5d25980, mpi, MVT::i8, 1);
SDValue node0x5d23ee0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d20df0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d23ee0);
dag->setRoot(node0x5d23ee0);
      }
      break;
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__:
      {
SDValue node0x5d29ca0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d27b40 = dag->getExtLoad(ISD::SEXTLOAD, dl, MVT::i32, entry, node0x5d29ca0, mpi, MVT::i16, 1);
SDValue node0x5d27cb0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d27b40, SDValue());
roots.reserve(1);
roots.push_back(node0x5d27cb0);
dag->setRoot(node0x5d27cb0);
      }
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__:
      {
SDValue node0x5d2b230 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d2b2e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d2b380 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5d2b230, node0x5d2b2e0);
SDValue node0x5d26980 = dag->getExtLoad(ISD::SEXTLOAD, dl, MVT::i32, entry, node0x5d2b380, mpi, MVT::i16, 1);
SDValue node0x5d29ff0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d26980, SDValue());
roots.reserve(1);
roots.push_back(node0x5d29ff0);
dag->setRoot(node0x5d29ff0);
      }
      break;
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__xpr_general__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__:
      {
SDValue node0x5d2f7c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d2d570 = dag->getExtLoad(ISD::ZEXTLOAD, dl, MVT::i32, entry, node0x5d2f7c0, mpi, MVT::i16, 1);
SDValue node0x5d2f2d0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d2d570, SDValue());
roots.reserve(1);
roots.push_back(node0x5d2f2d0);
dag->setRoot(node0x5d2f2d0);
      }
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__:
      {
SDValue node0x5d30df0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d30ea0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d30f40 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5d30df0, node0x5d30ea0);
SDValue node0x5d2c3b0 = dag->getExtLoad(ISD::ZEXTLOAD, dl, MVT::i32, entry, node0x5d30f40, mpi, MVT::i16, 1);
SDValue node0x5d2f4a0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d2c3b0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d2f4a0);
dag->setRoot(node0x5d2f4a0);
      }
      break;
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0__:
      {
SDValue node0x5d8f840 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d8f8e0 = dag->getLoad(MVT::i32, dl, entry, node0x5d8f840, mpi, 1);
SDValue node0x5d8d850 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d8f8e0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d8d850);
dag->setRoot(node0x5d8d850);
      }
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__:
      {
SDValue node0x5d90d20 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d90dd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d90e70 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5d90d20, node0x5d90dd0);
SDValue node0x5d90f00 = dag->getLoad(MVT::i32, dl, entry, node0x5d90e70, mpi, 1);
SDValue node0x5d8fa90 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d90f00, SDValue());
roots.reserve(1);
roots.push_back(node0x5d8fa90);
dag->setRoot(node0x5d8fa90);
      }
      break;
    case Codasip::i_nop_alias__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_add__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__x_0__x_0__:
      {
SDValue node0x5daa670 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5daa5a0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5daa670, SDValue());
roots.reserve(1);
roots.push_back(node0x5daa5a0);
dag->setRoot(node0x5daa5a0);
      }
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__x_0__xpr_general__:
      {
SDValue node0x5dab8b0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5daa810 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dab8b0, SDValue());
roots.reserve(1);
roots.push_back(node0x5daa810);
dag->setRoot(node0x5daa810);
      }
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__x_0__:
      {
SDValue node0x5dadae0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5dad810 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dadae0, SDValue());
roots.reserve(1);
roots.push_back(node0x5dad810);
dag->setRoot(node0x5dad810);
      }
      break;
    case Codasip::i_rtype_alu__opc_add__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5daef00 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5daefb0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5daf060 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5daef00, node0x5daefb0);
SDValue node0x5daeb90 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5daf060, SDValue());
roots.reserve(1);
roots.push_back(node0x5daeb90);
dag->setRoot(node0x5daeb90);
      }
      break;
    case Codasip::i_rtype_alu__opc_and__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__x_0__x_0__:
      {
SDValue node0x5db7ca0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5db7bd0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5db7ca0, SDValue());
roots.reserve(1);
roots.push_back(node0x5db7bd0);
dag->setRoot(node0x5db7bd0);
      }
      break;
    case Codasip::i_rtype_alu__opc_and__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5dbc290 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5dbc340 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5dbc3f0 = dag->getNode(ISD::AND, dl, MVT::i32, node0x5dbc290, node0x5dbc340);
SDValue node0x5dbbf20 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dbc3f0, SDValue());
roots.reserve(1);
roots.push_back(node0x5dbbf20);
dag->setRoot(node0x5dbbf20);
      }
      break;
    case Codasip::i_rtype_alu__opc_or__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__x_0__x_0__:
      {
SDValue node0x5dc5030 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5dc4de0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dc5030, SDValue());
roots.reserve(1);
roots.push_back(node0x5dc4de0);
dag->setRoot(node0x5dc4de0);
      }
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__x_0__xpr_general__:
      {
SDValue node0x5dc6270 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5dc51d0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dc6270, SDValue());
roots.reserve(1);
roots.push_back(node0x5dc51d0);
dag->setRoot(node0x5dc51d0);
      }
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__xpr_general__x_0__:
      {
SDValue node0x5dc84a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5dc8030 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dc84a0, SDValue());
roots.reserve(1);
roots.push_back(node0x5dc8030);
dag->setRoot(node0x5dc8030);
      }
      break;
    case Codasip::i_rtype_alu__opc_or__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5dc98c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5dc9970 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5dc9a20 = dag->getNode(ISD::OR, dl, MVT::i32, node0x5dc98c0, node0x5dc9970);
SDValue node0x5dc8220 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dc9a20, SDValue());
roots.reserve(1);
roots.push_back(node0x5dc8220);
dag->setRoot(node0x5dc8220);
      }
      break;
    case Codasip::i_rtype_alu__opc_sll__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__x_0__x_0__:
      {
SDValue node0x5dd2660 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5dd2590 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dd2660, SDValue());
roots.reserve(1);
roots.push_back(node0x5dd2590);
dag->setRoot(node0x5dd2590);
      }
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__xpr_general__x_0__:
      {
SDValue node0x5dd5980 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5dd56b0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dd5980, SDValue());
roots.reserve(1);
roots.push_back(node0x5dd56b0);
dag->setRoot(node0x5dd56b0);
      }
      break;
    case Codasip::i_rtype_alu__opc_sll__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5dd6da0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5dd6e50 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5dd6f00 = dag->getNode(ISD::SHL, dl, MVT::i32, node0x5dd6da0, node0x5dd6e50);
SDValue node0x5dd6a30 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5dd6f00, SDValue());
roots.reserve(1);
roots.push_back(node0x5dd6a30);
dag->setRoot(node0x5dd6a30);
      }
      break;
    case Codasip::i_rtype_alu__opc_slt__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__x_0__x_0__:
      {
SDValue node0x5ddfb40 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5ddfa70 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ddfb40, SDValue());
roots.reserve(1);
roots.push_back(node0x5ddfa70);
dag->setRoot(node0x5ddfa70);
      }
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__x_0__xpr_general__:
      {
SDValue node0x5de0c00 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5de0d80 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5de0e30 = dag->getSetCC(dl, MVT::i32, node0x5de0d80, node0x5de0c00, ISD::SETGT);
SDValue node0x5ddfce0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5de0e30, SDValue());
roots.reserve(1);
roots.push_back(node0x5ddfce0);
dag->setRoot(node0x5ddfce0);
      }
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__x_0__:
      {
SDValue node0x5de2fb0 = dag->getConstant(31LL, dl, MVT::i32);
SDValue node0x5de31d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5de3280 = dag->getNode(ISD::SRL, dl, MVT::i32, node0x5de31d0, node0x5de2fb0);
SDValue node0x5de2e60 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5de3280, SDValue());
roots.reserve(1);
roots.push_back(node0x5de2e60);
dag->setRoot(node0x5de2e60);
      }
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5de46b0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5de4760 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5de4810 = dag->getSetCC(dl, MVT::i32, node0x5de46b0, node0x5de4760, ISD::SETLT);
SDValue node0x5de4340 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5de4810, SDValue());
roots.reserve(1);
roots.push_back(node0x5de4340);
dag->setRoot(node0x5de4340);
      }
      break;
    case Codasip::i_rtype_alu__opc_sltu__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0__x_0__:
      {
SDValue node0x5d3a7f0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5d3a720 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d3a7f0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d3a720);
dag->setRoot(node0x5d3a720);
      }
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__x_0__xpr_general__:
      {
SDValue node0x5d3b8b0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5d3ba30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d3bae0 = dag->getSetCC(dl, MVT::i32, node0x5d3ba30, node0x5d3b8b0, ISD::SETNE);
SDValue node0x5d3a990 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d3bae0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d3a990);
dag->setRoot(node0x5d3a990);
      }
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5d3f0b0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d3f160 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d3f210 = dag->getSetCC(dl, MVT::i32, node0x5d3f0b0, node0x5d3f160, ISD::SETULT);
SDValue node0x5d3ed40 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d3f210, SDValue());
roots.reserve(1);
roots.push_back(node0x5d3ed40);
dag->setRoot(node0x5d3ed40);
      }
      break;
    case Codasip::i_rtype_alu__opc_sra__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__x_0__x_0__:
      {
SDValue node0x5d47f10 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5d47e40 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d47f10, SDValue());
roots.reserve(1);
roots.push_back(node0x5d47e40);
dag->setRoot(node0x5d47e40);
      }
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__x_0__:
      {
SDValue node0x5d4b230 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d4af60 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d4b230, SDValue());
roots.reserve(1);
roots.push_back(node0x5d4af60);
dag->setRoot(node0x5d4af60);
      }
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5d4c6f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d4c7a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d4c8e0 = dag->getNode(ISD::SRA, dl, MVT::i32, node0x5d4c6f0, node0x5d4c7a0);
SDValue node0x5d4c2e0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d4c8e0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d4c2e0);
dag->setRoot(node0x5d4c2e0);
      }
      break;
    case Codasip::i_rtype_alu__opc_srl__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__x_0__x_0__:
      {
SDValue node0x5d55550 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5d55480 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d55550, SDValue());
roots.reserve(1);
roots.push_back(node0x5d55480);
dag->setRoot(node0x5d55480);
      }
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__x_0__:
      {
SDValue node0x5d58870 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d585a0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d58870, SDValue());
roots.reserve(1);
roots.push_back(node0x5d585a0);
dag->setRoot(node0x5d585a0);
      }
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5d59d30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d59de0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d59f20 = dag->getNode(ISD::SRL, dl, MVT::i32, node0x5d59d30, node0x5d59de0);
SDValue node0x5d59920 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d59f20, SDValue());
roots.reserve(1);
roots.push_back(node0x5d59920);
dag->setRoot(node0x5d59920);
      }
      break;
    case Codasip::i_rtype_alu__opc_sub__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__x_0__x_0__:
      {
SDValue node0x5d62b90 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5d62ac0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d62b90, SDValue());
roots.reserve(1);
roots.push_back(node0x5d62ac0);
dag->setRoot(node0x5d62ac0);
      }
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__x_0__xpr_general__:
      {
SDValue node0x5d63bd0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5d63dd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d63e80 = dag->getNode(ISD::SUB, dl, MVT::i32, node0x5d63bd0, node0x5d63dd0);
SDValue node0x5d62d30 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d63e80, SDValue());
roots.reserve(1);
roots.push_back(node0x5d62d30);
dag->setRoot(node0x5d62d30);
      }
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__xpr_general__x_0__:
      {
SDValue node0x5d660c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d65df0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d660c0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d65df0);
dag->setRoot(node0x5d65df0);
      }
      break;
    case Codasip::i_rtype_alu__opc_sub__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5d674e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d67590 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d67640 = dag->getNode(ISD::SUB, dl, MVT::i32, node0x5d674e0, node0x5d67590);
SDValue node0x5d67170 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d67640, SDValue());
roots.reserve(1);
roots.push_back(node0x5d67170);
dag->setRoot(node0x5d67170);
      }
      break;
    case Codasip::i_rtype_alu__opc_xor__x_0__x_0__x_0__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__x_0__x_0__:
      {
SDValue node0x5d70280 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5d701b0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d70280, SDValue());
roots.reserve(1);
roots.push_back(node0x5d701b0);
dag->setRoot(node0x5d701b0);
      }
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__x_0__xpr_general__:
      {
SDValue node0x5d714c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d70420 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d714c0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d70420);
dag->setRoot(node0x5d70420);
      }
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__xpr_general__x_0__:
      {
SDValue node0x5d736f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d73420 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d736f0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d73420);
dag->setRoot(node0x5d73420);
      }
      break;
    case Codasip::i_rtype_alu__opc_xor__xpr_general__xpr_general__xpr_general__:
      {
SDValue node0x5d74b10 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d74bc0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d74c70 = dag->getNode(ISD::XOR, dl, MVT::i32, node0x5d74b10, node0x5d74bc0);
SDValue node0x5d747a0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d74c70, SDValue());
roots.reserve(1);
roots.push_back(node0x5d747a0);
dag->setRoot(node0x5d747a0);
      }
      break;
    case Codasip::i_rtype_shift__opc_slli__xpr_general__xpr_general__uimm5__:
      {
SDValue node0x5d799a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d79a50 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d79af0 = dag->getNode(ISD::SHL, dl, MVT::i32, node0x5d799a0, node0x5d79a50);
SDValue node0x5d78b50 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d79af0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d78b50);
dag->setRoot(node0x5d78b50);
      }
      break;
    case Codasip::i_rtype_shift__opc_srai__xpr_general__xpr_general__uimm5__:
      {
SDValue node0x5d7e820 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d7e8d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d7e970 = dag->getNode(ISD::SRA, dl, MVT::i32, node0x5d7e820, node0x5d7e8d0);
SDValue node0x5d7d9d0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d7e970, SDValue());
roots.reserve(1);
roots.push_back(node0x5d7d9d0);
dag->setRoot(node0x5d7d9d0);
      }
      break;
    case Codasip::i_rtype_shift__opc_srli__xpr_general__xpr_general__uimm5__:
      {
SDValue node0x5d836a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d83750 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d837f0 = dag->getNode(ISD::SRL, dl, MVT::i32, node0x5d836a0, node0x5d83750);
SDValue node0x5d82850 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d837f0, SDValue());
roots.reserve(1);
roots.push_back(node0x5d82850);
dag->setRoot(node0x5d82850);
      }
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__:
      {
SDValue node0x5ea50c0 = dag->getConstant(0LL, dl, MVT::i8);
SDValue node0x5ea5360 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5be5400 = dag->getStore(entry, dl, node0x5ea50c0, node0x5ea5360, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5be5400);
dag->setRoot(node0x5be5400);
      }
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__:
      {
SDValue node0x5ea6440 = dag->getConstant(0LL, dl, MVT::i8);
SDValue node0x5ea6780 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ea6830 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5de5cb0 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5ea6780, node0x5ea6830);
SDValue node0x5cd5ea0 = dag->getStore(entry, dl, node0x5ea6440, node0x5de5cb0, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5cd5ea0);
dag->setRoot(node0x5cd5ea0);
      }
      break;
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__x_0__:
      {
SDValue node0x5ea8c70 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ea8d20 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eef280 = dag->getTruncStore(entry, dl, node0x5ea8c70, node0x5ea8d20, mpi, MVT::i8, 1);
roots.reserve(1);
roots.push_back(node0x5eef280);
dag->setRoot(node0x5eef280);
      }
      break;
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__:
      {
SDValue node0x5eaa260 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eaa310 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eaa3c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5eaa510 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5eaa310, node0x5eaa3c0);
SDValue node0x5ea8e70 = dag->getTruncStore(entry, dl, node0x5eaa260, node0x5eaa510, mpi, MVT::i8, 1);
roots.reserve(1);
roots.push_back(node0x5ea8e70);
dag->setRoot(node0x5ea8e70);
      }
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__:
      {
SDValue node0x5eab170 = dag->getConstant(0LL, dl, MVT::i16);
SDValue node0x5eab410 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eab4b0 = dag->getStore(entry, dl, node0x5eab170, node0x5eab410, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5eab4b0);
dag->setRoot(node0x5eab4b0);
      }
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__:
      {
SDValue node0x5eac2d0 = dag->getConstant(0LL, dl, MVT::i16);
SDValue node0x5eac610 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eac6c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eac760 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5eac610, node0x5eac6c0);
SDValue node0x5eac7f0 = dag->getStore(entry, dl, node0x5eac2d0, node0x5eac760, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5eac7f0);
dag->setRoot(node0x5eac7f0);
      }
      break;
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__x_0__:
      {
SDValue node0x5eaebd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eaec80 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eef7e0 = dag->getTruncStore(entry, dl, node0x5eaebd0, node0x5eaec80, mpi, MVT::i16, 1);
roots.reserve(1);
roots.push_back(node0x5eef7e0);
dag->setRoot(node0x5eef7e0);
      }
      break;
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__:
      {
SDValue node0x5eb01c0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eb0270 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eb0320 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5eb0470 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5eb0270, node0x5eb0320);
SDValue node0x5eaedd0 = dag->getTruncStore(entry, dl, node0x5eb01c0, node0x5eb0470, mpi, MVT::i16, 1);
roots.reserve(1);
roots.push_back(node0x5eaedd0);
dag->setRoot(node0x5eaedd0);
      }
      break;
    case Codasip::i_stype_store__opc_sw__x_0__simm12__x_0__:
      {
SDValue node0x5eb10d0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5eb12d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eb1370 = dag->getStore(entry, dl, node0x5eb10d0, node0x5eb12d0, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5eb1370);
dag->setRoot(node0x5eb1370);
      }
      break;
    case Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__:
      {
SDValue node0x5eb2190 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5eb2430 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eb24e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eb2580 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5eb2430, node0x5eb24e0);
SDValue node0x5eb2610 = dag->getStore(entry, dl, node0x5eb2190, node0x5eb2580, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5eb2610);
dag->setRoot(node0x5eb2610);
      }
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__x_0__:
      {
SDValue node0x5eb49f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eb4aa0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eb4b40 = dag->getStore(entry, dl, node0x5eb49f0, node0x5eb4aa0, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5eb4b40);
dag->setRoot(node0x5eb4b40);
      }
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__:
      {
SDValue node0x5eb5f30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5eb5fe0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eb6090 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5eb6130 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5eb5fe0, node0x5eb6090);
SDValue node0x5eb61c0 = dag->getStore(entry, dl, node0x5eb5f30, node0x5eb6130, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5eb61c0);
dag->setRoot(node0x5eb61c0);
      }
      break;
    case Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__:
      {
SDValue node0x5eb76e0 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5eb79d0 = dag->getConstant(-4LL, dl, MVT::i32);
SDValue node0x5eb7bf0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eb7c90 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5eb76e0, node0x5eb7bf0);
SDValue node0x5eb7d20 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5eb7c90, node0x5eb79d0);
SDValue node0x5eb6af0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5eb7d20, SDValue());
roots.reserve(1);
roots.push_back(node0x5eb6af0);
dag->setRoot(node0x5eb6af0);
      }
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__:
      {
SDValue node0x5eb9550 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eb9120 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5eb9550, SDValue());
roots.reserve(1);
roots.push_back(node0x5eb9120);
dag->setRoot(node0x5eb9120);
      }
      break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__0__:
      {
SDValue node0x5ebf020 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5eb9630 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ebf020, SDValue());
roots.reserve(1);
roots.push_back(node0x5eb9630);
dag->setRoot(node0x5eb9630);
      }
      break;
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__immSpecClone__imm_1__1__:
      {
SDValue node0x5ebe920 = dag->getConstant(1LL, dl, MVT::i32);
SDValue node0x5eba830 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ebe920, SDValue());
roots.reserve(1);
roots.push_back(node0x5eba830);
dag->setRoot(node0x5eba830);
      }
      break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__0__:
      {
SDValue node0x5ebff20 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5ebf5b0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ebff20, SDValue());
roots.reserve(1);
roots.push_back(node0x5ebf5b0);
dag->setRoot(node0x5ebf5b0);
      }
      break;
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__immSpecClone__imm_1__1__:
      {
SDValue node0x5ebf780 = dag->getConstant(1LL, dl, MVT::i32);
SDValue node0x5ebac70 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ebf780, SDValue());
roots.reserve(1);
roots.push_back(node0x5ebac70);
dag->setRoot(node0x5ebac70);
      }
      break;
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__immspec_1_:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__AEXT_CLONE_:
      {
SDValue node0x5d1b150 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d1e780 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5d1b150, mpi, MVT::i8, 1);
SDValue node0x5ee3e60 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d1e780, SDValue());
roots.reserve(1);
roots.push_back(node0x5ee3e60);
dag->setRoot(node0x5ee3e60);
      }
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__AEXT_CLONE_:
      {
SDValue node0x5d1fe50 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d1f930 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d1ff20 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5d1fe50, node0x5d1f930);
SDValue node0x5ed97f0 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5d1ff20, mpi, MVT::i8, 1);
SDValue node0x5ee4a60 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ed97f0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ee4a60);
dag->setRoot(node0x5ee4a60);
      }
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ece5f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec42f0 = dag->getExtLoad(ISD::SEXTLOAD, dl, MVT::i32, entry, node0x5ece5f0, mpi, MVT::i8, 1);
SDValue node0x5ecd8e0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ec42f0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ecd8e0);
dag->setRoot(node0x5ecd8e0);
      }
      break;
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
      {
SDValue node0x5ece6a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec3d30 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5ece6a0, mpi, MVT::i8, 1);
SDValue node0x5ec2e10 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ec3d30, SDValue());
roots.reserve(1);
roots.push_back(node0x5ec2e10);
dag->setRoot(node0x5ec2e10);
      }
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__AEXT_CLONE_:
      {
SDValue node0x5d20bd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d242a0 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5d20bd0, mpi, MVT::i8, 1);
SDValue node0x5ee55f0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d242a0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ee55f0);
dag->setRoot(node0x5ee55f0);
      }
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
      {
SDValue node0x5d25a10 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d254f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d25ae0 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5d25a10, node0x5d254f0);
SDValue node0x5ee61c0 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5d25ae0, mpi, MVT::i8, 1);
SDValue node0x5ee6250 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ee61c0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ee6250);
dag->setRoot(node0x5ee6250);
      }
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ecf0d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec31e0 = dag->getExtLoad(ISD::ZEXTLOAD, dl, MVT::i32, entry, node0x5ecf0d0, mpi, MVT::i8, 1);
SDValue node0x5ecd980 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ec31e0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ecd980);
dag->setRoot(node0x5ecd980);
      }
      break;
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
      {
SDValue node0x5ecf180 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec2bb0 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5ecf180, mpi, MVT::i8, 1);
SDValue node0x5debe30 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ec2bb0, SDValue());
roots.reserve(1);
roots.push_back(node0x5debe30);
dag->setRoot(node0x5debe30);
      }
      break;
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__immspec_1_:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__AEXT_CLONE_:
      {
SDValue node0x5d26740 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d29d40 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5d26740, mpi, MVT::i16, 1);
SDValue node0x5ee6eb0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d29d40, SDValue());
roots.reserve(1);
roots.push_back(node0x5ee6eb0);
dag->setRoot(node0x5ee6eb0);
      }
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__AEXT_CLONE_:
      {
SDValue node0x5d2b410 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d2aef0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d2b4e0 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5d2b410, node0x5d2aef0);
SDValue node0x5ee7a80 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5d2b4e0, mpi, MVT::i16, 1);
SDValue node0x5ee7b10 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ee7a80, SDValue());
roots.reserve(1);
roots.push_back(node0x5ee7b10);
dag->setRoot(node0x5ee7b10);
      }
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ed0390 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ecfbe0 = dag->getExtLoad(ISD::SEXTLOAD, dl, MVT::i32, entry, node0x5ed0390, mpi, MVT::i16, 1);
SDValue node0x5ececc0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ecfbe0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ececc0);
dag->setRoot(node0x5ececc0);
      }
      break;
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
      {
SDValue node0x5ed0440 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec25f0 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5ed0440, mpi, MVT::i16, 1);
SDValue node0x5ecb0c0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ec25f0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ecb0c0);
dag->setRoot(node0x5ecb0c0);
      }
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__AEXT_CLONE_:
      {
SDValue node0x5d2c190 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d2f860 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5d2c190, mpi, MVT::i16, 1);
SDValue node0x5ee8740 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d2f860, SDValue());
roots.reserve(1);
roots.push_back(node0x5ee8740);
dag->setRoot(node0x5ee8740);
      }
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
      {
SDValue node0x5d30fd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d30ab0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d310a0 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5d30fd0, node0x5d30ab0);
SDValue node0x5ee9310 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5d310a0, mpi, MVT::i16, 1);
SDValue node0x5ee93a0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ee9310, SDValue());
roots.reserve(1);
roots.push_back(node0x5ee93a0);
dag->setRoot(node0x5ee93a0);
      }
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ed0e70 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec4870 = dag->getExtLoad(ISD::ZEXTLOAD, dl, MVT::i32, entry, node0x5ed0e70, mpi, MVT::i16, 1);
SDValue node0x5ecf750 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ec4870, SDValue());
roots.reserve(1);
roots.push_back(node0x5ecf750);
dag->setRoot(node0x5ecf750);
      }
      break;
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__immspec_1_AEXT_CLONE_:
      {
SDValue node0x5ec7260 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec6860 = dag->getExtLoad(ISD::EXTLOAD, dl, MVT::i32, entry, node0x5ec7260, mpi, MVT::i16, 1);
SDValue node0x5ec9940 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ec6860, SDValue());
roots.reserve(1);
roots.push_back(node0x5ec9940);
dag->setRoot(node0x5ec9940);
      }
      break;
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__immspec_1_:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ed2130 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ed21e0 = dag->getLoad(MVT::i32, dl, entry, node0x5ed2130, mpi, 1);
SDValue node0x5ed0a60 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ed21e0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ed0a60);
dag->setRoot(node0x5ed0a60);
      }
      break;
    case Codasip::i_rtype_alu__opc_slt__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
      {
SDValue node0x5ec06e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec0830 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5ec08e0 = dag->getSetCC(dl, MVT::i32, node0x5ec06e0, node0x5ec0830, ISD::SETGT);
SDValue node0x5ebfd50 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ec08e0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ebfd50);
dag->setRoot(node0x5ebfd50);
      }
      break;
    case Codasip::i_rtype_alu__opc_sltu__xpr_general__xpr_general__xpr_general__swappedCmpClone0__:
      {
SDValue node0x5ec12b0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec1400 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5ec14b0 = dag->getSetCC(dl, MVT::i32, node0x5ec12b0, node0x5ec1400, ISD::SETUGT);
SDValue node0x5ec0ed0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ec14b0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ec0ed0);
dag->setRoot(node0x5ec0ed0);
      }
      break;
    case Codasip::i_rtype_alu__opc_sra__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_:
      {
SDValue node0x5d31d00 = dag->getConstant(31LL, dl, MVT::i32);
SDValue node0x5d8d730 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d31f20 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d94a30 = dag->getNode(ISD::AND, dl, MVT::i32, node0x5d31f20, node0x5d31d00);
SDValue node0x5d8d6a0 = dag->getNode(ISD::SRA, dl, MVT::i32, node0x5d8d730, node0x5d94a30);
SDValue node0x5ee9620 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d8d6a0, SDValue());
roots.reserve(1);
roots.push_back(node0x5ee9620);
dag->setRoot(node0x5ee9620);
      }
      break;
    case Codasip::i_rtype_alu__opc_srl__xpr_general__xpr_general__xpr_general__SHIFT_MASK_CLONE_:
      {
SDValue node0x5d4c4d0 = dag->getConstant(31LL, dl, MVT::i32);
SDValue node0x5de9b40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5de9bd0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5d4c850 = dag->getNode(ISD::AND, dl, MVT::i32, node0x5de9bd0, node0x5d4c4d0);
SDValue node0x5f00460 = dag->getNode(ISD::SRL, dl, MVT::i32, node0x5de9b40, node0x5d4c850);
SDValue node0x5de9c60 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5f00460, SDValue());
roots.reserve(1);
roots.push_back(node0x5de9c60);
dag->setRoot(node0x5de9c60);
      }
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ed3260 = dag->getConstant(0LL, dl, MVT::i8);
SDValue node0x5ed3460 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ed3200 = dag->getStore(entry, dl, node0x5ed3260, node0x5ed3460, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5ed3200);
dag->setRoot(node0x5ed3200);
      }
      break;
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ed3be0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ed3c90 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec6530 = dag->getTruncStore(entry, dl, node0x5ed3be0, node0x5ed3c90, mpi, MVT::i8, 1);
roots.reserve(1);
roots.push_back(node0x5ec6530);
dag->setRoot(node0x5ec6530);
      }
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ed44f0 = dag->getConstant(0LL, dl, MVT::i16);
SDValue node0x5ed4710 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ed4490 = dag->getStore(entry, dl, node0x5ed44f0, node0x5ed4710, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5ed4490);
dag->setRoot(node0x5ed4490);
      }
      break;
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ed4eb0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ed4f60 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ec90a0 = dag->getTruncStore(entry, dl, node0x5ed4eb0, node0x5ed4f60, mpi, MVT::i16, 1);
roots.reserve(1);
roots.push_back(node0x5ec90a0);
dag->setRoot(node0x5ec90a0);
      }
      break;
    case Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ed5770 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5ed58f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ed5710 = dag->getStore(entry, dl, node0x5ed5770, node0x5ed58f0, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5ed5710);
dag->setRoot(node0x5ed5710);
      }
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__immspec_1_:
      {
SDValue node0x5ed6090 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5ed6140 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5ed5ed0 = dag->getStore(entry, dl, node0x5ed6090, node0x5ed6140, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5ed5ed0);
dag->setRoot(node0x5ed5ed0);
      }
      break;
    case Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__immspec_1_:
      {
SDValue node0x5ed5cf0 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5ed6930 = dag->getConstant(-4LL, dl, MVT::i32);
SDValue node0x5ed5d60 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5ed5cf0, node0x5ed6930);
SDValue node0x5ed54f0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5ed5d60, SDValue());
roots.reserve(1);
roots.push_back(node0x5ed54f0);
dag->setRoot(node0x5ed54f0);
      }
      break;
    case Codasip::e_movi32__:
case Codasip::e_movi32__GA:
case Codasip::e_movi32__ES:
case Codasip::e_movi32__MC:
case Codasip::e_movi32__BA:
case Codasip::e_movi32__JT:
case Codasip::e_movi32__CP:
      {
SDValue node0x5eb9f00 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5eb9680 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5eb9f00, SDValue());
roots.reserve(1);
roots.push_back(node0x5eb9680);
dag->setRoot(node0x5eb9680);
      }
      break;
    case Codasip::i_ret_alias__TAILCALL_CLONE_:
      {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__immspec_1_TAILCALL_CLONE_:
      {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_:
case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES:
case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC:
case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA:
      {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_:
case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES:
case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC:
case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA:
      {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
      {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
      {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_:
case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES:
case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC:
case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA:
      {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_:
case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_ES:
case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_MC:
case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_BA:
      {
dag->setRoot(entry);
      }
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__i32_TRUNC_CLONE_:
      {
SDValue node0x5e072a0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5e07320 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5e07c60 = dag->getTruncStore(entry, dl, node0x5e072a0, node0x5e07320, mpi, MVT::i8, 1);
roots.reserve(1);
roots.push_back(node0x5e07c60);
dag->setRoot(node0x5e07c60);
      }
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
      {
SDValue node0x5e071a0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5e07080 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5e07220 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e03770 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e07080, node0x5e07220);
SDValue node0x5e08600 = dag->getTruncStore(entry, dl, node0x5e071a0, node0x5e03770, mpi, MVT::i8, 1);
roots.reserve(1);
roots.push_back(node0x5e08600);
dag->setRoot(node0x5e08600);
      }
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__i32_TRUNC_CLONE_:
      {
SDValue node0x5e073a0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5e08c40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5e08f90 = dag->getTruncStore(entry, dl, node0x5e073a0, node0x5e08c40, mpi, MVT::i16, 1);
roots.reserve(1);
roots.push_back(node0x5e08f90);
dag->setRoot(node0x5e08f90);
      }
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
      {
SDValue node0x5e095d0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5e06a30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5e09650 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e04730 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e06a30, node0x5e09650);
SDValue node0x5e09a30 = dag->getTruncStore(entry, dl, node0x5e095d0, node0x5e04730, mpi, MVT::i16, 1);
roots.reserve(1);
roots.push_back(node0x5e09a30);
dag->setRoot(node0x5e09a30);
      }
      break;
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_:
      {
SDValue node0x5e09dc0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5e06ff0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5e09fb0 = dag->getTruncStore(entry, dl, node0x5e09dc0, node0x5e06ff0, mpi, MVT::i8, 1);
roots.reserve(1);
roots.push_back(node0x5e09fb0);
dag->setRoot(node0x5e09fb0);
      }
      break;
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__immspec_1_i32_TRUNC_CLONE_:
      {
SDValue node0x5e0a3a0 = dag->getConstant(0LL, dl, MVT::i32);
SDValue node0x5e07110 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5e0a580 = dag->getTruncStore(entry, dl, node0x5e0a3a0, node0x5e07110, mpi, MVT::i16, 1);
roots.reserve(1);
roots.push_back(node0x5e0a580);
dag->setRoot(node0x5e0a580);
      }
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__0_REG_EMUL_:
      {
SDValue node0x5e0ad00 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5e0c270 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e0adf0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5e11170 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e0c270, node0x5e0adf0);
SDValue node0x5e0a5e0 = dag->getStore(entry, dl, node0x5e0ad00, node0x5e11170, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5e0a5e0);
dag->setRoot(node0x5e0a5e0);
      }
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__1_BIGIMM_EMUL_:
      {
SDValue node0x5e0d8a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5e113a0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e108e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5e11430 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e113a0, node0x5e108e0);
SDValue node0x5e10290 = dag->getStore(entry, dl, node0x5e0d8a0, node0x5e11430, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5e10290);
dag->setRoot(node0x5e10290);
      }
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__2_REG_EMUL_:
      {
SDValue node0x5e0ec30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e0d240 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5e0e260 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e0ec30, node0x5e0d240);
SDValue node0x5e0eba0 = dag->getLoad(MVT::i32, dl, entry, node0x5e0e260, mpi, 1);
SDValue node0x5e0aca0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5e0eba0, SDValue());
roots.reserve(1);
roots.push_back(node0x5e0aca0);
dag->setRoot(node0x5e0aca0);
      }
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__3_BIGIMM_EMUL_:
      {
SDValue node0x5e0be60 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e11ef0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5e0fc40 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e0be60, node0x5e11ef0);
SDValue node0x5e10000 = dag->getLoad(MVT::i32, dl, entry, node0x5e0fc40, mpi, 1);
SDValue node0x5e12020 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5e10000, SDValue());
roots.reserve(1);
roots.push_back(node0x5e12020);
dag->setRoot(node0x5e12020);
      }
      break;
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__4_BIGIMM_EMUL_:
      {
SDValue node0x5e11610 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5e13090 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e13530 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5e0fd20 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e13090, node0x5e13530);
SDValue node0x5e0b3d0 = dag->getStore(entry, dl, node0x5e11610, node0x5e0fd20, mpi, 1);
roots.reserve(1);
roots.push_back(node0x5e0b3d0);
dag->setRoot(node0x5e0b3d0);
      }
      break;
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__5_BIGIMM_EMUL_:
      {
SDValue node0x5e0c110 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e143e0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5e0e720 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e0c110, node0x5e143e0);
SDValue node0x5e13e00 = dag->getLoad(MVT::i32, dl, entry, node0x5e0e720, mpi, 1);
SDValue node0x5e144e0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5e13e00, SDValue());
roots.reserve(1);
roots.push_back(node0x5e144e0);
dag->setRoot(node0x5e144e0);
      }
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__6_BIGIMM_EMUL_:
      {
SDValue node0x5e10ef0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e152b0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5e10e80 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e10ef0, node0x5e152b0);
SDValue node0x5e15370 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5e10e80, SDValue());
roots.reserve(1);
roots.push_back(node0x5e15370);
dag->setRoot(node0x5e15370);
      }
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__7_BIGIMM_EMUL_:
      {
SDValue node0x5e13120 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e16070 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5e10a70 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e13120, node0x5e16070);
SDValue node0x5e16130 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5e10a70, SDValue());
roots.reserve(1);
roots.push_back(node0x5e16130);
dag->setRoot(node0x5e16130);
      }
      break;
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__8_BIGIMM_EMUL_:
      {
SDValue node0x5e15990 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5e16e30 = dag->getRegister(TargetRegisterInfo::index2VirtReg(2), MVT::i32);
SDValue node0x5e10800 = dag->getNode(ISD::ADD, dl, MVT::i32, node0x5e15990, node0x5e16e30);
SDValue node0x5e16ef0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5e10800, SDValue());
roots.reserve(1);
roots.push_back(node0x5e16ef0);
dag->setRoot(node0x5e16ef0);
      }
      break;
    case Codasip::i_halt__opc_halt__:
      {
roots.reserve(0);
dag->setRoot(entry);
      }
      break;
    case Codasip::i_call_reg_alias__simm12__xpr_general__:
      {
SDValue node0x5bed590 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5bed960 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5f0bc20 = dag->getCopyToReg(entry, dl, dag->getRegister(Codasip::rf_xpr_1, MVT::i32), node0x5bed590, SDValue());
SDValue node0x5bedc10 = dag->getNode(ISD::BRIND, dl, MVT::Other, node0x5f0bc20, node0x5bed960);
roots.reserve(2);
roots.push_back(node0x5f0bc20);
roots.push_back(node0x5bedc10);
dag->setRoot(node0x5bedc10);
      }
      break;
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__:
      {
SDValue node0x5d17120 = dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32);
SDValue node0x5d173c0 = dag->getNode(ISD::BRIND, dl, MVT::Other, entry, node0x5d17120);
roots.reserve(1);
roots.push_back(node0x5d173c0);
dag->setRoot(node0x5d173c0);
      }
      break;
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__:
      {
SDValue node0x5d19df0 = dag->getNode(CodasipISD::GET_PC, dl, MVT::i32);
SDValue node0x5d19d70 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d19df0, SDValue());
SDValue node0x5d1a2f0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5d1a590 = dag->getNode(ISD::BRIND, dl, MVT::Other, node0x5d19d70, node0x5d1a2f0);
roots.reserve(2);
roots.push_back(node0x5d19d70);
roots.push_back(node0x5d1a590);
dag->setRoot(node0x5d1a590);
      }
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__1_:
      {
SDValue node0x5d59b10 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5dea510 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d59b10, SDValue());
roots.reserve(1);
roots.push_back(node0x5dea510);
dag->setRoot(node0x5dea510);
      }
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__2_:
      {
SDValue node0x5d31c80 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5deacb0 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5d31c80, SDValue());
roots.reserve(1);
roots.push_back(node0x5deacb0);
dag->setRoot(node0x5deacb0);
      }
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__5_:
      {
SDValue node0x5f017d0 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5deb460 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5f017d0, SDValue());
roots.reserve(1);
roots.push_back(node0x5deb460);
dag->setRoot(node0x5deb460);
      }
      break;
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__6_:
      {
SDValue node0x5cb7f40 = dag->getRegister(TargetRegisterInfo::index2VirtReg(1), MVT::i32);
SDValue node0x5debc10 = dag->getCopyToReg(entry, dl, dag->getRegister(TargetRegisterInfo::index2VirtReg(0), MVT::i32), node0x5cb7f40, SDValue());
roots.reserve(1);
roots.push_back(node0x5debc10);
dag->setRoot(node0x5debc10);
      }
      break;
    
    default:
      roots.reserve(1);
      roots.push_back(entry);
      dag->setRoot(entry);
  }
  dag->RemoveDeadNodes();
  return dag;
}

// turn optimizations back on
#ifdef _WIN32
  #pragma optimize("", on)
#endif
