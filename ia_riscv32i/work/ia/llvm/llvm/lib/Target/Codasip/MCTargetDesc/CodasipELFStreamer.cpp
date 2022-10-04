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


#include "CodasipMCTargetDesc.h"
#include "CodasipTargetStreamer.h"
#include "codasip/ObjectFile/CodasipAddressSpace.h"
#include "codasip/ObjectFile/CodasipSectionDefines.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCSubtargetInfo.h"

using namespace llvm;

namespace {

class CodasipTargetELFStreamer : public CodasipTargetStreamer {
  
public:
  CodasipTargetELFStreamer(MCStreamer &S, const MCSubtargetInfo &STI);
  
  MCELFStreamer &getStreamer();
  
  void finish() override;
  
  void emitDirectiveAbsOrg(const uint64_t Address, SMLoc Loc) override;
  void emitDirectiveAddressSpace(unsigned Index, SMLoc Loc) override;
  void emitDirectiveProfiler(const uint64_t Flag, StringRef Block, SMLoc Loc) override;

  virtual void emitDirectiveOptionPush();
  virtual void emitDirectiveOptionPop();
  virtual void emitDirectiveOptionRVC();
  virtual void emitDirectiveOptionNoRVC();
  virtual void emitDirectiveOptionRelax();
  virtual void emitDirectiveOptionNoRelax();
};

// This part is for ELF object output.
CodasipTargetELFStreamer::CodasipTargetELFStreamer(MCStreamer & S, const MCSubtargetInfo &STI) : CodasipTargetStreamer(S)
{
  MCAssembler &MCA = getStreamer().getAssembler();
  unsigned EFlags = MCA.getELFHeaderEFlags();
  MCA.setELFHeaderEFlags(EFlags);
}

MCELFStreamer &CodasipTargetELFStreamer::getStreamer() {
  return static_cast<MCELFStreamer &>(Streamer);
}

void CodasipTargetELFStreamer::finish() {
  MCELFStreamer &Streamer = getStreamer();
  MCContext &Ctx = Streamer.getContext();
  MCSection *AsTableSection = Ctx.getELFSection(".codasip_as", ELF::SHT_CODASIP_AS, 0);
  Streamer.SwitchSection(AsTableSection);

  // print address space count
  uint16_t ASCount = Ctx.getAsmInfo()->getAddressSpaces().size();
  Streamer.EmitIntValue(ASCount, sizeof(ASCount));

  for (const CodasipAddressSpace &AS : Ctx.getAsmInfo()->getAddressSpaces()) {
    Streamer.EmitBytes(AS.getId());
    Streamer.EmitIntValue(0, 1); // string ending 0
    Streamer.EmitIntValue(AS.getType(), sizeof(AS.getType()));
    Streamer.EmitIntValue(AS.getWordBitWidth(), sizeof(AS.getWordBitWidth()));
    Streamer.EmitIntValue(AS.getByteBitWidth(), sizeof(AS.getByteBitWidth()));
    Streamer.EmitIntValue(!AS.isLittleEndian(), sizeof(AS.isLittleEndian()));
  }
}

void CodasipTargetELFStreamer::emitDirectiveAbsOrg(const uint64_t Address, SMLoc Loc) {
  MCStreamer &Streamer = getStreamer();
  MCSection *CurrentSection = Streamer.getCurrentSectionOnly();
  MCSectionELF *CurrentELFSection = dyn_cast<MCSectionELF>(CurrentSection);

  // Current section must not have set absolute address
  if (CurrentELFSection->IsAbsoluteAddressSet()) {
    Streamer.getContext().reportError(Loc,
      "Absolute address of a current section is already set.");
    return;
  }

  // Print error if the requested address is not aligned
  if (Address % CurrentELFSection->getAlignment()) {
    Streamer.getContext().reportError(Loc, 
      "Absolute address is not aligned on " + std::to_string(CurrentELFSection->getAlignment()) + " bytes.");
    return;
  }

  CurrentELFSection->SetAbsoluteAddress(Address);
}

void CodasipTargetELFStreamer::emitDirectiveAddressSpace(unsigned Index, SMLoc Loc) {
  MCStreamer &Streamer = getStreamer();

  if (Index >= Streamer.getContext().getAsmInfo()->getAddressSpaces().size()) {
    Streamer.getContext().reportError(Loc, "Address space index is too big.");
    return;
  }

  // First set current data address space index
  MCContext &Context = Streamer.getContext();
  Context.setCurrentDataAddressSpaceIndex(Index);

  // Create new section from current section and given data address space index
  MCSection *CurrentSection = Streamer.getCurrentSectionOnly();
  MCSectionELF *S = dyn_cast<MCSectionELF>(CurrentSection);
  assert(S->getAssociatedSymbol() == nullptr && "There is some unexpected symbol.");
  MCSectionELF *NewS = Context.getELFSection(S->GetSectionBaseName(), S->getType(), S->getFlags(),
    S->getEntrySize(), S->getGroup(), S->getUniqueID(), nullptr/*S->getAssociatedSymbol() TODO need this?*/);
  Streamer.SwitchSection(NewS);
}

void CodasipTargetELFStreamer::emitDirectiveProfiler(const uint64_t Flag,
                                                     StringRef Block,
                                                     SMLoc Loc) {
  assert((Flag == CODASIP_PROFILE_FLAG_START || Flag == CODASIP_PROFILE_FLAG_END)
    && "Unsupported flag of .profiler directive.");
  MCStreamer &Streamer = getStreamer();
  MCContext &Context = Streamer.getContext();

  // Create temporary symbol in current section
  MCSymbol *S = Context.createTempSymbol("codasip_profiler", true, false);
  Streamer.EmitLabel(S);
  // Switch to .profile_info section
  auto CurrentSection = Streamer.getCurrentSection();
  MCSectionELF *Section = Context.getELFSection(CODASIP_PROFILE_INFO_NAME, ELF::SHT_PROGBITS, 0);
  Streamer.SwitchSection(Section);
  // Emit symbol value
  Streamer.EmitSymbolValue(S, CODASIP_PROFILE_INFO_ADDRESS_BYTES);
  // Emit flags value
  Streamer.EmitIntValue(Flag, CODASIP_PROFILE_INFO_FLAG_BYTES);
  // Emit zero-terminated string containing block identifier
  Streamer.EmitBytes(Block);
  Streamer.EmitBytes(StringRef("\0", 1));
  // Switch back to current section
  Streamer.SwitchSection(CurrentSection.first);
}

void CodasipTargetELFStreamer::emitDirectiveOptionPush() {}
void CodasipTargetELFStreamer::emitDirectiveOptionPop() {}
void CodasipTargetELFStreamer::emitDirectiveOptionRVC() {}
void CodasipTargetELFStreamer::emitDirectiveOptionNoRVC() {}
void CodasipTargetELFStreamer::emitDirectiveOptionRelax() {}
void CodasipTargetELFStreamer::emitDirectiveOptionNoRelax() {}

} // end anonymous namespace

namespace llvm {

MCTargetStreamer *createCodasipObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
  const Triple &TT = STI.getTargetTriple();
  if (TT.isOSBinFormatELF())
    return new CodasipTargetELFStreamer(S, STI);
  return nullptr;
}

} // end namespace llvm
