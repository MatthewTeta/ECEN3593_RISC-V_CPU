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


#include "Codasip.h"
#include "CodasipTargetMachine.h"
#include "codasip/Target/CodasipPrePostRAPeephole.h"
#include "codasip/Target/CodasipBasePeephole.h"

using namespace llvm;

static cl::list<std::string> disabledPeepholes("disable-codasip-peephole",
          cl::desc("Disables specified peephole patterns. Patterns are specified by their names separated by comma."),
          cl::value_desc("patterns"), cl::CommaSeparated, cl::ValueRequired);

namespace {

typedef std::map<unsigned, std::vector<unsigned> > CodeMap;

void addEqualMaps(CodeMap &EqualInstructions)
{
EqualInstructions[Codasip::i_call_alias__relative_addr20__] = {Codasip::i_call_alias__relative_addr20__, Codasip::i_call_alias__relative_addr20__ES, Codasip::i_call_alias__relative_addr20__MC, Codasip::i_call_alias__relative_addr20__BA, };
EqualInstructions[Codasip::i_call_reg_alias__simm12__x_0__] = {Codasip::i_call_reg_alias__simm12__x_0__, Codasip::i_call_reg_alias__simm12__x_0__ES, Codasip::i_call_reg_alias__simm12__x_0__MC, Codasip::i_call_reg_alias__simm12__x_0__BA, };
EqualInstructions[Codasip::e_movi32__] = {Codasip::e_movi32__, Codasip::e_movi32__GA, Codasip::e_movi32__ES, Codasip::e_movi32__MC, Codasip::e_movi32__BA, Codasip::e_movi32__JT, Codasip::e_movi32__CP, };
EqualInstructions[Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_] = {Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_, Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES, Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC, Codasip::i_jal_abs_calias__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA, };
EqualInstructions[Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_] = {Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_, Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_ES, Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_MC, Codasip::i_jtype_jlink__opc_jal__x_0__relative_addr20__TAILCALL_CLONE_BA, };
EqualInstructions[Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_] = {Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_, Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES, Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC, Codasip::i_btype_branches__opc_beq__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA, };
EqualInstructions[Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_] = {Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_, Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES, Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC, Codasip::i_btype_branches__opc_bge__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA, };
EqualInstructions[Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_] = {Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_, Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_ES, Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_MC, Codasip::i_btype_branches__opc_bgeu__x_0__x_0__relative_addr12__TAILCALL_CLONE_BA, };
EqualInstructions[Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_] = {Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_, Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_ES, Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_MC, Codasip::i_itype_jlreg__opc_jalr__x_0__simm12__x_0__TAILCALL_CLONE_BA, };
std::vector<unsigned>* data;
(void)data;
data = &(EqualInstructions[Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__]);
data->insert(data->end(), {Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__1_, Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__2_, Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__5_, Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__SYNTAX_CLONE_e_movi32__6_, });

}

// Using global variable to print warning only once.
// Not using global variable would require changing interface of
// pass constructors and createCodasipPre/PostRAPeepholePass
// methods all the way up to CodasipGenPAssConfig.cpp and Codasip.h
static bool printWarning = true;

// remove pattern from vector and delete it
static void removePattern(SmallVectorImpl<Pattern *> &patterns) {
  // disabling patterns
  for (auto &name : disabledPeepholes) {
    bool foundPattern = false;
    for (auto pattIt = patterns.begin(); pattIt != patterns.end();) {
      if (name.compare((*pattIt)->getName()) != 0) {
        ++pattIt;
        continue;
      }
      foundPattern = true;
      const auto &b = llvm::find(patterns, *pattIt);
      delete *b;
      pattIt = patterns.erase(b);
    }
    if (!foundPattern && printWarning) {
      errs() << "Warning: Peephole pattern " << name << " does not exist! \n";
    }
  }
  printWarning = false;
}

static bool getCheckImmOperandValue(const MachineOperand &mo,
                                    int64_t &result,
                                    LTOFileInfo *LtoFile) {
  const MachineFunction *mf = mo.getParent()->getParent()->getParent();
  if (mo.isImm()) {
    result = mo.getImm();
    return true;
  }
  return LtoFile->getSymbolAddress(&mo, mf, result);
}


struct CodasipPreRAPeephole : public PreRAPeephole
{
  CodasipPreRAPeephole() = default;
  CodasipPreRAPeephole(CodasipTargetMachine &tm);
  StringRef getPassName() const { return "Codasip Peephole preRA"; }
  static char ID;  
};

struct CodasipPostRAPeephole : public PostRAPeephole
{
  CodasipPostRAPeephole() = default;
  CodasipPostRAPeephole(CodasipTargetMachine &tm);
  StringRef getPassName() const { return "Codasip Peephole postRA"; }
  static char ID;  
};

} // end of anonymous namespace

char CodasipPreRAPeephole::ID = 0;
static RegisterPass<CodasipPreRAPeephole> X("codasip-peephole-preRA", "Codasip Peephole preRA ", false, false);

CodasipPreRAPeephole::CodasipPreRAPeephole(CodasipTargetMachine &tm)
: PreRAPeephole(tm, tm.getInstrInfo(), tm.getRegisterInfo(), ID)
{
  addEqualMaps(EqualInstructions);
  // fill vector
  
  // disabling patterns
  removePattern(VectorOfPatterns);
}

// create the pass
FunctionPass* llvm::createCodasipPreRAPeepholePass(CodasipTargetMachine &tm)
{
  return new CodasipPreRAPeephole(tm);
}

char CodasipPostRAPeephole::ID = 0;
static RegisterPass<CodasipPostRAPeephole> Y("codasip-peephole-postRA", "Codasip Peephole postRA ", false, false);

CodasipPostRAPeephole::CodasipPostRAPeephole(CodasipTargetMachine &tm)
: PostRAPeephole(tm, tm.getInstrInfo(), tm.getRegisterInfo(), ID)
{
  addEqualMaps(EqualInstructions);
  // fill vector
  
  // disabling patterns
  removePattern(VectorOfPatterns);
}

// create the pass
FunctionPass* llvm::createCodasipPostRAPeepholePass(CodasipTargetMachine &tm)
{
  return new CodasipPostRAPeephole(tm);
}

