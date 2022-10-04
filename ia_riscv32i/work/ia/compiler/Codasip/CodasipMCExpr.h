//===-- NVPTXMCExpr.h - NVPTX specific MC expression classes ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Modeled after ARMMCExpr

#ifndef LLVM_LIB_TARGET_CODASIP_CODASIPMCEXPR_H
#define LLVM_LIB_TARGET_CODASIP_CODASIPMCEXPR_H

#include "llvm/MC/MCExpr.h"

namespace llvm {

class CodasipTernaryMCExpr : public MCTargetExpr {
private:
  explicit CodasipTernaryMCExpr(const MCExpr *Condition,
                                const MCExpr *True,
                                const MCExpr *False)
      : Condition(Condition), True(True), False(False) {}

  /// Condition expression
  const MCExpr *Condition;
  /// True branch
  const MCExpr *True;
  /// False branch
  const MCExpr *False;

public:
  /// @name Construction
  /// @{

  static const CodasipTernaryMCExpr *create(const MCExpr *Condition,
                                            const MCExpr *True,
                                            const MCExpr *False,
                                            MCContext &Ctx);

  /// @}
  /// @name Accessors
  /// @{

  /// Get the condition of ternary expression.
  const MCExpr &getCondition() const { return *Condition; }
  /// Get the true branch of ternary expression.
  const MCExpr &getTrue() const { return *True; }
  /// Get the false branch of ternary expression.
  const MCExpr &getFalse() const { return *False; }

  /// @}

  void printImpl(raw_ostream &OS, const MCAsmInfo *MAI) const override;
  bool evaluateAsRelocatableImpl(MCValue &Res,
                                 const MCAsmLayout *Layout,
                                 const MCFixup *Fixup) const override;
  bool hasMask() const override;
  void visitUsedExpr(MCStreamer &Streamer) const override {};
  MCFragment *findAssociatedFragment() const override { return nullptr; }

  // There are no TLS CodasipExprs at the moment.
  void fixELFSymbolsInTLSFixups(MCAssembler &) const override {}

  static bool classof(const MCExpr *E) {
    return E->getKind() == MCExpr::Target;
  }
};

} // end namespace llvm

#endif
