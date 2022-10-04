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

#ifndef CODASIPBASEPEEPHOLE_H
#define CODASIPBASEPEEPHOLE_H

#include "codasip/misc/CodasipBaseJumpInfo.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/ISDOpcodes.h"
#include "llvm/CodeGen/LiveIntervals.h"
#include "llvm/CodeGen/LiveRangeEdit.h"
#include "llvm/CodeGen/LiveStacks.h"
#include "llvm/CodeGen/LiveVariables.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/Pass.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

#include <algorithm>

#define UNDEFINED -1
/// Max amount of mbbs that pattern can be split through (MAXBBS + 1)
/// in post RA. Empty mbbs don't count.
#define MAXBBS 2

namespace llvm {

class PatternInstr;
class ResultInstr;
class PatternOpConnection;
class PatternOp;
class IntermediateInstr;
class PatternOpConnection;
class PatternGroup;
class Pattern;

typedef std::map<unsigned, std::vector<unsigned>> CodeMap;
typedef SmallVectorImpl<PatternInstr *>::iterator PatternInstrIterator;
typedef SmallVectorImpl<PatternGroup *>::iterator PatternGroupIterator;

// ********************* RESULT GROUP **************************
/// \brief Represents group of M pattern with corresponding N result
/// instructions.
class PatternGroup {
  /// \brief Result instructions corresponding to this PatternGroup will be
  /// created before this instruction.
  ///
  /// This is stack and it needs to be updated whenever new place is required
  /// or it is no longer valid due to backtracking.
  SmallVector<PatternInstr *, 1> Place;

  /// Pattern that contains this group.
  Pattern *ParentPat;

  /// \brief Reg numbers of definitions that will be erased by replacing
  /// pattern.
  ///
  /// This DefsDel = DefsDel of previous pattern group - regs defined by result
  /// of this pattern group + regs deleted by this pattern group.
  /// Regs contained in mapping section are not included.
  /// These registers won't be defined in the interval from start of the pattern
  /// to the start of the next pattern group.
  SmallVector<unsigned, 1> DefsDel;

  /// \brief Reg numbers of definitions that will be created by replacement.
  ///
  /// This DefsCreate = DefsCreate of previous pattern group + regs defined by
  /// this pattern group.
  /// These registers will be defined in the interval from start of the pattern
  /// to the end of the program.
  SmallVector<unsigned, 1> DefsCreate;

  /// Instructions that will replace PatternInstrs.
  SmallVector<ResultInstr *, 5> ResultInstrs;

  /// Instructions that pattern wants to change.
  SmallVector<PatternInstr *, 5> PatternInstrs;

  /// Returns DefsCreate vector of this pattern group.
  SmallVectorImpl<unsigned> *getCreatedDefs() { return &DefsCreate; }

public:
  /// Returns place where result instructions will be created.
  PatternInstr *getPlace() { return Place.back(); }
  void addPlace(PatternInstr *pi) { Place.push_back(pi); }
  void popPlace();

  /// Reurns size of result instruction vector.
  unsigned getResultSize() const { return ResultInstrs.size(); }
  unsigned getPatternSize() const { return PatternInstrs.size(); }

  /// Returns Pattern that contains this group.
  Pattern *getParent() { return ParentPat; }
  void setParent(Pattern *pat) { ParentPat = pat; }

  /// Constructor.
  PatternGroup();

  /// Destructor.
  ~PatternGroup();

  /// Returns result instructions of the group.
  SmallVectorImpl<ResultInstr *> *getResultInstrs() { return &ResultInstrs; }

  /// Add result instruction to group.
  void addResultInstr(ResultInstr *ri);

  /// Returns pattern instructions of the group.
  SmallVectorImpl<PatternInstr *> *getPatternInstrs() { return &PatternInstrs; }
  /// Add pattern instruction to group.
  void addPatternInstr(PatternInstr *pi);

  /// \brief Returns registers that won't be defined after pattern instructions
  /// are
  /// replaced.
  ///
  /// They won't be defined in the interval from the start of the pattern to the
  /// start of the next pattern group.
  SmallVectorImpl<unsigned> *getDeletedDefs() { return &DefsDel; }

  /// \brief Fill info about reg defs created and deleted by this pattern group.
  ///
  /// It must be called after all pattern instructions have been found.
  /// \param [in] prevPG - previous pattern group or the same if it has no
  /// previous pattern group.
  void fillDefs(PatternGroup *prevPG, const TargetInstrInfo *TII);

  /// Returns ResultInstr on index.
  ResultInstr *getResultInstr(const unsigned index);

  /// Returns PatternInstr on index.
  PatternInstr *getPatternInstr(const unsigned index);

  /// Returns true if instruction mi is matched as some pattern instruction.
  bool isMatchedIn(const MachineInstr *mi) const;

  /// \brief Fill info related to mapping section.
  ///
  /// It fills it for pattern operands of pattern instructions in this pattern
  /// group.
  /// It must be used after the group is filled with all fully filled pattern
  /// and result instructions.
  void fillValueMapping();

  /// \brief Create and fill PatternOpConnection classes for pattern operands.
  /// \param [in, out] connections - vector of PatternOpConnection classes that
  /// will be updated and possibly extended.
  void fillOpConecctions(SmallVectorImpl<PatternOpConnection *> *connections);

  /// \brief Fill data connections of pattern instructions with their
  /// predecessors.
  ///
  /// Can be used only after PatternOpConnection classes for operands are
  /// filled.
  void fillConnectionsWithNext();

  /// Reinitialize all members that are filled during pattern search, so that it
  /// can be reused.
  void reset();

  /// Print info about this class to dbgs().
  void dump() const;
};

// ********************* PATTERN OPERANDS **************************
/// \brief Represents operand of pattern instruction.
/// Refactor hint: Maybe extend MachineOperand.
class PatternOp {
public:
  enum OpType {
    OTHER, ///< Operand is reg or imm or else, it can't be created by peephole.
    CONS   ///< Operand is constant (number known during compilation).
  };

private:
  /// True if this operand is register definition.
  bool IsDef = false;

  /// Type of operand
  OpType Type;

  /// Value of operand if it is CONS or id of operand is OTHER.
  int64_t Value;

  /// Real operand representing this pattern operand.
  MachineOperand *RealOp;

  /// PatternOpConnection class corresponding to this operand.
  PatternOpConnection *Connection;

  /// \brief Indexes of operand in result instruction that this operand is
  /// mapped to.
  ///
  /// It is used only in operands of PatternInstr to fill MappedTo member of
  /// this operand and operand of corresponding ResultInstr.
  /// PatternInstr that this operand belongs to must also have its ReplaceIdx
  /// set.
  int OpIdx;

  /// \brief Operand that this operand is mapped to.
  ///
  /// This thing is set according to in mapping section of peephole pattern.
  PatternOp *MappedTo;

  /// Intermediate instruction that this operand belongs to.
  IntermediateInstr *ParentInstr;

  /// Real instructions that use this operand and are not part of pattern.
  SmallVector<MachineInstr *, 1> OutsideUses;

  /// \brief If this operand represents real immediate operand,
  /// it is used for storing it's immediate value.
  ///
  /// When lto is enabled, it may be necessary to search file with symbol
  /// addresses to get operands imm value. In order to optimize this,
  /// This value is used to optimize the file lookup. It is set and
  /// accessed in patterns userConditions()
  int64_t immVal;

public:
  /// Destructor.
  ~PatternOp() { OutsideUses.clear(); }

  /// Constructor.
  explicit PatternOp(OpType type, int64_t value = UNDEFINED,
                     int opIdx = UNDEFINED, bool isDef = false);

  bool isDef() const { return IsDef; }
  /// Mark operand as definition.
  void setIsDef() { IsDef = true; }

  OpType getOpType() const { return Type; }
  int64_t getOpVal() const { return Value; }

  /// Used for setting MappedTo member. After Pattern is constructed use
  /// getMappedTo() instead.
  int getMappingIdx() const { return OpIdx; }

  /// Return operand that this one is mapped to.
  PatternOp *getMappedTo() { return MappedTo; }
  void setMappedTo(PatternOp *po) { MappedTo = po; }

  /// Return real operand matched to this one.
  MachineOperand *getRealOp() { return RealOp; }
  void setRealOp(MachineOperand *mo);

  /// Return instruction that it belongs to.
  IntermediateInstr *getParentInstr() { return ParentInstr; }
  void setParentInstr(IntermediateInstr *ins) { ParentInstr = ins; }

  /// Return info about def-use of operand across pattern.
  PatternOpConnection *getConnection();
  void setConnection(PatternOpConnection *con) { Connection = con; }

  /// Reinitialize all members that are filled during pattern search, so that it
  /// can be reused.
  void reset();

  /// \brief Returns true if the operand is used in mapping section.
  ///
  /// Works Only after Pattern construction.
  bool hasValueMapping() const { return MappedTo != nullptr; }

  /// \brief Returns true if Type and Value of operands are equal.
  ///
  /// When withDef is set, it also checks if both operands are definitions.
  bool isEqual(PatternOp *po, bool withDef = false) const;

  /// Print info about this class to dbgs().
  void dump() const;

  /// Get number of real register operand
  unsigned getReg();

  /// \brief Returns stored immediate value of real operand.
  ///
  /// Name needs to be same as for MachineOperand so generator
  /// in backendgen can be reused. It is used in patterns userCondition()
  /// function. Value must be set first.
  int64_t getImm() { return immVal; }

  /// \brief Stored immediate value of real operand to
  /// optimize later access to it.
  ///
  /// Name needs to be same as for MachineOperand so generator
  /// in backendgen can be reused. It is used in patterns
  /// userCondition() function.
  void setImm(const int64_t val) { immVal = val; }

  /// Return real instructions that use corresponding real operand and are not
  /// part of the pattern.
  SmallVectorImpl<MachineInstr *> *getOutsideUses() { return &OutsideUses; }
  void addOutsideUse(MachineInstr *mi) { OutsideUses.push_back(mi); }
};

// ********************* PATTERN OPERAND CONNECTIONS **************************
/// \brief Represents data connections across the whole pattern.
/// Pattern operands of the same type and value represent the same operand.
class PatternOpConnection {
  /// Type of operand this class corresponds to.
  PatternOp::OpType Type;

  /// Value of operand this class corresponds to.
  int64_t Value;

  /// \brief One pattern operand representing all pattern operands with this
  /// type and value.
  ///
  /// If operand is register, only reg number is the same for all pattern
  /// operands. It points to the first pattern operand of such type and value
  /// in the pattern. It points to PatternOp so it would be automatically
  /// discarded, when backtracking discards matched real operand.
  PatternOp *CommonOp;

  /// All ResultInstr that define this operand
  SmallVector<ResultInstr *, 4> DefInResultInstr;

  /// All ResultInstr that define this operand
  SmallVector<ResultInstr *, 4> UseInResultInstr;

  /// All PatternInstr that define this operand
  SmallVector<PatternInstr *, 4> DefInPatternInstr;

  /// All PatternInstr that use this operand
  SmallVector<PatternInstr *, 4> UseInPatternInstr;

public:
  /// Returns info about operand it represents.
  PatternOp::OpType getType() const { return Type; }
  int64_t getVal() const { return Value; }

  /// Destructor.
  ~PatternOpConnection();

  /// Constructor.
  explicit PatternOpConnection(PatternOp::OpType type,
                               int64_t value = UNDEFINED);

  /// \brief Returns real operand that was matched for all corresponding pattern
  /// operands.
  ///
  /// isDef does not have to be the same for all pattern operands.
  MachineOperand *getCommonRealOp();
  void setCommonOp(PatternOp *po) { CommonOp = po; }
  bool hasCommOpSet() { return CommonOp != nullptr; }

  /// Adding info about data connection.
  void addDefInResultInstr(ResultInstr *ri) { DefInResultInstr.push_back(ri); }
  void addUseInResultInstr(ResultInstr *ri) { UseInResultInstr.push_back(ri); }
  void addDefInPatternInstr(PatternInstr *pi) {
    DefInPatternInstr.push_back(pi);
  }
  void addUseInPatternInstr(PatternInstr *pi) {
    UseInPatternInstr.push_back(pi);
  }

  /// Returns info about data connections.
  SmallVectorImpl<ResultInstr *> *getDefInResultInstr() {
    return &DefInResultInstr;
  }
  SmallVectorImpl<ResultInstr *> *getUseInResultInstr() {
    return &UseInResultInstr;
  }
  SmallVectorImpl<PatternInstr *> *getDefInPatternInstr() {
    return &DefInPatternInstr;
  }
  SmallVectorImpl<PatternInstr *> *getUseInPatternInstr() {
    return &UseInPatternInstr;
  }

  /// Check data connections for exact instructions.
  bool isDefInResult(ResultInstr *ri) const {
    return std::find(DefInResultInstr.begin(), DefInResultInstr.end(), ri) !=
           DefInResultInstr.end();
  }
  bool isUseInResult(ResultInstr *ri) const {
    return std::find(UseInResultInstr.begin(), UseInResultInstr.end(), ri) !=
           UseInResultInstr.end();
  }
  bool isDefInPattern(PatternInstr *pi) const {
    return std::find(DefInPatternInstr.begin(), DefInPatternInstr.end(), pi) !=
           DefInPatternInstr.end();
  }
  bool isUseInPattern(PatternInstr *pi) const {
    return std::find(UseInPatternInstr.begin(), UseInPatternInstr.end(), pi) !=
           UseInPatternInstr.end();
  }

  /// Print info about this class to dbgs().
  void dump() const;
};

// ********************* INTERMEDIATE INSTRUCTION ***********************
/// \brief Represents instructions used in peephole patterns.
class IntermediateInstr {
protected:
  /// Place of this instruction amongst pattern or result instructions of the
  /// whole pattern.
  unsigned Idx;

  /// Opcode of the instruction.
  unsigned Opc;

  /// Corresponding real instruction, that was matched or created.
  MachineInstr *RealInstr;

  /// \brief Instruction operands.
  ///
  /// Their order represents their place in real instruction.
  SmallVector<PatternOp, 4> Operands;

  /// Pattern group that this instruction belongs to.
  PatternGroup *PatternGrp;

public:
  const TargetInstrInfo *TII;

  /// Destructor.
  virtual ~IntermediateInstr() { Operands.clear(); }

  /// Constructor.
  IntermediateInstr(const unsigned opc, const TargetInstrInfo *tii);

  /// Set instruction index.
  void setInstrIdx(const unsigned idx) { Idx = idx; }

  /// Returns opcode.
  unsigned getOpc() const { return Opc; }

  /// Returns real instruction, matched or created.
  MachineInstr *getRealInstr() { return RealInstr; }
  virtual void setRealInstr(MachineInstr *mi) { RealInstr = mi; }

  /// Returns number of operands.
  unsigned getNumberOperands() const { return Operands.size(); }

  /// Returns instructions operands.
  SmallVectorImpl<PatternOp> *getOperands() { return &Operands; }

  /// Adds operand to instruction.
  void addOperand(PatternOp op);

  /// Returns operand on position index.
  PatternOp *getPatOperand(const unsigned index);

  /// \brief Returns operand on position index.
  ///
  /// Needs to be same as in MachineInstr so that generator
  /// in backendgen can be reused.
  PatternOp &getOperand(const unsigned index);

  /// Returns info about specified operand.
  const MCOperandInfo &getOpDesc(const unsigned i) const;
  const MCOperandInfo &getOpDesc(const PatternOp *po) const;

  /// Returns corresponding pattern group.
  PatternGroup *getPatternGroup() { return PatternGrp; }
  void setPatternGroup(PatternGroup *pGrp) { PatternGrp = pGrp; }

  /// Print readable instruction name to dbgs().
  void nameDump() const;

  /// Reinitialize all members that are filled during pattern search, so that it
  /// can be reused.
  virtual void reset();

  /// Print info about this class to dbgs().
  virtual void dump() const;
};

// ********************* PATTERN INSTRUCTION ***********************
/// \brief Represents instructions that should be replaced by ResultInstr.
class PatternInstr : public IntermediateInstr {
  /// \brief Index of result instruction that this instruction corresponds to.
  ///
  /// Result instruction is in the same pattern group.
  /// It needs to be filled when instruction is used in mapping section.
  int ReplaceIdx;

  /// Vector of operands that it shares with previous pattern instruction.
  SmallVector<PatternOp *, 2> ConnectedOps;

  /// Variadic operands of real instruction that is matched to this one.
  SmallVector<MachineOperand, 4> VariadicOp;

public:
  /// Destructor.
  ~PatternInstr() override;

  /// Constructor
  PatternInstr(const unsigned opc, const TargetInstrInfo *tii,
               int replaceIdx = UNDEFINED);

  /// Returns index of corresponding replace instruction.
  int getReplaceIdx() const { return ReplaceIdx; }

  /// Returns operands that it shares with previous pattern instruction.
  SmallVectorImpl<PatternOp *> *getPrevPIConns() { return &ConnectedOps; }
  void addPrevPIConn(PatternOp *po) { ConnectedOps.push_back(po); }

  /// Returns variadic operands of corresponding real instruction.
  SmallVectorImpl<MachineOperand> *getVariadicOps() { return &VariadicOp; }
  void addVariadicOp(MachineOperand &mo) { VariadicOp.push_back(mo); }

  /// Set the instruction that was matched to this pattern instruction.
  void setRealInstr(MachineInstr *mi) override;

  /// Reinitialize all members that are filled during pattern search, so that it
  /// can be reused.
  void reset() override;

  /// Print info about this class to dbgs().
  void dump() const override;
};

// ********************* RESULT INSTRUCTION ***********************
/// \brief Describes instructions that will replace PatternInstr.
class ResultInstr : public IntermediateInstr {
public:
  /// Destructor
  ~ResultInstr() override = default;

  /// Constructor
  ResultInstr(const unsigned opc, const TargetInstrInfo *tii);

  /// Add variadic operands to newly created instruction.
  void addVariadicOperands(MachineInstrBuilder &MIB);

  /// Reinitialize all members that are filled during pattern search, so that it
  /// can be reused.
  void reset() override;

  /// Print info about this class to dbgs().
  void dump() const override;

  /// Set the instruction that was matched to this pattern instruction.
  void setRealInstr(MachineInstr *mi) override {
    IntermediateInstr::setRealInstr(mi);
  }

  /// \brief Set new instruction flags.
  ///
  /// It sets FrameSetup and FrameDestroy flags if they were in pattern
  /// instructions in the same pattern group.
  MachineInstrBuilder &setInstFlags(MachineInstrBuilder &MIB);
};

// ********************* PATTERN ***********************************
/// \brief Represents whole pattern.
class Pattern {
  /// Name of the pattern.
  std::string Name;

  /// \brief Registers affected by replacing pattern.
  ///
  /// These operands will be erased or moved by replacing the pattern,
  /// so debug instructions using them must be erased as well.
  SmallVector<unsigned, 1> DebugRegs;

  /// \brief Vector of searched through basic blocks.
  ///
  /// Doesn't contain empty basic blocks.
  SmallVector<MachineBasicBlock *, 2> UsedMBB;

  /// All OpsConnections classes for this pattern.
  SmallVector<PatternOpConnection *, 1> OpsConnections;

  /// All pattern groups that it contains.
  SmallVector<PatternGroup *, 1> PatternGroups;

  /// Fill info containing data dependencies of the pattern.
  void fillOpConecctions();

  /// Fill info about data connection with previous pattern instruction;
  void fillConnectionsWithNext();

  /// Fill info associated with mapping section.
  void fillValueMapping();

protected:
  /// class with info needed for lto
  LTOFileInfo *LtoFile = nullptr;

public:
  /// Destructor
  virtual ~Pattern();

  /// Constructor
  Pattern() = default;

  /// \brief Adds result instruction to pattern group.
  ///
  /// If pattern group wasn't already added to pattern, it does that as well.
  void addResultInstr(ResultInstr *ri, PatternGroup *pg);

  /// \brief Adds pattern instruction to pattern group.
  ///
  /// If pattern group wasn't already added to pattern, it does that as well.
  void addPatternInstr(PatternInstr *pi, PatternGroup *pg);

  /// Returns a name of the pattern.
  std::string getName() const { return Name; }
  void setName(std::string name) { Name = name; }

  /// Returns true if condition specified by user is satisfied.
  bool checkUserCondition();

  /// Returns all pattern groups of this pattern.
  SmallVectorImpl<PatternGroup *> *getPatternGroups() { return &PatternGroups; }

  /// Returns registers erased or moved by replacing the pattern.
  SmallVectorImpl<unsigned> *getDbgRegs() { return &DebugRegs; }
  void addDbgReg(unsigned i) { DebugRegs.push_back(i); }

  /// \brief Returns MBBs that were searched through when looking for pattern.
  ///
  /// Empty MBBs are not included.
  SmallVectorImpl<MachineBasicBlock *> *getUsedMBBs() { return &UsedMBB; }
  void addUsedMBBs(MachineBasicBlock *mbb) { UsedMBB.push_back(mbb); }

  /// \brief Updates used MBBs.
  ///
  /// It is used after backtracking or searching through new MBB.
  /// It updates in a way, so that lastMBB is the last used MBB.
  void updateUsedMBBs(MachineBasicBlock *lastMBB);

  /// Returns number MBBs that algorithm searched through.
  unsigned getNumUsedMBBs() const { return UsedMBB.size(); }

  /// Reinitialize all members that are filled during pattern search, so that it
  /// can be reused.
  void reset();

  /// Returns true if instruction is matched in pattern.
  bool isMatchedIn(const MachineInstr *mi) const;

  /// Print info about this class to dbgs().
  void dump() const;

  /// \brief Fill data members of various pattern structures.
  ///
  /// These structures can be filled only after all parts of the pattern are
  /// specified.
  void finishConstruction();

  /// Special conditions that may be supplied with patterns.
  virtual bool userCondition(std::vector<IntermediateInstr *> &foundInst) {
    return true;
  }

  /// \brief Returns predecessor to specified pattern instruction.
  ///
  /// If there is no predecessor, it returns input operand.
  void getPrevPI(PatternInstrIterator &piIt, PatternGroupIterator &pgIt);
};

// ******************* PEEPHOLE REPORT *****************************
/// \brief Collects and prints information needed for report
class CodasipPeepholeReport {
  /// Stream that report will be printed to.
  raw_ostream &outStr;

  /// Number of erased instructions.
  unsigned ErasedIns = 0;

  /// Number of created instructions.
  unsigned CreatedIns = 0;

  /// Names of found patterns.
  SmallVector<std::string, 4> FoundPatts;

public:
  /// Destructor
  ~CodasipPeepholeReport() { FoundPatts.clear(); }

  /// Constructor
  explicit CodasipPeepholeReport(raw_ostream &stream) : outStr(stream) {}

  /// Print summary.
  void printReportSum(const bool isPreRa) const;

  /// Print report after one pattern.
  void printOnePattern(Pattern *pat);
};

/// \brief Returns true if operands are equal.
///
/// When operand are registers, it doesn't take isDef into account.
bool realOpsAreEqual(const MachineOperand &mo1, const MachineOperand &mo2);

} // namespace llvm

#endif /* INCLUDE_CODASIP_TARGET_CODASIPBASEPEEPHOLE_H_ */
