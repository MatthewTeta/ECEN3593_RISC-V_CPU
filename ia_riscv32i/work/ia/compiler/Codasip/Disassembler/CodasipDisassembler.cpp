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


#include "MCTargetDesc/CodasipMCTargetDesc.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/CodeGen/TargetOpcodes.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCFixedLenDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/TargetRegistry.h"
#include "Codasip.h"
#include "common/codasip_integer.h"
#include "utility/codasip_log.h"
#include "Disassembler/CodasipDebundleFunctionGen.h"
#include "InstPrinter/CodasipInstPrinter.h"

using namespace llvm;

#define DEBUG_TYPE "Codasip-disassembler"

typedef MCDisassembler::DecodeStatus DecodeStatus;

namespace {
class CodasipDisassembler : public MCDisassembler {

public:
  CodasipDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
      : MCDisassembler(STI, Ctx) {}

  DecodeStatus getInstruction(MCInst &Instr, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address,
                              raw_ostream &VStream,
                              raw_ostream &CStream) const override;
  DecodeStatus getInstructionBuiltin(MCInst &Instr, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address) const override;
};
} // end anonymous namespace

static MCDisassembler *createCodasipDisassembler(const Target &T,
                                               const MCSubtargetInfo &STI,
                                               MCContext &Ctx) {
  return new CodasipDisassembler(STI, Ctx);
}

extern "C" void LLVMInitializeCodasipDisassembler() {
  // Register the disassembler for each target.
  TargetRegistry::RegisterMCDisassembler(TheCodasipTarget,
                                         createCodasipDisassembler);
}

void deparcel(SmallVector<uint8_t, 8> &Dst, ArrayRef<uint8_t> Src, const unsigned int ParcelBytes) {
  if (Src.size() % ParcelBytes) {
    codasip::LOG_WARNING() << "Cannot deparcel " << Src.size()
      << " bytes by parcel size of " << ParcelBytes << " bytes.";
    Dst.append(Src.begin(), Src.end());
    return;
  }
  const unsigned int ParcelCount = Src.size() / ParcelBytes;
  for (unsigned int i = 0; i < ParcelCount; i++) {
    const unsigned int SrcParcelIndex = ParcelCount - i - 1;
    const unsigned int SrcByteIndex = SrcParcelIndex * ParcelBytes;
    for (unsigned int j = 0; j < ParcelBytes; j++)
      Dst.emplace_back(Src[SrcByteIndex + j]);
  }
}

void bytesToInt(codasip::MaxUint &Dst, ArrayRef<uint8_t> Src) {
  for (size_t i = 0; i < Src.size(); i++) {
    Dst <<= 8;
    Dst |= Src[i];
  }
}

#ifndef _MSVC
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-function\"")
#endif
static DecodeStatus Decodexpr_generalRegisterClass(MCInst &Inst,
                                           uint64_t RegNo,
                                           uint64_t,
                                           const void *) {
  unsigned int Reg = 0;
  if (RegNo == 1)
    Reg = Codasip::rf_xpr_1;
  else if (RegNo == 2)
    Reg = Codasip::rf_xpr_2;
  else if (RegNo == 3)
    Reg = Codasip::rf_xpr_3;
  else if (RegNo == 4)
    Reg = Codasip::rf_xpr_4;
  else if (RegNo == 5)
    Reg = Codasip::rf_xpr_5;
  else if (RegNo == 6)
    Reg = Codasip::rf_xpr_6;
  else if (RegNo == 7)
    Reg = Codasip::rf_xpr_7;
  else if (RegNo == 8)
    Reg = Codasip::rf_xpr_8;
  else if (RegNo == 9)
    Reg = Codasip::rf_xpr_9;
  else if (RegNo == 10)
    Reg = Codasip::rf_xpr_10;
  else if (RegNo == 11)
    Reg = Codasip::rf_xpr_11;
  else if (RegNo == 12)
    Reg = Codasip::rf_xpr_12;
  else if (RegNo == 13)
    Reg = Codasip::rf_xpr_13;
  else if (RegNo == 14)
    Reg = Codasip::rf_xpr_14;
  else if (RegNo == 15)
    Reg = Codasip::rf_xpr_15;
  else if (RegNo == 16)
    Reg = Codasip::rf_xpr_16;
  else if (RegNo == 17)
    Reg = Codasip::rf_xpr_17;
  else if (RegNo == 18)
    Reg = Codasip::rf_xpr_18;
  else if (RegNo == 19)
    Reg = Codasip::rf_xpr_19;
  else if (RegNo == 20)
    Reg = Codasip::rf_xpr_20;
  else if (RegNo == 21)
    Reg = Codasip::rf_xpr_21;
  else if (RegNo == 22)
    Reg = Codasip::rf_xpr_22;
  else if (RegNo == 23)
    Reg = Codasip::rf_xpr_23;
  else if (RegNo == 24)
    Reg = Codasip::rf_xpr_24;
  else if (RegNo == 25)
    Reg = Codasip::rf_xpr_25;
  else if (RegNo == 26)
    Reg = Codasip::rf_xpr_26;
  else if (RegNo == 27)
    Reg = Codasip::rf_xpr_27;
  else if (RegNo == 28)
    Reg = Codasip::rf_xpr_28;
  else if (RegNo == 29)
    Reg = Codasip::rf_xpr_29;
  else if (RegNo == 30)
    Reg = Codasip::rf_xpr_30;
  else if (RegNo == 31)
    Reg = Codasip::rf_xpr_31;
  else
    return MCDisassembler::Fail;
  Inst.addOperand(MCOperand::createReg(Reg));
  return MCDisassembler::Success;
}

static DecodeStatus decodeMI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12(
  MCInst &Inst, uint64_t Imm, int64_t Address, const void *Decoder) {
  const CodasipDisassembler *Dis = static_cast<const CodasipDisassembler *>(Decoder);
  (void)Dis; // suppress warning

  int64_t MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12 = Imm;
  MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12 =  (  (  ( (codasip::Integer<13, true>)((const codasip::Integer<12, true>)MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12) << (codasip::Integer<32, true>)(0x1) )  )  + (codasip::Integer<64, true>)((codasip::Integer<64, true>)(Address)) ) ;

  if (!Dis->tryAddingSymbolicOperand(Inst, MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12, Address, true, 0, 4))
    Inst.addOperand(MCOperand::createImm(MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12));
  return MCDisassembler::Success;
}
static DecodeStatus decodeMI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20(
  MCInst &Inst, uint64_t Imm, int64_t Address, const void *Decoder) {
  const CodasipDisassembler *Dis = static_cast<const CodasipDisassembler *>(Decoder);
  (void)Dis; // suppress warning

  int64_t MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20 = Imm;
  MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20 =  (  (  ( (codasip::Integer<21, true>)((const codasip::Integer<20, true>)MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20) << (codasip::Integer<32, true>)(0x1) )  )  + (codasip::Integer<64, true>)((codasip::Integer<64, true>)(Address)) ) ;

  if (!Dis->tryAddingSymbolicOperand(Inst, MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20, Address, true, 0, 4))
    Inst.addOperand(MCOperand::createImm(MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20));
  return MCDisassembler::Success;
}

#ifndef _MSVC
_Pragma("GCC diagnostic pop")
#endif
#include "CodasipGenDisassemblerTables.inc"

DecodeStatus CodasipDisassembler::getInstruction(MCInst &MI, uint64_t &Size,
                                               ArrayRef<uint8_t> Bytes,
                                               uint64_t Address,
                                               raw_ostream &OS,
                                               raw_ostream &CS) const {
  CommentStream = &CS;
  DecodeStatus Result = Fail;
  // Start with zero size
  Size = 0;
  ArrayRef<uint8_t> ReadBytes = Bytes.take_front(4);
  Size += ReadBytes.size();
  SmallVector<uint8_t, 8> RawBytesBuffer;
  ArrayRef<uint8_t> RawBytes = ReadBytes;
  if (RawBytes.size() < 4) {
    RawBytesBuffer.insert(RawBytesBuffer.begin(), ReadBytes.begin(), ReadBytes.end());
    RawBytesBuffer.resize(4);
    RawBytes = ArrayRef<uint8_t>(RawBytesBuffer.data(), 4);
  }
  ArrayRef<uint8_t> SelectedBytes = RawBytes.take_front(4);
  SmallVector<uint8_t, 8> EndianFreeBytesBuffer(SelectedBytes.rbegin(), SelectedBytes.rend());
  ArrayRef<uint8_t> EndianFreeBytes(EndianFreeBytesBuffer.data(), EndianFreeBytesBuffer.size());
  ArrayRef<uint8_t> DeparceledBytes = EndianFreeBytes;
  codasip::MaxUint Insn;
  bytesToInt(Insn, DeparceledBytes);
  CodasipDebundleFunctionGen DebundleFunction;
  Result = DebundleFunction.Run(Insn, Size) ? Success : Fail;
  // Decoding failed
  if (Result == Fail) {
    Size = 0;
    return Result;
  }
  Result = decodeInstruction(DecoderTable32, MI, (uint64_t)Insn, Address, this, STI);
  // Decoding failed
  if (Result == Fail) {
    Size = 0;
    return Result;
  }

  return Result;
}

DecodeStatus CodasipDisassembler::getInstructionBuiltin(MCInst &MI, uint64_t &Size,
                                               ArrayRef<uint8_t> Bytes,
                                               uint64_t Address) const {
  DecodeStatus Result = Fail;
  // Start with zero size
  Size = 0;
  ArrayRef<uint8_t> ReadBytes = Bytes.take_back(4);
  Size += ReadBytes.size();
  SmallVector<uint8_t, 8> RawBytesBuffer;
  ArrayRef<uint8_t> RawBytes = ReadBytes;
  if (RawBytes.size() < 4) {
    RawBytesBuffer.insert(RawBytesBuffer.begin(), ReadBytes.begin(), ReadBytes.end());
    RawBytesBuffer.resize(4);
    RawBytes = ArrayRef<uint8_t>(RawBytesBuffer.data(), 4);
  }
  ArrayRef<uint8_t> SelectedBytes = RawBytes.take_front(4);
  codasip::MaxUint Insn;
  bytesToInt(Insn, SelectedBytes);
  Result = decodeInstruction(DecoderTable32, MI, (uint64_t)Insn, Address, this, STI);
  // Decoding failed
  if (Result == Fail) {
    Size = 0;
    return Result;
  }

  return Result;
}
