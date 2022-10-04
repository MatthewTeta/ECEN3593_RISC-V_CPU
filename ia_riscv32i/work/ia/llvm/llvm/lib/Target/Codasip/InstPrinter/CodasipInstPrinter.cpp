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


#include "CodasipInstPrinter.h"
#include "CodasipInstrInfo.h"

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/raw_ostream.h"

#include <utility>
#include <cstdio>

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#define GET_INSTRUCTION_NAME
#define PRINT_ALIAS_INSTR
#include "CodasipGenAsmWriter.inc"

CodasipInstPrinter::CodasipInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII, const MCRegisterInfo &MRI)
: MCInstPrinter(MAI,MII,MRI) {}

void CodasipInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const
{
  OS << getRegisterName(RegNo,Codasip::NoRegAltName);
}

// pref/suf data
typedef std::pair<const char*, const char*> SlotSyntax;
// Gets slots syntax based on a first slot and size of a (super)slot
inline static SlotSyntax GetSlotSyntax(const SlotData::value_type &slots)
{
  
  llvm_unreachable("unknown slot syntax");
  return SlotSyntax(0,0);
}

/// mask of slot coverage
class SlotMask: public std::vector<bool>
{
public:
  /// Construct clear mask
  SlotMask(unsigned size): std::vector<bool>(size,false) {}
  /// Detects first unset slot
  unsigned GetFirstFree() const
  {
    for (unsigned i=0; i<size(); ++i)
    {
      if (!at(i)) {
        return i;
      }
    }
    return size();
  }
};

static SlotSyntax GetBundleSyntax(SlotMask &slots, const MCOperand &MO)
{
  SlotSyntax syntax(0,0);
  // current slot
  unsigned S = slots.GetFirstFree();
  if (S>=SLOTS)
  {
    return syntax;
  }
  // the actual instruction
  assert(MO.isInst());
  const MCInst &MI = *MO.getInst();
  // get possible slots
  SlotData vars;
  CodasipInstrInfo::getAllPosInBundleImpl(MI.getOpcode(),vars);
  // bad?
  if (vars.empty())
  {
    return syntax;
  }
  // select the proper one (error otherwise)
  for (unsigned j=0; j<vars.size(); ++j)
  {
    // match?
    if (vars[j][0]==S)
    {
      // get pref/suf
      syntax = GetSlotSyntax(vars[j]);
      // set bits in the mask
      for (unsigned k=0; k<vars[j].size(); ++k)
      {
        const unsigned index = vars[j][k];
        assert(index < SLOTS);
        assert(!slots[index]);
        slots[index] = true;
      }
    }
  }
  return syntax;
}

// same as PrintBundle but without printing
bool CodasipInstPrinter::CheckBundle(const MCInst *bundle)
{
  // a mask of covered slots
  SlotMask slots(SLOTS);
  // print all items
  for (unsigned i=0; i<bundle->getNumOperands(); ++i)
  {
    // get syntax
    SlotSyntax syntax = GetBundleSyntax(slots, bundle->getOperand(i));
    // check
    if (!(syntax.first && syntax.second))
    {
      // bad
      return false;
    }
  }
  // all ok
  return true;
}

/* (Abbreviated) description of algorithm (for (super)slot printing):
 * For each bundle (assumes correct bundling):
 * 1. Start at slot 0 and at first instruction
 * 2. Take all possible first slots for the current instruction
 *    and choose the one equal to the current slot (for syntax printing)
 * 3. Shift to next (free) slot
 * 4. Go back to 2, unless at the end of bundle */
void CodasipInstPrinter::PrintBundle(const MCInst *bundle, raw_ostream &O)
{
  // a mask of covered slots
  SlotMask slots(SLOTS);
  // print all items
  for (unsigned i=0; i<bundle->getNumOperands(); ++i)
  {
    // get syntax
    SlotSyntax syntax = GetBundleSyntax(slots, bundle->getOperand(i));
    // this is prechecked
    assert(syntax.first && syntax.second);
    // print
    O << syntax.first;
    printInstruction(bundle->getOperand(i).getInst(), O);
    O << syntax.second;
  }
}

void CodasipInstPrinter::printInst(const MCInst *MI, raw_ostream &O, StringRef Annot, const MCSubtargetInfo &)
{
  if (MI->getOpcode() == TargetOpcode::BUNDLE) {
    printAnnotation(O, Annot);
    PrintBundle(MI, O);
    return;
  }
  if (!printAliasInstr(MI, O))
    printInstruction(MI, O);
  printAnnotation(O, Annot);
}

#define SHIFT_FLAG 0x1
#define MASK_FLAG  0x2

static unsigned GetAltNameIndex(int reg, int rc)
{
  switch (reg)
  {
    case Codasip::rf_xpr_0:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_1:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_2:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_3:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_4:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_5:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_6:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_7:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_8:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_9:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_10:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_11:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_12:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_13:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_14:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_15:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_16:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_17:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_18:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_19:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_20:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_21:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_22:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_23:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_24:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_25:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_26:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_27:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_28:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_29:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_30:
return Codasip::NoRegAltName;
case Codasip::rf_xpr_31:
return Codasip::NoRegAltName;

    default:
      llvm_unreachable("unknown register");
  }
  return Codasip::NoRegAltName;
}

void CodasipInstPrinter::printOperand(const MCInst* MI, unsigned opNum, raw_ostream& O)
{
  const unsigned code = MI->getOpcode();
  const MCInstrDesc& desc = MII.get(code);
  assert(opNum < desc.getNumOperands());
  const MCOperand& MO = MI->getOperand(opNum);
  const MCOperandInfo& opInfo = desc.OpInfo[opNum];
  // print
  if (MO.isReg()) {
    const unsigned altIndex = GetAltNameIndex(MO.getReg(), opInfo.RegClass);
    O << getRegisterName(MO.getReg(),altIndex);
  } else if (MO.isImm())
    O << formatHex(MO.getImm());
  else if (MO.isFPImm())
    O << MO.getFPImm();
  else {
    assert(MO.isExpr() && "unknown operand kind in printOperand");
    MO.getExpr()->print(O,nullptr);
  }
}
