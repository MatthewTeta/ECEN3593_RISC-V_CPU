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


// This file contains the entry points for global functions
// defined in the Codasip target library.

#ifndef TARGET_CODASIP_H
#define TARGET_CODASIP_H

#include "llvm/Target/TargetMachine.h"

#include <cstdint>
#include <string>

#define STACK_COUNT 1

namespace llvm {

class CodasipTargetMachine;
class FunctionPass;
class formatted_raw_ostream;
class MCExpr;
class MCInst;
class SMLoc;
class SourceMgr;
class Target;

// different types of passes of CodasipSmallerInstructionOptimization
enum CodasipSmallerInsPassType {OnlyEmul, OnlyJump, NormalInst, LtoJump};

FunctionPass* createCodasipISelDag(CodasipTargetMachine& tm);
FunctionPass* createCodasipNoopAdderPass(CodasipTargetMachine& tm);
FunctionPass* createCodasipJumpLengthCheckerPass(CodasipTargetMachine& tm);
FunctionPass* createCodasipCleanUpBundle();
FunctionPass* createCodasipPacketizer();
FunctionPass* createCodasipVliwNoopAdderPass(CodasipTargetMachine& tm);
FunctionPass* createCodasipCallCompletionPass(CodasipTargetMachine& tm);
FunctionPass* createCodasipMoiOptimPass(CodasipTargetMachine& tm);
FunctionPass* createCodasipSequencerPass(CodasipTargetMachine& tm);
FunctionPass* createCodasipMipsDelaySlotFillerPass();
FunctionPass* createCodasipSmallerInstructionsPass(CodasipTargetMachine& tm, CodasipSmallerInsPassType order);
FunctionPass* createCodasipPostRAPeepholePass(CodasipTargetMachine& tm);
FunctionPass* createCodasipPreRAPeepholePass(CodasipTargetMachine& tm);
FunctionPass* createCodasipCfiAdder(CodasipTargetMachine& tm);
FunctionPass* createCodasipDoubleJumpPass(CodasipTargetMachine& tm);
FunctionPass* createCodasipPropagateBuiltinConstantsPass(CodasipTargetMachine& tm);
FunctionPass* createCodasipInlineAsmRegPairsPass(CodasipTargetMachine& tm);
FunctionPass* createCodasipInlineAsmFastRegAlloc(CodasipTargetMachine& tm);

extern Target TheCodasipTarget;

void printLocation(const SMLoc Loc, const SourceMgr *SM);
void checkTruncationOverflow(const uint64_t Value,
                             const unsigned BitWidth,
                             const bool Signed,
                             const bool Masked,
                             const SMLoc Loc,
                             const SourceMgr *SM);
int codasip_fatal(uint32_t ExitCode, const char *Format, ...);
int64_t getAttributeValue(const MCInst &MI, const std::string &AttributeId, const SourceMgr *SM);

unsigned getLongJumpOpcodeStatic();

}

#endif
