/**
 * Codasip Ltd
 *
 * Copyright 2016 Codasip Ltd
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this
 * file, may be use, copied, modified, or distributed except in accordance with
 * the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 * \file    CodasipBaseJumplengthChecker.h
 * \date    26. 1. 2016
 * \author  Stanislav Melo
 * \version 5.5.0.
 * \brief   Base class for JumpLengthChecker
 */

#ifndef INCLUDE_CODASIP_TARGET_CODASIPBASEJUMPLENGTHCHECKER_H_
#define INCLUDE_CODASIP_TARGET_CODASIPBASEJUMPLENGTHCHECKER_H_

#include "codasip/Target/CodasipBaseTargetInstrInfo.h"
#include "codasip/misc/CodasipBaseJumpInfo.h"
#include "codasip/misc/utils.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineInstrBundle.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

//#define VERBOSE_J_LEN_CHECKER

namespace llvm {

struct BaseJumpLengthChecker : public MachineFunctionPass {
  // rename a type
  using BaseJumpInfoPtrListIt =
      std::list<std::shared_ptr<BaseJumpInfo>>::iterator;

  const TargetMachine *TM;
  /// Number of replaced instructions
  unsigned Counter;
  bool IsVliw = false;
  const CodasipBaseInstrInfo *CTII;
  MachineFunction *MF;
  LTOFileInfo *LtoFile;
  static char ID;
  /// List of all jump/call instructions that must be examined if they can jump
  /// to their destination.
  std::list<std::shared_ptr<BaseJumpInfo>> InstrsToExamine;

  BaseJumpLengthChecker(TargetMachine &tm, const CodasipBaseInstrInfo *ti,
                        char &ID);

  // only for initialization, do not use. TM needs to be initialized
  // by a proper ctor.
  BaseJumpLengthChecker();

  virtual ~BaseJumpLengthChecker();

  StringRef getPassName() const override {
    return "Codasip Jump Length Checker";
  }

  bool runOnMachineFunction(MachineFunction &F) override;

  /// \brief Creates new jump/call instruction in mbb.
  ///
  /// If new jump is replacing an old one, oldJump must be specified. Otherwise
  /// it is nullptr.
  MachineInstr *makeNewJumpCall(const BaseJumpInfo *oldJump,
                                BaseJumpInfo *newJump);

  /// Creates bundle of NOPs and newJump in mbb.
  MachineInstr *createJumpBundle(const BaseJumpInfo *newJump);

  /// Fills InstrsToExamine list
  void fillInstrsToExamine(MachineBasicBlock &mbb);

  /// Runs the pass on instructions from InstrsToExamine list. Returns true if
  /// any changes were made.
  bool runCheck();

  /// Handles the case when conditional jump can't reach its destination and
  /// model doesn't have conditional jump with inverted condition.
  void handleShortJumpGen(const BaseJumpInfoPtrListIt &oldInstrIt);

  /// Handles the case when conditional jump can't reach its destination but
  /// model has conditional jump with inverted condition.
  /// Takes iterator pointing to currently examinned instruction.
  /// Returns incremented input iterator.
  BaseJumpInfoPtrListIt
  handleShortJumpGenInvert(BaseJumpInfoPtrListIt &oldInstrIt);

  /// \brief Replaces jump instruction with another one that can reach the
  /// destination.
  ///
  /// If old jump can jump to destination, it does nothing and returns false.
  /// Takes iterator pointing to currently examinned instruction.
  /// Returns incremented input iterator if successfull replacement,
  /// unincremented input iterator otherwise.
  BaseJumpInfoPtrListIt getBiggerJump(BaseJumpInfoPtrListIt &oldInstrIt);

  /// \brief Replaces call instruction with another one that can reach the
  /// destination.
  ///
  /// If old call can jump to destination, it does nothing and returns false.
  /// Takes iterator pointing to currently examinned instruction.
  /// Returns incremented input iterator if successfull replacement,
  /// unincremented input iterator otherwise.
  BaseJumpInfoPtrListIt getBiggerCall(BaseJumpInfoPtrListIt &oldInstrIt);

  /// Change tail call for the biggest tail call that target has.
  /// Takes iterator pointing to currently examinned instruction.
  /// Returns incremented input iterator if successfull replacement,
  /// unincremented input iterator otherwise.
  BaseJumpInfoPtrListIt changeTailCall(BaseJumpInfoPtrListIt &oldInstrIt);

  /// Replace instruction I in a bundle with NOP.
  void rebuildOldBundle(MachineInstr *I);

  /// Replace old instruction with new one. Old instruction can be in bundle.
  /// It erases replaced instruction from InstrsToExamine list which invalidates
  /// input iterator.
  /// Returns iterator to successor of input iterator.
  BaseJumpInfoPtrListIt replaceInst(BaseJumpInfoPtrListIt &oldInstrIt,
                                    std::shared_ptr<BaseJumpInfo> &newInstr);

  /// Returns true if unconditional old jump can be replaced with the biggest
  /// unconditional jump
  bool canChangeCommon(const BaseJumpInfo *oldJump,
                       const BaseJumpInfo *newJump);

  /// Returns true if conditional jump can be replaced with conditional jump
  /// with inverted condition.
  bool canChangeInverted(const BaseJumpInfo *oldJump);

  /// Returns true if jump can stay the same except the destination.
  bool canChangeConditional(const BaseJumpInfo *oldJump);

  /// \brief Adds new basic block into function.
  ///
  /// New mbb is added after beforeMBB. Every instruction after spliceIns and
  /// its delay slots is moved to new basic block.
  MachineBasicBlock *addMBB(MachineBasicBlock *beforeMBB,
                            const BaseJumpInfo *spliceJump);

  /// Adds NOPs to delay slots of instruction mi.
  void addDelaySlotNops(MachineInstr *mi, unsigned numDelaySlots);

  /// Returns true if replaced conditional jump must jump to a new MBB
  /// to retain a programs semantics.
  bool needsNewMBB(const BaseJumpInfo *jumpIns) const;

  /// -------- virtual methods redefined in CodasipJumpLengthCheck.cpp --------

  /// \brief Allocates and creates CodasipJumpInfo representation of jump/call
  /// instruction.
  ///
  /// JumpInfo needs to be created this way, you can use it's virtual methods,
  /// that are implemented in backend of specific model. Returned value then
  /// needs to be deleted.
  /// \param [in] opc  Opcode of instruction that this BaseJumpInfo represents.
  /// \param [in] mi   Jump or call instruction about which this BaseJumpInfo is
  /// created.
  /// \param [in] dest Destination of jump/call instruction that this
  /// BaseJumpInfo represents.
  virtual std::shared_ptr<BaseJumpInfo>
  createJumpInfo(unsigned opc, MachineInstr *mi, const MachineOperand *dest) {
    return std::shared_ptr<BaseJumpInfo>(nullptr);
  }

  /// \brief Allocates and creates CodasipJumpInfo representation of jump/call
  /// instruction.
  ///
  /// JumpInfo needs to be created this way, you can use it's virtual methods,
  /// that are implemented in backend of specific model. Returned value then
  /// needs to be deleted.
  /// \param [in] opc    Opcode of instruction that this BaseJumpInfo
  /// represents.
  /// \param [in] posMBB MBB in which this jump/call should be.
  /// \param [in] dest   Destination of jump/call instruction that this
  /// BaseJumpInfo represents.
  virtual std::shared_ptr<BaseJumpInfo>
  createJumpInfo(unsigned opc, MachineFunction::iterator posMBB,
                 const MachineOperand *dest) {
    return std::shared_ptr<BaseJumpInfo>(nullptr);
  }

  /// Returns true if model has bundles.
  virtual bool hasBundles() { return false; }

  /// \brief Returns true if value can be represented on instruction operand.
  /// \param [in] imm   - Value that is tested.
  /// \param [in] width - Number of bit that operand has for value.
  /// \param [in] sign  - True if operand accepts signed value.
  /// \param [in] trunc - Value of this operand must be truncated to trunc
  /// value.
  virtual bool checkImmFits(int64_t imm, int width, bool sign, int trunc) {
    return false;
  }

  /// Get opcode of absolute bidirectional jump the can jump the farthest.
  virtual unsigned getLongJumpOpcode() { return 0; }

  /// Get opcode of absolute call the can jump the farthest.
  virtual unsigned getLongCallOpcode() { return 0; }

  /// Get opcode of tail call the can jump the farthest.
  virtual unsigned getLongTailCallOpcode() { return 0; }

  /// \brief Get opcode of smaller jump that should replace oldJumpOpcode.
  ///
  /// Returned opcode must be specified by user in file
  /// CodasipCustJmpLenCheck.inc.
  /// Returns the input parameter if no jump was found.
  virtual unsigned handleShortJumpGenCust(unsigned oldJumpOpcode) {
    return oldJumpOpcode;
  }

  /// \brief Get opcode of bigger jump that should replace oldJumpOpcode.
  ///
  /// Returned opcode must be specified by user in file
  /// CodasipCustJmpLenCheck.inc.
  /// Returns the input parameter if no jump was found.
  virtual unsigned handleLongJumpGenCust(unsigned oldJumpOpcode) {
    return oldJumpOpcode;
  }
};

} // End namespace llvm

#endif /* INCLUDE_CODASIP_TARGET_CODASIPBASEJUMPLENGTHCHECKER_H_ */
