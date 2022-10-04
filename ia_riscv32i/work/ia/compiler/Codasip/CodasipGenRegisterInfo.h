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


#ifndef CODASIPGENREGISTERINFO_H
#define CODASIPGENREGISTERINFO_H

#include "Codasip.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_ENUM
#define GET_REGINFO_HEADER
#include "CodasipGenRegisterInfo.inc"

#include <list>

namespace llvm {

// vector of strings
typedef std::vector<std::string> RegNamesVec;

class CodasipGen2RegisterInfo: public CodasipGenRegisterInfo
{
public:
  const TargetInstrInfo &TII;
  CodasipGen2RegisterInfo(const TargetInstrInfo &tii);
  const MCPhysReg* getCalleeSavedRegs(const MachineFunction* MF) const override;
  BitVector getReservedRegs(const MachineFunction &MF) const override;
  void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj, unsigned FIOperandNum, RegScavenger *RS=NULL) const override;
  Register getFrameRegister(const MachineFunction &MF) const override;
  unsigned getFrameRegister(const MachineFunction &MF, int space) const;
  // registers not overwritten by a call ~ callee saved registers
  const uint32_t *getCallPreservedMask(const MachineFunction &MF, CallingConv::ID) const override;
  // if Kind has default value, returns class containing BP
  const TargetRegisterClass* getPointerRegClass(const llvm::MachineFunction &MF, unsigned Kind) const override;
  const TargetRegisterClass* getLargestLegalSuperClass(const TargetRegisterClass* RC, const MachineFunction&) const override;
  bool requiresRegisterScavenging(const MachineFunction &MF) const override {
    return true;
  }
  // to materialize frame index constants (virtregs created by regScavenging)
  bool requiresFrameIndexScavenging(const MachineFunction &MF) const override {
    return true;
  }
  // dual stack registers
  unsigned GetSP(unsigned space) const;
  unsigned GetBP(unsigned space) const;
  const uint32_t *getNoPreservedMask() const override;
  // Frame index eliminitation info
  struct FiInfo {
    // indexes (base and offset)
    int bi,oi;
    // physical width if imm off, 0 otherwise
    unsigned w;
  };
  typedef std::list<FiInfo> IndList;
  FiInfo GetFiOpIndexes(MachineInstr &MI, unsigned FIOperandNum) const;
  bool CheckRegClass(const MachineRegisterInfo &MRI, const TargetRegisterClass *RC, unsigned Reg) const;
  bool hasReservedSpillSlot(const MachineFunction &MF, unsigned Reg, int &FrameIdx) const override;
  // for inline asm with 'p'
  virtual ArrayRef<MCPhysReg> getPairOrder(const TargetRegisterClass* RC, MachineFunction& MF) const;
protected:
  virtual bool HandleAR(MachineInstr &MI, unsigned ind, unsigned AR) const;
  bool CheckAR(const MachineInstr &MI, unsigned ind, unsigned AR) const;
  // Extra reserved registers from command line
  RegNamesVec ExtraReservedRegs;
  // Unreserved registers from command line
  RegNamesVec UnreservedRegs;
};

}

#endif
