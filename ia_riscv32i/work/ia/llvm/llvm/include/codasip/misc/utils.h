/**************************************************************************************************
 *                     Copyright (c) 2014  Codasip, Ltd. All Rights Reserved. *
 **************************************************************************************************/
/**
 *  \file
 *  \author jan
 *  \date   30 Oct 2014
 *  \brief  Declaration/Implementation of the class.
 */
#ifndef CODASIP_LLVM_UTILS_H_
#define CODASIP_LLVM_UTILS_H_

#include "codasip/Target/CodasipBaseTargetInstrInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/MC/MCAsmInfo.h"

#include <fstream>
#include <sstream>

namespace llvm {

/** Auxiliary function for checking of extends.
 * Prints an error and aborts if a custom type would cause an error.
 * E.g. extend of i33 to i64 on i32 arch is not allowed.
 * \param act  Legalize action.
 * \param inVt  Input type of an extend (for error print).
 * \param oldVt  Original output type (for error print). */
void CheckUnsupportedExtend(TargetLowering::LegalizeTypeAction act,
                            const EVT inVt, const EVT oldVt,
                            MachineFunction &mf);

/** Auxiliary function for fixing up emulation expansions.
 * Checks for side-effects such as toggling flags and moves the inserted range
 * before the affected instruction.
 * Originally in RegInfo as a helper function called by eliminateFrameIndex.
 * \param MIRange  a range of instructions to move.
 * \return true if any change is applied/instructions are moved. */
bool moveInsertedToSafety(iterator_range<MachineBasicBlock::iterator> MIRange);

/**
 * Find a max number of FI operands per MI in the function.
 * An indicator of number of emergency spill slots needed in the worst case.
 * \param MF  function to search through for MI with max FI operands.
 * \return    max number of FI operands per MI */
unsigned findMaxFIOperands(MachineFunction &MF);

/**
 * Returns operand that is jump or call destination of instruction mi. */
MachineOperand *getJumpCallDest(MachineInstr &mi);

} // namespace llvm

#endif // UTILS_H_
