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
#include "llvm/ADT/StringMap.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include "MCTargetDesc/CodasipFixupKinds.h"
#include "Codasip.h"
#include "CodasipMCExpr.h"

//#define DEBUG_CLASS

using namespace llvm;

cl::opt<bool> RiscvTarget("riscv-target", cl::desc("Codasip C/C++ Compiler use RISC-V target to produce compatible RISC-V ELF"), cl::init(false));

namespace {

class RelocationExpressionTableBuilder {
  typedef std::vector<std::string> ExpressionTable;
  typedef StringMap<uint32_t> ExpressionToIndex;

  // Stores all relocation expressions in correct order
  mutable ExpressionTable RelocationExpressions;
  // Provides map to quickly reuse index of already generated relocation expression
  mutable ExpressionToIndex RelocationExpressionsMap;
  // Size of already generated relocation expression table
  mutable uint32_t Size;

public:
  RelocationExpressionTableBuilder();
  uint32_t addExpression(const std::string &Expression) const;
  void write(raw_ostream &OS) const;
};

class CodasipELFObjectWriter : public MCELFObjectTargetWriter {
  RelocationExpressionTableBuilder ExprTabBuilder;

  void createRelocationExpression(raw_ostream &OS, const MCExpr *Expression, const MCSymbol &OperandSymbol,
                          const bool IsPCRel, const MCAsmInfo *MAI, const bool IsSigned,
                          const bool InParens = false) const;

public:
  CodasipELFObjectWriter(uint8_t OSABI);

  ~CodasipELFObjectWriter() override;

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel,
                        const MCSectionELF &Section) const override;
  bool needsRelocateWithSymbol(const MCSymbol &Sym, unsigned Type) const override;
  void createRelocationExpressionTable(raw_ostream &OS) const override;

  void addTargetSectionFlags(MCContext &Ctx, MCSectionELF &Sec) override;
  
private:
  const unsigned DataAddressSpaceIndex = 0;
  const unsigned ProgramAddressSpaceIndex = 0;

  unsigned DetermineAddressSpaceIndex(unsigned Flags) const;
};
}   // anonymous namespace

RelocationExpressionTableBuilder::RelocationExpressionTableBuilder()
    : Size(0) {
  // TODO is this valid?
  // there must be always NULL string in string table
  addExpression("");
}

uint32_t RelocationExpressionTableBuilder::addExpression(
  const std::string& Expression) const {
  // return existing index
  const auto it = RelocationExpressionsMap.find(Expression);
  if (it != RelocationExpressionsMap.end())
    return it->second;

  // create new index
  uint32_t Index = Size;
  // insert expression on new index
  RelocationExpressions.emplace_back(Expression);
  // create new record of expression to index
  RelocationExpressionsMap.insert(std::make_pair(Expression, Index));
  // update size
  Size += (Expression.size() + 1);
  // return newly used index
  return Index;
}

void RelocationExpressionTableBuilder::write(raw_ostream &OS) const {
  for (const std::string& Expression : RelocationExpressions)
    OS.write(Expression.c_str(), Expression.size() + 1);
}

CodasipELFObjectWriter::CodasipELFObjectWriter(uint8_t OSABI)
: MCELFObjectTargetWriter(/*Is64Bit*/ 0, OSABI,
                          RiscvTarget ? ELF::EM_RISCV : ELF::EM_CODASIP, /*HasRelocationAddend*/ true) {}

CodasipELFObjectWriter::~CodasipELFObjectWriter() {}

unsigned CodasipELFObjectWriter::getRelocType(MCContext &Ctx,
                                            const MCValue &Target,
                                            const MCFixup &Fixup,
                                            bool IsPCRel,
                                            const MCSectionELF &Section) const {
#ifdef DEBUG_CLASS
  dbgs() << "FixupKind=" << Fixup.getKind() << "\n";
#endif
  // Determine the type of the relocation
  unsigned Kind = Fixup.getKind();
  if (RiscvTarget) {
    // Taken from RISC-V target
    if (IsPCRel) {
      switch (Kind) {
      default:
        // Following line has to be removed when RISC-V and Codasip relocations works together
        dbgs() << "FixupKind=" << Fixup.getKind() << "\n";
        llvm_unreachable("invalid fixup kind!");
      case FK_Data_4:
      case FK_PCRel_4:
        return ELF::R_RISCV_32_PCREL;
      case Codasip::fixup_riscv_pcrel_hi20:
        return ELF::R_RISCV_PCREL_HI20;
      case Codasip::fixup_riscv_pcrel_lo12_i:
        return ELF::R_RISCV_PCREL_LO12_I;
      case Codasip::fixup_riscv_pcrel_lo12_s:
        return ELF::R_RISCV_PCREL_LO12_S;
      case Codasip::fixup_riscv_got_hi20:
        return ELF::R_RISCV_GOT_HI20;
      case Codasip::fixup_riscv_tls_got_hi20:
        return ELF::R_RISCV_TLS_GOT_HI20;
      case Codasip::fixup_riscv_tls_gd_hi20:
        return ELF::R_RISCV_TLS_GD_HI20;
      case Codasip::fixup_riscv_jal:
        return ELF::R_RISCV_JAL;
      case Codasip::fixup_riscv_branch:
        return ELF::R_RISCV_BRANCH;
      case Codasip::fixup_riscv_rvc_jump:
        return ELF::R_RISCV_RVC_JUMP;
      case Codasip::fixup_riscv_rvc_branch:
        return ELF::R_RISCV_RVC_BRANCH;
      case Codasip::fixup_riscv_call:
        return ELF::R_RISCV_CALL;
      case Codasip::fixup_riscv_call_plt:
        return ELF::R_RISCV_CALL_PLT;
      }
    }

    switch (Kind) {
    default:
      // Following line has to be removed when RISC-V and Codasip relocations works together
      dbgs() << "FixupKind=" << Fixup.getKind() << "\n";
      llvm_unreachable("invalid fixup kind!");
    case FK_Data_4:
      return ELF::R_RISCV_32;
    case FK_Data_8:
      return ELF::R_RISCV_64;
    case FK_Data_Add_1:
      return ELF::R_RISCV_ADD8;
    case FK_Data_Add_2:
      return ELF::R_RISCV_ADD16;
    case FK_Data_Add_4:
      return ELF::R_RISCV_ADD32;
    case FK_Data_Add_8:
      return ELF::R_RISCV_ADD64;
    case FK_Data_Sub_1:
      return ELF::R_RISCV_SUB8;
    case FK_Data_Sub_2:
      return ELF::R_RISCV_SUB16;
    case FK_Data_Sub_4:
      return ELF::R_RISCV_SUB32;
    case FK_Data_Sub_8:
      return ELF::R_RISCV_SUB64;
    case Codasip::fixup_riscv_hi20:
      return ELF::R_RISCV_HI20;
    case Codasip::fixup_riscv_lo12_i:
      return ELF::R_RISCV_LO12_I;
    case Codasip::fixup_riscv_lo12_s:
      return ELF::R_RISCV_LO12_S;
    case Codasip::fixup_riscv_tprel_hi20:
      return ELF::R_RISCV_TPREL_HI20;
    case Codasip::fixup_riscv_tprel_lo12_i:
      return ELF::R_RISCV_TPREL_LO12_I;
    case Codasip::fixup_riscv_tprel_lo12_s:
      return ELF::R_RISCV_TPREL_LO12_S;
    case Codasip::fixup_riscv_tprel_add:
      return ELF::R_RISCV_TPREL_ADD;
    case Codasip::fixup_riscv_relax:
      return ELF::R_RISCV_RELAX;
    case Codasip::fixup_riscv_align:
      return ELF::R_RISCV_ALIGN;
    }
  }

  const MCExpr* Expression = Fixup.getValue();
  std::string ExpressionStr;
  raw_string_ostream OS(ExpressionStr);
  const MCSymbolRefExpr *Sym = Target.getSymA();
#ifdef DEBUG_CLASS
  dbgs() << "getRelocType Target.isAbsolute()=" << Target.isAbsolute() << "  Target.getConstant=" << Target.getConstant()
    << " Target.getSymA()=" << Target.getSymA() << " Target.getSymB()=" << Target.getSymB() << " Target.getRefKind()=" << Target.getRefKind() << "\n";
#endif
  assert(Sym != nullptr && "Relocation with no symbol");
  // assert(Target.getSymB() == nullptr && 
  //   "Relocations do not support multiple symbols");
  createRelocationExpression(OS, Expression, Sym->getSymbol(), IsPCRel, Ctx.getAsmInfo(), Fixup.isSigned());
  OS.flush();

  // Encoding section for fixups solvable by linker
  switch (Kind) {
  case Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12: {
    ExpressionStr = " (  (  ( " + ExpressionStr + " -  i64  (  i64  ( current_address )  )  )  )  >>  i32  ( 0x1 )  ) ";
    break;
  }
  case Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12: {
    ExpressionStr = " (  (  ( " + ExpressionStr + " -  i64  (  i64  ( current_address )  )  )  )  >>  i32  ( 0x1 )  ) ";
    break;
  }
  case Codasip::FK_Codasip_MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20: {
    ExpressionStr = " (  (  ( " + ExpressionStr + " -  i64  (  i64  ( current_address )  )  )  )  >>  i32  ( 0x1 )  ) ";
    break;
  }
  default:
    break;
  }


  // Correct fixup for general relocations
  switch (Kind) {
  case FK_Data_1:
    Fixup.setByteCount(1);
    Fixup.setMsbOut(7);
    Fixup.setLsbOut(0);
    break;
  case FK_Data_2:
    Fixup.setByteCount(2);
    Fixup.setMsbOut(15);
    Fixup.setLsbOut(0);
    break;
  case FK_Data_4:
    Fixup.setByteCount(4);
    Fixup.setMsbOut(31);
    Fixup.setLsbOut(0);
    break;
  case FK_Data_8:
    Fixup.setByteCount(8);
    Fixup.setMsbOut(63);
    Fixup.setLsbOut(0);
    break;
  default:
    assert(Kind >= FirstTargetFixupKind && "unexpected general fixup kind!");
    assert(Kind < Codasip::FK_Codasip_Invalid && "invalid fixup kind!");
    // Enhance expression to correct bit manipulation, depends on placement position (MSB, MID, LSB)
    const std::string Type = /*Fixup.isSigned() ? */"i64"/* : "u64"*/;
    // Add shift when it is needed (MSB, MID)
    if (Fixup.getLsbValue() > 0) {
      const std::string Shift = std::to_string(Fixup.getLsbValue());
      ExpressionStr = Type + " ( " + ExpressionStr + " >> " + Shift + " )";
    }
    // Add mask when it is needed (MID, LSB)
    if (!Fixup.isSignPart()) {
      const size_t Size = Fixup.getMsbValue() - Fixup.getLsbValue() + 1;
      const std::string Mask = std::to_string(maskTrailingOnes<uint64_t>(Size));
      ExpressionStr = Type + " ( " + ExpressionStr + " & " + Mask + " )";
    }
    break;
  }

  // Hack for LAU != 8 architectures, we could only hope that it works
  const unsigned int ByteBytes = Section.GetByteBytes(*Ctx.getAsmInfo());
  const size_t bc = Fixup.getByteCount() / ByteBytes;
  // Hoping that nobody later touches MXFixup.ByteCount, MXFixup.MsbOut and MXFixup.LsbOut
  ExpressionStr = std::to_string(bc) + "#" + std::to_string(Fixup.getMsbOut()) +
    "#" + std::to_string(Fixup.getLsbOut()) + "#" + ExpressionStr;
  uint32_t index = ExprTabBuilder.addExpression(ExpressionStr);
#ifdef DEBUG_CLASS
  llvm::dbgs() << "New expression at index: " << index << " :" << ExpressionStr << "\n";
#endif
  Fixup.setExpressionIndex(index);

  // Determine the type of the relocation
  switch (Kind) {
  case FK_Data_1:
  case FK_Data_2:
  case FK_Data_4:
  case FK_Data_8:
    return ELF::R_CODASIP_EXPR;
  case Codasip::FK_Codasip_MI5valueIH1_13default_start7_5uimm53imm1_5uimm5:
  case Codasip::FK_Codasip_MI5valueIH1_13default_start8_6uimm203imm1_6uimm20:
    return ELF::R_CODASIP_EXPR;
    return ELF::R_CODASIP_EXPR;
  case Codasip::FK_Codasip_MI5valueIH1_13default_start8_6simm124simm1_6simm12:
  case Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12:
  case Codasip::FK_Codasip_MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12:
  case Codasip::FK_Codasip_MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20:
    return (Fixup.isSignPart() && !Expression->hasMask()) ? ELF::R_CODASIP_EXPR_S : ELF::R_CODASIP_EXPR;

  default:
    llvm_unreachable("invalid fixup kind!");
    // Default is unsigned for now, but everything should be handled though
    return ELF::R_CODASIP_EXPR;
  }
}

bool CodasipELFObjectWriter::needsRelocateWithSymbol(const MCSymbol &, unsigned) const {
  // Codasip support relocations with symbol only (Not the section symbol + offset)
  return true;
}

void CodasipELFObjectWriter::createRelocationExpressionTable(
  raw_ostream &OS) const {
  ExprTabBuilder.write(OS);
}

void CodasipELFObjectWriter::addTargetSectionFlags(MCContext &Ctx, 
                                                   MCSectionELF &Sec) {
  // already set in the frontend
  if (Sec.IsAddressSpaceSet())
    return;
  
  unsigned Type = Sec.getType();
  // TODO maybe not necessary since called only for user sections
  if (Type != ELF::SHT_STRTAB && Type != ELF::SHT_SYMTAB && 
      Type != ELF::SHT_DYNAMIC && Type != ELF::SHT_HASH && 
      Type != ELF::SHT_REL && Type != ELF::SHT_RELA && 
      Type != ELF::SHT_DYNSYM && 
      Type != ELF::SHT_CODASIP_AS && 
      Type != ELF::SHT_CODASIP_RELOCATION_EXPRESSION) {
    unsigned Index = DetermineAddressSpaceIndex(Sec.getFlags());
#ifdef DEBUG_CLASS
    outs() << "Setting address space index for section '" << 
      Sec.getSectionName() << "' to: " << Index << "\n";
#endif
    Sec.SetAddressSpaceIndex(Index);
  }
}

unsigned CodasipELFObjectWriter::DetermineAddressSpaceIndex(unsigned Flags) const {
  unsigned Index = DataAddressSpaceIndex;
  if (ProgramAddressSpaceIndex != DataAddressSpaceIndex && (Flags & ELF::SHF_EXECINSTR))
    Index = ProgramAddressSpaceIndex;
  return Index;
}

void CodasipELFObjectWriter::createRelocationExpression(raw_ostream &OS,
                                                const MCExpr *Expression,
                                                const MCSymbol &OperandSymbol,
                                                const bool IsPCRel,
                                                const MCAsmInfo *MAI,
                                                const bool IsSigned,
                                                const bool InParens) const {
  const std::string Type = "i64";
  OS << Type << " ";
  switch (Expression->getKind()) {
  case MCExpr::Target: {
    const CodasipTernaryMCExpr &Ternary = cast<CodasipTernaryMCExpr>(*Expression);
    OS << " ( ";
    createRelocationExpression(OS, &Ternary.getCondition(), OperandSymbol, IsPCRel, MAI, IsSigned);
    OS << " ? ";
    createRelocationExpression(OS, &Ternary.getTrue(), OperandSymbol, IsPCRel, MAI, IsSigned);
    OS << " : ";
    createRelocationExpression(OS, &Ternary.getFalse(), OperandSymbol, IsPCRel, MAI, IsSigned);
    OS << " )";
    return;
  }
  case MCExpr::Constant:
    OS << cast<MCConstantExpr>(*Expression).getValue();
    return;

  case MCExpr::SymbolRef: {
    const MCSymbolRefExpr &SRE = cast<MCSymbolRefExpr>(*Expression);
    const MCSymbol &Sym = SRE.getSymbol();
      OS << " ( ";
      if (&Sym == &OperandSymbol)
        OS << "$0 ";
      else if (Sym.getName() == ".Lcurrent_address")
        OS << "current_address ";
      else
        Sym.print(OS, MAI);
      OS << " ) ";
    if (SRE.getKind() != MCSymbolRefExpr::VK_None)
      SRE.printVariantKind(OS);

    return;
  }

  case MCExpr::Unary: {
    const MCUnaryExpr &UE = cast<MCUnaryExpr>(*Expression);
    std::string Operation;
    // TODO This hack is needed because linker does not support any unary operation
    bool BinaryHack = false;
    switch (UE.getOpcode()) {
    case MCUnaryExpr::LNot:  Operation = "!"; break;
    case MCUnaryExpr::Minus: Operation = "-"; BinaryHack = true; break;
    case MCUnaryExpr::Not:   Operation = "~"; break;
    case MCUnaryExpr::Plus:  Operation = "+"; BinaryHack = true; break;
    }
    if (BinaryHack)
      OS << " ( 0 ";
    OS << " " << Operation << " ";
    createRelocationExpression(OS, UE.getSubExpr(), OperandSymbol, IsPCRel, MAI, IsSigned);
    if (BinaryHack)
      OS << " ) ";
    return;
  }

  case MCExpr::Binary: {
    const MCBinaryExpr &BE = cast<MCBinaryExpr>(*Expression);

    OS << " ( ";
    createRelocationExpression(OS, BE.getLHS(), OperandSymbol, IsPCRel, MAI, IsSigned);
    OS << " ";

    switch (BE.getOpcode()) {
    case MCBinaryExpr::Add:  OS <<  "+"; break;
    case MCBinaryExpr::AShr: OS << ">>"; break;
    case MCBinaryExpr::And:  OS <<  "&"; break;
    case MCBinaryExpr::Div:  OS <<  "/"; break;
    case MCBinaryExpr::EQ:   OS << "=="; break;
    case MCBinaryExpr::GT:   OS <<  ">"; break;
    case MCBinaryExpr::GTE:  OS << ">="; break;
    case MCBinaryExpr::LAnd: OS << "&&"; break;
    case MCBinaryExpr::LOr:  OS << "||"; break;
    case MCBinaryExpr::LShr: OS << ">>"; break;
    case MCBinaryExpr::LT:   OS <<  "<"; break;
    case MCBinaryExpr::LTE:  OS << "<="; break;
    case MCBinaryExpr::Mod:  OS <<  "%"; break;
    case MCBinaryExpr::Mul:  OS <<  "*"; break;
    case MCBinaryExpr::NE:   OS << "!="; break;
    case MCBinaryExpr::Or:   OS <<  "|"; break;
    case MCBinaryExpr::Shl:  OS << "<<"; break;
    case MCBinaryExpr::Sub:  OS <<  "-"; break;
    case MCBinaryExpr::Xor:  OS <<  "^"; break;
    }

    OS << " ";
    createRelocationExpression(OS, BE.getRHS(), OperandSymbol, IsPCRel, MAI, IsSigned);
    OS << " ) ";

    return;
  }
  }

  llvm_unreachable("Invalid expression kind!");
}

std::unique_ptr<MCObjectTargetWriter> llvm::createCodasipELFObjectWriter(
                                                 uint8_t OSABI) {
  return llvm::make_unique<CodasipELFObjectWriter>(OSABI);
}
