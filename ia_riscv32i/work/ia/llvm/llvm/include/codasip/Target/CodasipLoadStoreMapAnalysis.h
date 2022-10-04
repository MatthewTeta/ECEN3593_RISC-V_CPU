/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip s.r.o.
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this
 * file, may be use, copied, modified, or distributed except in accordance with
 * the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 * \file
 * \date    2019-09-30
 * \author  Codasip (c) C compiler backend generator
 * \version 8.1.1-internal
 * \brief   Source for compiler backend
 * \project codasip_urisc.ia
 * \note          8.1.1-internal
 *                Project: codasip_urisc.ia
 *                Date: 2019-09-30 11:05:01
 *                Copyright (C) 2019 Codasip s.r.o.
 */

#ifndef CODASIPLOADSTOREMAPANALYSIS_H
#define CODASIPLOADSTOREMAPANALYSIS_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"
#include <map>

namespace llvm {

class CodasipLoadStoreMapAnalysis : public MachineFunctionPass {
public:
  using InnerVec = SmallVector<MachineBasicBlock::const_instr_iterator, 3>;
  using InnerVecIter =
      SmallVectorImpl<MachineBasicBlock::const_instr_iterator>::iterator;
  using InstrMap = std::map<const MachineBasicBlock *, InnerVec>;

private:
  /// Map of all load instructions contained in certain mbb. Instructions are
  /// ordered according to their appearance in mbb.
  InstrMap LoadMap;
  /// Map of all store instructions contained in certain mbb. Instructions are
  /// ordered according to their appearance in mbb.
  InstrMap StoreMap;
  /// Map of all instructions with side effects contained in certain mbb.
  /// Instructions are ordered according to their appearance in mbb.
  InstrMap SideEffectsMap;
  /// Map of all load, store and instructions with side effects contained in
  /// certain mbb. Instructions are ordered according to their appearance in
  /// mbb.
  InstrMap CombinedMap;
  /// Insert instruction \p mi to appropriate place in \p vec vector
  /// When \p inCombined is true, it inserts it only to CombinedMap vector,
  /// otherwise insert it to other appropriate vector
  InnerVecIter findInsertPlace(InnerVec &vec, const MachineInstr &mi,
                               bool inCombined);
  /// Erase instruction \p mi from \p vec vector
  void eraseFromVector(InnerVec &vec, const MachineInstr &mi);

public:
  static char ID;
  CodasipLoadStoreMapAnalysis();
  ~CodasipLoadStoreMapAnalysis() { releaseMemory(); }
  bool runOnMachineFunction(MachineFunction &F) override;
  void dump();
  const InstrMap &getLoadMap() { return LoadMap; }
  const InstrMap &getStoreMap() { return StoreMap; }
  const InstrMap &getSideEffectsMap() { return SideEffectsMap; }
  const InstrMap &getCombinedMap() { return CombinedMap; }
  /// Adds instruction to all appropriate maps
  void addInstr(const MachineInstr &mi);
  /// Erases instruction from all appropriate maps
  void eraseFromMaps(const MachineInstr &mi);
  void releaseMemory() override;
};

} // namespace llvm
#endif // LOADSTOREMAPANALYSIS_H
