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


#include "AsmParser/CodasipAsmParserHooks.h"
#include "MCTargetDesc/CodasipAsmBackend.h"
#include "MCTargetDesc/CodasipMCTargetDesc.h"
#include "MCTargetDesc/CodasipTargetStreamer.h"

#include <assert.h>
#include <string.h>

#include "codasip/ObjectFile/CodasipSectionDefines.h"
#include "llvm/CodeGen/TargetOpcodes.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCParser/MCAsmLexer.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"

#include "instrset/assembler/asmbasel/ast/assembler/node.h"
#include "instrset/assembler/asmbasel/parser_utility.h"

//#define DEBUG_CLASS

/// Main bison parser function
typedef void* yyscan_t;
extern int yyparse(yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base,
    ::codasip::ast::assembler::Node*& ast);
extern "C" int yylex_destroy(yyscan_t);
extern "C" int yylex_init(yyscan_t*);
extern void ScanBuffer(const char* buffer, yyscan_t);
extern void DeleteCurrentBuffer(yyscan_t);

// Forward declarations
namespace codasip {
namespace ast {
namespace assembler {
class Node;
}   // namespace codasip::ast::assembler
}   // namespace codasip::ast
}   // namespace codasip

using namespace llvm;

#define DEBUG_TYPE "asmparser"

extern cl::opt<bool> RiscvTarget;

cl::opt<bool> EnableAsmCompression(
  "enable-asm-compression", cl::Hidden, cl::init(true),
  cl::desc("Enable compression at assembly level"));

namespace {

/// CodasipOperand - Instances of this class represent a parsed machine
/// instruction
struct CodasipOperand : public MCParsedAsmOperand {

  enum KindTy {
    Token,
    Register,
    Immediate,
  } Kind;

  struct TokOp {
    const char *Data;
    unsigned Length;
  };

  struct RegOp {
    unsigned RegNum;
  };

  struct ImmOp {
    const MCExpr *Val;
  };

  SMLoc StartLoc, EndLoc;
  union {
    TokOp Tok;
    RegOp Reg;
    ImmOp Imm;
  };

  CodasipOperand(KindTy K) : MCParsedAsmOperand(), Kind(K) {}

public:
  CodasipOperand(const CodasipOperand &o) : MCParsedAsmOperand() {
    Kind = o.Kind;
    StartLoc = o.StartLoc;
    EndLoc = o.EndLoc;
    switch (Kind) {
    case Register:
      Reg = o.Reg;
      break;
    case Immediate:
      Imm = o.Imm;
      break;
    case Token:
      Tok = o.Tok;
      break;
    }
  }

  bool isToken() const override { return Kind == Token; }
  bool isReg() const override { return Kind == Register; }
  bool isImm() const override { return Kind == Immediate; }
  bool isMem() const override { return false; }

  bool isConstantImm() const {
    return isImm() && dyn_cast<MCConstantExpr>(getImm());
  }

  int64_t getConstantImm() const {
    const MCExpr *Val = getImm();
    return static_cast<const MCConstantExpr *>(Val)->getValue();
  }

  bool isSImm12() const {
    return (isConstantImm() && isInt<12>(getConstantImm()));
  }

  /// getStartLoc - Gets location of the first token of this operand
  SMLoc getStartLoc() const override { return StartLoc; }

  /// getEndLoc - Gets location of the last token of this operand
  SMLoc getEndLoc() const override { return EndLoc; }

  unsigned getReg() const override {
    assert(Kind == Register && "Invalid type access!");
    return Reg.RegNum;
  }

  const MCExpr *getImm() const {
    assert(Kind == Immediate && "Invalid type access!");
    return Imm.Val;
  }

  StringRef getToken() const {
    assert(Kind == Token && "Invalid type access!");
    return StringRef(Tok.Data, Tok.Length);
  }

  void print(raw_ostream &OS) const override {
    switch (Kind) {
    case Immediate:
      OS << *getImm();
      break;
    case Register:
      OS << "<register r";
      OS << getReg() << ">";
      break;
    case Token:
      OS << "'" << getToken() << "'";
      break;
    }
  }

  static std::unique_ptr<CodasipOperand> createToken(StringRef Str, SMLoc S) {
    auto Op = make_unique<CodasipOperand>(Token);
    Op->Tok.Data = Str.data();
    Op->Tok.Length = Str.size();
    Op->StartLoc = S;
    Op->EndLoc = S;
    return Op;
  }

  static std::unique_ptr<CodasipOperand> createReg(unsigned RegNo, SMLoc S,
                                                 SMLoc E) {
    auto Op = make_unique<CodasipOperand>(Register);
    Op->Reg.RegNum = RegNo;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }

  static std::unique_ptr<CodasipOperand> createImm(const MCExpr *Val, SMLoc S,
                                                 SMLoc E) {
    auto Op = make_unique<CodasipOperand>(Immediate);
    Op->Imm.Val = Val;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }

  void addExpr(MCInst &Inst, const MCExpr *Expr) const {
      assert(Expr && "Expr shouldn't be null!");
      if (auto *CE = dyn_cast<MCConstantExpr>(Expr))
        Inst.addOperand(MCOperand::createImm(CE->getValue(), CE->isMasked()));
      else
        Inst.addOperand(MCOperand::createExpr(Expr));
      MCOperand &Op = Inst.getOperand(Inst.getNumOperands() - 1);
      Op.setAttributeId(Expr->getAttributeId());
  }

  // Used by the TableGen Code
  void addRegOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands!");
    Inst.addOperand(MCOperand::createReg(getReg()));
  }

  void addImmOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands!");
    addExpr(Inst, getImm());
  }
};

} // end anonymous namespace.

class CodasipAsmParser : public MCTargetAsmParser {
  SmallVector<FeatureBitset, 4> FeatureBitStack;

  bool ProcessInstruction(MCInst &Inst, SMLoc IDLoc,
                          OperandVector &Operands,
                          MCStreamer &Out);
  // Needs to be cached until all CodasipAsmParser work is done
  codasip::assembler::ParserUtility::ParsedTokens m_ParsedTokens;

  // Generated CodasipAsmParser hooks
  CodasipAsmParserHooksGen m_GeneratedHooks;
  // User CodasipAsmParser hooks (for RISC-V)
  CodasipAsmParserHooks m_UserHooks;


  CodasipAsmParserHooksGen &getHooks() {
    return RiscvTarget ? m_UserHooks : m_GeneratedHooks;
  }
  CodasipTargetStreamer &getTargetStreamer() {
    MCTargetStreamer &TS = *getParser().getStreamer().getTargetStreamer();
    return static_cast<CodasipTargetStreamer &>(TS);
  }
  bool MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) override;

  bool ParseRegister(unsigned &RegNo, SMLoc &StartLoc, SMLoc &EndLoc) override;

  bool ParseInstruction(ParseInstructionInfo &Info, StringRef Name,
                        SMLoc NameLoc, OperandVector &Operands) override;
  bool Parse(codasip::ast::assembler::Node*& Ast, llvm::SMLoc NameLoc);
  static void Tokens2Operands(OperandVector &Operands,
    codasip::assembler::ParserUtility::ParsedTokens &tokens);

  bool ParseDirective(AsmToken DirectiveID) override;
  bool ParseDirectiveAbsOrg();
  bool ParseDirectiveAddressSpace();
  bool parseDirectiveOption();
  bool ParseDirectiveProfiler();

  /// from RV for .option norvc
  void setFeatureBits(uint64_t Feature, StringRef FeatureString) {
    if (!(getSTI().getFeatureBits()[Feature])) {
      MCSubtargetInfo &STI = copySTI();
      setAvailableFeatures(
          ComputeAvailableFeatures(STI.ToggleFeature(FeatureString)));
    }
  }

  void clearFeatureBits(uint64_t Feature, StringRef FeatureString) {
    if (getSTI().getFeatureBits()[Feature]) {
      MCSubtargetInfo &STI = copySTI();
      setAvailableFeatures(
          ComputeAvailableFeatures(STI.ToggleFeature(FeatureString)));
    }
  }

  void pushFeatureBits() {
    FeatureBitStack.push_back(getSTI().getFeatureBits());
  }

  bool popFeatureBits() {
    if (FeatureBitStack.empty())
      return true;

    FeatureBitset FeatureBits = FeatureBitStack.pop_back_val();
    copySTI().setFeatureBits(FeatureBits);
    setAvailableFeatures(ComputeAvailableFeatures(FeatureBits));

    return false;
  }

  // "=" is used as assignment operator for assembly statement, so can't be used
  // for symbol assignment.
  bool equalIsAsmAssignment() override { return false; }


// Auto-generated instruction matching functions
#define GET_ASSEMBLER_HEADER
#include "CodasipGenAsmMatcher.inc"

public:
  enum CodasipMatchResultTy {
    Match_Dummy = FIRST_TARGET_MATCH_RESULT_TY,
#define GET_OPERAND_DIAGNOSTIC_TYPES
#include "CodasipGenAsmMatcher.inc"
#undef GET_OPERAND_DIAGNOSTIC_TYPES
  };

  CodasipAsmParser(const MCSubtargetInfo &STI, MCAsmParser &Parser,
                   const MCInstrInfo &MII, const MCTargetOptions &Options)
  : MCTargetAsmParser(Options, STI, MII)

  {
    Parser.addAliasForDirective(".half", ".2byte");
    Parser.addAliasForDirective(".hword", ".2byte");
    Parser.addAliasForDirective(".word", ".4byte");
    Parser.addAliasForDirective(".dword", ".8byte");

    setAvailableFeatures(ComputeAvailableFeatures(STI.getFeatureBits()));
    codasip::assembler::ParserUtility::Init(Parser);

  }
};

#define GET_REGISTER_MATCHER
#define GET_MATCHER_IMPLEMENTATION
#include "CodasipGenAsmMatcher.inc"



bool CodasipAsmParser::MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                                             OperandVector &Operands,
                                             MCStreamer &Out,
                                             uint64_t &ErrorInfo,
                                             bool MatchingInlineAsm) {
  MCInst Inst;
  SMLoc ErrorLoc;

  switch (MatchInstructionImpl(Operands, Inst, ErrorInfo, MatchingInlineAsm)) {
  default:
    break;
  case Match_Success:
  {
    
    return ProcessInstruction(Inst, IDLoc, Operands, Out);
  }
  case Match_MissingFeature:
    return Error(IDLoc, "instruction use requires an option to be enabled");
  case Match_MnemonicFail:
    return Error(IDLoc, "unrecognized instruction mnemonic");
  case Match_InvalidOperand:
    ErrorLoc = IDLoc;
    if (ErrorInfo != ~0U) {
      if (ErrorInfo >= Operands.size())
        return Error(ErrorLoc, "too few operands for instruction");

      ErrorLoc = ((CodasipOperand &)*Operands[ErrorInfo]).getStartLoc();
      if (ErrorLoc == SMLoc())
        ErrorLoc = IDLoc;
    }
    return Error(ErrorLoc, "invalid operand for instruction");
  }
  llvm_unreachable("Unknown match type detected!");
}

#include "../CodasipCompressInst.inc"
bool CodasipAsmParser::ProcessInstruction(MCInst &Inst, SMLoc IDLoc,
                                          OperandVector &,
                                          MCStreamer &Out) {
  Inst.setLoc(IDLoc);
  MCInst CInst;
  bool Res = false;
  if (EnableAsmCompression && getSTI().hasFeature(Codasip::FeatureStdExtC))
    Res = compressInst(CInst, Inst, getSTI(), Out.getContext());
  getHooks().ProcessInstruction((Res ? CInst : Inst), IDLoc, Out, getSTI());
  return false;
}


bool CodasipAsmParser::ParseRegister(unsigned &RegNo, SMLoc &StartLoc,
                                   SMLoc &EndLoc) {
  const AsmToken &Tok = getParser().getTok();
  StartLoc = Tok.getLoc();
  EndLoc = Tok.getEndLoc();
  RegNo = 0;
  StringRef Name = getLexer().getTok().getIdentifier();

  if (!MatchRegisterName(Name) || !MatchRegisterAltName(Name)) {
    getParser().Lex(); // Eat identifier token.
    return false;
  }

  return Error(StartLoc, "invalid register name");
}

bool CodasipAsmParser::ParseInstruction(ParseInstructionInfo &Info,
                                      StringRef Name, SMLoc NameLoc,
                                      OperandVector &Operands) {
#ifdef DEBUG_CLASS
  outs() << "ParseInstruction\n" << NameLoc.getPointer() << "\n";
#endif
  // Ensure that if the instruction occurs when relaxation is enabled,
  // relocations are forced for the file. Ideally this would be done when there
  // is enough information to reliably determine if the instruction itself may
  // cause relaxations. Unfortunately instruction processing stage occurs in the
  // same pass as relocation emission, so it's too late to set a 'sticky bit'
  // for the entire file.
  if (getSTI().getFeatureBits()[Codasip::FeatureRelax]) {
    auto *Assembler = getTargetStreamer().getStreamer().getAssemblerPtr();
    if (Assembler != nullptr) {
      CodasipAsmBackend &MAB =
          static_cast<CodasipAsmBackend &>(Assembler->getBackend());
      MAB.setForceRelocs();
    }
  }


  // Parse instruction with Codasip instruction parser and provide correct parsed tokens for LLVM
  m_ParsedTokens.clear();

  // Parse to get Codasip AST
  codasip::ast::assembler::Node *Ast = nullptr;
  if (!Parse(Ast, NameLoc)) {
    codasip::assembler::ParserUtility::CleanAfterParse();
    return true; // Syntax error happened
  }
  

  // Convert Codasip AST to Codasip tokens
  codasip::assembler::ParserUtility::Ast2Tokens(m_ParsedTokens, *Ast, NameLoc);
  codasip::assembler::ParserUtility::CleanAfterParse();

  // Convert Codasip tokens into LLVM operands
  Tokens2Operands(Operands, m_ParsedTokens);

  // Repair LLVM lexer, otherwise LLVM will silently eat following statement
  getLexer().CodasipReset();



  // LLVM silently eats unprocessed tokens until end of statement, our algorithm has to eat it instead
  return false;
}

/**
 *  \brief  Parse instruction with Codasip re-flex + bison solution.
 *  \param[out] ast AST of the currently parsed instruction
 *  \param[in]  nameLoc Location of the instruction
 *  \return Flag that parsing was successful.
 */
bool CodasipAsmParser::Parse(codasip::ast::assembler::Node*& Ast, llvm::SMLoc NameLoc)
{
    yyscan_t Scanner;
    yylex_init(&Scanner);
    ScanBuffer(NameLoc.getPointer(), Scanner);
    int Res = 0;
    // Set base location for elements of conditional sections
    codasip::assembler::ParserUtility::SetBase(NameLoc);
    Res = yyparse(Scanner, getParser(), NameLoc, Ast);
#ifdef DEBUG_CLASS
    outs() << "res " << Res << "\n";
#endif
    DeleteCurrentBuffer(Scanner);
    yylex_destroy(Scanner);

    // Failure
    if (Res)
    {
        return false;
    }

    assert(Ast != nullptr);
    // Success
    return true;
}

void CodasipAsmParser::Tokens2Operands(OperandVector &Operands,
  codasip::assembler::ParserUtility::ParsedTokens &tokens) {
  for (codasip::assembler::ParsedToken *Token : tokens) {
    SMLoc S = Token->GetStartLocation();
    SMLoc E = Token->GetEndLocation();
    if (Token->GetType() == codasip::assembler::ParsedToken::TOKEN) {
      // Skip comma, because LLVM do not handle it
      if (Token->GetString() == ",")
        continue;
      Operands.emplace_back(
        CodasipOperand::createToken(StringRef(Token->GetString().c_str(), Token->GetString().size()),
                                    S));
    } else if (Token->GetType() == codasip::assembler::ParsedToken::REGISTER) {
      StringRef RegName(Token->GetString().c_str(), Token->GetString().size());
      // Match register name
      unsigned RegNo = MatchRegisterName(RegName);
      // Try alt name
      if (RegNo == 0)
        RegNo = MatchRegisterAltName(RegName);
      Operands.emplace_back(CodasipOperand::createReg(RegNo, S, E));
    } else if (Token->GetType() == codasip::assembler::ParsedToken::IMMEDIATE) {
      codasip::assembler::ParserUtility::LLVMTokens llvmTokens;
      codasip::assembler::ParserUtility::ConvertCodasipToLlvmTokens(llvmTokens,
        Token->GetParsedTokens());
      const llvm::MCExpr* Expression =
        codasip::assembler::ParserUtility::CreateExpression(llvmTokens);
      // Set attribute identifier to MCExpr
      Expression->setAttributeId(Token->GetString());
      Operands.emplace_back(CodasipOperand::createImm(Expression, S, E));
    } else
      assert(false && "Unknown parsed token type.");
  }
}

bool CodasipAsmParser::ParseDirective(AsmToken DirectiveID) {
  StringRef IDVal = DirectiveID.getString();

  if (IDVal == ".abs_org")
    return ParseDirectiveAbsOrg();
  if (IDVal == ".address_space")
    return ParseDirectiveAddressSpace();
  // Only silences errors and warnings
  if (IDVal == ".option")
    return parseDirectiveOption();
  if (IDVal == ".profiler")
    return ParseDirectiveProfiler();
  return true;
}

bool CodasipAsmParser::ParseDirectiveAbsOrg() {
  MCAsmParser &Parser = getParser();
  SMLoc S = getTok().getLoc();
  Twine Msg = "unexpected token, expected constant expression";

  // Could not parse an expression
  const MCExpr *Res;
  if (Parser.parseExpression(Res))
    return Error(S, Msg);

  // Expression could is not a constant expression
  auto *CE = dyn_cast<MCConstantExpr>(Res);
  if (!CE)
    return Error(S, Msg);

  // Execute directive
  const int64_t Address = CE->getValue();
  getTargetStreamer().emitDirectiveAbsOrg(Address, S);

  // Read end of statement
  if (Parser.getTok().isNot(AsmToken::EndOfStatement))
    return Error(Parser.getTok().getLoc(), "unexpected token, expected end of statement");
  return false;
}

bool CodasipAsmParser::ParseDirectiveAddressSpace() {
  MCAsmParser &Parser = getParser();
  const AsmToken &Tok = Parser.getTok();
  SMLoc S = Tok.getLoc();

  // Read address space index
  if (Tok.isNot(AsmToken::Integer))
    return Error(S, "unexpected token, expected identifier");
  const unsigned Index = Tok.getIntVal();
  Parser.Lex();

  // Execute directive
  getTargetStreamer().emitDirectiveAddressSpace(Index, S);

  // Read end of statement
  if (Parser.getTok().isNot(AsmToken::EndOfStatement))
    return Error(Parser.getTok().getLoc(), "unexpected token, expected end of statement");
  return false;
}

bool CodasipAsmParser::parseDirectiveOption() {
  MCAsmParser &Parser = getParser();
  // Get the option token.
  AsmToken Tok = Parser.getTok();
  // At the moment only identifiers are supported.
  if (Tok.isNot(AsmToken::Identifier))
    return Error(Parser.getTok().getLoc(),
                 "unexpected token, expected identifier");

  StringRef Option = Tok.getIdentifier();

  if (Option == "push") {
    getTargetStreamer().emitDirectiveOptionPush();

    Parser.Lex();
    if (Parser.getTok().isNot(AsmToken::EndOfStatement))
      return Error(Parser.getTok().getLoc(),
                   "unexpected token, expected end of statement");

    pushFeatureBits();
    return false;
  }

  if (Option == "pop") {
    SMLoc StartLoc = Parser.getTok().getLoc();
    getTargetStreamer().emitDirectiveOptionPop();

    Parser.Lex();
    if (Parser.getTok().isNot(AsmToken::EndOfStatement))
      return Error(Parser.getTok().getLoc(),
                   "unexpected token, expected end of statement");

    if (popFeatureBits())
      return Error(StartLoc, ".option pop with no .option push");

    return false;
  }

  if (Option == "rvc") {
    getTargetStreamer().emitDirectiveOptionRVC();

    Parser.Lex();
    if (Parser.getTok().isNot(AsmToken::EndOfStatement))
      return Error(Parser.getTok().getLoc(),
                   "unexpected token, expected end of statement");

    setFeatureBits(Codasip::FeatureStdExtC, "c");
    return false;
  }

  if (Option == "norvc") {
    getTargetStreamer().emitDirectiveOptionNoRVC();

    Parser.Lex();
    if (Parser.getTok().isNot(AsmToken::EndOfStatement))
      return Error(Parser.getTok().getLoc(),
                   "unexpected token, expected end of statement");
    clearFeatureBits(Codasip::FeatureStdExtC, "c");
    return false;
  }

  if (Option == "relax") {
    getTargetStreamer().emitDirectiveOptionRelax();

    Parser.Lex();
    if (Parser.getTok().isNot(AsmToken::EndOfStatement))
      return Error(Parser.getTok().getLoc(),
                   "unexpected token, expected end of statement");

    setFeatureBits(Codasip::FeatureRelax, "relax");
    return false;
  }

  if (Option == "norelax") {
    getTargetStreamer().emitDirectiveOptionNoRelax();

    Parser.Lex();
    if (Parser.getTok().isNot(AsmToken::EndOfStatement))
      return Error(Parser.getTok().getLoc(),
                   "unexpected token, expected end of statement");

    clearFeatureBits(Codasip::FeatureRelax, "relax");
    return false;
  }

  // Unknown option.
  Warning(Parser.getTok().getLoc(),
          "unknown option, expected 'push', 'pop', 'rvc', 'norvc', 'relax' or "
          "'norelax'");
  Parser.eatToEndOfStatement();
  return false;
}

bool CodasipAsmParser::ParseDirectiveProfiler() {
  MCAsmParser &Parser = getParser();
  SMLoc S = Parser.getTok().getLoc();
  Twine Msg = "unexpected token, expected string";

  // Read flags
  if (Parser.getTok().isNot(AsmToken::String))
    return Error(Parser.getTok().getLoc(), Msg);
  StringRef Flags = Parser.getTok().getStringContents();
  Parser.Lex();

  // Prepare flag value
  CodasipProfileFlag Flag = CODASIP_PROFILE_FLAG_NONE;
  if (Flags == "s")
    Flag = CODASIP_PROFILE_FLAG_START;
  else if (Flags.str() == "x")
    Flag = CODASIP_PROFILE_FLAG_END;
  else
    return Error(S, "Unsupported '.profiler' directive flag '" + Flags +
      "'. The only supported '.profiler' directive flags are 's' (start) and 'x' (end)");

  // Read block of provided
  std::string Block = "";
  if (Parser.getTok().isNot(AsmToken::EndOfStatement)) {
    // Read comma
    if (Parser.getTok().isNot(AsmToken::Comma))
      return Error(Parser.getTok().getLoc(), "unexpected token, expected comma");
    Parser.Lex();

    // Read block
    if (Parser.getTok().isNot(AsmToken::String))
      return Error(Parser.getTok().getLoc(), Msg);
    Block = Parser.getTok().getStringContents().str();
    Parser.Lex();
  }

  // Execute directive
  getTargetStreamer().emitDirectiveProfiler(Flag, Block, S);

  // Read end of statement
  if (Parser.getTok().isNot(AsmToken::EndOfStatement))
    return Error(Parser.getTok().getLoc(),
                 "unexpected token, expected end of statement");
  return false;
}



extern "C" void LLVMInitializeCodasipAsmParser() {
  RegisterMCAsmParser<CodasipAsmParser> X(TheCodasipTarget);
}
