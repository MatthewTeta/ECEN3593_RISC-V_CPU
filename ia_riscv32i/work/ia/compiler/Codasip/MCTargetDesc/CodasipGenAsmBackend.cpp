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


#include "CodasipGenAsmBackend.h"

//#define DEBUG_CLASS

// how many different sizes of nops are there?
#define NOP_SIZES 1

using namespace llvm;

const MCFixupKindInfo &CodasipGenAsmBackend::getFixupKindInfo(MCFixupKind Kind) const {
  const static MCFixupKindInfo Infos[Codasip::NumTargetFixupKinds] = {
    // Taken from RISC-V target
    // name                      offset bits  flags
    { "fixup_riscv_hi20",         12,     20,  0 },
    { "fixup_riscv_lo12_i",       20,     12,  0 },
    { "fixup_riscv_lo12_s",        0,     32,  0 },
    { "fixup_riscv_pcrel_hi20",   12,     20,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_pcrel_lo12_i", 20,     12,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_pcrel_lo12_s",  0,     32,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_got_hi20",     12,     20,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_tprel_hi20",   12,     20,  0 },
    { "fixup_riscv_tprel_lo12_i", 20,     12,  0 },
    { "fixup_riscv_tprel_lo12_s",  0,     32,  0 },
    { "fixup_riscv_tprel_add",     0,      0,  0 },
    { "fixup_riscv_tls_got_hi20", 12,     20,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_tls_gd_hi20",  12,     20,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_jal",          12,     20,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_branch",        0,     32,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_rvc_jump",      2,     11,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_rvc_branch",    0,     16,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_call",          0,     64,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_call_plt",      0,     64,  MCFixupKindInfo::FKF_IsPCRel },
    { "fixup_riscv_relax",         0,      0,  0 },
    { "fixup_riscv_align",         0,      0,  0 },
    {"FK_Codasip_MI5valueIH1_13default_start7_5uimm53imm1_5uimm5", 0, 5, 0},
    {"FK_Codasip_MI5valueIH1_13default_start8_6simm124simm1_6simm12", 0, 12, 0},
    {"FK_Codasip_MI5valueIH1_13default_start8_6uimm203imm1_6uimm20", 0, 20, 0},
    {"FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12", 0, 12, MCFixupKindInfo::FKF_IsPCRel},
    {"FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", 0, 12, MCFixupKindInfo::FKF_IsPCRel},
    {"FK_Codasip_MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20", 0, 20, MCFixupKindInfo::FKF_IsPCRel}
  };

  if (Kind < FirstTargetFixupKind)
    return MCAsmBackend::getFixupKindInfo(Kind);

  assert(unsigned(Kind - FirstTargetFixupKind) < getNumFixupKinds() && "Invalid kind!");
  return Infos[Kind - FirstTargetFixupKind];
}

bool CodasipGenAsmBackend::writeNopData(raw_ostream &OS, uint64_t Count) const {
  // skip, if called with Count=0
  if (Count==0) {
    return true;
  }
  // size/instr
  struct NopFillRecord {
    unsigned Size;
    const char* Coding;
  };
  // table of nops from biggest to smallest
  static const std::array<NopFillRecord,NOP_SIZES> Nops {{
    {4,"\x13\x0\x0\x0"}, 
  }};
  // make the fill
  auto CurrentNop = Nops.cbegin();
  while (CurrentNop != Nops.cend()) {
    // can be inserted?
    if (Count < CurrentNop->Size) {
      ++CurrentNop;
      continue;
    }
    // print
    OS.write(CurrentNop->Coding, CurrentNop->Size);
    // detract
    assert(Count >= CurrentNop->Size);
    Count -= CurrentNop->Size;
    // done?
    if (Count==0) {
      return true;
    }
  }
  // failed (Count is remainder now, always non-zero)
  assert(Count);
  return false;
}

uint64_t adjustFixupValue(const MCFixup &Fixup, uint64_t Value, MCContext &Ctx) {
  const unsigned Kind = Fixup.getKind();
  switch (Kind) {
  // Taken from RISC-V target
  case Codasip::fixup_riscv_got_hi20:
  case Codasip::fixup_riscv_tls_got_hi20:
  case Codasip::fixup_riscv_tls_gd_hi20:
    llvm_unreachable("Relocation should be unconditionally forced\n");
  case FK_Data_1:
  case FK_Data_2:
  case FK_Data_4:
  case FK_Data_8:
    return Value;
  case Codasip::fixup_riscv_lo12_i:
  case Codasip::fixup_riscv_pcrel_lo12_i:
  case Codasip::fixup_riscv_tprel_lo12_i:
    return Value & 0xfff;
  case Codasip::fixup_riscv_lo12_s:
  case Codasip::fixup_riscv_pcrel_lo12_s:
  case Codasip::fixup_riscv_tprel_lo12_s:
    return (((Value >> 5) & 0x7f) << 25) | ((Value & 0x1f) << 7);
  case Codasip::fixup_riscv_hi20:
  case Codasip::fixup_riscv_pcrel_hi20:
  case Codasip::fixup_riscv_tprel_hi20:
    // Add 1 if bit 11 is 1, to compensate for low 12 bits being negative.
    return ((Value + 0x800) >> 12) & 0xfffff;
  case Codasip::fixup_riscv_jal: {
    if (!isInt<21>(Value))
      Ctx.reportError(Fixup.getLoc(), "fixup value out of range");
    if (Value & 0x1)
      Ctx.reportError(Fixup.getLoc(), "fixup value must be 2-byte aligned");
    // Need to produce imm[19|10:1|11|19:12] from the 21-bit Value.
    unsigned Sbit = (Value >> 20) & 0x1;
    unsigned Hi8 = (Value >> 12) & 0xff;
    unsigned Mid1 = (Value >> 11) & 0x1;
    unsigned Lo10 = (Value >> 1) & 0x3ff;
    // Inst{31} = Sbit;
    // Inst{30-21} = Lo10;
    // Inst{20} = Mid1;
    // Inst{19-12} = Hi8;
    Value = (Sbit << 19) | (Lo10 << 9) | (Mid1 << 8) | Hi8;
    return Value;
  }
  case Codasip::fixup_riscv_branch: {
    if (!isInt<13>(Value))
      Ctx.reportError(Fixup.getLoc(), "fixup value out of range");
    if (Value & 0x1)
      Ctx.reportError(Fixup.getLoc(), "fixup value must be 2-byte aligned");
    // Need to extract imm[12], imm[10:5], imm[4:1], imm[11] from the 13-bit
    // Value.
    unsigned Sbit = (Value >> 12) & 0x1;
    unsigned Hi1 = (Value >> 11) & 0x1;
    unsigned Mid6 = (Value >> 5) & 0x3f;
    unsigned Lo4 = (Value >> 1) & 0xf;
    // Inst{31} = Sbit;
    // Inst{30-25} = Mid6;
    // Inst{11-8} = Lo4;
    // Inst{7} = Hi1;
    Value = (Sbit << 31) | (Mid6 << 25) | (Lo4 << 8) | (Hi1 << 7);
    return Value;
  }
  case Codasip::fixup_riscv_call:
  case Codasip::fixup_riscv_call_plt: {
    // Jalr will add UpperImm with the sign-extended 12-bit LowerImm,
    // we need to add 0x800ULL before extract upper bits to reflect the
    // effect of the sign extension.
    uint64_t UpperImm = (Value + 0x800ULL) & 0xfffff000ULL;
    uint64_t LowerImm = Value & 0xfffULL;
    return UpperImm | ((LowerImm << 20) << 32);
  }
  case Codasip::fixup_riscv_rvc_jump: {
    // Need to produce offset[11|4|9:8|10|6|7|3:1|5] from the 11-bit Value.
    unsigned Bit11  = (Value >> 11) & 0x1;
    unsigned Bit4   = (Value >> 4) & 0x1;
    unsigned Bit9_8 = (Value >> 8) & 0x3;
    unsigned Bit10  = (Value >> 10) & 0x1;
    unsigned Bit6   = (Value >> 6) & 0x1;
    unsigned Bit7   = (Value >> 7) & 0x1;
    unsigned Bit3_1 = (Value >> 1) & 0x7;
    unsigned Bit5   = (Value >> 5) & 0x1;
    Value = (Bit11 << 10) | (Bit4 << 9) | (Bit9_8 << 7) | (Bit10 << 6) |
            (Bit6 << 5) | (Bit7 << 4) | (Bit3_1 << 1) | Bit5;
    return Value;
  }
  case Codasip::fixup_riscv_rvc_branch: {
    // Need to produce offset[8|4:3], [reg 3 bit], offset[7:6|2:1|5]
    unsigned Bit8   = (Value >> 8) & 0x1;
    unsigned Bit7_6 = (Value >> 6) & 0x3;
    unsigned Bit5   = (Value >> 5) & 0x1;
    unsigned Bit4_3 = (Value >> 3) & 0x3;
    unsigned Bit2_1 = (Value >> 1) & 0x3;
    Value = (Bit8 << 12) | (Bit4_3 << 10) | (Bit7_6 << 5) | (Bit2_1 << 3) |
            (Bit5 << 2);
    return Value;
  }
  default:
    assert(Kind >= FirstTargetFixupKind && "unexpected general fixup kind!");
    assert(Kind < Codasip::FK_Codasip_Invalid && "invalid fixup kind!");
    // TODO remove ByteCount from the MCFixup
    // Number of bits of the fixup part
    unsigned NumBitsPart = Fixup.getMsbValue() - Fixup.getLsbValue() + 1;

    // Adjust fixup value
    uint64_t CurVal = Value;
#ifdef DEBUG_CLASS
    outs() << "SHR=" << Fixup.getLsbValue() << "\n";
#endif
    CurVal >>= Fixup.getLsbValue();
    uint64_t Mask = maskTrailingOnes<uint64_t>(NumBitsPart);
#ifdef DEBUG_CLASS
    outs() << "MASK=" << Mask << "\n";
#endif
    CurVal &= Mask;
#ifdef DEBUG_CLASS
    outs() << "Masked CurVal=" << CurVal << "\n";
    outs() << "SLR=" << Fixup.getLsbOut() << "\n";
#endif
    CurVal <<= Fixup.getLsbOut();
#ifdef DEBUG_CLASS
    outs() << "Apply CurVal=" << CurVal << "\n";
#endif
    return CurVal;
  }
}

void CodasipGenAsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                                 const MCValue &Target,
                                 MutableArrayRef<char> Data, uint64_t Value,
                                 bool IsResolved,
                                 const MCSubtargetInfo *STI, const MCSectionELF &Section) const {
#ifdef DEBUG_CLASS
  outs() << "CodasipGenAsmBackend::applyFixup Fixup.getKind()=" << Fixup.getKind()
    << " Fixup.getOffset()=" << Fixup.getOffset() << " Value=" << Value << " IsResolved=" << IsResolved
    << " Fixup.getMsbValue()=" << Fixup.getMsbValue() << " Fixup.getLsbValue()=" << Fixup.getLsbValue()
    << " Fixup.getMsbOut()=" << Fixup.getMsbOut() << " Fixup.getLsbOut()=" << Fixup.getLsbOut()
    << " Fixup.isSignPart()=" << Fixup.isSignPart() << " Fixup.isSigned()=" << Fixup.isSigned() << "\n";
#endif

  const unsigned Kind = Fixup.getKind();
  uint64_t CurVal = Value;

  // Encoding section for fixups solvable by assembler backend
    bool encodingSectionHasMask = false;
  switch (Kind) {
  case Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12: {
    CurVal =  (  (  ( (codasip::MaxInt)(int64_t)CurVal - (codasip::Integer<64, true>)((codasip::Integer<64, true>)(0)) )  )  >> (codasip::Integer<32, true>)(0x1) ) ;
    break;
  }
  case Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12: {
    CurVal =  (  (  ( (codasip::MaxInt)(int64_t)CurVal - (codasip::Integer<64, true>)((codasip::Integer<64, true>)(0)) )  )  >> (codasip::Integer<32, true>)(0x1) ) ;
    break;
  }
  case Codasip::FK_Codasip_MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20: {
    CurVal =  (  (  ( (codasip::MaxInt)(int64_t)CurVal - (codasip::Integer<64, true>)((codasip::Integer<64, true>)(0)) )  )  >> (codasip::Integer<32, true>)(0x1) ) ;
    break;
  }
  default:
    break;
  }


#ifdef DEBUG_CLASS
  outs() << "Start CurVal=" << CurVal << "\n";
#endif
  // Does not change anything
  if (!CurVal) return;

  // Number of bits of the fixup value
  MCFixupKindInfo Info = getFixupKindInfo(Fixup.getKind());
  const unsigned NumBits = Info.TargetSize;
  // Check that value will fit into given bits
  if (Fixup.isSignPart())
    checkTruncationOverflow(CurVal, NumBits, Fixup.isSigned(),
      Fixup.getValue()->hasMask() || encodingSectionHasMask,
      Fixup.getLoc(), Asm.getContext().getSourceManager());

  // Adjust fixup value
  CurVal = adjustFixupValue(Fixup, CurVal, Asm.getContext());

  // Shift the value into position.
  // Only for RISC-V fixups, Codasip is always 0. Codasip way is Fixup.getLsbOut() above ...
  CurVal <<= Info.TargetOffset;

  // Number of bytes we need to fixup
  unsigned NumBytes = 0;
  switch (Kind) {
  case FK_Data_1:
  case FK_Data_2:
  case FK_Data_4:
  case FK_Data_8:
    NumBytes = (NumBits + 7) / 8;
    break;
  default:
    assert(Kind >= FirstTargetFixupKind && "unexpected general fixup kind!");
    assert(Kind < Codasip::FK_Codasip_Invalid && "invalid fixup kind!");
    NumBytes = Fixup.getByteCount();
    break;
  }
  unsigned Offset = Fixup.getOffset();
  // Fix for RISC-V
  if (NumBytes == 0)
    NumBytes = alignTo(Info.TargetSize + Info.TargetOffset, 8) / 8;

  
  // For each byte of the fragment that the fixup touches, mask in the bits from the fixup value.
  for (unsigned i = 0; i < NumBytes; i++) {
    
    const unsigned Index = i;
    
#ifdef DEBUG_CLASS
    outs() << "Part 1=" << (unsigned)((uint8_t)(CurVal >> (i * 8))) << "\n";
    outs() << "Data 1=" << (unsigned)Data[Offset + Index] << "\n";
#endif
    Data[Offset + i] |= ((uint8_t)(CurVal >> (Index * 8)));
#ifdef DEBUG_CLASS
    outs() << "Data 2=" << (unsigned)Data[Offset + Index] << "\n";
#endif
  }
}

std::unique_ptr<MCObjectTargetWriter>
CodasipGenAsmBackend::createObjectTargetWriter() const {
  return createCodasipELFObjectWriter(OSABI);
}
