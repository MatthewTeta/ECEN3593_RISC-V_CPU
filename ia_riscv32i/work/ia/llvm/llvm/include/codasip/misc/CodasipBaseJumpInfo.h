/**
 * Codasip Ltd
 *
 * Copyright 2018 Codasip Ltd
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this
 * file, may be use, copied, modified, or distributed except in accordance with
 * the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 * \file    CodasipBaseJumpInfo.h
 * \date    31. 10. 2018
 * \author  Stanislav Melo
 * \version 5.5.0.
 * \brief   Base class for JumpInfo
 */

#ifndef CODASIP_LLVM_BASEJUMPINFO_H_
#define CODASIP_LLVM_BASEJUMPINFO_H_

#include "codasip/misc/utils.h"

namespace llvm {

typedef MachineBasicBlock::instr_iterator InstrIt;

// class that represents file containing sybols and their adresses
// that is used in -link-info-optim argument
class LTOFileInfo {
  bool UseFile = false;
  std::ifstream File;
  // Name of the symbol it is looking for in codasip lto info file
  std::string Pattern = "";
  // Name of the compiled file that examined instruction containing this
  // symbol is in. It is necessary only for local symbols.
  std::string FileName = "";
  // Searched symbol is global or local
  bool IsGlobalLinkSymbol = false;

private:
  /// Sets Pattern and IsGlobalLinkSymbol information based on \p symbol.
  /// \param symbol  Symbol that will be searched in codasip lto info file.
  /// \param mf      Function which contains optimization candidate
  ///                instruction with symbol.
  void setPatternInfo(const MachineOperand *symbol, const MachineFunction *mf);

  /// \brief Get address of pattern in codasip lto info file.
  ///
  /// Pattern, FileName and IsGlobalLinkSymbol must be set first.
  /// \param result Address that is associated with pattern.
  /// \return True if pattern was found. */
  bool searchLTOFile(int64_t &result);

public:
  LTOFileInfo();
  ~LTOFileInfo();
  bool useLTOFile() const { return UseFile; }

  /// Returns address of selected MachineBasicBlock or nearest previous
  /// MachineBasicBlock that has address.
  bool getPrevSymbolAddress(MachineBasicBlock **mbb, int64_t &address);
  /// The same but nearest next
  bool getNextSymbolAddress(MachineBasicBlock **mbb, int64_t &address);

  /// \brief Get symbol address from codasip lto info file.
  ///
  /// \param symbol  It returns address of this symbol
  /// \param mf      Function which contains the symbol.
  /// \param file    Codasip lto info file.
  /// \param address Found address of the symbol.
  /// \return        True if symbol was found. */
  bool getSymbolAddress(const MachineOperand *symbol, const MachineFunction *mf,
                        int64_t &address);
};

/// SlotData is vector of vectors
///   SlotData          - Vector, containing all possible instruction
///                       positions inside a bundle.
///   SlotData.size()   - Number of combinations an instruction can exist in
///                       a bundle.
///   SlotData[]        - Vector, containing slots an instruction occupies
///                       inside a bundle in this particular combination.
///   SlotData[].size() - Number of slots instruction occupies inside a
///                       bundle. It should be the same across all combinations.

/// Types of jump:
///   absolute - It jumps to value specified by operand, calls can
///              be ONLY absolute.
///   relative - It jumps to PC + value specified by operand.
///   direct   - Operand contains jump destination.
///   indirect - Operand contains pointer to jump destination.

/// Information about jump/call ins needed for this pass.
/// So far it is the first place that contains all this information.
class BaseJumpInfo {

public:
  /// Possible directions of jumps.
  enum JmpDirection {
    BACK,    ///< Jumps only to BB's before its location.
    FORWARD, ///< Jumps only to BB's after its location.
    BOTH     ///< Jumps both ways.
  };
  /// Types of computing/checking instruction address with lto
  enum InstrAddrComputationMode {
    SINGLE,  ///< Use the address of the nearest previous mbb. (default)
    DOUBLE,  ///< Use the address of the nearest previous and next mbb.
    FUNCTION ///< Use the address of the function that the instruction is in.
  };

protected:
  /// Number of delay slots.
  int DelaySlots = 0;
  /// Position where this instruction is or shoud be.
  InstrIt Position;
  unsigned Opcode = 0;
  /// Number of bits used to encode jump destination
  unsigned BitWidth = 0;
  SlotData BundlePosition;
  bool IsAbsolute = false;
  unsigned NumInsInBundle = 0;
  /// Jump direction
  JmpDirection Direction = BOTH;
  /// Contains jump/call destination
  MachineOperand Destination;
  /// Basic block where this instruction is or shoud be.
  MachineFunction::iterator PositionMBB;
  /// Function where this instruction is or shoud be.
  MachineFunction *PositionMF = nullptr;

public:
  /// Constructors.
  BaseJumpInfo(const MachineOperand *mo) : Destination(*mo) {}

  /// Returns true if instruction can occupy the slot.
  bool canOccupySlot(unsigned slot) const;

  /// Return first viable slot that instruction can occupy in a bundle.
  unsigned getFirstInsSlot() const;
  unsigned getInsDelaySlots(const TargetInstrInfo *tii,
                            const MachineFunction *mf) const;

  /// \brief Returns true if instruction can jump to destination.
  ///
  /// Checks if jump can represent destination address on number of bits
  /// assigned for it's address operand and if it can jump in destinations
  /// direction.
  /// \param [in] dest Destination that instr jumps to.
  /// \param [in] strict If set to true, function returns false when it doesn't
  /// have sufficient info about destination address.
  /// \param [in] ltoFile Class representing file with
  ///             symbol addresses used in lto.
  /// \return True if instruction can jump to specified destination.
  bool canJumpToDestination(const MachineOperand *dest, bool strict,
                            LTOFileInfo *ltoFile) const;

  /// Returns true if this jump has delay slots.
  int getNumDelaySlots() const { return DelaySlots; }
  bool hasDelaySlots() const { return (DelaySlots > 0); }

  unsigned getOpcode() const { return Opcode; }
  bool isAbsolute() const { return IsAbsolute; }
  unsigned getBitWidth() const { return BitWidth; }
  const MachineOperand *getDestination() const { return &Destination; }
  void setDestination(const MachineOperand &mo) { Destination = mo; }
  InstrIt getPosition() const { return Position; }
  void setPosition(InstrIt pos) { Position = pos; }
  MachineFunction *getMFPosition() const { return PositionMF; }
  MachineFunction::iterator getMBBPosition() const {
    assert(PositionMF != nullptr && PositionMBB != PositionMF->end());
    return ((Position != PositionMBB->instr_end())
                ? Position->getParent()->getIterator()
                : PositionMBB);
  }
  void setMBBPosition(MachineFunction::iterator pos) { PositionMBB = pos; }
  /// Returns instruction that is on position specified it this class.
  MachineInstr *getInstruction() const {
    assert(PositionMF != nullptr && PositionMBB != PositionMF->end() &&
           Position != PositionMBB->instr_end());
    return &(*Position);
  }
  // Positions are dependant on instruction that this class represents
  void setInstruction(MachineInstr *mi) {
    Position = mi->getIterator();
    PositionMBB = mi->getParent()->getIterator();
    PositionMF = mi->getParent()->getParent();
  }
  unsigned getNumInsInBundle() const { return NumInsInBundle; }
  JmpDirection getJumpDirection() const { return Direction; }

  /// Returns true if this jump is bundled.
  bool isBundled(unsigned bundleSize) const {
    return (BundlePosition[0].size() < bundleSize);
  }

  /// Destructor.
  virtual ~BaseJumpInfo() { BundlePosition.clear(); }

  /// Returns opcode of jump instruction that is the same as \p opcode,
  /// but it has inverted condition.
  unsigned getInvertJumpOpcode(const CodasipBaseInstrInfo *cii) const;

  /// Latency is number of delay slots + 1 (from Mips)
  unsigned getLatency() const { return DelaySlots + 1; }

private:
  /// \brief Returns true if instruction can jump in the direction of
  /// destination.
  ///
  /// Some jumps can only add to/subtract from PC, therefore they can only jump
  /// in one direction.
  bool canJumpInDirection(const MachineBasicBlock *dest) const;
  bool canJumpInDirection(unsigned fromAddr, unsigned toAddr) const;
  /// \brief Computes instruction address with info about mbb address
  /// and instruction distance to the beginning of that mbb.
  ///
  /// \param [in] startMbb mbb used in instr address computation
  /// \param [out] result Computed instruction address.
  /// \param [in] ltoFile File containing mbbs addresses.
  /// \return True if instruction address was sucessfuly computed.
  bool instrAddrPrevRef(MachineBasicBlock *startMbb, int64_t &result,
                        LTOFileInfo *ltoFile) const;
  /// \brief Uses instructions mbb in address computation implicitly
  bool instrAddrPrevRef(int64_t &result, LTOFileInfo *ltoFile) const;
  bool instrAddrNextRef(int64_t &result, LTOFileInfo *ltoFile) const;

  /// Returns true if address of MBB1 is lesser or equal than address of MBB2.
  static bool hasLEAddress(const MachineBasicBlock *MBB1,
                           const MachineBasicBlock *MBB2);

  /// \brief Returns true if value can be represented by operand with certain
  /// properties.
  ///
  /// \param [in] imm Value that is being examined.
  /// \param [in] width Number of bits that operand for representing value.
  /// \param [in] sign True if operand accepts signed values.
  /// \param [in] trunc Operand expects value to be rounded to this value.
  /// \return True if value can be represented by operand.
  virtual bool immediateFits(int64_t imm, int width, bool sign,
                             int trunc) const {
    return false;
  }

  /// Computes distance between intruction specified by iterators and the
  /// beggining of dest basic block.
  virtual unsigned computeDistance(MachineFunction &F,
                                   MachineFunction::iterator FI, InstrIt I,
                                   MachineBasicBlock *dest) const {
    return 0;
  }
};

} // namespace llvm

#endif // BASEJUMPINFO_H_
