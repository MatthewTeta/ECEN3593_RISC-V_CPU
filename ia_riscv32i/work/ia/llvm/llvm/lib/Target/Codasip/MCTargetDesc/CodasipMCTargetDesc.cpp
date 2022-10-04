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


#include "llvm/MC/MachineLocation.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/Support/TargetRegistry.h"

#include "CodasipMCTargetDesc.h"
#include "CodasipMCAsmInfo.h"
#include "CodasipMCELFStreamer.h"
#include "CodasipTargetStreamer.h"
#include "InstPrinter/CodasipInstPrinter.h"

#define GET_INSTRINFO_MC_DESC
#include "CodasipGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "CodasipGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "CodasipGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo* createCodasipMCInstrInfo()
{
  MCInstrInfo *X = new MCInstrInfo();
  InitCodasipMCInstrInfo(X);
  return X;
}

static MCRegisterInfo* createCodasipMCRegisterInfo(const Triple &)
{
  MCRegisterInfo *X = new MCRegisterInfo();
  const int RA = Codasip:: rf_xpr_1;
  InitCodasipMCRegisterInfo(X,RA);
  return X;
}

static MCSubtargetInfo* createCodasipMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS)
{
  //MCSubtargetInfo *X = new MCSubtargetInfo();
  //InitCodasipMCSubtargetInfo(X, TT, CPU, FS);
  //return X;
  if (CPU.empty())
    CPU = "codasip";
  return createCodasipMCSubtargetInfoImpl(TT, CPU, FS);
}

static MCAsmInfo* createCodasipMCAsmInfo(const MCRegisterInfo &MRI, const Triple &TT)
{
  MCAsmInfo *MAI = new CodasipMCAsmInfo(TT);
  // get SP (space 0)
  const int SP = Codasip:: rf_xpr_2 ;
  // note: our registers have only one dwarf number each
  MCCFIInstruction Inst = MCCFIInstruction::createDefCfa(nullptr, MRI.getDwarfRegNum(SP,0), 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

namespace {

class CodasipMCInstrAnalysis : public MCInstrAnalysis {
public:
  CodasipMCInstrAnalysis(const MCInstrInfo *Info) : MCInstrAnalysis(Info) {}

  bool evaluateBranch(const MCInst &Inst, uint64_t Addr, uint64_t Size,
                      uint64_t &Target) const override {
    unsigned NumOps = Inst.getNumOperands();
    if (NumOps == 0)
      return false;
    switch (Info->get(Inst.getOpcode()).OpInfo[NumOps - 1].OperandType) {
    case MCOI::OPERAND_UNKNOWN:
    case MCOI::OPERAND_IMMEDIATE:
      // jal, bal ...
      Target = Inst.getOperand(NumOps - 1).getImm();
      return true;
    case MCOI::OPERAND_PCREL:
      // b, j, beq ...
      Target = Addr + Inst.getOperand(NumOps - 1).getImm();
      return true;
    default:
      return false;
    }
  }
  bool isLabel(const MCInst &Inst) const override {
    switch (Inst.getOpcode()) {
    case Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_beq__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_beq__x_0__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_beq__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_beq__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_beq__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_beq__xpr_general__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_beq__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_beq__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bge__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bge__x_0__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bge__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bge__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bge__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bge__xpr_general__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bge__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bge__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bgeu__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bgeu__x_0__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bgeu__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bgeu__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bgeu__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bgeu__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_blt__x_0__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_blt__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_blt__x_0__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_blt__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_blt__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_blt__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_blt__xpr_general__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_blt__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_blt__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bltu__x_0__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bltu__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bltu__x_0__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bltu__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bltu__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bltu__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bltu__xpr_general__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bltu__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bltu__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bne__x_0__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bne__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bne__x_0__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bne__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bne__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bne__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_btype_branches__opc_bne__xpr_general__x_0__relative_addr12__:
    case Codasip::i_btype_branches__opc_bne__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_btype_branches__opc_bne__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_beqz_alias__x_0__relative_addr12__:
    case Codasip::i_beqz_alias__x_0_alias__relative_addr12__:
    case Codasip::i_beqz_alias__xpr_general__relative_addr12__:
    case Codasip::i_bgez_alias__x_0__relative_addr12__:
    case Codasip::i_bgez_alias__x_0_alias__relative_addr12__:
    case Codasip::i_bgez_alias__xpr_general__relative_addr12__:
    case Codasip::i_bgt_alias__x_0__x_0__relative_addr12__:
    case Codasip::i_bgt_alias__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_bgt_alias__x_0__xpr_general__relative_addr12__:
    case Codasip::i_bgt_alias__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_bgt_alias__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_bgt_alias__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_bgt_alias__xpr_general__x_0__relative_addr12__:
    case Codasip::i_bgt_alias__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_bgt_alias__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_bgtu_alias__x_0__x_0__relative_addr12__:
    case Codasip::i_bgtu_alias__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_bgtu_alias__x_0__xpr_general__relative_addr12__:
    case Codasip::i_bgtu_alias__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_bgtu_alias__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_bgtu_alias__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_bgtu_alias__xpr_general__x_0__relative_addr12__:
    case Codasip::i_bgtu_alias__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_bgtu_alias__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_bgtz_alias__x_0__relative_addr12__:
    case Codasip::i_bgtz_alias__x_0_alias__relative_addr12__:
    case Codasip::i_bgtz_alias__xpr_general__relative_addr12__:
    case Codasip::i_ble_alias__x_0__x_0__relative_addr12__:
    case Codasip::i_ble_alias__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_ble_alias__x_0__xpr_general__relative_addr12__:
    case Codasip::i_ble_alias__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_ble_alias__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_ble_alias__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_ble_alias__xpr_general__x_0__relative_addr12__:
    case Codasip::i_ble_alias__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_ble_alias__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_bleu_alias__x_0__x_0__relative_addr12__:
    case Codasip::i_bleu_alias__x_0__x_0_alias__relative_addr12__:
    case Codasip::i_bleu_alias__x_0__xpr_general__relative_addr12__:
    case Codasip::i_bleu_alias__x_0_alias__x_0__relative_addr12__:
    case Codasip::i_bleu_alias__x_0_alias__x_0_alias__relative_addr12__:
    case Codasip::i_bleu_alias__x_0_alias__xpr_general__relative_addr12__:
    case Codasip::i_bleu_alias__xpr_general__x_0__relative_addr12__:
    case Codasip::i_bleu_alias__xpr_general__x_0_alias__relative_addr12__:
    case Codasip::i_bleu_alias__xpr_general__xpr_general__relative_addr12__:
    case Codasip::i_blez_alias__x_0__relative_addr12__:
    case Codasip::i_blez_alias__x_0_alias__relative_addr12__:
    case Codasip::i_blez_alias__xpr_general__relative_addr12__:
    case Codasip::i_bltz_alias__x_0__relative_addr12__:
    case Codasip::i_bltz_alias__x_0_alias__relative_addr12__:
    case Codasip::i_bltz_alias__xpr_general__relative_addr12__:
    case Codasip::i_bnez_alias__x_0__relative_addr12__:
    case Codasip::i_bnez_alias__x_0_alias__relative_addr12__:
    case Codasip::i_bnez_alias__xpr_general__relative_addr12__:
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__:
    case Codasip::i_jal_abs_calias__opc_jal__xpr_general__relative_addr20__:
    case Codasip::i_call_alias__relative_addr20__:
    case Codasip::i_j_alias__relative_addr20__:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__:
    case Codasip::i_jtype_jlink__opc_jal__x_0_alias__relative_addr20__:
    case Codasip::i_jtype_jlink__opc_jal__xpr_general__relative_addr20__:
      return true;
    default:
      return false;
    }
  }
};

}

static MCInstPrinter* createCodasipMCInstPrinter
(const Triple &, unsigned SyntaxVariant, const MCAsmInfo &MAI,
 const MCInstrInfo &MII, const MCRegisterInfo &MRI)
{
  return new CodasipInstPrinter(MAI,MII,MRI);
}

static MCStreamer *createELFStreamer(const Triple &T, MCContext &Ctx,
                                     std::unique_ptr<MCAsmBackend> &&TAB,
                                     std::unique_ptr<MCObjectWriter> &&OW,
                                     std::unique_ptr<MCCodeEmitter> &&Emitter,
                                     bool RelaxAll) {
  return createCodasipELFStreamer(T, Ctx, std::move(TAB), std::move(OW), std::move(Emitter), RelaxAll);
}

static MCInstrAnalysis *createCodasipMCInstrAnalysis(const MCInstrInfo *Info) {
  return new CodasipMCInstrAnalysis(Info);
}

extern "C" void LLVMInitializeCodasipTargetMC()
{
  // Register the MC asm info.
  TargetRegistry::RegisterMCAsmInfo(TheCodasipTarget, createCodasipMCAsmInfo);
  // Register the MC codegen info.
  //TargetRegistry::registerMCAdjustCodeGenOpts(TheCodasipTarget, createCodasipMCAdjustCodeGenOpts);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheCodasipTarget, createCodasipMCInstrInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheCodasipTarget, createCodasipMCRegisterInfo);
  // Instruction printer
  TargetRegistry::RegisterMCInstPrinter(TheCodasipTarget, createCodasipMCInstPrinter);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheCodasipTarget, createCodasipMCSubtargetInfo);
  // Register the MC instruction analyzer.
  TargetRegistry::RegisterMCInstrAnalysis(TheCodasipTarget, createCodasipMCInstrAnalysis);

  TargetRegistry::RegisterMCAsmBackend(TheCodasipTarget, createCodasipAsmBackend);
  TargetRegistry::RegisterMCCodeEmitter(TheCodasipTarget, createCodasipMCCodeEmitter);

  TargetRegistry::RegisterELFStreamer(TheCodasipTarget, createELFStreamer);
  TargetRegistry::RegisterObjectTargetStreamer(
                  TheCodasipTarget, createCodasipObjectTargetStreamer);

  // // Register the asm target streamer.
  TargetRegistry::RegisterAsmTargetStreamer(TheCodasipTarget,
                                            createCodasipAsmTargetStreamer);
}

