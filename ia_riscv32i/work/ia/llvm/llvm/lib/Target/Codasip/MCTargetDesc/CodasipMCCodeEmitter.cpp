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


#include <cstdarg>
#include "MCTargetDesc/CodasipMCTargetDesc.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"
#include "MCTargetDesc/CodasipBundleFunctionGen.h"
#include "MCTargetDesc/CodasipCustomFixupEncoder.h"
#include "MCTargetDesc/CodasipFixupKinds.h"
#include "Codasip.h"
#include "CodasipMCExpr.h"
#include "codasip/ObjectFile/CodasipObjectFile.h" // APIntToCodasipInt
#include "common/codasip_integer.h"

//#define DEBUG_CLASS

extern llvm::cl::opt<bool> RiscvTarget;

namespace llvm {

/**
 *  \brief  Print location on stderr.
 */
void printLocation(const SMLoc Loc, const SourceMgr *SM) {
  if (Loc.isValid() && SM) {
    unsigned CurBuf = SM->FindBufferContainingLoc(Loc);
    assert(CurBuf && "Invalid or unspecified location!");
    const MemoryBuffer *CurMB = SM->getMemoryBuffer(CurBuf);
    auto LineCol = SM->getLineAndColumn(Loc, CurBuf);
    errs() << CurMB->getBufferIdentifier() << ":" << LineCol.first << ":" << LineCol.second;
  } else
    errs() << "?:?:?";
}

/**
 *  \brief  Print warning about relocation truncation.
 *  \param[in]  Value Relocation value.
 *  \param[in]  BitWidth Bit-width of the result.
 *  \param[in]  Signed Sign of the result.
 *  \param[in]  Loc Location in the source buffer.
 *  \param[in]  SM Source manager, it is missing for *integrated_as mod.
 */
void printTruncationWarning(const uint64_t Value, const unsigned BitWidth, const bool Signed,
  const SMLoc Loc, const SourceMgr *SM) {
  const char *Sign = Signed ? "Signed" : "Unsigned";
  const uint64_t Truncated = Value & maskTrailingOnes<uint64_t>(BitWidth);

  printLocation(Loc, SM);

  errs() << ": warning: " << Sign
    << " relocation truncation overflow, value " << Value << "(0x";
  errs().write_hex(Value);
  errs() << ") was truncated to ";
  if (Signed)
    errs() << SignExtend64(Truncated, BitWidth);
  else
    errs() << Truncated;
  errs() << "(0x";
  errs().write_hex(Truncated);
  errs() << ").\n";
}

/**
 *  \brief  Checks that given Value fits into specified BitWidth.
 *  \param[in]  Value Checked value.
 *  \param[in]  BitWidth Bit-width of the result.
 *  \param[in]  Signed Sign of the result.
 *  \param[in]  Masked Initial expression was masked (Value could fit anywhere then).
 *  \param[in]  Loc Location in the source buffer.
 *  \param[in]  SM Source manager, it is missing for *integrated_as mod.
 */
void checkTruncationOverflow(const uint64_t Value, const unsigned BitWidth,
                             const bool Signed, const bool Masked, const SMLoc Loc, const SourceMgr *SM) {
  if (RiscvTarget)
    return;

  const unsigned TruncatedBits = sizeof(uint64_t) * 8 - BitWidth;
  if (Signed) {
    if ((Value & (0x1ull << (BitWidth - 1))) == 0) {
      if (countLeadingZeros(Value) < TruncatedBits)
        printTruncationWarning(Value, BitWidth, true, Loc, SM);
    } else {
      if (!Masked && countLeadingOnes(Value) < TruncatedBits)
        printTruncationWarning(Value, BitWidth, true, Loc, SM);
    }
  } else {
    if (!Masked && countLeadingZeros(Value) < TruncatedBits)
      printTruncationWarning(Value, BitWidth, false, Loc, SM);
  }
}

/**
 *  \brief  Execute codasip_fatal.
 *  \param[in]  ExitCode Exit code
 *  \param[in]  Format Formatted text
 */
int codasip_fatal(uint32_t ExitCode, const char *Format, ...) {
  va_list VL;
  va_start(VL, Format);
  vprintf(Format, VL);
  va_end(VL);
  printf("\n");
  exit(ExitCode);
}

/**
 *  \brief  Implementation placed here because header needs to be rebuild on change.
 *  \param[in]  MI Instruction
 *  \param[in]  AttributeId Attribute identifier
 *  \param[in]  SM Source manager, if available
 */
int64_t getAttributeValue(const MCInst& MI, const std::string &AttributeId, const SourceMgr *SM) {
  for (unsigned int i = 0; i < MI.getNumOperands(); i++) {
    const MCOperand &Op = MI.getOperand(i);
    if (Op.getAttributeId() == AttributeId) {
      if (!Op.isImm()) {
        printLocation(MI.getLoc(), SM);
        errs() << "Expecting constant value operand.\n";
        return 0;
      }
      return Op.getImm();
    }
  }
  assert(false && "Missing attribute identifier of encoding/decoding section in instruction.");
  return 0;
}

}   // namespace llvm

using namespace llvm;

#define DEBUG_TYPE "mccodeemitter"

STATISTIC(MCNumEmitted, "Number of MC instructions emitted");

namespace {

class CodasipMCCodeEmitter : public MCCodeEmitter {
  CodasipMCCodeEmitter(const CodasipMCCodeEmitter &) = delete;
  void operator=(const CodasipMCCodeEmitter &) = delete;
  const MCInstrInfo &MCII;
  MCContext &Ctx;
  // Generated custom fixup encoder
  CodasipCustomFixupEncoderGen m_GeneratedCustomFixupEncoder;
  // User custom fixup encoder (for RISC-V)
  CodasipCustomFixupEncoder m_UserCustomFixupEncoder;

public:
  CodasipMCCodeEmitter(const MCInstrInfo &mcii, MCContext &ctx) : MCII(mcii), Ctx(ctx), m_GeneratedCustomFixupEncoder(ctx), m_UserCustomFixupEncoder(ctx) {}

  ~CodasipMCCodeEmitter() override {}
  
  const CodasipCustomFixupEncoderGen &getCustomFixupEncoder() const;




  void encodeInstruction(const MCInst &MI, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  /// TableGen'erated function for getting the binary encoding for an
  /// instruction.

  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;


  /// Return binary encoding of operand. If the machine operand requires
  /// relocation, record the relocation and return zero.

  unsigned getMachineOpValue(const MCInst &MI,
                             const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;


  uint64_t encodeMI5valueIH1_13default_start7_5uimm53imm1_5uimm5(const MCInst &MI,
    unsigned OpIdx,
    SmallVectorImpl<MCFixup> &Fixups,
    const MCSubtargetInfo &STI) const;
  uint64_t encodeMI5valueIH1_13default_start8_6simm124simm1_6simm12(const MCInst &MI,
    unsigned OpIdx,
    SmallVectorImpl<MCFixup> &Fixups,
    const MCSubtargetInfo &STI) const;
  uint64_t encodeMI5valueIH1_13default_start8_6uimm203imm1_6uimm20(const MCInst &MI,
    unsigned OpIdx,
    SmallVectorImpl<MCFixup> &Fixups,
    const MCSubtargetInfo &STI) const;
  uint64_t encodeMI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12(const MCInst &MI,
    unsigned OpIdx,
    SmallVectorImpl<MCFixup> &Fixups,
    const MCSubtargetInfo &STI) const;
  uint64_t encodeMI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12(const MCInst &MI,
    unsigned OpIdx,
    SmallVectorImpl<MCFixup> &Fixups,
    const MCSubtargetInfo &STI) const;
  uint64_t encodeMI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20(const MCInst &MI,
    unsigned OpIdx,
    SmallVectorImpl<MCFixup> &Fixups,
    const MCSubtargetInfo &STI) const;

};
} // end anonymous namespace

MCCodeEmitter *llvm::createCodasipMCCodeEmitter(const MCInstrInfo &MCII,
                                              const MCRegisterInfo &MRI,
                                              MCContext &Ctx) {
  return new CodasipMCCodeEmitter(MCII, Ctx);
}

const CodasipCustomFixupEncoderGen &CodasipMCCodeEmitter::getCustomFixupEncoder() const {
  return RiscvTarget ? m_UserCustomFixupEncoder : m_GeneratedCustomFixupEncoder;
}




void CodasipMCCodeEmitter::encodeInstruction(const MCInst &MI, raw_ostream &OS,
                                           SmallVectorImpl<MCFixup> &Fixups,
                                           const MCSubtargetInfo &STI) const {
  uint64_t Bits = getBinaryCodeForInstr(MI, Fixups, STI);
  support::endian::write(OS, (uint32_t)(Bits), support::little);

  ++MCNumEmitted; // Keep track of the # of mi's emitted.
}


unsigned CodasipMCCodeEmitter::getMachineOpValue(const MCInst &MI,
                                                 const MCOperand &MO,
                                                 SmallVectorImpl<MCFixup> &Fixups,
                                                 const MCSubtargetInfo &STI) const {
#ifdef DEBUG_CLASS
  outs() << "CodasipMCCodeEmitter::getMachineOpValue\n";
#endif

  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());

  // MO must be an immediate, only encoder methods should handle expressions properly
  assert(MO.isImm() && "Unexpected expression. Missing encoder method.");
  return MO.getImm();
}


uint64_t CodasipMCCodeEmitter::encodeMI5valueIH1_13default_start7_5uimm53imm1_5uimm5(const MCInst &MI,
  unsigned OpIdx,
  SmallVectorImpl<MCFixup> &Fixups,
  const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpIdx);
  if (MO.isImm()) {
    int64_t MI5valueIH1_13default_start7_5uimm53imm1_5uimm5 = MO.getImm();
    bool encodingSectionHasMask = false;
    switch (MI.getOpcode()) {
    case Codasip::i_rtype_shift__opc_slli__x_0__x_0__uimm5__:
    case Codasip::i_rtype_shift__opc_slli__x_0__x_0_alias__uimm5__:
    case Codasip::i_rtype_shift__opc_slli__x_0__xpr_general__uimm5__:
    case Codasip::i_rtype_shift__opc_slli__x_0_alias__x_0__uimm5__:
    case Codasip::i_rtype_shift__opc_slli__x_0_alias__x_0_alias__uimm5__:
    case Codasip::i_rtype_shift__opc_slli__x_0_alias__xpr_general__uimm5__:
    case Codasip::i_rtype_shift__opc_slli__xpr_general__x_0__uimm5__:
    case Codasip::i_rtype_shift__opc_slli__xpr_general__x_0_alias__uimm5__:
    case Codasip::i_rtype_shift__opc_slli__xpr_general__xpr_general__uimm5__:
    case Codasip::i_rtype_shift__opc_srai__x_0__x_0__uimm5__:
    case Codasip::i_rtype_shift__opc_srai__x_0__x_0_alias__uimm5__:
    case Codasip::i_rtype_shift__opc_srai__x_0__xpr_general__uimm5__:
    case Codasip::i_rtype_shift__opc_srai__x_0_alias__x_0__uimm5__:
    case Codasip::i_rtype_shift__opc_srai__x_0_alias__x_0_alias__uimm5__:
    case Codasip::i_rtype_shift__opc_srai__x_0_alias__xpr_general__uimm5__:
    case Codasip::i_rtype_shift__opc_srai__xpr_general__x_0__uimm5__:
    case Codasip::i_rtype_shift__opc_srai__xpr_general__x_0_alias__uimm5__:
    case Codasip::i_rtype_shift__opc_srai__xpr_general__xpr_general__uimm5__:
    case Codasip::i_rtype_shift__opc_srli__x_0__x_0__uimm5__:
    case Codasip::i_rtype_shift__opc_srli__x_0__x_0_alias__uimm5__:
    case Codasip::i_rtype_shift__opc_srli__x_0__xpr_general__uimm5__:
    case Codasip::i_rtype_shift__opc_srli__x_0_alias__x_0__uimm5__:
    case Codasip::i_rtype_shift__opc_srli__x_0_alias__x_0_alias__uimm5__:
    case Codasip::i_rtype_shift__opc_srli__x_0_alias__xpr_general__uimm5__:
    case Codasip::i_rtype_shift__opc_srli__xpr_general__x_0__uimm5__:
    case Codasip::i_rtype_shift__opc_srli__xpr_general__x_0_alias__uimm5__:
    case Codasip::i_rtype_shift__opc_srli__xpr_general__xpr_general__uimm5__:
      checkTruncationOverflow(MI5valueIH1_13default_start7_5uimm53imm1_5uimm5, 5, 0, MO.isMasked() || encodingSectionHasMask, MI.getLoc(), Ctx.getSourceManager());
      break;
    default:
      break;
    }
    return MI5valueIH1_13default_start7_5uimm53imm1_5uimm5;
  }
  assert(MO.isExpr());
  // Function hook for custom fixup
  if (getCustomFixupEncoder().customEncodeMI5valueIH1_13default_start7_5uimm53imm1_5uimm5(MI, MO, Fixups, STI))
    return 0;
  const Codasip::Fixups Kind = Codasip::FK_Codasip_MI5valueIH1_13default_start7_5uimm53imm1_5uimm5;
  (void)Kind; // suppress warning
  const MCInstrDesc &IDesc = MCII.get(MI.getOpcode());
  (void)IDesc; // suppress warning
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 4, 0, IDesc.getSize(), 24, 20, 1, 0));
  return 0;
}

uint64_t CodasipMCCodeEmitter::encodeMI5valueIH1_13default_start8_6simm124simm1_6simm12(const MCInst &MI,
  unsigned OpIdx,
  SmallVectorImpl<MCFixup> &Fixups,
  const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpIdx);
  if (MO.isImm()) {
    int64_t MI5valueIH1_13default_start8_6simm124simm1_6simm12 = MO.getImm();
    bool encodingSectionHasMask = false;
    switch (MI.getOpcode()) {
    case Codasip::i_call_reg_alias__simm12__x_0__:
    case Codasip::i_call_reg_alias__simm12__x_0_alias__:
    case Codasip::i_call_reg_alias__simm12__xpr_general__:
    case Codasip::i_itype_alu__opc_addi__x_0__x_0__simm12__:
    case Codasip::i_itype_alu__opc_addi__x_0__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_addi__x_0__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_addi__x_0_alias__x_0__simm12__:
    case Codasip::i_itype_alu__opc_addi__x_0_alias__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_addi__x_0_alias__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_addi__xpr_general__x_0__simm12__:
    case Codasip::i_itype_alu__opc_addi__xpr_general__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_andi__x_0__x_0__simm12__:
    case Codasip::i_itype_alu__opc_andi__x_0__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_andi__x_0__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_andi__x_0_alias__x_0__simm12__:
    case Codasip::i_itype_alu__opc_andi__x_0_alias__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_andi__x_0_alias__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_andi__xpr_general__x_0__simm12__:
    case Codasip::i_itype_alu__opc_andi__xpr_general__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_andi__xpr_general__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_ori__x_0__x_0__simm12__:
    case Codasip::i_itype_alu__opc_ori__x_0__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_ori__x_0__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_ori__x_0_alias__x_0__simm12__:
    case Codasip::i_itype_alu__opc_ori__x_0_alias__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_ori__x_0_alias__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_ori__xpr_general__x_0__simm12__:
    case Codasip::i_itype_alu__opc_ori__xpr_general__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_ori__xpr_general__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_slti__x_0__x_0__simm12__:
    case Codasip::i_itype_alu__opc_slti__x_0__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_slti__x_0__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_slti__x_0_alias__x_0__simm12__:
    case Codasip::i_itype_alu__opc_slti__x_0_alias__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_slti__x_0_alias__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__:
    case Codasip::i_itype_alu__opc_slti__xpr_general__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_sltiu__x_0__x_0__simm12__:
    case Codasip::i_itype_alu__opc_sltiu__x_0__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_sltiu__x_0__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_sltiu__x_0_alias__x_0__simm12__:
    case Codasip::i_itype_alu__opc_sltiu__x_0_alias__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_sltiu__x_0_alias__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__:
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_xori__x_0__x_0__simm12__:
    case Codasip::i_itype_alu__opc_xori__x_0__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_xori__x_0__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_xori__x_0_alias__x_0__simm12__:
    case Codasip::i_itype_alu__opc_xori__x_0_alias__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_xori__x_0_alias__xpr_general__simm12__:
    case Codasip::i_itype_alu__opc_xori__xpr_general__x_0__simm12__:
    case Codasip::i_itype_alu__opc_xori__xpr_general__x_0_alias__simm12__:
    case Codasip::i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0_alias__:
    case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__:
    case Codasip::i_itype_jlreg__opc_jalr__x_0_alias__simm12__x_0__:
    case Codasip::i_itype_jlreg__opc_jalr__x_0_alias__simm12__x_0_alias__:
    case Codasip::i_itype_jlreg__opc_jalr__x_0_alias__simm12__xpr_general__:
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0__:
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0_alias__:
    case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lb__x_0_alias__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lb__x_0_alias__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lb__x_0_alias__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lbu__x_0__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lbu__x_0_alias__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lbu__x_0_alias__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lbu__x_0_alias__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lh__x_0_alias__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lh__x_0_alias__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lh__x_0_alias__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lhu__x_0__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lhu__x_0_alias__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lhu__x_0_alias__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lhu__x_0_alias__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lw__x_0_alias__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lw__x_0_alias__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lw__x_0_alias__simm12__xpr_general__:
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0__:
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0_alias__:
    case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__:
    case Codasip::i_li_alias__x_0__simm12__:
    case Codasip::i_li_alias__x_0_alias__simm12__:
    case Codasip::i_li_alias__xpr_general__simm12__:
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__:
    case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0_alias__:
    case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__:
    case Codasip::i_stype_store__opc_sb__x_0_alias__simm12__x_0__:
    case Codasip::i_stype_store__opc_sb__x_0_alias__simm12__x_0_alias__:
    case Codasip::i_stype_store__opc_sb__x_0_alias__simm12__xpr_general__:
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__x_0__:
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__x_0_alias__:
    case Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__:
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__:
    case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0_alias__:
    case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__:
    case Codasip::i_stype_store__opc_sh__x_0_alias__simm12__x_0__:
    case Codasip::i_stype_store__opc_sh__x_0_alias__simm12__x_0_alias__:
    case Codasip::i_stype_store__opc_sh__x_0_alias__simm12__xpr_general__:
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__x_0__:
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__x_0_alias__:
    case Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__:
    case Codasip::i_stype_store__opc_sw__x_0__simm12__x_0__:
    case Codasip::i_stype_store__opc_sw__x_0__simm12__x_0_alias__:
    case Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__:
    case Codasip::i_stype_store__opc_sw__x_0_alias__simm12__x_0__:
    case Codasip::i_stype_store__opc_sw__x_0_alias__simm12__x_0_alias__:
    case Codasip::i_stype_store__opc_sw__x_0_alias__simm12__xpr_general__:
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__x_0__:
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__x_0_alias__:
    case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__:
      checkTruncationOverflow(MI5valueIH1_13default_start8_6simm124simm1_6simm12, 12, 1, MO.isMasked() || encodingSectionHasMask, MI.getLoc(), Ctx.getSourceManager());
      break;
    default:
      break;
    }
    return MI5valueIH1_13default_start8_6simm124simm1_6simm12;
  }
  assert(MO.isExpr());
  // Function hook for custom fixup
  if (getCustomFixupEncoder().customEncodeMI5valueIH1_13default_start8_6simm124simm1_6simm12(MI, MO, Fixups, STI))
    return 0;
  const Codasip::Fixups Kind = Codasip::FK_Codasip_MI5valueIH1_13default_start8_6simm124simm1_6simm12;
  (void)Kind; // suppress warning
  const MCInstrDesc &IDesc = MCII.get(MI.getOpcode());
  (void)IDesc; // suppress warning
  switch (MI.getOpcode()) {
  case Codasip::i_call_reg_alias__simm12__x_0__:
  case Codasip::i_call_reg_alias__simm12__x_0_alias__:
  case Codasip::i_call_reg_alias__simm12__xpr_general__:
  case Codasip::i_itype_alu__opc_addi__x_0__x_0__simm12__:
  case Codasip::i_itype_alu__opc_addi__x_0__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_addi__x_0__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_addi__x_0_alias__x_0__simm12__:
  case Codasip::i_itype_alu__opc_addi__x_0_alias__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_addi__x_0_alias__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_addi__xpr_general__x_0__simm12__:
  case Codasip::i_itype_alu__opc_addi__xpr_general__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_andi__x_0__x_0__simm12__:
  case Codasip::i_itype_alu__opc_andi__x_0__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_andi__x_0__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_andi__x_0_alias__x_0__simm12__:
  case Codasip::i_itype_alu__opc_andi__x_0_alias__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_andi__x_0_alias__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_andi__xpr_general__x_0__simm12__:
  case Codasip::i_itype_alu__opc_andi__xpr_general__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_andi__xpr_general__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_ori__x_0__x_0__simm12__:
  case Codasip::i_itype_alu__opc_ori__x_0__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_ori__x_0__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_ori__x_0_alias__x_0__simm12__:
  case Codasip::i_itype_alu__opc_ori__x_0_alias__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_ori__x_0_alias__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_ori__xpr_general__x_0__simm12__:
  case Codasip::i_itype_alu__opc_ori__xpr_general__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_ori__xpr_general__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_slti__x_0__x_0__simm12__:
  case Codasip::i_itype_alu__opc_slti__x_0__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_slti__x_0__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_slti__x_0_alias__x_0__simm12__:
  case Codasip::i_itype_alu__opc_slti__x_0_alias__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_slti__x_0_alias__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__:
  case Codasip::i_itype_alu__opc_slti__xpr_general__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_sltiu__x_0__x_0__simm12__:
  case Codasip::i_itype_alu__opc_sltiu__x_0__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_sltiu__x_0__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_sltiu__x_0_alias__x_0__simm12__:
  case Codasip::i_itype_alu__opc_sltiu__x_0_alias__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_sltiu__x_0_alias__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__:
  case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_xori__x_0__x_0__simm12__:
  case Codasip::i_itype_alu__opc_xori__x_0__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_xori__x_0__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_xori__x_0_alias__x_0__simm12__:
  case Codasip::i_itype_alu__opc_xori__x_0_alias__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_xori__x_0_alias__xpr_general__simm12__:
  case Codasip::i_itype_alu__opc_xori__xpr_general__x_0__simm12__:
  case Codasip::i_itype_alu__opc_xori__xpr_general__x_0_alias__simm12__:
  case Codasip::i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__:
  case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__:
  case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0_alias__:
  case Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__xpr_general__:
  case Codasip::i_itype_jlreg__opc_jalr__x_0_alias__simm12__x_0__:
  case Codasip::i_itype_jlreg__opc_jalr__x_0_alias__simm12__x_0_alias__:
  case Codasip::i_itype_jlreg__opc_jalr__x_0_alias__simm12__xpr_general__:
  case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0__:
  case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__x_0_alias__:
  case Codasip::i_itype_jlreg__opc_jalr__xpr_general__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lb__x_0__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lb__x_0__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lb__x_0_alias__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lb__x_0_alias__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lb__x_0_alias__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lbu__x_0__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lbu__x_0__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lbu__x_0__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lbu__x_0_alias__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lbu__x_0_alias__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lbu__x_0_alias__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lh__x_0__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lh__x_0__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lh__x_0_alias__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lh__x_0_alias__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lh__x_0_alias__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lhu__x_0__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lhu__x_0__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lhu__x_0__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lhu__x_0_alias__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lhu__x_0_alias__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lhu__x_0_alias__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lw__x_0__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lw__x_0__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lw__x_0_alias__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lw__x_0_alias__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lw__x_0_alias__simm12__xpr_general__:
  case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0__:
  case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0_alias__:
  case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__:
  case Codasip::i_li_alias__x_0__simm12__:
  case Codasip::i_li_alias__x_0_alias__simm12__:
  case Codasip::i_li_alias__xpr_general__simm12__:
    Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 11, 0, IDesc.getSize(), 31, 20, 1, 1));
    break;
  case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__:
  case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0_alias__:
  case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__:
  case Codasip::i_stype_store__opc_sb__x_0_alias__simm12__x_0__:
  case Codasip::i_stype_store__opc_sb__x_0_alias__simm12__x_0_alias__:
  case Codasip::i_stype_store__opc_sb__x_0_alias__simm12__xpr_general__:
  case Codasip::i_stype_store__opc_sb__xpr_general__simm12__x_0__:
  case Codasip::i_stype_store__opc_sb__xpr_general__simm12__x_0_alias__:
  case Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__:
  case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__:
  case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0_alias__:
  case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__:
  case Codasip::i_stype_store__opc_sh__x_0_alias__simm12__x_0__:
  case Codasip::i_stype_store__opc_sh__x_0_alias__simm12__x_0_alias__:
  case Codasip::i_stype_store__opc_sh__x_0_alias__simm12__xpr_general__:
  case Codasip::i_stype_store__opc_sh__xpr_general__simm12__x_0__:
  case Codasip::i_stype_store__opc_sh__xpr_general__simm12__x_0_alias__:
  case Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__:
  case Codasip::i_stype_store__opc_sw__x_0__simm12__x_0__:
  case Codasip::i_stype_store__opc_sw__x_0__simm12__x_0_alias__:
  case Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__:
  case Codasip::i_stype_store__opc_sw__x_0_alias__simm12__x_0__:
  case Codasip::i_stype_store__opc_sw__x_0_alias__simm12__x_0_alias__:
  case Codasip::i_stype_store__opc_sw__x_0_alias__simm12__xpr_general__:
  case Codasip::i_stype_store__opc_sw__xpr_general__simm12__x_0__:
  case Codasip::i_stype_store__opc_sw__xpr_general__simm12__x_0_alias__:
  case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__:
    Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 11, 5, IDesc.getSize(), 31, 25, 1, 1));
    Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 4, 0, IDesc.getSize(), 11, 7, 0, 1));
    break;
  default:
    llvm_unreachable("Unexpected MCInst in encode function");
    break;
  }
  return 0;
}

uint64_t CodasipMCCodeEmitter::encodeMI5valueIH1_13default_start8_6uimm203imm1_6uimm20(const MCInst &MI,
  unsigned OpIdx,
  SmallVectorImpl<MCFixup> &Fixups,
  const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpIdx);
  if (MO.isImm()) {
    int64_t MI5valueIH1_13default_start8_6uimm203imm1_6uimm20 = MO.getImm();
    bool encodingSectionHasMask = false;
    switch (MI.getOpcode()) {
    case Codasip::i_utype_ops__opc_auipc__x_0__uimm20__:
    case Codasip::i_utype_ops__opc_auipc__x_0_alias__uimm20__:
    case Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__:
    case Codasip::i_utype_ops__opc_lui__x_0__uimm20__:
    case Codasip::i_utype_ops__opc_lui__x_0_alias__uimm20__:
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__:
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__1_:
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__2_:
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__5_:
    case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__6_:
      checkTruncationOverflow(MI5valueIH1_13default_start8_6uimm203imm1_6uimm20, 20, 0, MO.isMasked() || encodingSectionHasMask, MI.getLoc(), Ctx.getSourceManager());
      break;
    default:
      break;
    }
    return MI5valueIH1_13default_start8_6uimm203imm1_6uimm20;
  }
  assert(MO.isExpr());
  // Function hook for custom fixup
  if (getCustomFixupEncoder().customEncodeMI5valueIH1_13default_start8_6uimm203imm1_6uimm20(MI, MO, Fixups, STI))
    return 0;
  const Codasip::Fixups Kind = Codasip::FK_Codasip_MI5valueIH1_13default_start8_6uimm203imm1_6uimm20;
  (void)Kind; // suppress warning
  const MCInstrDesc &IDesc = MCII.get(MI.getOpcode());
  (void)IDesc; // suppress warning
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 19, 0, IDesc.getSize(), 31, 12, 1, 0));
  return 0;
}

uint64_t CodasipMCCodeEmitter::encodeMI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12(const MCInst &MI,
  unsigned OpIdx,
  SmallVectorImpl<MCFixup> &Fixups,
  const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpIdx);
  if (MO.isImm()) {
    int64_t MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12 = MO.getImm();
    bool encodingSectionHasMask = false;
    // Encoding section for fixups solvable by assembler frontend
    MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12 =  (  (  ( (codasip::MaxInt)MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12 - (codasip::Integer<64, true>)((codasip::Integer<64, true>)(0)) )  )  >> (codasip::Integer<32, true>)(0x1) ) ;
    switch (MI.getOpcode()) {
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
      checkTruncationOverflow(MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12, 12, 1, MO.isMasked() || encodingSectionHasMask, MI.getLoc(), Ctx.getSourceManager());
      break;
    default:
      break;
    }
    return MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12;
  }
  assert(MO.isExpr());
  // Function hook for custom fixup
  if (getCustomFixupEncoder().customEncodeMI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12(MI, MO, Fixups, STI))
    return 0;
  const Codasip::Fixups Kind = Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12;
  (void)Kind; // suppress warning
  const MCInstrDesc &IDesc = MCII.get(MI.getOpcode());
  (void)IDesc; // suppress warning
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 11, 11, IDesc.getSize(), 31, 31, 1, 1));
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 9, 4, IDesc.getSize(), 30, 25, 0, 1));
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 3, 0, IDesc.getSize(), 11, 8, 0, 1));
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 10, 10, IDesc.getSize(), 7, 7, 0, 1));
  return 0;
}

uint64_t CodasipMCCodeEmitter::encodeMI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12(const MCInst &MI,
  unsigned OpIdx,
  SmallVectorImpl<MCFixup> &Fixups,
  const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpIdx);
  if (MO.isImm()) {
    int64_t MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12 = MO.getImm();
    bool encodingSectionHasMask = false;
    // Encoding section for fixups solvable by assembler frontend
    MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12 =  (  (  ( (codasip::MaxInt)MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12 - (codasip::Integer<64, true>)((codasip::Integer<64, true>)(0)) )  )  >> (codasip::Integer<32, true>)(0x1) ) ;
    switch (MI.getOpcode()) {
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
      checkTruncationOverflow(MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12, 12, 1, MO.isMasked() || encodingSectionHasMask, MI.getLoc(), Ctx.getSourceManager());
      break;
    default:
      break;
    }
    return MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12;
  }
  assert(MO.isExpr());
  // Function hook for custom fixup
  if (getCustomFixupEncoder().customEncodeMI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12(MI, MO, Fixups, STI))
    return 0;
  const Codasip::Fixups Kind = Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12;
  (void)Kind; // suppress warning
  const MCInstrDesc &IDesc = MCII.get(MI.getOpcode());
  (void)IDesc; // suppress warning
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 11, 11, IDesc.getSize(), 31, 31, 1, 1));
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 9, 4, IDesc.getSize(), 30, 25, 0, 1));
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 3, 0, IDesc.getSize(), 11, 8, 0, 1));
  Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 10, 10, IDesc.getSize(), 7, 7, 0, 1));
  return 0;
}

uint64_t CodasipMCCodeEmitter::encodeMI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20(const MCInst &MI,
  unsigned OpIdx,
  SmallVectorImpl<MCFixup> &Fixups,
  const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpIdx);
  if (MO.isImm()) {
    int64_t MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20 = MO.getImm();
    bool encodingSectionHasMask = false;
    // Encoding section for fixups solvable by assembler frontend
    MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20 =  (  (  ( (codasip::MaxInt)MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20 - (codasip::Integer<64, true>)((codasip::Integer<64, true>)(0)) )  )  >> (codasip::Integer<32, true>)(0x1) ) ;
    switch (MI.getOpcode()) {
    case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__:
    case Codasip::i_jal_abs_calias__opc_jal__xpr_general__relative_addr20__:
    case Codasip::i_call_alias__relative_addr20__:
    case Codasip::i_j_alias__relative_addr20__:
    case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__:
    case Codasip::i_jtype_jlink__opc_jal__x_0_alias__relative_addr20__:
    case Codasip::i_jtype_jlink__opc_jal__xpr_general__relative_addr20__:
      checkTruncationOverflow(MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20, 20, 1, MO.isMasked() || encodingSectionHasMask, MI.getLoc(), Ctx.getSourceManager());
      break;
    default:
      break;
    }
    return MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20;
  }
  assert(MO.isExpr());
  // Function hook for custom fixup
  if (getCustomFixupEncoder().customEncodeMI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20(MI, MO, Fixups, STI))
    return 0;
  const Codasip::Fixups Kind = Codasip::FK_Codasip_MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20;
  (void)Kind; // suppress warning
  const MCInstrDesc &IDesc = MCII.get(MI.getOpcode());
  (void)IDesc; // suppress warning
  switch (MI.getOpcode()) {
  case Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__:
  case Codasip::i_jal_abs_calias__opc_jal__xpr_general__relative_addr20__:
    break;
  case Codasip::i_call_alias__relative_addr20__:
  case Codasip::i_j_alias__relative_addr20__:
  case Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__:
  case Codasip::i_jtype_jlink__opc_jal__x_0_alias__relative_addr20__:
  case Codasip::i_jtype_jlink__opc_jal__xpr_general__relative_addr20__:
    Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 19, 19, IDesc.getSize(), 31, 31, 1, 1));
    Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 9, 0, IDesc.getSize(), 30, 21, 0, 1));
    Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 10, 10, IDesc.getSize(), 20, 20, 0, 1));
    Fixups.push_back(MCFixup::createCodasip(0, MO.getExpr(), MCFixupKind(Kind), MI.getLoc(), 18, 11, IDesc.getSize(), 19, 12, 0, 1));
    break;
  default:
    llvm_unreachable("Unexpected MCInst in encode function");
    break;
  }
  return 0;
}


#ifndef _MSVC
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wcast-qual\"")
#endif
#include "CodasipGenMCCodeEmitter.inc"
#ifndef _MSVC
_Pragma("GCC diagnostic pop")
#endif
