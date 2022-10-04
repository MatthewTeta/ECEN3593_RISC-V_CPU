//===-- llvm/ADT/Hashing.h - Utilities for hashing --------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_ADT_SEQUENCE_ALIGNMENT_H
#define LLVM_ADT_SEQUENCE_ALIGNMENT_H

#include "llvm/ADT/Optional.h"
#include "llvm/ADT/SmallVector.h"

#include "codasip/FunctionMerging/ArrayView.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <limits.h> // INT_MIN
#include <list>
#include <vector>

#define ScoreSystemType int

namespace llvm {

// Store alignment result here
template <typename Ty> class AlignedSequence {
public:
  std::list<std::pair<Ty, Ty>> Data;

  AlignedSequence() {}

  AlignedSequence(const AlignedSequence<Ty> &Other) : Data(Other.Data) {}
  AlignedSequence(AlignedSequence<Ty> &&Other) : Data(std::move(Other.Data)) {}

  AlignedSequence<Ty> &operator=(const AlignedSequence<Ty> &Other) {
    Data = Other.Data;
    return (*this);
  }

  void append(const AlignedSequence<Ty> &Other) {
    Data.insert(Data.end(), Other.Data.begin(), Other.Data.end());
  }

  void splice(AlignedSequence<Ty> &Other) {
    Data.splice(Data.end(), Other.Data);
  }
};

class ScoringSystem {
  ScoreSystemType Gap;
  ScoreSystemType Match;
  Optional<ScoreSystemType> Mismatch;

public:
  ScoringSystem(
      ScoreSystemType Gap, ScoreSystemType Match,
      Optional<ScoreSystemType> Mismatch = Optional<ScoreSystemType>()) {
    this->Gap = Gap;
    this->Match = Match;
    this->Mismatch = Mismatch;
  }

  bool getAllowMismatch() { return ((bool)Mismatch); }

  Optional<ScoreSystemType> getMismatchPenalty() { return Mismatch; }

  ScoreSystemType getGapPenalty() { return Gap; }

  ScoreSystemType getMatchProfit() { return Match; }
};

template <typename ContainerType,
          typename MatchFnTy =
              std::function<bool(typename ContainerType::value_type,
                                 typename ContainerType::value_type)>,
          typename Ty = typename ContainerType::value_type>
class SequenceAligner {
private:
  ScoringSystem Scoring;
  MatchFnTy Match;
  Ty Blank;

  ArrayView<ContainerType> Seq0;
  ArrayView<ContainerType> Seq1;

  AlignedSequence<Ty> Result;

public:
  SequenceAligner(ScoringSystem Scoring, MatchFnTy Match, Ty Blank,
                  ContainerType &Seq0, ContainerType &Seq1)
      : Scoring(Scoring), Match(Match), Blank(Blank), Seq0(Seq0), Seq1(Seq1) {}

  ScoringSystem &getScoring() { return Scoring; }

  bool match(Ty Val1, Ty Val2) { return Match(Val1, Val2); }

  MatchFnTy getMatchOperation() { return Match; }

  Ty getBlank() { return Blank; }

  AlignedSequence<Ty> &getResult() { return Result; }

  size_t getNumSequences() { return 2; }

  ArrayView<ContainerType> &getSequence(int idx) {
    assert((idx == 0 || idx == 1));
    return (idx == 0) ? Seq0 : Seq1;
  }
};

#include "codasip/FunctionMerging/SAHirschberg.h"
#include "codasip/FunctionMerging/SANeedlemanWunsch.h"
//#include "llvm/ADT/MySA.h"

} // namespace llvm

#endif
