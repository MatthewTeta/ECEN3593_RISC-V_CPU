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


#define DEBUG_TYPE "codasip-asm-printer"

#include "llvm/MC/MCSymbol.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/IR/Mangler.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Type.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/MC/MCInst.h"
#include "llvm/CodeGen/MachineConstantPool.h"

#include "Codasip.h"
#include "CodasipInstrInfo.h"
#include "CodasipTargetMachine.h"
#include "CodasipMachineFunction.h"
#include "InstPrinter/CodasipInstPrinter.h"
#include "MCTargetDesc/CodasipTargetStreamer.h"

#include <iostream>
#include <cstdio>

using namespace llvm;

extern cl::opt<bool> EnableAsmCompression;

class CodasipAsmPrinter: public AsmPrinter
{
public:
  explicit CodasipAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> MS);
  StringRef getPassName() const override {return "Codasip Assembly Printer";}
  void EmitStartOfAsmFile(Module &M) override;
  void EmitEndOfAsmFile(Module &M) override;
  void EmitFunctionBodyStart() override;
  void EmitFunctionEntryLabel() override;
  // We want to print all labels (for now).
  bool isBlockOnlyReachableByFallthrough(const MachineBasicBlock *MBB) const override;
private:
  void EmitInstruction(const MachineInstr *MI) override;
  bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNo, const char *ExtraCode, raw_ostream &O) override;
  bool PrintAsmMemoryOperand(const MachineInstr *MI, unsigned OpNo, const char *ExtraCode, raw_ostream &O) override;
  // auxs
  void PrintAsmRegOperand(const MachineOperand &MO, raw_ostream &O) const;
  void PrintAsmRegisterPair(const MachineInstr *MI, unsigned OpNo, raw_ostream &O) const;
  // for address space
  void EmitGlobalVariable(const GlobalVariable *GV) override;
  void EmitConstantPool() override;
  // for compressInst
  void EmitToStreamer(MCStreamer &S, const MCInst &Inst);
  /// Auxiliary
  void PrintInstruction(const MachineInstr *MI);
  // Lowering methods
  MCInst *LowerMachineInstr2MCInst(const MachineInstr *MI);
  MCOperand LowerMachineOperand2MCOp(const MachineOperand &MO, const MachineInstr &MI, unsigned opNum);
  const MCExpr *LowerSymbolOperand(const MachineOperand &MO, const MachineOperand::MachineOperandType MOTy, unsigned Offset);
  /// Does the current module have debug info?
  bool hasDebug;
  /// Context of a current machine function
  MCContext *Ctx;
  /// For convenience
  CodasipTargetStreamer *CStream;
};

extern "C" void LLVMInitializeCodasipAsmPrinter() {
  RegisterAsmPrinter<CodasipAsmPrinter> X(TheCodasipTarget);
}

CodasipAsmPrinter::CodasipAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> MS)
: AsmPrinter(TM,std::move(MS))
{
  Ctx = NULL;
  hasDebug = false;
  CStream = static_cast<CodasipTargetStreamer*>(OutStreamer->getTargetStreamer());
}

#define EMIT {OutStreamer->EmitRawText(O.str()); pbuf = "";}

void CodasipAsmPrinter::EmitInstruction(const MachineInstr *MI)
{
  // get bb and func
  const MachineBasicBlock *BB = MI->getParent();
  const MachineFunction *MF = BB->getParent();
  // set context
  Ctx = &(MF->getContext());
  // auxiliary buffer for printing
  SmallString<128> pbuf;
  raw_svector_ostream O(pbuf);
  // is this a beginning of a BB?
  const MachineInstr *front = NULL;
  for (MachineBasicBlock::const_iterator I=BB->begin(); front==NULL && I!=BB->end(); ++I)
  {
    if (!I->isDebugInstr())
    {
      front = &*I;
      break;
    }
  }
  // is this an ending of a BB?
  
  // actually print the instruction(s)
  PrintInstruction(MI);
}

const MCExpr *CodasipAsmPrinter::LowerSymbolOperand(const MachineOperand &MO, const MachineOperand::MachineOperandType MOTy, unsigned Offset)
{
  MCSymbolRefExpr::VariantKind Kind = MCSymbolRefExpr::VK_None;
  const MCSymbol *Symbol;
  switch (MOTy) {
  case MachineOperand::MO_MachineBasicBlock:
    Symbol = MO.getMBB()->getSymbol();
    break;
  case MachineOperand::MO_GlobalAddress:
    Symbol = getSymbol(MO.getGlobal());
    Offset += MO.getOffset();
    break;
  case MachineOperand::MO_MCSymbol:
    Symbol = MO.getMCSymbol();
    Offset += MO.getOffset();
    break;
  case MachineOperand::MO_BlockAddress:
    Symbol = GetBlockAddressSymbol(MO.getBlockAddress());
    Offset += MO.getOffset();
    break;
  case MachineOperand::MO_ExternalSymbol:
    Symbol = GetExternalSymbolSymbol(MO.getSymbolName());
    Offset += MO.getOffset();
    break;
  case MachineOperand::MO_JumpTableIndex:
    Symbol = GetJTISymbol(MO.getIndex());
    break;
  case MachineOperand::MO_ConstantPoolIndex:
    Symbol = GetCPISymbol(MO.getIndex());
    Offset += MO.getOffset();
    break;
  default:
    llvm_unreachable("<unknown operand type>");
  }
  const MCSymbolRefExpr *MCSym = MCSymbolRefExpr::create(Symbol, Kind, *Ctx);
  if (!Offset)
    return MCSym;
  // Assume offset is never negative.
  assert(Offset > 0);
  const MCConstantExpr *OffsetExpr =  MCConstantExpr::create(Offset, *Ctx);
  const MCBinaryExpr *Add = MCBinaryExpr::createAdd(MCSym, OffsetExpr, *Ctx);
  return Add;
}

MCOperand CodasipAsmPrinter::LowerMachineOperand2MCOp(const MachineOperand &MO, const MachineInstr &MI, unsigned opNum)
{
  const int offset = 0;
  MachineOperand::MachineOperandType MOTy = MO.getType();
  const MCExpr* Expr = nullptr;
  switch (MOTy) {
  default:
    llvm_unreachable("unknown operand type");
    break;
  case MachineOperand::MO_Register:
    // Ignore all implicit register operands.
    if (MO.isImplicit())
      return MCOperand();
    return MCOperand::createReg(MO.getReg());
  case MachineOperand::MO_Immediate:
    Expr = MCConstantExpr::create(MO.getImm(), *Ctx);
    break;
  case MachineOperand::MO_FPImmediate:
    return MCOperand::createFPImm(MO.getFPImm()->getValueAPF().bitcastToAPInt().getLimitedValue());
  case MachineOperand::MO_MachineBasicBlock:
  case MachineOperand::MO_GlobalAddress:
  case MachineOperand::MO_ExternalSymbol:
  case MachineOperand::MO_JumpTableIndex:
  case MachineOperand::MO_ConstantPoolIndex:
  case MachineOperand::MO_BlockAddress:
  case MachineOperand::MO_MCSymbol:
    Expr = LowerSymbolOperand(MO, MOTy, offset);
    break;
  case MachineOperand::MO_RegisterMask:
    return MCOperand();
  }
  assert(Expr != nullptr);
  // Apply compiler encoding by updating the existing expression
  const unsigned opc = MI.getOpcode();
  unsigned shift = 0;
  int64_t mask = 0;
  switch (opc) {
case Codasip::i_itype_alu__opc_addi__xpr_general__x_0__simm12__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_alu__opc_andi__xpr_general__xpr_general__simm12__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_alu__opc_ori__xpr_general__x_0__simm12__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_alu__opc_ori__xpr_general__xpr_general__simm12__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_alu__opc_slti__xpr_general__x_0__simm12__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_alu__opc_slti__xpr_general__xpr_general__simm12__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_alu__opc_sltiu__xpr_general__x_0__simm12__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_alu__opc_sltiu__xpr_general__xpr_general__simm12__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_alu__opc_xori__xpr_general__x_0__simm12__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_alu__opc_xori__xpr_general__xpr_general__simm12__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lb__x_0__simm12__x_0__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lb__x_0__simm12__xpr_general__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lbu__x_0__simm12__x_0__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lbu__x_0__simm12__xpr_general__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lh__x_0__simm12__x_0__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lh__x_0__simm12__xpr_general__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lhu__x_0__simm12__x_0__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lhu__x_0__simm12__xpr_general__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lw__x_0__simm12__x_0__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lw__x_0__simm12__xpr_general__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__x_0__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_rtype_shift__opc_slli__xpr_general__xpr_general__uimm5__:
  switch (opNum) {
  case 2: mask=31LLU; break;
  }
  break;
  case Codasip::i_rtype_shift__opc_srai__xpr_general__xpr_general__uimm5__:
  switch (opNum) {
  case 2: mask=31LLU; break;
  }
  break;
  case Codasip::i_rtype_shift__opc_srli__xpr_general__xpr_general__uimm5__:
  switch (opNum) {
  case 2: mask=31LLU; break;
  }
  break;
  case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_stype_store__opc_sb__xpr_general__simm12__x_0__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_stype_store__opc_sb__xpr_general__simm12__xpr_general__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_stype_store__opc_sh__xpr_general__simm12__x_0__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_stype_store__opc_sh__xpr_general__simm12__xpr_general__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_stype_store__opc_sw__x_0__simm12__x_0__:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_stype_store__opc_sw__x_0__simm12__xpr_general__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_stype_store__opc_sw__xpr_general__simm12__x_0__:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_utype_ops__opc_auipc__xpr_general__uimm20__:
  switch (opNum) {
  case 1: shift=12; mask=1048575LLU; break;
  }
  break;
  case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__:
  switch (opNum) {
  case 1: shift=12; mask=1048575LLU; break;
  }
  break;
  case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__x_0__AEXT_CLONE_:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lb__xpr_general__simm12__xpr_general__AEXT_CLONE_:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__x_0__AEXT_CLONE_:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lbu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__x_0__AEXT_CLONE_:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lh__xpr_general__simm12__xpr_general__AEXT_CLONE_:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__x_0__AEXT_CLONE_:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_itype_loads__opc_lhu__xpr_general__simm12__xpr_general__AEXT_CLONE_:
  switch (opNum) {
  case 2: break;
  }
  break;
  case Codasip::e_movi32__:
  switch (opNum) {
  case 1: mask=4294967295LLU; break;
  }
  break;
  case Codasip::i_stype_store__opc_sb__x_0__simm12__x_0__i32_TRUNC_CLONE_:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_stype_store__opc_sb__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_stype_store__opc_sh__x_0__simm12__x_0__i32_TRUNC_CLONE_:
  switch (opNum) {
  case 0: break;
  }
  break;
  case Codasip::i_stype_store__opc_sh__x_0__simm12__xpr_general__i32_TRUNC_CLONE_:
  switch (opNum) {
  case 1: break;
  }
  break;
  case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__1_BIGIMM_EMUL_:
  switch (opNum) {
  case 2: mask=4294967295LLU; break;
  }
  break;
  case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__3_BIGIMM_EMUL_:
  switch (opNum) {
  case 2: mask=4294967295LLU; break;
  }
  break;
  case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__4_BIGIMM_EMUL_:
  switch (opNum) {
  case 2: mask=4294967295LLU; break;
  }
  break;
  case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__5_BIGIMM_EMUL_:
  switch (opNum) {
  case 2: mask=4294967295LLU; break;
  }
  break;
  case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__6_BIGIMM_EMUL_:
  switch (opNum) {
  case 2: mask=4294967295LLU; break;
  }
  break;
  case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__7_BIGIMM_EMUL_:
  switch (opNum) {
  case 2: mask=4294967295LLU; break;
  }
  break;
  case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__8_BIGIMM_EMUL_:
  switch (opNum) {
  case 2: mask=4294967295LLU; break;
  }
  break;
  }
switch (opc) {
case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__1_:
switch (opNum) {
case 1: shift=12; mask=1048575LLU; break;
}
break;
case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__2_:
switch (opNum) {
case 1: mask=4095LLU; break;
}
break;
case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__5_:
switch (opNum) {
case 1: shift=12; mask=1048575LLU; break;
}
break;
case Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__6_:
switch (opNum) {
case 1: mask=4095LLU; break;
}
break;
}

  if (shift)
  {
      const MCExpr* aux = MCConstantExpr::create(shift, *Ctx);
      Expr = MCBinaryExpr::createLShr(Expr, aux, *Ctx);
  }
  if (mask)
  {
      const MCExpr* aux = MCConstantExpr::create(mask, *Ctx);
      Expr = MCBinaryExpr::createAnd(Expr, aux, *Ctx);
  }
  return MCOperand::createExpr(Expr);
}

MCInst *CodasipAsmPrinter::LowerMachineInstr2MCInst(const MachineInstr *MI)
{
  MCInst *OutMI = new (*Ctx) MCInst;
  OutMI->setOpcode(MI->getOpcode());
  for (unsigned i=0, e=MI->getNumOperands(); i != e; ++i)
  {
    const MachineOperand &MO = MI->getOperand(i);
    MCOperand MCOp = LowerMachineOperand2MCOp(MO, *MI, i);
    if (MCOp.isValid())
      OutMI->addOperand(MCOp);
  }
  return OutMI;
}

void CodasipAsmPrinter::PrintInstruction(const MachineInstr *MI)
{
  // vliw bundle - obsolete
  const MCInstrInfo &MCII = *TM.getMCInstrInfo();
  
  
  // a lone instruction
  if (!MI->isBundle()) {
    // call instr printer
    MCInst *tmpInst = LowerMachineInstr2MCInst(MI);
    const MCInstrDesc &IDesc = MCII.get(tmpInst->getOpcode());
    // handle pseudo inst
    if (IDesc.isPseudo()) {
      std::string s;
      raw_string_ostream ss(s);
      CodasipInstPrinter Printer(*TM.getMCAsmInfo(), MCII, *TM.getMCRegisterInfo());
      Printer.printInst(tmpInst, ss, "", *TM.getMCSubtargetInfo());
      EmitInlineAsm(ss.str(), *TM.getMCSubtargetInfo(), TM.Options.MCOptions);
    } else
      EmitToStreamer(*OutStreamer, *tmpInst);
  }
  
}

void CodasipAsmPrinter::PrintAsmRegisterPair(const MachineInstr *MI, unsigned opNum, raw_ostream &O) const
{
  const MachineOperand &MO1 = MI->getOperand(opNum);
  // the other half is the next one
  assert(opNum+1 <= MI->getNumOperands());
  const MachineOperand &MO2 = MI->getOperand(opNum+1);
  if (!(MO1.isReg() && MO2.isReg()))
  {
    const char* msg = "faulty usage of the 'p' modifier";
    // fixme: this prints faulty line!
    // todo: do soner? (e.g. in IsCodasipInlineAsmWithP)
    MI->emitError(msg);
    abort();
  }
  // find a suitable super-reg
  const MCRegisterInfo* RI = TM.getMCRegisterInfo();
  const unsigned reg1 = MO1.getReg();
  const unsigned reg2 = MO2.getReg();
  // - this should be assured by register allocation
  assert(reg1+1 == reg2 && "faulty 'p' usage");
  unsigned super = 0;
  for (unsigned r=0; r < RI->getNumRegs(); ++r)
  {
    // using 'p' is user's responsibility
    if (RI->isSubRegister(r,reg1) && RI->isSubRegister(r,reg2))
    {
      // note: do more checks?
      super = r;
      break;
    }
  }
  assert(super && "failed to find a super-register for 'p' modifier");
  // print the super
  O << CodasipInstPrinter::getRegisterName(super,Codasip::NoRegAltName);
}

void CodasipAsmPrinter::PrintAsmRegOperand(const MachineOperand &MO, raw_ostream &O) const
{
  assert(MO.isReg());
  const unsigned reg = MO.getReg();
  O << CodasipInstPrinter::getRegisterName(reg,Codasip::NoRegAltName);
}

// for inline asm
bool CodasipAsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned opNum, const char *ExtraCode, raw_ostream &O)
{
  // Does this asm operand have a single letter operand modifier?
  if (ExtraCode && ExtraCode[0])
  {
    assert(ExtraCode[1]==0);
    // Codasip custom
    if (ExtraCode[0]=='p')
    {
      PrintAsmRegisterPair(MI, opNum, O);
      return false;
    }
    // unknown or standard modifier
    return AsmPrinter::PrintAsmOperand(MI,opNum,ExtraCode,O);
  }
  // no modifier, just an operand
  // - printing same-ish as AsmPrinter::PrintAsmOperand
  const MachineOperand &MO = MI->getOperand(opNum);
  // imm
  if (MO.isImm())
  {
    O << MO.getImm();
  }
  // global
  else if (MO.isGlobal())
  {
    PrintSymbolOperand(MO, O);
  }
  // reg
  else
  {
    PrintAsmRegOperand(MO, O);
  }
  return false;
}

bool CodasipAsmPrinter::PrintAsmMemoryOperand(const MachineInstr *MI, unsigned OpNo, const char *ExtraCode, raw_ostream &O)
{
  // avoid infinite loop (see AsmPrinter::PrintAsmOperand)
  const MachineOperand &MO = MI->getOperand(OpNo);
  if (MO.isReg() && ExtraCode==nullptr)
  {
    PrintAsmRegOperand(MO, O);
    return false;
  }
  return PrintAsmOperand(MI,OpNo,ExtraCode,O);
}

// if there are only global varibles and no functions, no section is printed :(
void CodasipAsmPrinter::EmitStartOfAsmFile(Module &M)
{
  //OutStreamer.EmitRawText(StringRef("  .data")); - no longer needed
  // search for debug info
  hasDebug = false;
  // -find a non-empty func
  for (Module::iterator i1=M.begin(); i1!=M.end(); ++i1)
  {
    // find a non-empty bb
    for (Function::iterator i2=i1->begin(); i2!=i1->end(); ++i2)
    {
      // look at the instructions
      for (BasicBlock::iterator i3=i2->begin(); i3!=i2->end(); ++i3)
      {
        const DebugLoc &dl = i3->getDebugLoc();
        if (dl) {
          hasDebug = true;
          return;
        }
      }
    }
  }
}

// print dwarf info
void CodasipAsmPrinter::EmitEndOfAsmFile(Module &M)
{
}

void CodasipAsmPrinter::EmitFunctionEntryLabel()
{
  // print alignment, if set
  
  AsmPrinter::EmitFunctionEntryLabel();
}

// print vararg metainfo
void CodasipAsmPrinter::EmitFunctionBodyStart()
{
  // cfi - return address
  
  OutStreamer->EmitCFIReturnColumn(1);
  
}

// The default behaviour was causing problems on -O0 so it needs to be overwritten
bool CodasipAsmPrinter::isBlockOnlyReachableByFallthrough(const MachineBasicBlock *MBB) const
{
  return false;
}

void CodasipAsmPrinter::EmitGlobalVariable(const GlobalVariable *GV)
{
  // note1: this directive is printed in front of every kind of GV
  //        (=> if it causes SwitchSection then the directives will be in this order: AS, Switch, GV itself)
  //      - there were some exceptions in AsmPrinter::EmitGlobalVariable
  //        but I don't think they were intended
  // note2: zero-fill is not checked here (Codasip does not support address spaces with those)
  // note3: address space needs to be printed always
  CStream->emitDirectiveAddressSpace(GV->getType()->getAddressSpace(), SMLoc());
  AsmPrinter::EmitGlobalVariable(GV);
}


// Taken from AsmPrinter.cpp and edited (changes marked)
// Unfortunately, it needs to be this way (I can't just add something and then call parent method)
namespace {
// Keep track the alignment, constpool entries per Section.
  struct SectionCPs {
    MCSection *S;
    unsigned Alignment;
    //=== CODASIP ===
    unsigned AddressSpace;
    //===============
    SmallVector<unsigned, 4> CPEs;
    //=== CODASIP ===
    // Added parameter
    SectionCPs(MCSection *s, unsigned a, unsigned AS) : S(s), Alignment(a), AddressSpace(AS) {}
  };
}

/// EmitConstantPool - Print to the current output stream assembly
/// representations of the constants in the constant pool MCP. This is
/// used to print out constants which have been "spilled to memory" by
/// the code generator.
///
void CodasipAsmPrinter::EmitConstantPool() {
  const MachineConstantPool *MCP = MF->getConstantPool();
  const std::vector<MachineConstantPoolEntry> &CP = MCP->getConstants();
  if (CP.empty()) return;

  // Calculate sections for constant pool entries. We collect entries to go into
  // the same section together to reduce amount of section switch statements.
  SmallVector<SectionCPs, 4> CPSections;
  for (unsigned i = 0, e = CP.size(); i != e; ++i) {
    const MachineConstantPoolEntry &CPE = CP[i];
    unsigned Align = CPE.getAlignment();

    SectionKind Kind = CPE.getSectionKind(&getDataLayout());

    const Constant *C = nullptr;
    if (!CPE.isMachineConstantPoolEntry())
      C = CPE.Val.ConstVal;

    MCSection *S = getObjFileLowering().getSectionForConstant(getDataLayout(),
                                                              Kind, C, Align);
    //=== CODASIP ===
    unsigned currAS = GetSpace4Vt(EVT::getEVT(CPE.getType(), true));
    //===============

    // The number of sections are small, just do a linear search from the
    // last section to the first.
    bool Found = false;
    unsigned SecIdx = CPSections.size();
    while (SecIdx != 0) {
      //=== CODASIP ===
      // Added the second part of the condition
      if (CPSections[--SecIdx].S == S && CPSections[SecIdx].AddressSpace == currAS) {
        Found = true;
        break;
      }
    }
    if (!Found) {
      SecIdx = CPSections.size();
      //=== CODASIP ===
      // Added parameter
      CPSections.push_back(SectionCPs(S, Align, currAS));
    }

    if (Align > CPSections[SecIdx].Alignment)
      CPSections[SecIdx].Alignment = Align;
    CPSections[SecIdx].CPEs.push_back(i);
  }

  // Now print stuff into the calculated sections.
  const MCSection *CurSection = nullptr;
  unsigned CurSectionAS = 0;
  unsigned Offset = 0;
  for (unsigned i = 0, e = CPSections.size(); i != e; ++i) {
    for (unsigned j = 0, ee = CPSections[i].CPEs.size(); j != ee; ++j) {
      unsigned CPI = CPSections[i].CPEs[j];
      MCSymbol *Sym = GetCPISymbol(CPI);
      if (!Sym->isUndefined())
        continue;

      if (CurSection != CPSections[i].S || CurSectionAS != CPSections[i].AddressSpace) {
        OutStreamer->SwitchSection(CPSections[i].S);
        // like in EmitGlobalVariable
        CStream->emitDirectiveAddressSpace(CPSections[i].AddressSpace, SMLoc());
        EmitAlignment(Log2_32(CPSections[i].Alignment));
        CurSection = CPSections[i].S;
        CurSectionAS = CPSections[i].AddressSpace;
        Offset = 0;
      }

      MachineConstantPoolEntry CPE = CP[CPI];

      // Emit inter-object padding for alignment.
      unsigned AlignMask = CPE.getAlignment() - 1;
      unsigned NewOffset = (Offset + AlignMask) & ~AlignMask;
      OutStreamer->EmitZeros(NewOffset - Offset);

      Type *Ty = CPE.getType();
      Offset = NewOffset + getDataLayout().getTypeAllocSize(Ty);

      OutStreamer->EmitLabel(Sym);
      if (CPE.isMachineConstantPoolEntry())
        EmitMachineConstantPoolValue(CPE.Val.MachineCPVal);
      else
        EmitGlobalConstant(getDataLayout(), CPE.Val.ConstVal);
    }
  }
}

#include "CodasipCompressInst.inc"

void CodasipAsmPrinter::EmitToStreamer(MCStreamer &S, const MCInst &Inst) {
  MCInst CInst;
  bool Res = false;
  if (EnableAsmCompression && TM.getMCSubtargetInfo()->hasFeature(Codasip::FeatureStdExtC))
    Res = compressInst(CInst, Inst, *TM.getMCSubtargetInfo(),
                       OutStreamer->getContext());
  AsmPrinter::EmitToStreamer(*OutStreamer, Res ? CInst : Inst);
}