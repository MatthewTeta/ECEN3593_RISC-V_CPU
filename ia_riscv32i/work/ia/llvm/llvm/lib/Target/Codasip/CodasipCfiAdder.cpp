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


#define DEBUG_TYPE "cfi-adder"
/// Number of address space that holds cfa info.
#define CFA_ADDR_SPACE 0

#include "Codasip.h"
#include "CodasipInstructionSemantics.h"
#include "CodasipRegisterInfo.h"
#include "CodasipTargetMachine.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"

using namespace llvm;

typedef std::map<unsigned, int64_t> RegImmMap;

namespace {

/// Expands any FrameSetup/FrameDestroy instructions.
class CfiAdder : public MachineFunctionPass {
public:
  /// Internal representation for operands.
  struct InternalOp {
    /// It is true if operand is register
    bool isReg;
    /// Immediate value from examined instruction.
    int64_t immVal;
    /// register number from examined instruction.
    int64_t regNum;
    /// Dwarf register number corresponding to this register
    int dwarf;
    /// It is true if operand is implicit register
    bool implicit;

    InternalOp()
        : isReg(true), immVal(-1), regNum(-1), dwarf(-1), implicit(false) {}
    /// Returns true if InternalOp was only created and not filled.
    bool notFilled() const {
      return (isReg && immVal == -1 && regNum == -1 && dwarf == -1 &&
              !implicit);
    }
  };

  /// Indexes of operands in MachineInstruction.
  enum Index {
    DST,      ///< destination register
    BASE,     ///< base reg for store/load
    OFF,      ///< offset imm for store/load
    VAL = DST ///< reg that is being stored in store
  };

  /// States that frame instruction might represent.
  enum CfiOperation {
    StoreRarSpImm,   ///< store rar [sp + imm]
    StoreRarBpImm,   ///< store rar [bp + imm]
    StoreRarSp,      ///< store rar [sp]
    StoreRarBp,      ///< store rar [bp]
    StoreRarRx,      ///< store rar [rx] where rx = sp/bp + big imm
    StoreRarRxImm,   ///< store rar [rx + imm] where rx = sp/bp + big imm
    StoreBpSp,       ///< store bp [sp]
    StoreBpSpImm,    ///< store bp [sp + imm]
    SpIsSpPlusImm,   ///< sp = sp + imm
    SpIsSpPlusRx,    ///< sp = sp + rx
    SpIsBpPlusImm,   ///< sp = bp + imm
    BpIsSpPlusImm,   ///< bp = sp + imm
    BpIsSpPlusRx,    ///< bp = sp + rx
    BpIsBpPlusImm,   ///< bp = bp + imm
    RxIsSpBpPlusImm, ///< rx = sp/bp + imm
    RxIsRxPlusImm,   ///< rx = rx + imm
    MovImm,          ///< rx = big imm
    MovBpToSp,       ///< sp = bp
    MovSpToBp,       ///< bp = sp
    Nothing,         ///< don't generate cfi for this
    Error            ///< error
  };

  // Get pass name.
  StringRef getPassName() const { return "Codasip CFI Adder"; }

  // Empty constructor.
  CfiAdder()
      : MachineFunctionPass(ID), TII(nullptr), TRI(nullptr), CRI(nullptr),
        TFL(nullptr), TM(nullptr) {
    reInitialize();
  }

  // Constructor.
  CfiAdder(CodasipTargetMachine &tm)
      : MachineFunctionPass(ID), TII(tm.getInstrInfo()),
        TRI(tm.getRegisterInfo()),
        CRI(static_cast<const CodasipRegisterInfo *>(TRI)),
        TFL(tm.getFrameLowering()), TM(&tm) {
    reInitialize();
  }

  bool runOnMachineFunction(MachineFunction &MF);
  static char ID;

protected:
  const CodasipInstrInfo *TII;
  const TargetRegisterInfo *TRI;
  const CodasipRegisterInfo *CRI;
  const TargetFrameLowering *TFL;
  const CodasipTargetMachine *TM;
  /// Current machine function.
  MachineFunction *MF;
  /// Current examined instruction.
  MachineInstr *ExaminedIns;
  /// Maps register number with immediate value that register contains.
  RegImmMap FoundMoves;
  /// Shift of the (first) stack pointer is stored here
  int64_t SpShift;
  /// Shift of the base/frame pointer is stored here
  int64_t BpShift;
  /// Is true if changes to stack pointer are still relevant to cfi information
  /// (sp value wsn't yet coppied to bp).
  bool IsSpChangeRelevant;
  /// If return address is stored on stack, cfa computation must 
  /// account for this element on stack. 
  
  const int RaShift = 0;
  

protected:
  /// Returns MCCFIInstruction to coresponding MachineInstr.
  const MCCFIInstruction *transferToCfi(const MachineInstr &MI);
  /// \brief Checks if cfi ins from prologue and epilogue correctly follow each
  /// other.
  ///
  /// If not it rearanges them by creating new ones and erasing old ones.
  /// \param [in,out] MI - Examined cfi instruction.
  /// \param [in]     II - Place in MBB where MI is.
  /// \return true if any ins were moved.
  bool rearangeCfi(MachineInstr &MI, MachineBasicBlock::iterator II);
  /// \brief Rearange existind cfi from prolog if needed.
  /// \return true if any ins was moved.
  bool correctCFIIns(MachineFunction &MF);
  /// \brief Emits cfi for the ExaminedIns to the given place.
  /// \param [in] II - place where cfi ins will be emitted to.
  virtual bool emitCfi(MachineBasicBlock::iterator II);
  /// \brief Helper method for creating cfi instruction
  /// \param [in] OpType - Opcode of cfi instruction that will be created.
  /// \param [in] offset - Offset operand of cfi instruction.
  /// \param [in] reg    - Dwarf register operand of cfi instruction.
  /// \return CFIIndex of new cfi instruction.
  unsigned createCfiIns(MCCFIInstruction::OpType cfiOpc, int offset,
                        int reg = 0);
  /// \brief Creates internal representation for instruction operand.
  /// \param [out] operand - Structure for internal representation of operands
  /// that will be filled.
  /// \param [in]     n       - Node representing the operand in the semantics
  /// of ExamineIns.
  void createInternalOp(InternalOp &operand, const SDNode *n);
  /// \brief Resets all internal values so the CfiAdder can be used for another
  /// function.
  /// \param [in] mf - Machine function in which cfi instructions are being
  /// added.
  void reInitialize(MachineFunction *mf = nullptr);
  /// \brief Decodes the function of ExaminedIns based on its semantics.
  /// \param [out] ops    - Vector of internal representations of ExaminedIns
  /// operands. It will be filled.
  /// \param [out] op1Idx - Index of first operand of decoded state in
  /// ExaminedIns.
  /// \param [out] op2Idx - Index of second operand of decoded state in
  /// ExaminedIns.
  /// \param [in]  root   - Root node of ExaminedIns semantics.
  /// \param [out] sign   - Sign that will be used during cfi offset
  /// computation.
  /// \param [in]  space  - Number of address space it searches for sp/bp.
  /// \return State that ExaminedIns represents.
  CfiAdder::CfiOperation decodeStateGeneral(SmallVectorImpl<InternalOp> &ops,
                                            unsigned &op1Idx, unsigned &op2Idx,
                                            SDNode *root, int &sign,
                                            unsigned space);
  /// \brief Helps to decode the function of ADD ExaminedIns.
  /// \param [out] ops    - Vector of internal representations of ExaminedIns
  /// operands. It will be filled.
  /// \param [in]  op1Idx - Index of first operand of decoded state in
  /// ExaminedIns.
  /// \param [in]  op2Idx - Index of second operand of decoded state in
  /// ExaminedIns.
  /// \param [in]  space  - Number of address space it searches for sp/bp.
  /// ExaminedIns.
  /// \return State that ExaminedIns represents.
  CfiAdder::CfiOperation decodeStateAdd(const SmallVectorImpl<InternalOp> &ops,
                                        unsigned op1Idx, unsigned op2Idx,
                                        unsigned space);
  /// \brief Helps to decode the function of STORE ExaminedIns.
  /// \param [out] ops    - Vector of internal representations of ExaminedIns
  /// operands. It will be filled.
  /// \param [in]  op1Idx - Index of first operand of decoded state in
  /// ExaminedIns..
  /// \param [in]  op2Idx - Index of second operand of decoded state in
  /// ExaminedIns.
  /// \param [in]  space  - Number of address space it searches for sp/bp.
  /// \return State that ExaminedIns represents.
  CfiAdder::CfiOperation
  decodeStateStore(const SmallVectorImpl<InternalOp> &ops, unsigned op1Idx,
                   unsigned op2Idx, unsigned space);
  /// \brief Helps to decode the function of MOV ExaminedIns.
  /// \param [out] ops    - Vector of internal representations of ExaminedIns
  /// operands. It will be filled.
  /// \param [in]  space  - Number of address space it searches for sp/bp.
  /// \return State that ExaminedIns represents.
  CfiAdder::CfiOperation decodeStateMov(const SmallVectorImpl<InternalOp> &ops,
                                        unsigned space);
  /// \brief Returns codasips graph representation of instruction.
  /// \param [in]  examinedMi - Examinned instruction.
  /// \param [out]  sem - codasips graph instr representation. Needs to be
  /// deleted at the end.
  /// \return Root node of the graph.
  SDNode *getFilteredCodasipPattern(MachineInstr *examinedMi,
                                    SelectionDAG **sem);
  /// \brief Runs decodeStateGeneral through multiple address spaces.
  CfiAdder::CfiOperation decodeState(SmallVectorImpl<InternalOp> &ops,
                                     unsigned &op1Idx, unsigned &op2Idx,
                                     int &sign, SDNode *root);
};

} // end of anonymous namespace

#include "CodasipCustCfiAdder.inc"

char CfiAdder::ID = 0;

static RegisterPass<CustCfiAdder> X("cfi-adder", "Codasip CFI Adder", false,
                                    false);

/// Preprocess root nodes of instruction.
/// \param [in] roots - Vector of all roots of instruction semantics DAG.
/// \return One root used for instruction recognition or nullptr when
/// instruction doesn't have valid roots.
static SDNode *filterRoots(std::vector<SDValue> &roots) {
  SDNode *root = nullptr;
  unsigned numOfValidRoots = 0;
  for (SDValue &hlpRoot : roots) {
    // discard roots that only set some flag (1-bit outputs)
    if (hlpRoot->getOpcode() == ISD::CopyToReg &&
        hlpRoot->getOperand(1).getScalarValueSizeInBits() == 1) {
      continue;
    }
    ++numOfValidRoots;
    root = hlpRoot.getNode();
  }
  // incorrect number of valid roots
  if (numOfValidRoots != 1) {
    return nullptr;
  }
  // empty semantics
  if (root->getOpcode() == ISD::EntryToken) {
    return nullptr;
  }
  return root;
}

void CfiAdder::reInitialize(MachineFunction *mf) {
  SpShift = 0;
  BpShift = 0;
  IsSpChangeRelevant = true;
  MF = mf;
  ExaminedIns = nullptr;
}

bool CfiAdder::correctCFIIns(MachineFunction &MF) {
  bool movedIns = false;
  bool changed = false;
  for (MachineFunction::iterator FI = MF.begin(); FI != MF.end(); ++FI) {
    do {
      for (MachineBasicBlock::iterator MBI = FI->begin(); MBI != FI->end();
           ++MBI) {
        MachineInstr &MI = *MBI;
        // basic cfi emitted in frame lowering
        if (MI.getOpcode() == TargetOpcode::CFI_INSTRUCTION &&
            MI.getFlag(MachineInstr::FrameSetup)) {
          movedIns = rearangeCfi(MI, MBI);
          changed |= movedIns;
          if (movedIns) {
            break;
          }
        }
      }
    } while (movedIns);
  }
  return changed;
}

bool CfiAdder::rearangeCfi(MachineInstr &MI, MachineBasicBlock::iterator II) {
  DebugLoc dl;
  MachineBasicBlock *MB = II->getParent();
  const MCCFIInstruction *cfiIns = transferToCfi(MI);

  // check the type of cfi ins
  switch (cfiIns->getOperation()) {
  case MCCFIInstruction::OpDefCfa:
    if (&(*MF->begin()) != MB || II == MB->begin()) {
      return false;
    }
    // create this cfa ins on new place and erase the old one
    BuildMI(*MB, MB->begin(), dl, TII->get(TargetOpcode::CFI_INSTRUCTION))
        .addCFIIndex(MI.getOperand(0).getCFIIndex())
        .setMIFlag(MachineInstr::FrameSetup);
    MI.eraseFromParent();
    return true;
  default:
    return false;
  }
  return false;
}

const MCCFIInstruction *CfiAdder::transferToCfi(const MachineInstr &MI) {
  if (MI.getOpcode() != TargetOpcode::CFI_INSTRUCTION) {
    return nullptr;
  }
  assert(MI.getOperand(0).isCFIIndex());
  unsigned cfiIndex = MI.getOperand(0).getCFIIndex();
  return &(MF->getFrameInstructions()[cfiIndex]);
}

bool CfiAdder::runOnMachineFunction(MachineFunction &MF_) {
  bool changed = false;
  reInitialize(&MF_);
  changed |= correctCFIIns(*MF);
  for (MachineFunction::iterator FI = MF->begin(); FI != MF->end(); ++FI) {
    MachineBasicBlock::iterator MBI = FI->begin();
    // loop that can iterate also through ins inside bundles
    for (MachineInstr &MI : FI->instrs()) {
      // get te position of the beggining of the bundle that MI is in
      if (MI.isBundle()) {
        MBI = MI.getIterator();
      }
      // if target does not have bundles, get the position of MI
      else if (!MI.isBundle() && !MI.isInsideBundle()) {
        MBI = MI.getIterator();
      }
      // basic cfi emitted in frame lowering
      if (MI.getOpcode() == TargetOpcode::CFI_INSTRUCTION)
        continue;
      // is this setup/destroy?
      if (!(MI.getFlag(MachineInstr::FrameSetup) ||
            MI.getFlag(MachineInstr::FrameDestroy))) {
        continue;
      }
      ExaminedIns = &MI;
      // emit cfi
      changed |= emitCfi(MBI);
    }
  }
  
  return changed;
}

unsigned CfiAdder::createCfiIns(MCCFIInstruction::OpType cfiOpc, int offset,
                                int reg) {
  unsigned CFIIndex = 0;
  if (cfiOpc == MCCFIInstruction::OpAdjustCfaOffset) {
    MCCFIInstruction cfiIns =
        MCCFIInstruction::createAdjustCfaOffset(nullptr, offset);
    CFIIndex = MF->addFrameInst(cfiIns);
  } else if (cfiOpc == MCCFIInstruction::OpDefCfa) {
    MCCFIInstruction cfiIns =
        MCCFIInstruction::createDefCfa(nullptr, reg, -offset);
    CFIIndex = MF->addFrameInst(cfiIns);
  } else if (cfiOpc == MCCFIInstruction::OpOffset) {
    MCCFIInstruction cfiIns =
        MCCFIInstruction::createOffset(nullptr, reg, offset);
    CFIIndex = MF->addFrameInst(cfiIns);
  } else {
    assert(false && " unsuported cfi ins");
  }
  return CFIIndex;
}

void CfiAdder::createInternalOp(InternalOp &operand, const SDNode *n) {
  switch (n->getOpcode()) {
  case ISD::CopyToReg:
    createInternalOp(operand, n->getOperand(1).getNode());
    return;
  case ISD::Register: {
    // get oper index
    assert(RegisterSDNode::classof(n));
    unsigned reg = cast<RegisterSDNode>(n)->getReg();
    operand.isReg = true;
    // fixreg
    if (!TargetRegisterInfo::isVirtualRegister(reg)) {
      operand.regNum = reg;
      operand.implicit = true;
      break;
    }
    MachineOperand op =
        ExaminedIns->getOperand(TargetRegisterInfo::virtReg2Index(reg));
    if (op.isReg()) {
      operand.regNum = op.getReg();
      break;
    }
    // other oper
    assert(op.isImm());
    operand.isReg = false;
    operand.implicit = false;
    operand.immVal = op.getImm();
    break;
  }
  case ISD::Constant:
    operand.isReg = false;
    operand.implicit = false;
    operand.immVal = cast<ConstantSDNode>(n)->getSExtValue();
    break;
  default:
    assert(false);
  }
  // set dwarf, if reg
  if (operand.isReg) {
    assert(operand.regNum >= 0);
    operand.dwarf = TRI->getDwarfRegNum(operand.regNum, 0);
    assert(operand.dwarf >= 0);
  }
}

CfiAdder::CfiOperation
CfiAdder::decodeStateMov(const SmallVectorImpl<InternalOp> &ops,
                         unsigned space) {
  if (!ops[DST].isReg) {
    return Error;
  }
  if (!ops[BASE].isReg && ops[DST].regNum != (int)CRI->GetSP(space) &&
      ops[DST].regNum != (int)CRI->GetBP(space)) {
    return MovImm;
  }
  if (!ops[BASE].isReg) {
    return Error;
  }
  if (ops[DST].regNum == (int)CRI->GetSP(space) &&
      ops[BASE].regNum == (int)CRI->GetBP(space) && TFL->hasFP(*MF)) {
    return MovBpToSp;
  }
  if (ops[DST].regNum == (int)CRI->GetBP(space) &&
      ops[BASE].regNum == (int)CRI->GetSP(space) && TFL->hasFP(*MF)) {
    return MovSpToBp;
  }
  if (ops[DST].regNum == (int)CRI->GetSP(space) &&
      ops[BASE].regNum == (int)CRI->GetSP(space)) {
    return Nothing;
  }
  return Error;
}

CfiAdder::CfiOperation
CfiAdder::decodeStateStore(const SmallVectorImpl<InternalOp> &ops,
                           unsigned op1Idx, unsigned op2Idx, unsigned space) {
  if (!ops[VAL].isReg || ops[VAL].regNum == (int)CRI->GetSP(space)) {
    return Error;
  }
  if (!ops[op1Idx].isReg || (ops[op2Idx].isReg && !ops[op2Idx].notFilled())) {
    return Error;
  }
  if (!TFL->hasFP(*MF) && ops[VAL].regNum == (int)CRI->GetBP(space)) {
    if (ops[op1Idx].regNum == (int)CRI->GetSP(space)) {
      if (ops[op2Idx].notFilled()) {
        return StoreBpSp;
      } else {
        return StoreBpSpImm;
      }
    }
  }
  if (ops[op1Idx].regNum == (int)CRI->GetSP(space)) {
    if (ops[op2Idx].notFilled()) {
      return StoreRarSp;
    } else {
      return StoreRarSpImm;
    }
  }
  if (ops[op1Idx].regNum == (int)CRI->GetBP(space)) {
    if (ops[op2Idx].notFilled()) {
      return StoreRarBp;
    } else {
      return StoreRarBpImm;
    }
  }
  if (ops[op1Idx].regNum != (int)CRI->GetSP(space) &&
      ops[op1Idx].regNum != (int)CRI->GetBP(space)) {
    if (FoundMoves.count(ops[op1Idx].regNum) == 0) {
      return Error;
    }
    if (ops[op2Idx].notFilled()) {
      return StoreRarRx;
    } else {
      return StoreRarRxImm;
    }
  }
  return Error;
}

CfiAdder::CfiOperation
CfiAdder::decodeStateAdd(const SmallVectorImpl<InternalOp> &ops,
                         unsigned op1Idx, unsigned op2Idx, unsigned space) {
  if (!ops[DST].isReg || !ops[op1Idx].isReg) {
    return Error;
  }
  // no imm in instruction
  if (ops[op2Idx].isReg) {
    // .. = .. + rx
    if (ops[op2Idx].regNum == (int)CRI->GetSP(space) ||
        ops[op2Idx].regNum == (int)CRI->GetBP(space)) {
      return Error;
    }
    // .. = sp + rx
    if (ops[op1Idx].regNum != (int)CRI->GetSP(space)) {
      return Error;
    }
    // we know what imm goes to rx
    if (FoundMoves.count(ops[op2Idx].regNum) == 0) {
      return Error;
    }
    // sp = sp + rx
    if (ops[DST].regNum == (int)CRI->GetSP(space)) {
      return SpIsSpPlusRx;
    }
    // bp = sp + rx
    if (ops[DST].regNum == (int)CRI->GetBP(space)) {
      return BpIsSpPlusRx;
    }
    // rx = sp + rx
    // if this needs to be modified, try it also on model test-5879-16bit
    if (ops[DST].regNum == ops[op2Idx].regNum) {
      return Nothing;
    }
  }
  // immediate in instruction
  // .. = .. + imm
  else if (!ops[op2Idx].isReg) {
    // sp = .. + imm
    if (ops[DST].regNum == (int)CRI->GetSP(space)) {
      // sp = sp + imm
      if (ops[op1Idx].regNum == (int)CRI->GetSP(space)) {
        // In frame setup, when cfa is moved from SP to BP and then the SP is
        // updated,
        // don't change cfi computation
        if (TFL->hasFP(*MF) && !IsSpChangeRelevant &&
            ExaminedIns->getFlag(MachineInstr::FrameSetup)) {
          return Nothing;
        }
        return SpIsSpPlusImm;
      }
      // sp = bp + imm
      if (ops[op1Idx].regNum == (int)CRI->GetBP(space)) {
        return SpIsBpPlusImm;
      }
    }
    // bp = sp + imm
    if (ops[DST].regNum == (int)CRI->GetBP(space) &&
        ops[op1Idx].regNum == (int)CRI->GetSP(space)) {
      return BpIsSpPlusImm;
    }
    // bp = bp + imm
    if (ops[DST].regNum == (int)CRI->GetBP(space) &&
        ops[op1Idx].regNum == (int)CRI->GetBP(space) && TFL->hasFP(*MF)) {
      return BpIsBpPlusImm;
    }
    // rx = .. + imm
    if (ops[DST].regNum != (int)CRI->GetBP(space) &&
        ops[DST].regNum != (int)CRI->GetBP(space)) {
      // rx = sp/bp + imm
      if (ops[op1Idx].regNum == (int)CRI->GetSP(space) ||
          ops[op1Idx].regNum == (int)CRI->GetBP(space)) {
        return RxIsSpBpPlusImm;
      } else {
        // rx = rx + imm
        if (FoundMoves.count(ops[op1Idx].regNum) == 0) {
          return Error;
        }
        return RxIsRxPlusImm;
      }
    }
  }
  return Error;
}

CfiAdder::CfiOperation
CfiAdder::decodeStateGeneral(SmallVectorImpl<InternalOp> &ops, unsigned &op1Idx,
                             unsigned &op2Idx, SDNode *root, int &sign,
                             unsigned space) {
  if (!root) {
    return Error;
  }
  switch (root->getOpcode()) {
  default:
    return Error;
  case ISD::STORE: {
    if (root->getOperand(1).getOpcode() != ISD::Register) {
      return Error;
    }
    createInternalOp(ops[VAL], root->getOperand(1).getNode());
    root = root->getOperand(2).getNode();
    if (root->getOpcode() == ISD::Register) {
      createInternalOp(ops[BASE], root);
    } else if (root->getOpcode() == ISD::ADD) {
      if (root->getOperand(0).getOpcode() != ISD::Register ||
          root->getOperand(1).getOpcode() != ISD::Register) {
        return Error;
      }
      createInternalOp(ops[BASE], root->getOperand(0).getNode());
      createInternalOp(ops[OFF], root->getOperand(1).getNode());
    } else {
      return Error;
    }
    // store of RAR/BP
    if (!ops[VAL].isReg && !ops[BASE].isReg) {
      return Error;
    }
    op1Idx = BASE;
    op2Idx = OFF;
    CfiOperation state = decodeStateStore(ops, op1Idx, op2Idx, space);
    if (state == Error) {
      op1Idx = OFF;
      op2Idx = BASE;
      state = decodeStateStore(ops, op1Idx, op2Idx, space);
    }
    return state; // End of STORE case
  }
  case ISD::CopyToReg: {
    createInternalOp(ops[DST], root);
    root = root->getOperand(2).getNode();
    switch (root->getOpcode()) {
    default:
      return Error;
    case ISD::SUB:
      sign = sign * (-1);
      LLVM_FALLTHROUGH;
    case ISD::ADD: {
      if (root->getOperand(0).getOpcode() != ISD::Register ||
          root->getOperand(1).getOpcode() != ISD::Register) {
        return Error;
      }
      createInternalOp(ops[BASE], root->getOperand(0).getNode());
      createInternalOp(ops[OFF], root->getOperand(1).getNode());
      op1Idx = BASE;
      op2Idx = OFF;
      CfiOperation state = decodeStateAdd(ops, op1Idx, op2Idx, space);
      if (state == Error) {
        op1Idx = OFF;
        op2Idx = BASE;
        state = decodeStateAdd(ops, op1Idx, op2Idx, space);
      }
      return state;
    }
    case ISD::Register: {
      // it is mov that moves big immediate to general purpouse register
      // that will be later added to sp or bp
      createInternalOp(ops[BASE], root);
      op2Idx = op1Idx = BASE;
      CfiOperation state = decodeStateMov(ops, space);
      return state;
    }
    case ISD::LOAD:
      return Nothing;
    }
    return Error; // End of CopyToReg case
  }
  }
  return Error;
}

SDNode *CfiAdder::getFilteredCodasipPattern(MachineInstr *examinedMi,
                                            SelectionDAG **sem) {
  std::vector<SDValue> roots;
  *sem = GetCodasipPattern(*TM, *MF, examinedMi->getOpcode(), roots);
  LLVM_DEBUG({
    dbgs() << "instr: ";
    examinedMi->dump();
    dbgs() << " with semantics: ";
    (*sem)->dump();
  });
  SDNode *root = filterRoots(roots);
  if (root == nullptr) {
    LLVM_DEBUG(errs() << "cfi emission: unsupported kind of a frame operation "
                      << "encountered\n";);
    roots.clear();
    delete *sem;
    return nullptr;
  }
  return root;
}

CfiAdder::CfiOperation CfiAdder::decodeState(SmallVectorImpl<InternalOp> &ops,
                                             unsigned &op1Idx, unsigned &op2Idx,
                                             int &sign, SDNode *root) {
  // emit proper cfi
  CfiAdder::CfiOperation state = Nothing;
  for (unsigned space = 0; space < STACK_COUNT; ++space) {
    state = decodeStateGeneral(ops, op1Idx, op2Idx, root, sign, space);
    // it is valid operation in default address space
    if (state != Error && space == CFA_ADDR_SPACE) {
      break;
    }
    // it is valid stack operation but in address space that doesn't ifluence
    // cfa computation
    if (state != Error && space != CFA_ADDR_SPACE) {
      state = Nothing;
      break;
    }
  }
  return state;
}

// we need iterator in case of bundles
bool CfiAdder::emitCfi(MachineBasicBlock::iterator II) {
  MachineBasicBlock *MB = II->getParent();
  DebugLoc dl = ExaminedIns->getDebugLoc();
  ++II;
  // determine setup/destroy
  const bool isSetup = ExaminedIns->getFlag(MachineInstr::FrameSetup);
  MachineInstr::MIFlag flag =
      (isSetup ? MachineInstr::FrameSetup : MachineInstr::FrameDestroy);
  // Frame destroy instructions should not go beyond this point,
  // it breaks cxx library.
  // get instr code and semantics
  if (!isSetup) {
    return false;
  }
  SelectionDAG *sem = nullptr;
  SDNode *root = getFilteredCodasipPattern(ExaminedIns, &sem);
  if (!root) {
    return false;
  }
  // operands (dst, base/src, off)
  SmallVector<InternalOp, 3> ops;
  ops.resize(3);
  unsigned op1Idx = 0, op2Idx = 0;
  int sign = -1;
  CfiAdder::CfiOperation state = decodeState(ops, op1Idx, op2Idx, sign, root);
  unsigned CFIIndex;
  bool buildsIns = true;
  LLVM_DEBUG(dbgs() << "decoded state: " << state << "\n\n";);
  switch (state) {
  case SpIsSpPlusImm: {
    int64_t immVal = sign * ops[op2Idx].immVal;
    // remember the shift
    // must take value * sign so that we have information if it was sub
    SpShift += immVal;
    CFIIndex = createCfiIns(MCCFIInstruction::OpAdjustCfaOffset, immVal);
    break;
  }
  case SpIsSpPlusRx: {
    int64_t immVal = sign * FoundMoves[ops[op2Idx].regNum];
    SpShift += immVal;
    CFIIndex = createCfiIns(MCCFIInstruction::OpAdjustCfaOffset, immVal);
    break;
  }
  case SpIsBpPlusImm: {
    assert(TFL->hasFP(*MF));
    int64_t immVal = sign * ops[op2Idx].immVal;
    CFIIndex = createCfiIns(MCCFIInstruction::OpDefCfa, immVal, ops[DST].dwarf);
    break;
  }
  case BpIsBpPlusImm: {
    int64_t immVal = sign * ops[op2Idx].immVal;
    BpShift += immVal;
    CFIIndex = createCfiIns(MCCFIInstruction::OpAdjustCfaOffset, immVal);
    break;
  }
  case MovBpToSp: {
    CFIIndex =
        createCfiIns(MCCFIInstruction::OpDefCfa, BpShift, ops[DST].dwarf);
    break;
  }
  case MovSpToBp: {
    CFIIndex = createCfiIns(MCCFIInstruction::OpDefCfa, SpShift + RaShift,
                            ops[DST].dwarf);
    IsSpChangeRelevant = false;
    break;
  }
  case BpIsSpPlusImm: {
    assert(TFL->hasFP(*MF));
    int64_t immVal = SpShift + RaShift + sign * ops[op2Idx].immVal;
    BpShift += immVal;
    CFIIndex = createCfiIns(MCCFIInstruction::OpDefCfa, immVal, ops[DST].dwarf);
    IsSpChangeRelevant = false;
    break;
  }
  case BpIsSpPlusRx: {
    assert(TFL->hasFP(*MF));
    int64_t immVal = SpShift + RaShift + sign * FoundMoves[ops[op2Idx].regNum];
    BpShift += immVal;
    CFIIndex = createCfiIns(MCCFIInstruction::OpDefCfa, immVal, ops[DST].dwarf);
    IsSpChangeRelevant = false;
    break;
  }
  case RxIsSpBpPlusImm: {
    FoundMoves[ops[DST].regNum] = ops[op2Idx].immVal;
    buildsIns = false;
    break;
  }
  case MovImm: {
    FoundMoves[ops[DST].regNum] = ops[op2Idx].immVal;
    buildsIns = false;
    break;
  }
  case RxIsRxPlusImm: {
    FoundMoves[ops[DST].regNum] += ops[op2Idx].immVal;
    buildsIns = false;
    break;
  }
  case StoreBpSpImm:
  case StoreRarSpImm: {
    int64_t immVal = ops[op2Idx].immVal + sign * (SpShift + RaShift);
    CFIIndex = createCfiIns(MCCFIInstruction::OpOffset, immVal, ops[VAL].dwarf);
    break;
  }
  case StoreRarBpImm: {
    int64_t immVal = ops[op2Idx].immVal + sign * BpShift;
    CFIIndex = createCfiIns(MCCFIInstruction::OpOffset, immVal, ops[VAL].dwarf);
    break;
  }
  case StoreRarRx: {
    int64_t immVal =
        FoundMoves[ops[op1Idx].regNum] + sign * (SpShift + RaShift);
    CFIIndex = createCfiIns(MCCFIInstruction::OpOffset, immVal, ops[VAL].dwarf);
    break;
  }
  case StoreBpSp:
  case StoreRarSp: {
    int64_t immVal = sign * (SpShift + RaShift);
    CFIIndex = createCfiIns(MCCFIInstruction::OpOffset, immVal, ops[VAL].dwarf);
    break;
  }
  case StoreRarBp: {
    CFIIndex = createCfiIns(MCCFIInstruction::OpOffset, sign * BpShift,
                            ops[VAL].dwarf);
    break;
  }
  case StoreRarRxImm: {
    int64_t immVal = FoundMoves[ops[op1Idx].regNum] + ops[op2Idx].immVal +
                     sign * (SpShift + RaShift);
    CFIIndex = createCfiIns(MCCFIInstruction::OpOffset, immVal, ops[VAL].dwarf);
    break;
  }
  case Nothing:
    buildsIns = false;
    break;
  case Error:
    LLVM_DEBUG(errs() << "cfi emission: unsupported kind of a frame operation"
                      << " encountered\n\n";);
    buildsIns = false;
  }
  if (buildsIns) {
    BuildMI(*MB, II, dl, TII->get(TargetOpcode::CFI_INSTRUCTION))
        .addCFIIndex(CFIIndex)
        .setMIFlag(flag);
  }
  // free dag
  if (sem) {
    delete sem;
  }
  return buildsIns;
}

FunctionPass *llvm::createCodasipCfiAdder(CodasipTargetMachine &tm) {
  return new CustCfiAdder(tm);
}
