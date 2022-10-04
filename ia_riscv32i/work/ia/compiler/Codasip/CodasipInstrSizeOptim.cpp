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


#define DEBUG_TYPE "codasip-instrsizeoptim"

#include "Codasip.h"
#include "CodasipJumpInfo.h"
#include "CodasipTargetMachine.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

namespace {

class SmallerInstructions : public MachineFunctionPass {
  const CodasipInstrInfo *CII;
  const CodasipRegisterInfo *CRI;
  MachineRegisterInfo *MRI;
  MachineFunction *MF;
  const int OptimType;
  LTOFileInfo *LtoFile;
  // helper used to represent operands of the new smaller instruction if needed
  // must be erased after use
  MachineInstr *SpecialIns;
  // set true if SpecialIns will be used
  bool UseSpecialIns;
  // set true if implicit operands of the old and new instructions differ
  // old implicit operands will be removed and new created during instruction
  // swap
  bool RedefImplicitOps;

public:
  static char ID;
  // mandatory functions
  SmallerInstructions();
  SmallerInstructions(CodasipTargetMachine &tm, CodasipSmallerInsPassType type);
  ~SmallerInstructions();
  StringRef getPassName() const { return "CodasipSmallerInstructions"; }
  bool runOnMachineFunction(MachineFunction &F);

private:
  /// \brief Get opcodes of smaller, semantically equivalent instructions.
  /// \param [in] opcode - opcode of old instruction
  /// \param [out] newOpc - opcodes of smaller, semantically equivalent
  /// instructions
  void getSmallerInstr(unsigned opcode, std::vector<unsigned> &newOpc) const;
  /// \brief Returns true if new instruction satisfies the same predicates as
  /// the old one.
  /// \param [in] opcode - opcode of new instruction
  /// \param [in] mi - old instruction
  bool predicateCheck(unsigned opcode, const MachineInstr *mi) const;
  /// \brief Returns true if new instruction can also jump to the destination of
  /// old instruction.
  /// \param [in] opcode - opcode of new instruction
  /// \param [in] mi - old instruction
  bool jumpCheck(unsigned opcode, MachineInstr *mi) const;
  /// \brief Returns true if new instruction can replace the old one.
  ///
  /// If new instruction has different order or number of operands, SpecialIns
  /// si set.
  /// \param [in] opcode - opcode of new instruction
  /// \param [in] mi - old instruction
  /// \param [in] reverseIns - old instruction with swapped input operands, if
  /// mi is commutable
  ///                          nullptr otherwise
  bool instrEquivalenceCheck(unsigned newOpc, MachineInstr *mi,
                             MachineInstr *reverseIns);
  /// \brief Get the smallest instruction that can replace the original one
  /// \param [in] newOpcs - opcodes of smaller, semantically
  /// equivalentinstructions
  /// \param [in] mi - old instruction
  /// \return opcode of the smallest instruction that satisfies necessary checks
  unsigned findSmallest(std::vector<unsigned> newOpcs, MachineInstr *mi);

  /// \brief Returns true, if new instruction can support all variable operands
  /// of the old one.
  /// \param [in] opcode - opcode of new instruction
  /// \param [in] mi - old instruction
  bool variadicOpEqCheck(unsigned opcode, const MachineInstr *mi) const;
  /// \brief Returns true, if new register operand can be represented by the
  /// same register class as the old register operand.
  /// \param [in] newOp - new operand info
  /// \param [in] oldOp - old operand
  bool regClassOpCheck(const MCOperandInfo &newOp,
                       const MachineOperand &oldOp) const;
  /// \brief Returns true, if operand that must be identical in the new
  /// instruction are identical
  /// \param [in] opcode - opcode of new instruction
  /// \param [in] mi - old instruction
  bool tiedOpCheck(unsigned opcode, const MachineInstr *mi) const;
  /// \brief Returns true, if new instruction implicitli defines same registers
  /// as the old one.
  ///
  /// Registers marked as unused in codal are not checked in emualtions.
  /// Sets RedefImplicitOps if need be.
  /// \param [in] opcode - opcode of new instruction
  /// \param [in] mi - old instruction
  bool implicitDefsCheck(unsigned opcode, const MachineInstr *mi);
  /// \brief Returns true, if new instruction implicitli uses same registers as
  /// the old one.
  ///
  /// Registers marked as unused in codal are not checked in emualtions.
  /// Sets RedefImplicitOps if need be.
  /// \param [in] opcode - opcode of new instruction
  /// \param [in] mi - old instruction
  bool implicitUsesCheck(unsigned opcode, const MachineInstr *mi);
  /// \brief Returns true, if operand of the old instruction can be used in the
  /// new one.
  /// \param [in] newOpPos - index of operand descriptor in the new instruction
  /// \param [in] newIns - descriptor of the new instruction
  /// \param [in] oldOp - old operand
  /// \param [in] oldOpInfo - old operand descriptor
  bool explicitOpToOpCheck(unsigned newOpPos, const MCInstrDesc &newIns,
                           const MachineOperand &oldOp,
                           const MCOperandInfo &oldOpInfo) const;
  /// \brief Returns true, if new immediate operand can represent a value of the
  /// old one.
  /// \param [in] opcode - opcode of the new instruction
  /// \param [in] newPos - index of immediate operand in the new instruction
  /// \param [in] oldOp - old immediate operand
  bool immToImmCheck(unsigned opcode, unsigned newPos,
                     const MachineOperand &oldOp) const;
  /// \brief Returns true, if new instruction can support operands of the old
  /// one.
  /// \param [in] opcode - opcode of new instruction
  /// \param [in] mi - old instruction
  bool operandEquivalenceCheck(unsigned opcode, const MachineInstr *mi);
  /// \brief Check if the old instruction can be replaced by new one, that
  /// doesn't have the same operands.
  /// \param [in] opcode - opcode of new instruction
  /// \param [in] mi - old instruction
  /// \return new smaller instruction or nullptr
  MachineInstr *specialCaseOperandCheck(unsigned opcode, MachineInstr *mi);

  /// \brief Returns true, if register is marked as unused in codal
  /// \param [in] reg - register number
  bool isUnusedReg(unsigned reg) const;
  /// \brief Set new value of SpecialIns member and erase the old one.
  /// \param [in] newSpecialIns - new value
  /// \param [in] protectedIns - if old value is this instruction, don't erase
  /// it
  void setSpecialIns(MachineInstr *newSpecialIns,
                     const MachineInstr *protectedIns);
  /// \brief Erase SpecialIns member.
  void cleanCompare();
  /// \brief If instruction is commutable, create a new one with swappes input
  /// operands.
  /// \param [in] origIns - original instructions
  /// \return new instruction with swapped operands or nullptr
  MachineInstr *createReverseInstr(MachineInstr *origIns) const;
  /// \brief Change the old instruction and its operands to smaller one.
  /// \param [in] newOpcode - opcode of new instruction
  /// \param [in] mi - old instruction
  /// \return iterator to the changed instruction
  MachineBasicBlock::instr_iterator changeToSmaller(unsigned newOpcode,
                                                    MachineInstr *mi);
  bool runOptim(MachineBasicBlock &mbb);
};
} // namespace

static bool isDestinationOp(const MachineOperand &oldOp) {
  // getJumpCallDest accepts non const parameter, but sometimes its usage is
  // nested too deep
  MachineOperand *dest =
      getJumpCallDest(*(const_cast<MachineInstr *>(oldOp.getParent())));
  return (dest == &oldOp);
}

char SmallerInstructions::ID = 0;
char &SmallerInstructionsID = SmallerInstructions::ID;
static RegisterPass<SmallerInstructions>
    X("smaller-inst-optim", "CodasipSmallerInstructions", false, false);

SmallerInstructions::SmallerInstructions()
    : MachineFunctionPass(ID), CII(nullptr), CRI(nullptr), MRI(nullptr),
      MF(nullptr), OptimType(0), LtoFile(nullptr), SpecialIns(nullptr),
      UseSpecialIns(false), RedefImplicitOps(false) {}

SmallerInstructions::SmallerInstructions(CodasipTargetMachine &tm,
                                         CodasipSmallerInsPassType type)
    : MachineFunctionPass(ID), CII(tm.getInstrInfo()),
      CRI(static_cast<const CodasipRegisterInfo *>(tm.getRegisterInfo())),
      MRI(nullptr), MF(nullptr), OptimType(type), LtoFile(new LTOFileInfo()),
      SpecialIns(nullptr), UseSpecialIns(false), RedefImplicitOps(false) {}

SmallerInstructions::~SmallerInstructions() { delete LtoFile; }

void SmallerInstructions::getSmallerInstr(unsigned opcode,
                                          std::vector<unsigned> &newOpc) const {
  switch (opcode) {
    case Codasip::e_movi32__:
case Codasip::e_movi32__GA:
case Codasip::e_movi32__ES:
case Codasip::e_movi32__MC:
case Codasip::e_movi32__BA:
case Codasip::e_movi32__JT:
case Codasip::e_movi32__CP:
newOpc.reserve(4);
newOpc.push_back(Codasip::i_itype_alu__opc_addi__xpr_general__x_0__simm12__);
newOpc.push_back(Codasip::i_itype_alu__opc_ori__xpr_general__x_0__simm12__);
newOpc.push_back(Codasip::i_itype_alu__opc_xori__xpr_general__x_0__simm12__);
newOpc.push_back(Codasip::i_utype_ops__opc_lui__xpr_general__uimm20__);
break;
case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__1_BIGIMM_EMUL_:
newOpc.reserve(1);
newOpc.push_back(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__);
break;
case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__3_BIGIMM_EMUL_:
newOpc.reserve(1);
newOpc.push_back(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__);
break;
case Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__4_BIGIMM_EMUL_:
newOpc.reserve(1);
newOpc.push_back(Codasip::i_stype_store__opc_sw__xpr_general__simm12__xpr_general__);
break;
case Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__5_BIGIMM_EMUL_:
newOpc.reserve(1);
newOpc.push_back(Codasip::i_itype_loads__opc_lw__xpr_general__simm12__xpr_general__);
break;
case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__6_BIGIMM_EMUL_:
newOpc.reserve(1);
newOpc.push_back(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__);
break;
case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__7_BIGIMM_EMUL_:
newOpc.reserve(1);
newOpc.push_back(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__);
break;
case Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__8_BIGIMM_EMUL_:
newOpc.reserve(1);
newOpc.push_back(Codasip::i_itype_alu__opc_addi__xpr_general__xpr_general__simm12__);
break;

  default:
    break;
  }
}

// ============================ whole instruction checks ======================

bool SmallerInstructions::predicateCheck(unsigned opcode,
                                         const MachineInstr *mi) const {
  if (CII->isPredicated(*mi)) {
    return CII->isPredicated(opcode) &&
           (CII->isPredicatedTrue(*mi) == CII->isPredicatedTrue(opcode));
  }
  if (CII->isPredicated(opcode)) {
    return false;
  }
  return true;
}

bool SmallerInstructions::jumpCheck(unsigned opcode, MachineInstr *mi) const {
  // when jumps aren't checked in pass, return true
  if (OptimType == OnlyEmul || OptimType == NormalInst) {
    return true;
  }
  if (OptimType == LtoJump && !mi->isBranch() && !mi->isCall() &&
      !mi->isReturn()) {
    return true;
  }
  MachineOperand *dest = getJumpCallDest(*mi);
  if (!dest) {
    return false;
  }
  CodasipJumpInfo newJumpInfo = CodasipJumpInfo(opcode, mi, dest, CII);
  if (!newJumpInfo.canJumpToDestination(dest, true, LtoFile)) {
    return false;
  }
  return true;
}

bool SmallerInstructions::instrEquivalenceCheck(unsigned newOpc,
                                                MachineInstr *mi,
                                                MachineInstr *reverseIns) {
  bool saveRedefImplicitOp = RedefImplicitOps;
  LLVM_DEBUG(dbgs() << "  checking: " << CII->getName(newOpc) << "\n";);
  // end checks immediately after fail, other checks may crash otherwise
  bool pred = predicateCheck(newOpc, mi);
  if (!pred) {
    LLVM_DEBUG(dbgs() << "predicate check: false \n";);
    return false;
  }
  bool jmp = jumpCheck(newOpc, mi);
  if (!jmp) {
    LLVM_DEBUG(dbgs() << "jump check: false \n";);
    return false;
  }
  bool op = operandEquivalenceCheck(newOpc, mi);
  if (op) {
    UseSpecialIns = false;
    LLVM_DEBUG(dbgs() << "-1- All checks: true \n";);
    setSpecialIns(nullptr, reverseIns);
    return true;
  }
  LLVM_DEBUG(dbgs() << "operand check: false \n";);
  if (mi->isCommutable() && reverseIns != nullptr) {
    // try to match instruction with swaped use operands
    op = operandEquivalenceCheck(newOpc, reverseIns);
    if (op) {
      LLVM_DEBUG(dbgs() << "-2- All checks: true \n";);
      UseSpecialIns = true;
      setSpecialIns(reverseIns, reverseIns);
      return true;
    }
    LLVM_DEBUG(dbgs() << "operand check on reverse: false \n";);
  }
  // try to match some special cases
  MachineInstr *newIns = specialCaseOperandCheck(newOpc, mi);
  if (newIns != nullptr) {
    LLVM_DEBUG(dbgs() << "-3- All checks: true \n";);
    UseSpecialIns = true;
    setSpecialIns(newIns, reverseIns);
    return true;
  }
  LLVM_DEBUG(dbgs() << "operand check on special cases: false \n";);
  RedefImplicitOps = saveRedefImplicitOp;
  return false;
}

unsigned SmallerInstructions::findSmallest(std::vector<unsigned> newOpcs,
                                           MachineInstr *mi) {
  unsigned smallest = mi->getOpcode();
  MachineInstr *reverseIns = nullptr;
  if (mi->isCommutable()) {
    reverseIns = createReverseInstr(mi);
  }
  for (unsigned examinedOpc : newOpcs) {
    if (CII->get(examinedOpc).getSize() >= CII->get(smallest).getSize()) {
      continue;
    }
    if (!instrEquivalenceCheck(examinedOpc, mi, reverseIns)) {
      continue;
    }
    smallest = examinedOpc;
  }
  if (SpecialIns != reverseIns && reverseIns != nullptr) {
    // erase unused commutable instruction
    reverseIns->eraseFromParent();
  }
  return smallest;
}

// ====================== operand checks ======================================

bool SmallerInstructions::variadicOpEqCheck(unsigned opcode,
                                            const MachineInstr *mi) const {
  const MCInstrDesc newMCID = CII->get(opcode);
  if (newMCID.isVariadic()) {
    // check only not variadic explicit operands
    for (unsigned i = 0; i < newMCID.getNumOperands(); ++i) {
      if (!explicitOpToOpCheck(i, newMCID, mi->getOperand(i),
                               mi->getDesc().OpInfo[i])) {
        return false;
      }
    }
    return true;
  }
  if (mi->getNumExplicitOperands() != mi->getDesc().getNumOperands()) {
    // old instruction can have and has some variadic operands
    return false;
  }
  // old instruction can have but doesn't have variadic operands
  // check only not variadic explicit operands
  for (unsigned i = 0; i < newMCID.getNumOperands(); ++i) {
    if (!explicitOpToOpCheck(i, newMCID, mi->getOperand(i),
                             mi->getDesc().OpInfo[i])) {
      return false;
    }
  }
  return true;
}

bool SmallerInstructions::regClassOpCheck(const MCOperandInfo &newOp,
                                          const MachineOperand &oldOp) const {
  if (TargetRegisterInfo::isVirtualRegister(oldOp.getReg())) {
    const TargetRegisterClass *oldTrc = MRI->getRegClass(oldOp.getReg());
    const TargetRegisterClass *newTrc = CRI->getRegClass(newOp.RegClass);
    return (newTrc == oldTrc);
  }
  return CRI->getRegClass(newOp.RegClass)->contains(oldOp.getReg());
}

bool SmallerInstructions::tiedOpCheck(unsigned opcode,
                                      const MachineInstr *mi) const {
  const MCInstrDesc MCID = CII->get(opcode);
  for (unsigned i = 0; i < MCID.getNumOperands(); ++i) {
    if (MCID.getOperandConstraint(i, MCOI::TIED_TO) != MCOI::TIED_TO) {
      continue;
    }
    if (mi->getNumOperands() <= i) {
      return false;
    }
    // isTied does not work
    if (!mi->getOperand(i).isReg() || !mi->getOperand(0).isReg() ||
        mi->getOperand(i).getReg() != mi->getOperand(0).getReg()) {
      return false;
    }
  }
  return true;
}

bool SmallerInstructions::implicitDefsCheck(unsigned opcode,
                                            const MachineInstr *mi) {
  const MCInstrDesc newMCID = CII->get(opcode);
  std::vector<MCPhysReg> checked;
  const MCPhysReg *oldImpDefs = mi->getDesc().getImplicitDefs();
  for (unsigned oldIdx = 0; oldIdx < mi->getDesc().getNumImplicitDefs();
       ++oldImpDefs, ++oldIdx) {
    bool found = false;
    const MCPhysReg *newImpDefs = newMCID.getImplicitDefs();
    for (unsigned newIdx = 0; newIdx < newMCID.getNumImplicitDefs();
         ++newImpDefs, ++newIdx) {
      if (*oldImpDefs == *newImpDefs) {
        found = true;
        checked.push_back(*oldImpDefs);
        // if their positions don't match, implicit registers must be redefined
        if (oldIdx != newIdx) {
          RedefImplicitOps = true;
        }
        break;
      }
    }
    if (!found) {
      // take a look at the actual machine data
      bool deadDef = false;
      for (const MachineOperand &iOp : mi->implicit_operands()) {
        if (!iOp.isReg()) {
          continue;
        }
        if (iOp.getReg() == *oldImpDefs && iOp.isDef()) {
          if (iOp.isDead())
            deadDef = true;
          break;
        }
      }
      // is it a dropped auxiliary reg (of an emulation) or a completely unused reg?
      if (deadDef || isUnusedReg(*oldImpDefs))
        RedefImplicitOps = true;
      else
        return false;
    }
  }
  if (newMCID.getNumImplicitDefs() == 0) {
    return true;
  }
  for (const MCPhysReg *newImpDefs = newMCID.getImplicitDefs(); *newImpDefs;
       ++newImpDefs) {
    if (llvm::find(checked, *newImpDefs) != checked.end()) {
      continue;
    }
    // new instruction has more implicit registers
    // note: a call emulation is never isPseudo
    if (!newMCID.isPseudo() || !isUnusedReg(*newImpDefs)) {
      // in pseudo instructions, implicit registers that are set as unused in
      // codal don't have to match
      return false;
    }
    // unmatched unused register needs to be removed
    RedefImplicitOps = true;
  }
  return true;
}

bool SmallerInstructions::implicitUsesCheck(unsigned opcode,
                                            const MachineInstr *mi) {
  const MCInstrDesc newMCID = CII->get(opcode);
  std::vector<MCPhysReg> checked;
  const MCPhysReg *oldImpUses = mi->getDesc().getImplicitUses();
  for (unsigned oldIdx = 0; oldIdx < mi->getDesc().getNumImplicitUses();
       ++oldImpUses, ++oldIdx) {
    bool found = false;
    const MCPhysReg *newImpUses = newMCID.getImplicitUses();
    for (unsigned newIdx = 0; newIdx < newMCID.getNumImplicitUses();
         ++newImpUses, ++newIdx) {
      if (*oldImpUses == *newImpUses) {
        found = true;
        checked.push_back(*oldImpUses);
        // if their positions don't match, implicit registers must be redefined
        if (oldIdx != newIdx) {
          RedefImplicitOps = true;
        }
        break;
      }
    }
    if (!found && (!mi->isPseudo() || !isUnusedReg(*oldImpUses))) {
      // in pseudo instructions, implicit registers that are set as unused in
      // codal don't have to match
      return false;
    }
    if (!found && mi->isPseudo() && isUnusedReg(*oldImpUses)) {
      // unmatched unused register needs to be removed
      RedefImplicitOps = true;
    }
  }
  if (newMCID.getNumImplicitUses() == 0) {
    return true;
  }
  for (const MCPhysReg *newImpUses = newMCID.getImplicitUses(); *newImpUses;
       ++newImpUses) {
    if (llvm::find(checked, *newImpUses) != checked.end()) {
      continue;
    }
    // new instruction has more implicit registers
    if (!newMCID.isPseudo() || !isUnusedReg(*newImpUses)) {
      // in pseudo instructions, implicit registers that are set as unused in
      // codal don't have to match
      return false;
    }
    // unmatched unused register needs to be removed
    RedefImplicitOps = true;
  }
  return true;
}

bool SmallerInstructions::explicitOpToOpCheck(
    unsigned newOpPos, const MCInstrDesc &newIns, const MachineOperand &oldOp,
    const MCOperandInfo &oldOpInfo) const {
  const MCOperandInfo &newOp = newIns.OpInfo[newOpPos];
  if (newOp.OperandType != oldOpInfo.OperandType) {
    return false;
  }
  if (newOp.OperandType == MCOI::OPERAND_IMMEDIATE) {
    return immToImmCheck(newIns.getOpcode(), newOpPos, oldOp);
  }
  if (newOp.OperandType == MCOI::OPERAND_REGISTER) {
    if (!oldOp.isReg()) {
      return false;
    }
    return regClassOpCheck(newOp, oldOp);
  }
  return true;
}

bool SmallerInstructions::immToImmCheck(unsigned opcode, unsigned newPos,
                                        const MachineOperand &oldOp) const {
  if (!oldOp.isImm() && !oldOp.isGlobal() && !oldOp.isSymbol() &&
      !oldOp.isJTI() && !oldOp.isMBB()) {
    return false;
  }
  if ((oldOp.getParent()->isBranch() || oldOp.getParent()->isCall() ||
       oldOp.getParent()->isReturn()) &&
      isDestinationOp(oldOp)) {
    // destination operand was already checked in another function.
    // GetImmProperties would not return correct result for it
    return true;
  }
  // initialize to the default case in CodasipGenInstrInfo2::GetImmProperties
  // consult with documentation or with creator of that method
  int width = 0;
  int trunc = -1;
  bool sign = true;
  // jump/call destinations are not checked here
  CII->GetImmProperties(opcode, newPos, width, sign, trunc);
  // immediate can have any size, instr is emulation and will be expanded
  if (width == 0 && sign && trunc == -1) {
    return true;
  }
  // instr doesn't have immediate at that position
  if (width == -1 && !sign && trunc == -1) {
    return false;
  }
  if (oldOp.isImm()) {
    return CheckImmImpl(oldOp.getImm(), width, sign, trunc);
  }
  if ((oldOp.isGlobal() || oldOp.isSymbol() || oldOp.isJTI() ||
       oldOp.isMBB()) && trunc == 0 && LtoFile->useLTOFile()) {
    // can't get value of the old operand directly, only option is to find it in
    // lto symbol file
    int64_t address = 0;
    bool found = LtoFile->getSymbolAddress(
        &oldOp, oldOp.getParent()->getParent()->getParent(), address);
    if (!found) {
      return false;
    }
    return CheckImmImpl(address, width, sign, trunc);
  }
  return false;
}

bool SmallerInstructions::operandEquivalenceCheck(unsigned opcode,
                                                  const MachineInstr *mi) {
  const MCInstrDesc newMCID = CII->get(opcode);
  bool result = true;
  if (newMCID.isVariadic() || mi->isVariadic()) {
    result &= variadicOpEqCheck(opcode, mi);
    result &= tiedOpCheck(opcode, mi);
    result &= implicitDefsCheck(opcode, mi);
    result &= implicitUsesCheck(opcode, mi);
    return result;
  }
  if (newMCID.getNumOperands() != mi->getNumExplicitOperands()) {
    return false;
  }
  // operands are equal
  for (unsigned i = 0; i < newMCID.getNumOperands(); ++i) {
    if (!explicitOpToOpCheck(i, newMCID, mi->getOperand(i),
                             mi->getDesc().OpInfo[i])) {
      return false;
    }
  }
  result &= tiedOpCheck(opcode, mi);
  result &= implicitDefsCheck(opcode, mi);
  result &= implicitUsesCheck(opcode, mi);
  return result;
}

MachineInstr *SmallerInstructions::specialCaseOperandCheck(unsigned opcode,
                                                           MachineInstr *mi) {
  const MCInstrDesc newMCID = CII->get(opcode);
  unsigned bigNumImplUses = mi->getDesc().getNumImplicitUses();
  unsigned bigNumImplDefs = mi->getDesc().getNumImplicitDefs();
  unsigned bigNumExplDefs = mi->getNumExplicitDefs();
  unsigned bigNumExplUses =
      mi->getNumExplicitOperands() - mi->getNumExplicitDefs();
  unsigned bigNumExplOperands = bigNumExplDefs + bigNumExplUses;
  unsigned smallNumImplUses = newMCID.getNumImplicitUses();
  unsigned smallNumImplDefs = newMCID.getNumImplicitDefs();
  unsigned smallNumExplDefs = newMCID.getNumDefs();
  unsigned smallNumExplUses = newMCID.getNumOperands() - newMCID.getNumDefs();
  unsigned smallNumExplOperands = smallNumExplDefs + smallNumExplUses;

  // ---- case 1 ----
  // rx = big-ins ry, imm --> small-ins imm, rx-impl_def, ry-impl_use
  if (bigNumImplUses == 0 && bigNumImplDefs == 0 && bigNumExplDefs == 1 &&
      bigNumExplUses == 2 && smallNumImplUses == 1 && smallNumImplDefs == 1 &&
      smallNumExplDefs == 0 && smallNumExplUses == 1 &&
      newMCID.OpInfo[0].OperandType == MCOI::OPERAND_IMMEDIATE) {
    // tied check - no need, new instruction doesnt have general register
    // operands
    // defs check
    const MachineOperand *oldExplDef = mi->defs().begin();
    if (oldExplDef->getReg() != *(newMCID.getImplicitDefs())) {
      return nullptr;
    }
    // uses reg check
    unsigned oldExplRegOpIdx = 0;
    unsigned oldExplImmOpIdx = 0;
    for (unsigned i = bigNumExplDefs; i < bigNumExplOperands; ++i) {
      if (mi->getOperand(i).isReg()) {
        oldExplRegOpIdx = i;
      }
      if (mi->getOperand(i).isImm()) {
        oldExplImmOpIdx = i;
      }
    }
    if (mi->getOperand(oldExplRegOpIdx).getReg() !=
        *(newMCID.getImplicitUses())) {
      return nullptr;
    }
    // uses imm check
    if (!explicitOpToOpCheck(0, newMCID, mi->getOperand(oldExplImmOpIdx),
                             mi->getDesc().OpInfo[oldExplImmOpIdx])) {
      return nullptr;
    }
    // create new instr
    MachineInstrBuilder mib =
        BuildMI(*(mi->getParent()), mi, mi->getDebugLoc(), CII->get(opcode));
    mib.add(mi->getOperand(oldExplImmOpIdx));
    return mib.getInstr();
  }
  // ---- case 2 (case 1 inverse) ----
  // big-ins imm, rx-impl_def, ry-impl_use --> rx = small-ins ry, imm
  if (bigNumImplUses == 1 && bigNumImplDefs == 1 && bigNumExplDefs == 0 &&
      bigNumExplUses == 1 && smallNumImplUses == 0 && smallNumImplDefs == 0 &&
      smallNumExplDefs == 1 && smallNumExplUses == 2 &&
      mi->explicit_operands().begin()->isImm()) {
    unsigned smallImmIdx = 0;
    unsigned smallRegIdx = 0;
    if (newMCID.OpInfo[smallNumExplDefs].OperandType ==
            MCOI::OPERAND_IMMEDIATE &&
        newMCID.OpInfo[smallNumExplDefs + 1].OperandType ==
            MCOI::OPERAND_REGISTER) {
      smallImmIdx = smallNumExplDefs;
      smallRegIdx = smallNumExplDefs + 1;
    } else if (newMCID.OpInfo[smallNumExplDefs].OperandType ==
                   MCOI::OPERAND_REGISTER &&
               newMCID.OpInfo[smallNumExplDefs + 1].OperandType ==
                   MCOI::OPERAND_IMMEDIATE) {
      smallImmIdx = smallNumExplDefs + 1;
      smallRegIdx = smallNumExplDefs;
    } else {
      return nullptr;
    }
    // tied check
    bool checkTied = false;
    for (unsigned i = 0; i < smallNumExplOperands; ++i) {
      if (newMCID.getOperandConstraint(i, MCOI::TIED_TO) == MCOI::TIED_TO) {
        checkTied = true;
        break;
      }
    }
    if (checkTied) {
      if (*(mi->getDesc().getImplicitUses()) !=
          *(mi->getDesc().getImplicitDefs())) {
        return nullptr;
      }
    }
    // defs check
    const MachineOperand *oldImplDef = mi->implicit_operands().begin();
    if (!oldImplDef->isReg() || !oldImplDef->isImplicit() ||
        !oldImplDef->isDef()) {
      return nullptr;
    }
    if (!regClassOpCheck(newMCID.OpInfo[0], *oldImplDef)) {
      return nullptr;
    }
    // uses reg check
    const MachineOperand *oldImplUse =
        std::next(mi->implicit_operands().begin());
    if (!oldImplUse->isReg() || !oldImplUse->isImplicit() ||
        !oldImplUse->isUse()) {
      return nullptr;
    }
    if (!regClassOpCheck(newMCID.OpInfo[smallRegIdx], *oldImplUse)) {
      return nullptr;
    }
    // uses imm check
    if (!explicitOpToOpCheck(smallImmIdx, newMCID, mi->getOperand(0),
                             mi->getDesc().OpInfo[0])) {
      return nullptr;
    }
    // create new instr
    MachineInstrBuilder mib =
        BuildMI(*(mi->getParent()), mi, mi->getDebugLoc(), CII->get(opcode));
    mib.addDef(oldImplDef->getReg());
    // instruction generated in .td file has immediate use operands after
    // register use ones
    mib.addReg(oldImplUse->getReg());
    mib.add(mi->getOperand(0));
    return mib.getInstr();
  }
  // ---- case 3 ----
  // [rx]* = big-ins ry, imm, [rz-impl_def]* --> [rx]* = small-ins imm,
  // [rz-impl_def]*, ry-impl_use
  if (bigNumImplUses == 0 && bigNumExplUses == 2 && smallNumImplUses == 1 &&
      smallNumExplUses == 1 && smallNumExplDefs == bigNumExplDefs &&
      smallNumExplOperands < bigNumExplOperands) {
    // one operand must be immediate the other ine register
    unsigned bigImmIdx = 0;
    unsigned bigRegIdx = 0;
    if (mi->getOperand(bigNumExplDefs).isImm() &&
        mi->getOperand(bigNumExplDefs + 1).isReg()) {
      bigImmIdx = bigNumExplDefs;
      bigRegIdx = bigNumExplDefs + 1;
    } else if (mi->getOperand(bigNumExplDefs).isReg() &&
               mi->getOperand(bigNumExplDefs + 1).isImm()) {
      bigImmIdx = bigNumExplDefs + 1;
      bigRegIdx = bigNumExplDefs;
    } else {
      return nullptr;
    }
    // tied check - no ties allowed, because new instr doesn't have explicit def
    // operand to be tied with
    for (unsigned i = 0; i < smallNumExplOperands; ++i) {
      if (newMCID.getOperandConstraint(i, MCOI::TIED_TO) == MCOI::TIED_TO) {
        return nullptr;
      }
    }
    // defs check
    for (unsigned i = 0; i < smallNumExplDefs; ++i) {
      if (!explicitOpToOpCheck(i, newMCID, mi->getOperand(i),
                               mi->getDesc().OpInfo[i])) {
        return nullptr;
      }
    }
    if (!implicitDefsCheck(opcode, mi)) {
      return nullptr;
    }
    // uses reg check
    if (mi->getOperand(bigRegIdx).getReg() != *(newMCID.getImplicitUses())) {
      return nullptr;
    }
    // uses imm check
    // instruction generated in .td file has immediate use operands after
    // register use ones
    if (!explicitOpToOpCheck(smallNumExplDefs, newMCID,
                             mi->getOperand(bigImmIdx),
                             mi->getDesc().OpInfo[bigNumExplDefs + 1])) {
      return nullptr;
    }
    // create new instr
    MachineInstrBuilder mib =
        BuildMI(*(mi->getParent()), mi, mi->getDebugLoc(), CII->get(opcode));
    for (const auto &op : mi->defs()) {
      mib.add(op);
    }
    mib.add(mi->getOperand(bigImmIdx));
    return mib.getInstr();
  }
  // ---- case 4 (case 3 inverse) ----
  // [rx]* = big-ins imm, [rz-impl_def]*, ry-impl_use --> [rx]* = small-ins ry,
  // imm, [rz-impl_def]*
  if (bigNumImplUses == 1 && bigNumExplUses == 1 &&
      bigNumExplDefs == smallNumExplDefs && smallNumImplUses == 0 &&
      smallNumExplUses == 2 && smallNumExplOperands > bigNumExplOperands) {
    // one operand must be immediate the other ine register
    unsigned smallImmIdx = 0;
    unsigned smallRegIdx = 0;
    if (newMCID.OpInfo[bigNumExplDefs].OperandType == MCOI::OPERAND_IMMEDIATE &&
        newMCID.OpInfo[bigNumExplDefs + 1].OperandType ==
            MCOI::OPERAND_REGISTER) {
      smallImmIdx = bigNumExplDefs;
      smallRegIdx = bigNumExplDefs + 1;
    } else if (newMCID.OpInfo[bigNumExplDefs].OperandType ==
                   MCOI::OPERAND_REGISTER &&
               newMCID.OpInfo[bigNumExplDefs + 1].OperandType ==
                   MCOI::OPERAND_IMMEDIATE) {
      smallImmIdx = bigNumExplDefs + 1;
      smallRegIdx = bigNumExplDefs;
    } else {
      return nullptr;
    }
    // tied check
    // big instr has only one implicit use operand
    const MachineOperand *oldImpUse = mi->implicit_operands().begin();
    bool checkTied = false;
    for (unsigned i = 0; i < smallNumExplOperands; ++i) {
      if (newMCID.getOperandConstraint(i, MCOI::TIED_TO) == MCOI::TIED_TO) {
        checkTied = true;
        break;
      }
    }
    if (checkTied) {
      if (bigNumExplDefs != 1 ||
          mi->getOperand(0).getReg() != oldImpUse->getReg()) {
        return nullptr;
      }
    }
    // defs check
    if (!implicitDefsCheck(opcode, mi)) {
      return nullptr;
    }
    for (unsigned i = 0; i < smallNumExplDefs; ++i) {
      if (!explicitOpToOpCheck(i, newMCID, mi->getOperand(i),
                               mi->getDesc().OpInfo[i])) {
        return nullptr;
      }
    }
    // uses reg check
    if (!regClassOpCheck(newMCID.OpInfo[smallRegIdx], *oldImpUse)) {
      return nullptr;
    }
    // uses imm check
    if (!explicitOpToOpCheck(smallImmIdx, newMCID,
                             mi->getOperand(bigNumExplDefs),
                             mi->getDesc().OpInfo[bigNumExplDefs])) {
      return nullptr;
    }
    // create new instr
    MachineInstrBuilder mib =
        BuildMI(*(mi->getParent()), mi, mi->getDebugLoc(), CII->get(opcode));
    for (const auto &op : mi->defs()) {
      mib.add(op);
    }
    mib.addReg(oldImpUse->getReg());
    mib.add(mi->getOperand(bigNumExplDefs));
    return mib.getInstr();
  }
  // ---- case 5 ----
  // [ra]* = big-ins [rb]+, [rc-imp_def]*, [rd-imp_use]* --> [ra]* = small-ins
  // rb, [rc-imp_def]*, [rd-imp_use]*
  if (smallNumExplUses == 1 && smallNumExplDefs == bigNumExplDefs &&
      smallNumExplOperands < bigNumExplOperands) {
    // all use operands must be identical
    const MachineOperand *firstUse = mi->explicit_uses().begin();
    for (const auto &mo : mi->explicit_uses()) {
      if (!firstUse->isIdenticalTo(mo)) {
        return nullptr;
      }
    }
    // tied check
    if (!tiedOpCheck(opcode, mi)) {
      return nullptr;
    }
    // defs check
    for (unsigned i = 0; i < (smallNumExplDefs - 1); ++i) {
      if (!explicitOpToOpCheck(i, newMCID, mi->getOperand(i),
                               mi->getDesc().OpInfo[i])) {
        return nullptr;
      }
    }
    if (!implicitDefsCheck(opcode, mi)) {
      return nullptr;
    }
    // uses reg check
    if (!implicitUsesCheck(opcode, mi)) {
      return nullptr;
    }
    // create new instr
    MachineInstrBuilder mib =
        BuildMI(*(mi->getParent()), mi, mi->getDebugLoc(), CII->get(opcode));
    for (const auto &op : mi->defs()) {
      mib.add(op);
    }
    mib.add(mi->getOperand(bigNumExplDefs));
    return mib.getInstr();
  }
  // ---- case 6 ----
  // ra = big-ins [rb]*, [imm]*, [rc-imp_use]* --> small-ins [rb]*, [imm]*,
  // ra-imp_def, [rc-imp_use]*
  if (smallNumExplDefs == 0 && smallNumImplDefs == 1 && bigNumExplDefs == 1 &&
      bigNumImplDefs == 0 && bigNumExplUses == smallNumExplUses &&
      smallNumExplOperands < bigNumExplOperands) {
    // tied check - no ties allowed, because new instr doesn't have explicit def
    // operand to be tied with
    for (unsigned i = 0; i < smallNumExplOperands; ++i) {
      if (newMCID.getOperandConstraint(i, MCOI::TIED_TO) == MCOI::TIED_TO) {
        return nullptr;
      }
    }
    // defs check
    const MachineOperand *oldDef = mi->defs().begin();
    if (oldDef->getReg() != *(newMCID.getImplicitDefs())) {
      return nullptr;
    }
    // uses check
    for (unsigned i = 0; i < smallNumExplOperands; ++i) {
      if (!explicitOpToOpCheck(i, newMCID, mi->getOperand(i + 1),
                               mi->getDesc().OpInfo[i + 1])) {
        return nullptr;
      }
    }
    if (!implicitUsesCheck(opcode, mi)) {
      return nullptr;
    }
    // create new instr
    MachineInstrBuilder mib =
        BuildMI(*(mi->getParent()), mi, mi->getDebugLoc(), CII->get(opcode));
    for (const auto &op : mi->explicit_uses()) {
      mib.add(op);
    }
    return mib.getInstr();
  }
  // ---- case 7 (case 6 inverse) ----
  // big-ins [rb]*, [imm]*, ra-imp_def, [rc-imp_use]* --> ra = small-ins [rb]*,
  // [imm]*, [rc-imp_use]*
  if (smallNumExplDefs == 1 && smallNumImplDefs == 0 && bigNumExplDefs == 0 &&
      bigNumImplDefs == 1 && bigNumExplUses == smallNumExplUses &&
      smallNumExplOperands > bigNumExplOperands) {
    // tied check - no ties allowed, could be extended
    for (unsigned i = 0; i < smallNumExplOperands; ++i) {
      if (newMCID.getOperandConstraint(i, MCOI::TIED_TO) == MCOI::TIED_TO) {
        return nullptr;
      }
    }
    // defs check
    const MachineOperand &oldDef = mi->getOperand(bigNumExplOperands);
    if (!oldDef.isReg() || !oldDef.isDef() || !oldDef.isImplicit()) {
      return nullptr;
    }
    if (!regClassOpCheck(newMCID.OpInfo[0], oldDef)) {
      return nullptr;
    }
    // uses check
    for (unsigned i = 0; i < bigNumExplOperands; ++i) {
      if (!explicitOpToOpCheck(i + 1, newMCID, mi->getOperand(i),
                               mi->getDesc().OpInfo[i])) {
        return nullptr;
      }
    }
    if (!implicitUsesCheck(opcode, mi)) {
      return nullptr;
    }
    // create new instr
    MachineInstrBuilder mib =
        BuildMI(*(mi->getParent()), mi, mi->getDebugLoc(), CII->get(opcode));
    mib.addDef(oldDef.getReg());
    for (const auto &op : mi->explicit_uses()) {
      mib.add(op);
    }
    return mib.getInstr();
  }
  return nullptr;
}

// ============================= help functions ===============================

bool SmallerInstructions::isUnusedReg(unsigned reg) const {
  if (!MRI->isReserved(reg)) {
    return false;
  }
  // if it is SP or BP
  for (unsigned space = 0; space < STACK_COUNT; ++space) {
    if (reg == CRI->GetSP(space) || reg == CRI->GetBP(space)) {
      return false;
    }
  }
  return true;
}

void SmallerInstructions::setSpecialIns(MachineInstr *newSpecialIns,
                                        const MachineInstr *protectedIns) {
  if (SpecialIns != nullptr && SpecialIns != protectedIns) {
    SpecialIns->eraseFromParent();
  }
  SpecialIns = newSpecialIns;
}

void SmallerInstructions::cleanCompare() {
  UseSpecialIns = false;
  if (SpecialIns != nullptr) {
    SpecialIns->eraseFromParent();
    SpecialIns = nullptr;
  }
}

MachineInstr *
SmallerInstructions::createReverseInstr(MachineInstr *origIns) const {
  if (origIns->getNumOperands() != 3) {
    return nullptr;
  }
  MachineInstrBuilder mib =
      BuildMI(*(origIns->getParent()), origIns, origIns->getDebugLoc(),
              CII->get(origIns->getOpcode()));
  mib.add(origIns->getOperand(0));
  mib.add(origIns->getOperand(2));
  mib.add(origIns->getOperand(1));
  return mib.getInstr();
}

MachineBasicBlock::instr_iterator
SmallerInstructions::changeToSmaller(unsigned newOpcode, MachineInstr *mi) {
  LLVM_DEBUG(dbgs() << "Changed for:\n    ";);
  if (!UseSpecialIns) {
    mi->setDesc(CII->get(newOpcode));
    LLVM_DEBUG(mi->print(dbgs(), false););
    if (RedefImplicitOps) {
      // test-5010
      for (unsigned i = mi->getNumOperands() - 1;
           i > mi->getNumExplicitOperands(); --i) {
        mi->RemoveOperand(i);
      }
      if (mi->getNumOperands() > mi->getNumExplicitOperands()) {
        mi->RemoveOperand(mi->getNumExplicitOperands());
      }
      mi->addImplicitDefUseOperands(*MF);
    }
    return mi->getIterator();
  }
  assert(SpecialIns != nullptr);
  // change the old instruction rather than create a new one, because of added
  // nops
  for (unsigned i = mi->getNumOperands() - 1; i > 0; --i) {
    mi->RemoveOperand(i);
  }
  mi->RemoveOperand(0);
  mi->setDesc(CII->get(newOpcode));
  for (const auto &op : SpecialIns->operands()) {
    mi->addOperand(op);
  }
  UseSpecialIns = false;
  LLVM_DEBUG(mi->print(dbgs(), false););
  return mi->getIterator();
}

bool SmallerInstructions::runOptim(MachineBasicBlock &mbb) {
  bool AnyChange = false;
  for (MachineBasicBlock::instr_iterator it = mbb.instr_begin();
       it != mbb.instr_end(); ++it) {
    MachineInstr &mi = *it;
    std::vector<unsigned> newOpcs;
    getSmallerInstr(mi.getOpcode(), newOpcs);
    unsigned newOpcode = mi.getOpcode();
    switch (OptimType) {
    case OnlyEmul:
      // only emulations, no jump emulations
      if (!mi.isPseudo() || mi.isBranch() || mi.isCall() || mi.isReturn()) {
        continue;
      }
      break;
    case LtoJump:
      // normal instructions + jumps if lto info is present
      if ((mi.isBranch() || mi.isCall() || mi.isReturn()) &&
          !LtoFile->useLTOFile()) {
        continue;
      }
      break;
    case NormalInst:
      // only normal instructions - no jumps
      if ((mi.isBranch() || mi.isCall() || mi.isReturn())) {
        continue;
      }
      break;
    case OnlyJump:
      // only jumps, with and without lto
      if (!mi.isBranch() && !mi.isCall() && !mi.isReturn()) {
        continue;
      }
      break;
    default:
      assert(false && "Unsupported second argument of "
                      "createCodasipSmallerInstructionsPass");
    }
    LLVM_DEBUG({
      dbgs() << "Examinning: ";
      mi.dump();
    });
    newOpcode = findSmallest(newOpcs, &mi);
    if (newOpcode != mi.getOpcode()) {
      it = changeToSmaller(newOpcode, &mi);
      AnyChange |= true;
    }
    cleanCompare();
  }
  return AnyChange;
}

bool SmallerInstructions::runOnMachineFunction(MachineFunction &F) {
  LLVM_DEBUG(dbgs() << "********* Codasip instr size optim *********\n");
  LLVM_DEBUG(F.dump());
  MF = &F;
  MRI = &F.getRegInfo();
  bool Changed = false;
  for (MachineBasicBlock &mbb : F) {
    // go over basicblocks and see if we can catch some fast optim
    Changed = runOptim(mbb);
  }
  LLVM_DEBUG(dbgs() << "\n");
  return Changed;
}

// create the pass
FunctionPass *
llvm::createCodasipSmallerInstructionsPass(CodasipTargetMachine &tm,
                                           CodasipSmallerInsPassType type) {
  return new SmallerInstructions(tm, type);
}
