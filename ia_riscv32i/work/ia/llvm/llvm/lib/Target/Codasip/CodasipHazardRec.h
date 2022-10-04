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


#include "llvm/CodeGen/ScoreboardHazardRecognizer.h"

#include <list>
#include <set>

namespace llvm {

class TargetInstrInfo;
class TargetRegisterInfo;

/// Represents writes which occusrs in the same cycle.
typedef std::set<unsigned> regList;
/// Our own version of a scoreboard for register writes.
struct RegisterBoard: public std::list<regList>
{
  unsigned getDepth() const {return size();}
  /// Creates a list with 'n' empty items.
  void reset(unsigned n);
  /** Advances/perishes older records, adds a new one.
   * Hence, the depth (size of the list) remains same. */
  void advance();
  /** Is the given register pending?
   * In other words: does it have a record? */
  bool isPending(unsigned r, const TargetRegisterInfo &TRI);
  /** Adds a register in the given cycle.
   * Asserts if the list isn't long enough. */
  void addReg(unsigned c, unsigned r);
  /// Prints the scoreboard.
  void dump() const;
};
  
/// Codasip post-RA hazard recognizer
class MachineHazardRecognizer: public ScoreboardHazardRecognizer
{
  const TargetInstrInfo *TII;
  const TargetRegisterInfo *TRI;
public:
  MachineHazardRecognizer(const InstrItineraryData *ItinData,
                          const TargetInstrInfo *tii,
                          const TargetRegisterInfo *tri)
  : ScoreboardHazardRecognizer(ItinData, NULL), TII(tii), TRI(tri) {}
  // check scoreboards
  bool Empty();
  // enriched Advance and Reset
  void Reset();
  void AdvanceCycle();
  // our own hazard detection
  // - almost same as in llvm but over machine instr
  ScheduleHazardRecognizer::HazardType getMachHazardType(const MachineInstr *MI, int Stalls=0);
  // another mi variation
  void EmitMachInstruction(const MachineInstr *MI);
  void EmitMachInstruction2(const MachineInstr *MI);
private:
  // for data hazards
  RegisterBoard Registers;
};

}
