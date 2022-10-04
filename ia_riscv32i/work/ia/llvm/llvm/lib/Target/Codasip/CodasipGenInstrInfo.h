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


#ifndef CODASIPGENINSTRUCTIONINFO_H
#define CODASIPGENINSTRUCTIONINFO_H

#include "Codasip.h"
#include "CodasipRegisterInfo.h"
#include "CodasipInstructionSemantics.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/ScheduleHazardRecognizer.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/ISDOpcodes.h"
#include "codasip/Target/CodasipBaseTargetInstrInfo.h"

#include <set>

#define TargetInstrInfo CodasipBaseInstrInfo
#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_HEADER
#include "CodasipGenInstrInfo.inc"
#undef TargetInstrInfo

namespace llvm
{

/// Auxiliary structure for storing information about jumps
struct JumpInfo
{
  /// Zero, if indirect
  unsigned Length;
  bool IsAbsolute;
  /// Set if relative. 0 means signed.
  char Direction;
};

/// Auxiliary structure for returning information about builtins
/// It's easier to generate this than to read this from instruction information or from GetImmProperties
struct BuiltinInfo
{
  /// Corresponding DAG node ID (CodasipISD::NodeType)
  unsigned NodeID;
  /// Instruction opcode of the corresponding base instruction
  unsigned InstrID;
  /// Data types of input operands
  std::vector<MVT> InputInfo;
  /// Which operands are imms? (true vals)
  /// Indexes correspond with InputInfo
  /// - indexes in an IR call are shifted by one
  std::vector<bool> InputInfo2;
};

class CodasipGenInstrInfo2: public CodasipGenInstrInfo
{
  const CodasipRegisterInfo RI;

public:
  explicit CodasipGenInstrInfo2(CodasipTargetMachine &TM);
  const CodasipRegisterInfo& getRegisterInfo() const {return RI;}
  void copyPhysReg(MachineBasicBlock &MBB,
                   MachineBasicBlock::iterator MI,
                   const DebugLoc& DL,
                   unsigned DestReg,
                   unsigned SrcReg,
                   bool KillSrc) const override;
  void storeRegToStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MBBI,
                           unsigned SrcReg,
                           bool isKill,
                           int FrameIndex,
                           const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI) const override;
  void loadRegFromStackSlot(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MBBI,
                            unsigned DestReg,
                            int FrameIndex,
                            const TargetRegisterClass *RC,
                            const TargetRegisterInfo *TRI) const override;
  /// Emits a basic instruction (e.g. SP+Imm)
  virtual void EmitEssentialInstr(MachineBasicBlock &MBB,
                                  MachineBasicBlock::iterator MI,
                                  DebugLoc DL,
                                  ISD::NodeType Opc,
                                  SmallVectorImpl<MachineOperand> &Ops) const;
  unsigned getAnalyzableBrOpc(unsigned Opc) const override;
  bool reverseBranchCondition(SmallVectorImpl<MachineOperand> &Cond) const override;
  bool analyzeCompare(const MachineInstr &MI, unsigned &SrcReg, unsigned &SrcReg2, int &CmpMask, int &CmpValue) const override;
  /// Returns the length of a jump in bites.
  JumpInfo GetJumpInfo(int op) const;
  llvm::ISD::CondCode isCondWithSense(int opc) const override;
  void getCodasipInstr(std::vector<int> &Opcs, int Operation, MVT Type) const override;
  void getCondBranchOpc(std::vector<int>& Opcs, ISD::CondCode CC) const override;
  /** Retrieves info about an imm operand.
   * \param opcode  ID of an instruction.
   * \param opnum   Index of an operand. */
  void GetImmProperties(unsigned opCode, unsigned opNum, int& width, bool& sign, int& trunc) const;
  /// Retrieve info about a builtin
  BuiltinInfo GetBuiltinInfo(unsigned intrinCode) const;
  ScheduleHazardRecognizer* CreateTargetPostRAHazardRecognizer(const InstrItineraryData *II, const ScheduleDAG *DAG) const override;
  bool expandPostRAPseudo(MachineInstr& MI) const override;
  /** Central implementation of expansion of dummy instructions and emulations with custom insertors.
   * \param MIp   Pointer at the instruction which needs replacing.
   * \param BB    Input and return basic block as for EmitInstrWithCustomInserter.
   * \param postRA Is called post-RA?
   * \return   Was there a change? */
  virtual bool ExpandDummiesImpl(MachineInstr *MIp, MachineBasicBlock* &BB, const bool postRA) const;
  unsigned getRA() const override;
  unsigned getBP(unsigned space) const override;
  llvm::SelectionDAG* GetCodasipPattern(const TargetMachine &TM, MachineFunction &mf, unsigned icode, std::vector<SDValue>& roots) const override;
  unsigned getLongJumpOpcode() const;
  unsigned getLongCallOpcode() const;
  unsigned getShortCallOpcode() const;
  unsigned getLongTailCallOpcode() const;
  unsigned getShortTailCallOpcode() const;
  // === VLIW-related methods ===
  void insertNoop(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI) const override;
  void insertNoopOnPos(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, unsigned pos) const override;
  void getAllPosInBundle(int opc, SlotData &vect) const override;
  static void getAllPosInBundleImpl(int opc, SlotData &vect);
  bool isSchedulingBoundary(const MachineInstr &MI, const MachineBasicBlock *MBB, const MachineFunction &MF) const override;
  virtual bool isPredicable(const MachineInstr &MI) const override;
  virtual bool PredicateInstruction(MachineInstr &MI,
                                    ArrayRef<MachineOperand> Cond) const override;
  virtual bool isProfitableToIfCvt(MachineBasicBlock &MBB, unsigned NumCycles,
                                   unsigned ExtraPredCycles,
                                   BranchProbability Probability) const override;
  virtual bool isProfitableToIfCvt(MachineBasicBlock &TMBB,
                                   unsigned NumTCycles, unsigned ExtraTCycles,
                                   MachineBasicBlock &FMBB,
                                   unsigned NumFCycles, unsigned ExtraFCycles,
                                   BranchProbability Probability) const override;
  virtual bool isPredicated(const MachineInstr &MI) const override;
  virtual bool isPredicated(unsigned Opcode) const;
  virtual bool isPredicatedTrue(const MachineInstr &MI) const;
  virtual bool isPredicatedTrue(unsigned Opcode) const;
  virtual bool DefinesPredicate(MachineInstr &MI, std::vector<MachineOperand> &Pred) const override;
  virtual bool SubsumesPredicate(ArrayRef<MachineOperand> Pred1,
                                 ArrayRef<MachineOperand> Pred2) const override;
  virtual bool isPredicableBlock(MachineBasicBlock &MBB, SmallVectorImpl<MachineOperand> &Cond) const override;
  virtual bool isProfitableToDupForIfCvt(MachineBasicBlock &MBB, unsigned NumCycles,
                                         BranchProbability Probability) const override;
  virtual unsigned getEquivalentCondOpcode(ArrayRef<MachineOperand> Cond, int RegPos) const;
  /// Is lib cs supported?
  bool LibCSSupported() const;
  /// Instruction for LibCS call
  unsigned GetLibCSSpillInstr() const;
  /// RA register for LibCS call
  unsigned GetLibCSSpillReg() const;
  /// Return size of the MI in bytes, zero if unknown.
  unsigned getInstSizeInBytes(const MachineInstr &MI) const override;
  /// In case the link register (RA) needs to be saved, find a unused register
  /// that can be used for saving before calling an outlined function and
  /// restored after.
  unsigned findRegisterToSaveLRTo(const outliner::Candidate &C) const;
  /// Return true if the function can safely be outlined from.
  bool isFunctionSafeToOutlineFrom(MachineFunction &MF, bool OutlineFromLinkOnceODRs) const override;
  /// Return true if MBB is safe to outline from, and return any
  /// target-specific information in Flags.
  bool isMBBSafeToOutlineFrom(MachineBasicBlock &MBB, unsigned &Flags) const override;
  /// Calculate target-specific information for a set of outlining candidates.
  outliner::OutlinedFunction getOutliningCandidateInfo(std::vector<outliner::Candidate> &RepeatedSequenceLocs) const override;
  /// Return if/how a given MachineInstr should be outlined.
  outliner::InstrType getOutliningType(MachineBasicBlock::iterator &MBBI, unsigned Flags) const override;
  /// Insert a custom frame for outlined functions.
  void buildOutlinedFrame(MachineBasicBlock &MBB, MachineFunction &MF, const outliner::OutlinedFunction &OF) const override;
  /// Insert a call to an outlined function into a given basic block.
  MachineBasicBlock::iterator insertOutlinedCall(Module &M, MachineBasicBlock &MBB,
                                                 MachineBasicBlock::iterator &It,
                                                 MachineFunction &MF,
                                                 const outliner::Candidate &C) const override;
  // outline by default if optimizing for size
  bool shouldOutlineFromFunctionByDefault(MachineFunction &MF) const override;

protected:
  int ReverseBranchConditionOpc(int Opc) const;
  /// Optimization set of instructions handled in ExpandDummiesImpl
  std::set<unsigned> ExpandedInstrs;
  /** Instruction used for lib callee saved regs call.
   * Default/invalid value is 0 (Codasip::PHI). */
  unsigned LibCSSpillInstr;
  /** Alternate RA register (for LibCSSpillInstr).
   * Default/invalid value is 0 (Codasip::NoRegister). */
  unsigned LibCSSpillReg;
  
private:
  bool useAlternativeLinkReg() const;
  int getMatchingCondBranchOpcode(int Opc, bool sense) const;
  bool isPredReg(const MachineOperand *PredMO) const;
  bool copyCondToPredReg(MachineOperand *PredMO) const;
  bool isLiveInMBB(MachineInstr *ParentInstr, unsigned Reg) const;
  MachineBasicBlock::iterator identifyPositionInParentBlock( MachineInstr *PredMOSource) const;
  bool getFreePredRegister(MachineInstr *ParentInstr, unsigned *FreePredReg) const;
  bool isThereSuitableCopy(MachineOperand *PredMO) const; 
  bool isThereSuitableCondEmul(ArrayRef<MachineOperand> Cond, int RegPos, MachineOperand *PredMO, MachineInstr *PredInstr, bool &InvertJump) const;
  bool emulCondToPredReg(ArrayRef<MachineOperand> Cond, int RegPos, MachineOperand *PredMO, MachineInstr *PredInst) const;
  unsigned getPredReg(MachineInstr *MI) const;
  bool isCondNegated(unsigned Opc, unsigned OpcNeg, MachineFunction *MF) const;
  llvm::ISD::CondCode getISDType(unsigned Opc, MachineFunction *MF) const;
  bool LowerExtractSubreg(MachineInstr* MIp, MachineBasicBlock* &MBB) const;
};

/** Checks a value for imm oper.
 * Needs to be globally visible, is called from various places. */
bool CheckImmImpl(int64_t Imm, int width, bool sign, int trunc);

/// Computes distance between two points in a function
unsigned ComputeDistance(MachineFunction &F, MachineFunction::iterator FI, MachineBasicBlock::instr_iterator I, MachineBasicBlock *dest);

/// Reads (or computes, if inline asm) encoding size
unsigned GetEncodingSize(const MachineBasicBlock::instr_iterator &I);

/// Is the given intrinsic code a codasip one?
bool IsCodasipIntrin(unsigned intrinCode);
/// Is the given intrinsic code a codasip memory intrinsic?
bool IsCodasipMemIntrin(unsigned intrinCode);

inline unsigned CodasipGenInstrInfo2::GetLibCSSpillInstr() const
{
  return LibCSSpillInstr;
}

inline unsigned CodasipGenInstrInfo2::GetLibCSSpillReg() const
{
  return LibCSSpillReg;
}

inline llvm::SelectionDAG* CodasipGenInstrInfo2::GetCodasipPattern(const TargetMachine &TM,
                                                                   MachineFunction &mf,
                                                                   unsigned icode,
                                                                   std::vector<SDValue>& roots) const
{
  return llvm::GetCodasipPattern(TM, mf, icode, roots);
}

inline unsigned CodasipGenInstrInfo2::getRA() const
{
  return RI.getRARegister();
}

inline unsigned CodasipGenInstrInfo2::getBP(unsigned space) const
{
  return RI.GetBP(space);
}

}

#endif
