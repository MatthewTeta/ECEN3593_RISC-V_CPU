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
 * \file
 * \date    2016-08-19 14:05:32
 * \author  Stanislav Melo
 * \version 6.2.0
 * \brief   peephole optimizer that is run before register allocation
 */

#ifndef CODASIPPREPOSTRAPEEPHOLE_H
#define CODASIPPREPOSTRAPEEPHOLE_H

#include "codasip/Target/CodasipBasePeephole.h"
#include "codasip/Target/CodasipLoadStoreMapAnalysis.h"
#include "codasip/misc/CodasipBaseJumpInfo.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/SetOperations.h"
#include "llvm/CodeGen/ISDOpcodes.h"

#include <map>

namespace llvm {

// ******************** PEEPHOLE PASS ******************************
/// \brief Parts of matching and replacing patterns that are common for pre and
/// post RA.
class CodasipPeepholeBase {
  /// \brief Max amount of MBBs that pattern can be split through.
  ///
  /// Empty MBBs do not count.
  const unsigned Break = MAXBBS;

protected:
  TargetMachine *TM = nullptr;
  LiveIntervals *LI = nullptr;

  /// Pattern currently being examined.
  Pattern *CurPat = nullptr;

  /// Map of clones that are generated automatically by backendgen.
  CodeMap CallRetClones;
  MachineRegisterInfo *MRI = nullptr;

  /// \brief Map of equal instructions with different opcode.
  ///
  /// It is generated automatically by backendgen.
  CodeMap EqualInstructions;
  const TargetInstrInfo *TII = nullptr;
  const TargetRegisterInfo *TRI = nullptr;

private:
  /// \brief Reverts one pattern instruction back reseting reverted instruction.
  ///
  /// If necessary it reverts and resets pattern group as well.
  /// Retains real instruction from pattern instraction that it reverted to.
  /// It won't revert first and second patter instruction. (from the whole
  /// pattern)
  /// \param [in, out] piIt - pattern instraction that is going to be reverted.
  /// \param [in, out] pgIt - pattern group containing piIt
  /// \param [out]     mi   - real instruction matched to reverted pattern
  /// instruction
  /// \return true when reverted successfully
  bool backtrackPI(PatternInstrIterator &piIt, PatternGroupIterator &pgIt,
                   MachineInstr **mi);

public:
  /// class with info needed for lto
  LTOFileInfo *LtoFile = nullptr;

  /// Vector of all peephole patterns in the model.
  SmallVector<Pattern *, 2> VectorOfPatterns;

  /// Constructor.
  CodasipPeepholeBase() {}
  CodasipPeepholeBase(TargetMachine &tm, const TargetRegisterInfo *tri,
                      const TargetInstrInfo *tii);

  /// Destructor.
  virtual ~CodasipPeepholeBase();

  /// Creates replace instructions and erases pattern instructions.
  void replace();

  /// Creates new instructions according to ResultInstrs of pattern group pg.
  void makeNewInstructions(PatternGroup *pg);

  /// Add pattern to vector of patterns.
  void addPattern(Pattern *pat);

  /// \brief Returns true if pattern instruction can be matched to real
  /// instruction.
  ///
  /// It also updates matched instruction info in pattern instruction.
  bool checkAndSetInstr(MachineInstr *mi, PatternInstr *pi);

  /// Returns true if it found some pattern that started in MBB.
  bool findPattern(MachineBasicBlock *mbb);

  /// \brief Find real instruction that matches pattern instruction.
  ///
  /// It must also be able to move to Place of corresponding pattern group.
  /// \param [in, out] pi - Instruction it tries to find match to. If it does,
  /// update its structure.
  /// \param [in]      startMI - It searches for pi after this instruction.
  /// \return true if fitting instruction was found.
  bool findNextInstrAndPlace(PatternInstr *pi, MachineInstr *startMI);

  /// Returns true if opcode \p key is considered to be equal with opcode \p
  /// val.
  bool checkClonesEquals(unsigned key, unsigned val);

  /// \brief Add some existing operand to the new instruction.
  ///
  /// \param [in] ri - result instruction that describes instruction it is
  /// adding operand to.
  /// \param [in] po - pattern operand describing the operand it is adding.
  /// \param [in, out] MIB - instruction that it adds operand to.
  /// \return True, if such operand was added.
  bool getExistingOperand(ResultInstr *ri, PatternOp *po,
                          MachineInstrBuilder &MIB);

  /// \brief Creates operand for new instruction.
  ///
  /// It is possible only if operand is constant or register definition pre RA.
  /// \param [in] po - pattern operand describing the operand it tries to
  /// create.
  /// \param [in,out] MIB  - New instruction that operand will be added to.
  /// \return True if operand was created.
  bool createOperand(PatternOp *po, MachineInstrBuilder &MIB);

  /// \brief Run optimization on one basic block.
  ///
  /// \param [in, out] mbb - block in which searching starts
  /// \param [in, out] report - structure for final report
  /// \param [in]      printReport - true if report should be printed
  /// \return true if some pattern was replaced.
  bool runOptim(MachineBasicBlock *mbb, CodasipPeepholeReport &report,
                bool printReport);

  /// \brief Check if operands of pattern instruction can be mapped to operands
  /// of real
  /// instruction.
  ///
  /// If they can, update pattern instructions info about matched operands.
  /// \param [in, out] pi - pattern instruction which operands it examines and
  /// which match info it modifies.
  /// \param [in] mi - real instruction which operands it examines.
  /// \return true if all operands were matched
  bool checkAndSetOperands(PatternInstr *pi, MachineInstr *mi);

  /// Returns true if pattern operand \p po can be matched to real operand \p
  /// mo.
  bool checkOperands(PatternOp &po, MachineOperand &mo);

  /// Find all instructions of pattern except first one. Return true if
  /// successful.
  bool findTheRest();

  /// \brief Find next pattern instruction that was NOT data connected to
  /// previous
  /// pattern instruction.
  ///
  /// \param [in] startMI - real instruction after which the search starts.
  /// \param [in,out] pi - pattern instruction that it looks for. If found, it
  /// modifies its match info.
  /// \return True if pattern instruction was found.
  bool findNextInstrWOChain(MachineInstr *startMI, PatternInstr *pi);

  /// \brief Determine if search for next pattern instruction can be terminated
  /// early.
  ///
  /// Conditions: - It must be in post RA peephole.
  ///             - Pattern instruction peephole is looking for
  ///               must have data dependency with previous pattern instruction.
  ///
  /// \param [in] mi - real instruction that is being examined
  /// \param [in] pi - pattern instruction it is looking for
  /// \return true if search can end on examined instruction.

  // When code looks like this:
  // ...
  // pt1 - already found pattern instruction
  // ...
  // examined - instruction that is being examined if it is next pattern ins
  // ...
  // pt2 - actual next pattern instruction, not found yet
  //
  // and pt1, examined, pt2 have the same reg operand, search can be ended on
  // examined ins.,
  // depending on which of them uses and which defines the register.
  //
  // pt1       examined      pt2     ends early (replace ins will be at
  // pt1/pt2)
  // def         def         def       N/N
  // def         def         use       N/N
  // def         def         def       N/N
  // def         use         def       mapp/N
  // def         use         use       Y/N
  // use         def         def       N/N
  // use         def         use       N/N
  // use         use         def       N/Y
  // use         use         use       Y/Y
  bool endSearch(MachineInstr *mi, PatternInstr *pi);

  /// \brief Check if search for unconnected pattern can continue in some
  /// another MBB.
  ///
  /// If it can, get first real instruction of that MBB.
  ///
  /// Search can continue in another MBB:
  ///   - If it is the only successor of previously searched MBB.
  ///   - If it has only one predecessor.
  ///   - If it hasn't searched through more than MAXBBS MBBs.
  ///
  /// Empty MBBs are skipped.
  /// It changes pattern info about used MBBs
  /// \param [out] mi  - First real instruction of another MBB.
  /// \param [in] mbb - last examined MBB.
  /// \returns True if search can continue in another MBB.
  bool transferToNextBB(MachineInstr **mi, MachineBasicBlock *mbb);

  /// Check if register classes of operands differ.
  unsigned needsConversion(MachineOperand *fromMo, MachineOperand *toMo);

  /// \brief Check if register classes of operands differ.
  ///
  /// It works only when operands are of the same reg class or one reg class is
  /// subset of another.
  /// \param [in] fromMo - operand that will be converted
  /// \param [in] toRc - reg class that operand will be converted to
  /// \return zero if no conversion is needed. TargetOpcode::SUBREG_TO_REG or
  /// TargetOpcode::COPY depending on what conversion is necessary.
  unsigned needsConversion(MachineOperand *fromMo, unsigned toRc);

  /// Com
  MachineInstr *getNextMI(MachineInstr *mi);

  /// \brief Find place in the program where pattern group can create its result
  /// instructions.
  ///
  /// It may change place info in examined pattern group.
  /// \param [in] pi - pattern instruction, of examined pattern group, that was
  /// matched last.
  /// \return true if suitable place was found.
  bool findSuitablePlace(PatternInstr *pi);

  /// Print info about this class to dbgs().
  void patternDump();

  /// Erase matched pattern instructions.
  /// \param [out] affectedMBBs - Mbbs that contain erased instructions.
  /// \param [out] affectedVirtRegs - Virt regs that had their liveness
  ///                                 info deleted
  void eraseReplacedIns(SmallVectorImpl<MachineBasicBlock *> &affectedMBBs,
                        SmallVectorImpl<unsigned> &affectedVirtRegs);

  /// \brief Returns true if register \p reg is live between the end of \p mbb
  /// and the end of function.
  ///
  /// It should be used for reserved physical registers, because their liveness
  /// is not tracked by other llvm liveness tracking
  bool liveInSuccMbbManual(const MachineBasicBlock *mbb, unsigned reg);

  /// \brief Like CodasipPeepholeBase::physRegUsedOutsideMbb, but if register \p
  /// reg is not reserved, it is less time consuming using live in information.
  bool
  physRegUsedToEnd(unsigned reg, const PatternGroup *pg,
                   MachineBasicBlock *from,
                   df_iterator_default_set<const MachineBasicBlock *> &visited);

  /// \brief Returns true if register \p reg is used without prior redefinition
  /// between instructions \p from and \p to.
  ///
  /// Boundaries \p from and \p to do not have to be in the same mbb, but mbb
  /// containing \p to must be reachable from mbb containing \p from.
  /// If boundaries are not in the same mbb, all successors of mbb containing \p
  /// from are also searched. This search uses DFS on CFG so it might be costly.
  /// Argument \p visited contains mbbs that don't have to be searched. After
  /// the method it also contains searched mbbs.
  /// Instructions using \p reg that are matched in pattern group \p pg do not
  /// count.
  /// Debug instructions using \p reg do not count, but reg is saved
  /// in DebugRegs of the pattern.
  /// \p isRedef is set to true if \p reg is redefined between \p from and \p
  /// to. It also works for reserved phys registers.
  bool physRegUsedFromTo(
      unsigned reg, const PatternGroup *pg, const MachineInstr *from,
      const MachineInstr *to, bool &isRedef,
      df_iterator_default_set<const MachineBasicBlock *> &visited);

  /// \brief Returns true if register \p reg is used without prior redefinition
  /// between instructions \p from and \p to.
  ///
  /// Both boundaries \p from and \p to must be in the same mbb that is \p mbb.
  /// Instructions using \p reg that are matched in pattern group \p pg do not
  /// count.
  /// Debug instructions using \p reg do not count, but reg is saved
  /// in DebugRegs of the pattern.
  /// \p isRedef is set to true if \p reg is redefined between \p from and \p
  /// to. It also works for reserved phys registers.
  bool physRegUsedFromToSingleMbb(unsigned reg, const PatternGroup *pg,
                                  MachineBasicBlock::const_instr_iterator from,
                                  MachineBasicBlock::const_instr_iterator to,
                                  bool &isRedef, const MachineBasicBlock *mbb);

  /// \brief Returns true if register \p reg is used in mbb that is successor of
  /// mbb \p from without prior redefinition.
  ///
  /// If some use is matched in pattern group \p pg it does not count as use.
  /// If some use is debug instruction, it does not count as use, but reg is
  /// saved in DebugRegs of the pattern. It performs DFS on CFG so it may be
  /// time consuming. Argument \p visited contains mbbs that don't have to be
  /// searched. After the method it also contains searched mbbs. It also works
  /// for reserved phys registers.
  bool physRegUsedOutsideMbb(
      unsigned reg, const PatternGroup *pg, const MachineBasicBlock *from,
      df_iterator_default_set<const MachineBasicBlock *> &visited);

  // Virtual methods.

  /// \brief Creates conversion instruction.
  ///
  /// It works only when operands it is converting are of the same reg class or
  /// one reg class is subset of another.
  /// \param [in] conOpc - opcode of conversion instruction
  /// \param [in] position - position where new instruction will be created.
  /// \param [in] fromMo - operand being converted
  /// \param [in] toRc - register class to which it converts the operand
  /// \return convert instruction
  virtual MachineInstr *createConversionIns(unsigned conOpc,
                                            MachineInstr *position,
                                            MachineOperand *fromMo,
                                            unsigned toRc) {
    return nullptr;
  }

  /// \brief Check if real, examined instruction can be moved to new position.
  ///
  /// The new position is somewhere before examined instruction.
  ///
  /// It can't be moved if that would result in:
  ///     - redefinition of some registers
  ///     - usage of undefined registers
  ///
  /// \param [in] fromMi - examined instruction, also one end of examined
  /// interval
  /// \param [in] toMi - place tahat instruction will move to, also another end
  /// of examined interval
  /// \return true if move is possible.
  virtual bool canGoUp(MachineInstr *examinedMi, MachineInstr *toMi,
                       PatternGroup *pg) {
    return false;
  }

  /// \brief Check if all matched instructions of pattern group can be moved to
  /// a new
  /// position.
  ///
  /// The new position is somewhere after place position of pattern group.
  ///
  /// It can't be moved if that would result in:
  ///     - redefinition of some registers
  ///     - usage of undefined registers
  ///
  /// \param [in] newPlace - real instruction representing new place
  /// \param [in] pg - pattern group with matched instructions that need to be
  /// moved
  /// \return true if move is possible for all instructions.
  virtual bool canGoDown(MachineInstr *newPlace, PatternGroup *pg) {
    return false;
  }

  /// \brief Create new operand for result instruction.
  ///
  /// It is possible only in pre RA and only for register defs.
  /// \param [in] ri - result instruction that describes instruction for created
  /// operands
  /// \param [in] po - pattern operand describing created operand
  /// \param [in, out] MIB - instruction to which created operand will be added
  /// \return true if such operand was created
  virtual bool createReturnOp(ResultInstr *ri, PatternOp *po,
                              MachineInstrBuilder &MIB) {
    return false;
  }

  /// \brief Find real instruction that can be matched to pattern instruction.
  ///
  /// If it was found, it updates matched info of pattern instruction.
  /// \param [in] searchStartMI - real instruction with which the search starts
  /// \param [in, out] nextPI - pattern instruction that it tries to match
  /// \return true if pattern instruction was matched
  virtual bool findNextInstr(MachineInstr *searchStartMI,
                             PatternInstr *nextPI) {
    return false;
  }

  /// \brief Recomputes liveness flags of physical registers and live-in lists
  ///  of mbbs
  ///
  /// \param [in] affectedMBBs - Mbbs that contained matched instructions.
  /// Liveness recomputation starts from them.
  /// \param [in] affectedVirtRegs - Virt regs that it will recompute liveness
  /// for.
  virtual void
  customRecomputeLiveInfo(SmallVectorImpl<MachineBasicBlock *> &affectedMBBs,
                          SmallVectorImpl<unsigned> &affectedVirtRegs) {
    return;
  }

  /// \brief Connects real operands with their uses outside of the matched
  /// pattern.
  ///
  /// Operands must be specified in mapping section of the pattern.
  /// It creates conversion instructions if needed.
  /// \param [in] op - pattern operand with mapping section that is being
  /// connected
  virtual void connectValueMapping(PatternOp &op) { return; }

  /// brief\ Check if program uses registers that would be deleted by replacing
  /// pattern
  /// group.
  ///
  /// It checks use of registers in interval defined by last pattern instruction
  /// of pattern group and real instruction.
  /// \param [in] pg - group that defines deleted reg definitions and border of
  /// examined interval
  /// \param [in] endMI - real instruction that is end border of the interval.
  /// If no end border is specified, it continues to the end of program
  /// \return false if no deleted definitions are used in the interval.
  virtual bool usedDeletedDefs(PatternGroup *pg, MachineInstr *endMI) {
    return true;
  }
};

// ********************** PRE RA PEEPHOLE **************************
/// \brief Implements optimization before Register Allocation.
class PreRAPeephole : public CodasipPeepholeBase, public MachineFunctionPass {
  typedef std::pair<const MachineBasicBlock *, const MachineBasicBlock *>
      reachableMapKey;
  CodasipLoadStoreMapAnalysis *LSA = nullptr;
  // for each key pair mbb1 and mbb2, it holds set of every mbb that is on some
  // path between them
  std::map<reachableMapKey, df_iterator_default_set<const MachineBasicBlock *>>
      pathMbbs;
  // for each key pair mbb1 and mbb2, it holds set of mbbs that are predecessor
  // of mbb2 but are not dominated by mbb1
  std::map<reachableMapKey, df_iterator_default_set<const MachineBasicBlock *>>
      reachableRevMbbs;

  /// Computes set of every mbb that is on some path between predMbb and succMbb
  /// and set of mbbs that are predecessors of endMbb, but are not dominated by
  /// beginMbb
  /// predMbb must be a predecessor of succMbb
  /// It may be expensive operation. It stores results in this class so they
  /// don't have to be recomputed again.
  void fillMbbMaps(const MachineBasicBlock *predMbb,
                   const MachineBasicBlock *succMbb);

public:
  /// Id for pass manager.
  static char ID;

  /// Returns pass name.
  StringRef getPassName() const override { return "preRA peephole"; }

  /// Constructor.
  PreRAPeephole() : CodasipPeepholeBase(), MachineFunctionPass(ID){};
  PreRAPeephole(TargetMachine &tm, const TargetInstrInfo *tii,
                const TargetRegisterInfo *tri, char &ID)
      : CodasipPeepholeBase(tm, tri, tii), MachineFunctionPass(ID) {}

  /// Destructor.
  ~PreRAPeephole() {}

  /// Other passes that this pass uses.
  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequired<LiveIntervals>();
    AU.addRequired<CodasipLoadStoreMapAnalysis>();
    MachineFunctionPass::getAnalysisUsage(AU);
  }

  /// \brief Find next pattern instruction that shares some operand with its
  /// predecessor.
  ///
  /// If pattern instruction is matched, update its matched info.
  /// \param [in] startPosMI - real instruction from which the search starts
  /// \param [in, out] pi - pattern instruction it tries to match
  /// \return true if pattern instruction was matched
  bool findNextConnectedInstr(MachineInstr *startPosMI, PatternInstr *pi);

  /// Help function for creating virtual register with register class \p rc
  unsigned createVirtReg(unsigned rc);

  /// Returns true if definition of register \p defReg can be moved to location
  /// \p newLoc
  bool canMovDefTo(MachineInstr *newLoc, unsigned defReg);

  /// \brief Returns true if physical register can be moved from place described
  /// by succMi or predMi to the other one without changing the semantics of the
  /// program.
  ///
  /// Debug instructions are not considered in this analysis, but reg used by
  /// them is saved in DebugRegs of the pattern. \param [in] succMi -
  /// Instruction containing examined register or place where register wants to
  /// be moved. It must be successor to predMi in CFG \param [in] predMi -
  /// Instruction containing examined register or place where register wants to
  /// be moved. It must be predecessor to succMi in CFG \param [in] reg -
  /// Examined register \param [in] pg - Pattern group containing instruction
  /// with register that reg was matched to \return true if register can be
  /// moved
  bool canMovPhysRegTo(const MachineInstr *succMi, const MachineInstr *predMi,
                       const MachineOperand &reg, PatternGroup *pg);
  /// Return every mbb that is on some path between predMbb and succMbb
  /// predMbb must be a predecessor of succMbb
  const df_iterator_default_set<const MachineBasicBlock *> &
  getPathMbbsBetween(const MachineBasicBlock *predMbb,
                     const MachineBasicBlock *succMbb);
  /// Return mbbs that are predecessors of endMbb, but are not dominated by
  /// beginMbb
  const df_iterator_default_set<const MachineBasicBlock *> &
  getReachableRevMbbs(const MachineBasicBlock *beginMbb,
                      const MachineBasicBlock *endMbb);

  /// Returns true if usage of register \p useReg can be moved to location \p
  /// newLoc
  bool canMovUseTo(MachineInstr *newLoc, unsigned useReg);

  /// Creates conversion instruction. See virtual method.
  MachineInstr *createConversionIns(unsigned conOpc, MachineInstr *position,
                                    MachineOperand *fromMo,
                                    MachineOperand *toMo);

  /// Com
  void connectOperands(MachineOperand *oldMo, MachineOperand *newMo,
                       unsigned convResReg, MachineInstr *use);

  /// Fills OutsideUses vector of PatternGroup \p pg with instructions that use
  /// register that is mapped to another register in mapping section
  void getInsUsingMapping(PatternGroup *pg, MachineInstr *border);

  /// \brief Returns instruction that uses \p reg after \p startPosMI
  /// instruction
  /// in use chain.
  MachineRegisterInfo::use_instr_iterator
  findStartPos(MachineInstr *startPosMI, const MachineOperand *reg);

  /// \brief Returns true if memory ins \p movedMi violates any memory
  /// skipping rules when skipping after instruction block limited by
  /// \p beginMi and \p endMi borders. Borders must be in the same mbb.
  bool memSkippedInMbb(const MachineInstr *beginMi, const MachineInstr *endMi,
                       const MachineInstr *movedMi) const;

  /// \brief Returns true if memory ins \p movedMi violates any memory
  /// skipping rules when skipping after instruction block limited by
  /// \p beginMi and \p endMi borders. Borders are not in the same mbb.
  bool memSkippedInFunc(const MachineInstr *beginMi, const MachineInstr *endMi,
                        const MachineInstr *movedMi);

  // Override functions

  /// \brief Check if real, examined instruction can be moved to new position.
  ///
  /// The new position is somewhere before examined instruction. See virtual
  /// method.
  bool canGoUp(MachineInstr *examinedMi, MachineInstr *toMi,
               PatternGroup *pg) override;

  /// \brief Check if all matched instructions of pattern group can be moved to
  /// new
  /// position.
  ///
  /// The new position is somewhere after place position of pattern group.
  /// See virtual method.
  bool canGoDown(MachineInstr *newPlace, PatternGroup *pg) override;

  /// \brief Check if program uses registers that would be deleted by replacing
  /// pattern
  /// group.
  ///
  /// See virtual method.
  bool usedDeletedDefs(PatternGroup *pg, MachineInstr *border) override;

  /// \brief Creates conversion instruction.
  ///
  /// See virtual method.
  MachineInstr *createConversionIns(unsigned conOpc, MachineInstr *position,
                                    MachineOperand *fromMo,
                                    unsigned toRc) override;

  /// \brief Create new operand for result instruction.
  ///
  /// See virtual method.
  bool createReturnOp(ResultInstr *ri, PatternOp *po,
                      MachineInstrBuilder &MIB) override;

  /// \brief Find real instruction that can be matched to pattern instruction.
  ///
  /// See virtual method.
  bool findNextInstr(MachineInstr *searchStartMI,
                     PatternInstr *nextPI) override;

  /// \brief Connects real operands with their uses outside of the matched
  /// pattern.
  ///
  /// Operands must be specified in mapping section of the pattern.
  /// See virtual method.
  void connectValueMapping(PatternOp &op) override;

  /// Run this optimization on machine function \p F
  bool runOnMachineFunction(MachineFunction &F) override;

  /// Recompute live info only for virtual registers contained in
  /// affectedVirtRegs
  void
  customRecomputeLiveInfo(SmallVectorImpl<MachineBasicBlock *> &affectedMBBs,
                          SmallVectorImpl<unsigned> &affectedVirtRegs) override;
};

// ********************* POST RA PEEPHOLE **************************
/// \brief Implements optimization after Register Allocation.
class PostRAPeephole : public CodasipPeepholeBase, public MachineFunctionPass {
public:
  /// Com
  static char ID;

  /// Return pass name.
  StringRef getPassName() const override { return "postRA peephole"; }

  /// Constructor.
  PostRAPeephole() : CodasipPeepholeBase(), MachineFunctionPass(ID){};
  PostRAPeephole(TargetMachine &tm, const TargetInstrInfo *tii,
                 const TargetRegisterInfo *tri, char &ID)
      : CodasipPeepholeBase(tm, tri, tii), MachineFunctionPass(ID) {}

  /// Destructor.
  ~PostRAPeephole() {}

  /// Returns true if \p examined instruction satisfies certain criteria in
  /// interval < \p beginMI, \p endMI]
  bool dataDepCheckAux(MachineInstr *beginMI, MachineInstr *endMI,
                       MachineInstr *examined);

  // Override functions

  /// \brief Check if real, examined instruction can be moved to new position.
  ///
  /// The new position is somewhere before examined instruction. See virtual
  /// method.
  bool canGoUp(MachineInstr *examinedMi, MachineInstr *toMi,
               PatternGroup *pg) override;

  /// \brief Check if all matched instructions of pattern group can be moved to
  /// new
  /// position.
  ///
  /// The new position is somewhere after place position of pattern group.
  /// See virtual method.
  bool canGoDown(MachineInstr *newPlace, PatternGroup *pg) override;

  /// \brief Find real instruction that can be matched to pattern instruction.
  ///
  /// See virtual method.
  bool findNextInstr(MachineInstr *searchStartMI,
                     PatternInstr *nextPI) override;

  /// \brief Check if program uses registers that would be deleted by replacing
  /// pattern
  /// group.
  ///
  /// See virtual method.
  bool usedDeletedDefs(PatternGroup *pg, MachineInstr *mi) override;

  /// \brief Corrects kill flags for register uses after inserting new
  /// instructions.
  ///
  /// See virtual method.
  void
  customRecomputeLiveInfo(SmallVectorImpl<MachineBasicBlock *> &affectedMBBs,
                          SmallVectorImpl<unsigned> &affectedVirtRegs) override;

  /// Run this optimization on machine function \p F
  bool runOnMachineFunction(MachineFunction &F) override;
};

} // namespace llvm

#endif // CODASIPPREPOSTRAPEEPHOLE_H
