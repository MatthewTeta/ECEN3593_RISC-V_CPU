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
#ifndef CODASIPASMPARSERHOOKSGEN_5_H_
#define CODASIPASMPARSERHOOKSGEN_5_H_

namespace llvm {
class MCInst;
class MCStreamer;
class MCSubtargetInfo;
class SMLoc;
}

namespace llvm {

/**
 *  \class  CodasipAsmParserHooksGen
 *  \brief  This class is automatically generated, editing it is not advisable
 */
class CodasipAsmParserHooksGen  {
protected:
    const MCSubtargetInfo* m_STI;
public:
    /**
     *  \brief  ~CodasipAsmParserHooksGen
     */
    virtual ~CodasipAsmParserHooksGen();
protected:
    const MCSubtargetInfo& getSTI() const ;
public:
    /**
     *  \brief  ProcessInstruction
     */
    virtual void ProcessInstruction(MCInst &Inst, SMLoc IDLoc, MCStreamer &Out, const MCSubtargetInfo &STI);
    /**
     *  \brief  CodasipAsmParserHooksGen
     */
    CodasipAsmParserHooksGen();
};
/**
 *  \brief  getSTI
 */
inline const MCSubtargetInfo& CodasipAsmParserHooksGen::getSTI() const 
{
    return *m_STI;
}
} // namespace llvm

#endif // CODASIPASMPARSERHOOKSGEN_5_H_
