//===----- SuperBlock.h - SuperBlock -------------------------------------===//
//
// author : Tomas Minac
// mail   : minac@codasip.com
// about  : this class implement abstraction upon SuperBlock, very similar like
//          in opt-superblock, but here we use Machine* prefix before
//          MachineBasicBlock etc.
//
//===----------------------------------------------------------------------===//

#ifndef __SUPERBLOCK_H__
#define __SUPERBLOCK_H__

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/CodeGen/MachineDominators.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineLoopInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/ScheduleDAG.h"
#include "llvm/CodeGen/ScheduleHazardRecognizer.h"
#include "llvm/CodeGen/SchedulerRegistry.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/Target/TargetMachine.h"
#include <sstream>
#include <string>
#include <vector>

namespace llvm {

class MachineBasicBlock;

class SuperBlock {
private:
  std::vector<MachineBasicBlock *> BBs;

public:
  SuperBlock() = default;
  explicit SuperBlock(std::vector<MachineBasicBlock *> &NewSuperBlock) {
    BBs = NewSuperBlock;
  }

  static SuperBlock *Create() { return new SuperBlock(); }
  static SuperBlock *Create(std::vector<MachineBasicBlock *> &NewSuperBlock) {
    return new SuperBlock(NewSuperBlock);
  }
  using MBBVector = std::vector<MachineBasicBlock *>;
  using iterator = MBBVector::iterator;
  using const_iterator = MBBVector::const_iterator;
  using reverse_iterator = MBBVector::reverse_iterator;
  using const_reverse_iterator = MBBVector::const_reverse_iterator;

  inline iterator begin() { return BBs.begin(); }
  inline const_iterator begin() const { return BBs.begin(); }
  inline iterator end() { return BBs.end(); }
  inline const_iterator end() const { return BBs.end(); }

  inline reverse_iterator rbegin() { return BBs.rbegin(); }
  inline const_reverse_iterator rbegin() const { return BBs.rbegin(); }
  inline reverse_iterator rend() { return BBs.rend(); }
  inline const_reverse_iterator rend() const { return BBs.rend(); }

  inline size_t size() const { return BBs.size(); }
  inline bool empty() const { return BBs.empty(); }

  void addToEnd(MachineBasicBlock *bb) { BBs.push_back(bb); }

  /// isBBInSBB - check if BasicBlock is in SuperBlock
  bool isBBInSBB(MachineBasicBlock *BB) { return is_contained(BBs, BB); }

  MachineBasicBlock *operator[](int i) {
    if (i < 0 || (unsigned)i >= BBs.size())
      return nullptr;
    return BBs[i];
  }

  /// sizeInst - return instruction count in SuperBlock
  size_t sizeInst() {
    size_t sum = 0;
    for (const auto &BB : *this) {
      sum += BB->size();
    }
    return sum;
  }

  void dump() {
    for (const auto &BB : BBs) {
      dbgs() << BB->getBasicBlock()->getName() << "\n";
    }
  }

  void dump(bool longVersion) {
    if (longVersion) {
      for (const auto &BB : BBs) {
        dbgs() << *BB << "\n";
      }
    } else {
      dump();
    }
  }

  void erase(iterator start, iterator end) { BBs.erase(start, end); }
};

} // namespace llvm

#endif
