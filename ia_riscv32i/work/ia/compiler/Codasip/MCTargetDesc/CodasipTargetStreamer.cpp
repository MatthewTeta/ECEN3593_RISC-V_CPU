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


#include "CodasipTargetStreamer.h"
#include "codasip/ObjectFile/CodasipAddressSpace.h"
#include "codasip/ObjectFile/CodasipSectionDefines.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

CodasipTargetStreamer::CodasipTargetStreamer(MCStreamer &S)
: MCTargetStreamer(S) {}

// This part is for ascii assembly output
CodasipTargetAsmStreamer::CodasipTargetAsmStreamer(MCStreamer &S,
                                                   formatted_raw_ostream &OS)
: CodasipTargetStreamer(S), OS(OS) {}

void CodasipTargetAsmStreamer::emitDirectiveAbsOrg(const uint64_t Address,
                                                   SMLoc Loc) {
  MCStreamer &Streamer = getStreamer();
  MCSection *CurrentSection = Streamer.getCurrentSectionOnly();

  // this may fail in case of asm->asm compilation
  // Print error if the requested address is not aligned
  if (Address % CurrentSection->getAlignment()) {
    Streamer.getContext().reportError(
      Loc, "Absolute address is not aligned on " +
        std::to_string(CurrentSection->getAlignment()) + " bytes.");
    return;
  }

  OS << "\t.abs_org\t" << Address << "\n";
}

void CodasipTargetAsmStreamer::emitDirectiveAddressSpace(unsigned Index,
                                                         SMLoc Loc) {
  MCStreamer &Streamer = getStreamer();
  MCContext &Ctx = Streamer.getContext();

  // this may fail in case of asm->asm compilation
  if (Index >= Ctx.getAsmInfo()->getAddressSpaces().size()) {
    Ctx.reportError(Loc, "Address space index is too big.");
    return;
  }

  OS << "\t.address_space\t" << Index << "\n";
}

void CodasipTargetAsmStreamer::emitDirectiveProfiler(const uint64_t Flag,
                                                     StringRef Block,
                                                     SMLoc Loc) {
  OS << "\t.profiler\t";
  switch (Flag) {
  case CODASIP_PROFILE_FLAG_START:
    OS << "\"s\"";
    break;
  case CODASIP_PROFILE_FLAG_END:
    OS << "\"x\"";
    break;
  default:
    assert(false && "Unsupported flag of .profiler directive.");
  }
  OS << ", \"" << Block << "\"\n";
}

void CodasipTargetAsmStreamer::emitDirectiveOptionPush() {
  OS << "\t.option\tpush\n";
}

void CodasipTargetAsmStreamer::emitDirectiveOptionPop() {
  OS << "\t.option\tpop\n";
}

void CodasipTargetAsmStreamer::emitDirectiveOptionRVC() {
  OS << "\t.option\trvc\n";
}

void CodasipTargetAsmStreamer::emitDirectiveOptionNoRVC() {
  OS << "\t.option\tnorvc\n";
}

void CodasipTargetAsmStreamer::emitDirectiveOptionRelax() {
  OS << "\t.option\trelax\n";
}

void CodasipTargetAsmStreamer::emitDirectiveOptionNoRelax() {
  OS << "\t.option\tnorelax\n";
}

namespace llvm {
  
MCTargetStreamer *
createCodasipAsmTargetStreamer(MCStreamer &S, formatted_raw_ostream &OS,
                               MCInstPrinter *InstPrint, bool isVerboseAsm) {
  return new CodasipTargetAsmStreamer(S, OS);
}

} // end namespace llvm
