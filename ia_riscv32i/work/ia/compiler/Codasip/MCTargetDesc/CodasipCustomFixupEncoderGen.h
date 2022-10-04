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
 * \author  Codasip (c) Assembler generator
 * \version 9.1.1-1255
 * \brief   Source for assembler
 * \project MI11ia_riscv32i
 */
#ifndef CODASIPCUSTOMFIXUPENCODERGEN_3_H_
#define CODASIPCUSTOMFIXUPENCODERGEN_3_H_

#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCSubtargetInfo.h"

namespace llvm {

/**
 *  \class  CodasipCustomFixupEncoderGen
 *  \brief  This class is automatically generated, editing it is not advisable
 */
class CodasipCustomFixupEncoderGen  {
protected:
    MCContext& Ctx;
public:
    /**
     *  \brief  CodasipCustomFixupEncoderGen
     */
    CodasipCustomFixupEncoderGen(MCContext& Ctx);
    /**
     *  \brief  ~CodasipCustomFixupEncoderGen
     */
    virtual ~CodasipCustomFixupEncoderGen();
    /**
     *  \brief  customEncodeMI5valueIH1_13default_start7_5uimm53imm1_5uimm5
     */
    virtual bool customEncodeMI5valueIH1_13default_start7_5uimm53imm1_5uimm5(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const ;
    /**
     *  \brief  customEncodeMI5valueIH1_13default_start8_6simm124simm1_6simm12
     */
    virtual bool customEncodeMI5valueIH1_13default_start8_6simm124simm1_6simm12(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const ;
    /**
     *  \brief  customEncodeMI5valueIH1_13default_start8_6uimm203imm1_6uimm20
     */
    virtual bool customEncodeMI5valueIH1_13default_start8_6uimm203imm1_6uimm20(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const ;
    /**
     *  \brief  customEncodeMI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12
     */
    virtual bool customEncodeMI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const ;
    /**
     *  \brief  customEncodeMI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12
     */
    virtual bool customEncodeMI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const ;
    /**
     *  \brief  customEncodeMI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20
     */
    virtual bool customEncodeMI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const ;
};
} // namespace llvm

#endif // CODASIPCUSTOMFIXUPENCODERGEN_3_H_
