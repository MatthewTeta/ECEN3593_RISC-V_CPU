#ifndef CODASIPELFOBJECTWRITER_H
#define CODASIPELFOBJECTWRITER_H

#include "llvm/MC/MCELFObjectWriter.h"

namespace llvm {

class MCContext;
class MCValue;
class MCFixup;
class raw_ostream;

class CodasipELFObjectWriter : public MCELFObjectTargetWriter {

public:
  CodasipELFObjectWriter(uint8_t OSABI);

  ~CodasipELFObjectWriter() override;

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel,
                        const MCSectionELF &Section) const override;
  void createRelocationExpressionTable(raw_ostream &OS) const override;
};

} // namespace llvm

#endif
