//===----- BunchOfSuperBlocks.h - SuperBlock ------------------------------===//
//
// author : Tomas Minac
// mail   : minac@codasip.com
// about  : this class implement abstraction upon bunch of SuperBlocks.
//          Similar to BunchOfSuperBlocks.h from opt-superblocks, but
//          here is used MachineBasicBlock instead BasicBlock etc.
//
//===----------------------------------------------------------------------===//

#ifndef __BUNCHOFSUPERBLOCK_H__
#define __BUNCHOFSUPERBLOCK_H__

#include "SuperBlock.h"
#include "llvm/IR/Module.h"
#include <map>
#include <set>

#define PATTERN_STRING ".__SP__"
#define SEPARATOR_STRING "__"

namespace llvm {

class SuperBlock;

class BunchOfSuperBlocks {
private:
  std::string patternString;
  std::string separatorString;
  std::vector<SuperBlock *> bunchOfSBBs;

  /// map of numbering to superblocks themselves.
  std::map<unsigned, SuperBlock *> mapNumbToSuperBlock;

  /// LLVM sometimes invalidates superblocks by inserting empty BBs.
  /// Reevaluate and fix it.
  void fixSuperBlocks();

  /// helper function to check for "sibling" connection between blocks.
  /// checks for a common predecessor.
  bool isSuccOfPred(SuperBlock::iterator &sbbIt, SuperBlock *sb);

  /// Figure out the SB of this MBB based on the __SP__#N_ naming...
  void processBasicBlock(MachineBasicBlock *mbb,
                         std::vector<SuperBlock *> &vecOfNotMarkedBB);

public:
  using iterator = std::vector<SuperBlock *>::iterator;
  using const_iterator = std::vector<SuperBlock *>::const_iterator;
  inline iterator begin() { return bunchOfSBBs.begin(); }
  inline const_iterator begin() const { return bunchOfSBBs.begin(); }
  inline iterator end() { return bunchOfSBBs.end(); }
  inline const_iterator end() const { return bunchOfSBBs.end(); }

  inline size_t size() const { return bunchOfSBBs.size(); }
  inline bool empty() const { return bunchOfSBBs.empty(); }

  BunchOfSuperBlocks() {
    patternString = PATTERN_STRING;
    separatorString = SEPARATOR_STRING;
  }

  // void addToBunch(SuperBlock *superBlock) {
  //   bunchOfSBBs.push_back(superBlock);
  // }

  void dump() {
    for (const auto &SBB : *this) {
      dbgs() << "\nSuperBlock: ";
      SBB->dump();
      dbgs() << "--------------------------------\n";
    }
  }

  /// read all blocks in MF and sort them to superblocks. Add them to the Bunch.
  void readFunction(MachineFunction *f);
};

} // namespace llvm

#endif
