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


#ifndef CODASIPMCTARGETDESC_H
#define CODASIPMCTARGETDESC_H

#include <memory>
#include "llvm/Config/config.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/DataTypes.h"

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCInstPrinter;
class MCObjectTargetWriter;
class MCObjectWriter;
class MCRegisterInfo;
class MCStreamer;
class MCSubtargetInfo;
class MCTargetStreamer;
class StringRef;
class Target;
class Triple;
class raw_ostream;
class raw_pwrite_stream;
class formatted_raw_ostream;

extern Target TheCodasipTarget;

MCCodeEmitter *createCodasipMCCodeEmitter(const MCInstrInfo &MCII,
                                          const MCRegisterInfo &MRI,
                                          MCContext &Ctx);

MCAsmBackend *createCodasipAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                      const MCRegisterInfo &MRI,
                                      const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter> createCodasipELFObjectWriter(uint8_t OSABI);

MCTargetStreamer *createCodasipObjectTargetStreamer(MCStreamer &S,
                                                    const MCSubtargetInfo &STI);

MCTargetStreamer *createCodasipAsmTargetStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm);

} // End llvm namespace

// Defines symbolic names for Codasip registers.
// This defines a mapping from register name to register number.
#define GET_REGINFO_ENUM
#include "CodasipGenRegisterInfo.inc"

// Defines symbolic names for the Codasip instructions.
#define GET_INSTRINFO_ENUM
#include "CodasipGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "CodasipGenSubtargetInfo.inc"

#endif
