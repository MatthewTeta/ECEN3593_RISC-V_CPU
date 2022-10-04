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
#include "CodasipCustomFixupEncoderGen.h"

namespace llvm {

CodasipCustomFixupEncoderGen::CodasipCustomFixupEncoderGen(MCContext& Ctx)
 :  Ctx(Ctx)
{

}
CodasipCustomFixupEncoderGen::~CodasipCustomFixupEncoderGen()
{

}
bool CodasipCustomFixupEncoderGen::customEncodeMI5valueIH1_13default_start7_5uimm53imm1_5uimm5(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const 
{
    // No custom fixup was created
    return false;
}
bool CodasipCustomFixupEncoderGen::customEncodeMI5valueIH1_13default_start8_6simm124simm1_6simm12(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const 
{
    // No custom fixup was created
    return false;
}
bool CodasipCustomFixupEncoderGen::customEncodeMI5valueIH1_13default_start8_6uimm203imm1_6uimm20(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const 
{
    // No custom fixup was created
    return false;
}
bool CodasipCustomFixupEncoderGen::customEncodeMI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const 
{
    // No custom fixup was created
    return false;
}
bool CodasipCustomFixupEncoderGen::customEncodeMI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const 
{
    // No custom fixup was created
    return false;
}
bool CodasipCustomFixupEncoderGen::customEncodeMI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo& STI) const 
{
    // No custom fixup was created
    return false;
}
} // namespace llvm
