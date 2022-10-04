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


#ifndef LLVM_LIB_TARGET_CODASIP_MCTARGETDESC_CODASIPGENASMBACKEND_H_
#define LLVM_LIB_TARGET_CODASIP_MCTARGETDESC_CODASIPGENASMBACKEND_H_

#include "MCTargetDesc/CodasipMCTargetDesc.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include "CodasipFixupKinds.h"
#include "Codasip.h"
#include "common/codasip_integer.h"

namespace llvm {
class CodasipGenAsmBackend : public MCAsmBackend {
protected:
  const MCSubtargetInfo &STI;

private:
  uint8_t OSABI;

public:
  CodasipGenAsmBackend(const MCSubtargetInfo &STI, uint8_t OSABI)
      : MCAsmBackend(0 ? support::big : support::little), STI(STI), OSABI(OSABI) {}
  ~CodasipGenAsmBackend() override {}

  virtual void setForceRelocs() {};
  bool shouldForceRelocation(const MCAssembler &Asm,
                             const MCFixup &Fixup,
                             const MCValue &Target) override {
    const unsigned Kind = Fixup.getKind();
    // TODO now it is done as in old assembler, all relative fixups goes to the linker
    //      this removed all the truncation warnings on titanium model, but not fixed him
    bool RelativeFixup = false;
    if (Kind == Codasip::fixup_riscv_pcrel_lo12_i
      || Kind == Codasip::fixup_riscv_pcrel_lo12_s
      || Kind == Codasip::fixup_riscv_pcrel_hi20
      || Kind == Codasip::fixup_riscv_got_hi20)
      RelativeFixup = true;
    if (Kind == Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12
      || Kind == Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12
      || Kind == Codasip::FK_Codasip_MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20)
      RelativeFixup = true;

    return RelativeFixup;
  }
  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved,
                  const MCSubtargetInfo *STI, const MCSectionELF &Section) const override;

  std::unique_ptr<MCObjectTargetWriter>
  createObjectTargetWriter() const override;

  bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                            const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override {
    return false;
  }

  unsigned getNumFixupKinds() const override { return Codasip::NumTargetFixupKinds; }

  bool mayNeedRelaxation(const MCInst &Inst,
                         const MCSubtargetInfo &STI) const override
  { return false; }

  void relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI,
                        MCInst &Res) const override {

    llvm_unreachable("CodasipGenAsmBackend::relaxInstruction() unimplemented");
  }

  bool writeNopData(raw_ostream &OS, uint64_t Count) const override;

  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override;
};

} // end namespace llvm

#endif   //LLVM_LIB_TARGET_CODASIP_MCTARGETDESC_CODASIPGENASMBACKEND_H_
