//===-- NVPTXMCExpr.cpp - NVPTX specific MC expression classes ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/MC/MCContext.h"

#include "CodasipMCExpr.h"

using namespace llvm;

#define DEBUG_TYPE "codasip-mcexpr"

const CodasipTernaryMCExpr *CodasipTernaryMCExpr::create(const MCExpr *Condition,
                                                         const MCExpr *True,
                                                         const MCExpr *False,
                                                         MCContext &Ctx) {
  return new (Ctx) CodasipTernaryMCExpr(Condition, True, False);
}

void CodasipTernaryMCExpr::printImpl(raw_ostream &OS,
                                     const MCAsmInfo *MAI) const {
  getCondition().print(OS, MAI);
  OS << " ? ";
  getTrue().print(OS, MAI);
  OS << " : ";
  getFalse().print(OS, MAI);
}

bool CodasipTernaryMCExpr::evaluateAsRelocatableImpl(MCValue &Res,
                               const MCAsmLayout *Layout,
                               const MCFixup *Fixup) const {
  // Evaluate condition
  int64_t ConditionValue = 0;
  bool Absolute = getCondition().evaluateAsAbsolute(ConditionValue, *Layout);

  // Condition is not absolute
  if (!Absolute)
    return getCondition().evaluateAsRelocatable(Res, Layout, Fixup);

  // Evaluate branch based on condition value
  return ConditionValue
    ? getTrue().evaluateAsRelocatable(Res, Layout, Fixup)
    : getFalse().evaluateAsRelocatable(Res, Layout, Fixup);
}

bool CodasipTernaryMCExpr::hasMask() const {
  return getCondition().hasMask() || getTrue().hasMask() || getFalse().hasMask();
}
