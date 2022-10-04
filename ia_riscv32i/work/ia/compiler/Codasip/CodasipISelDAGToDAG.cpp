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


/* Creates target specific DAG from general one.
 * We should try to leave this file as it is and describe
 * as much as we can in td in InstrInfo.td */

#define DEBUG_TYPE "codasip-isel"

#include "llvm/IR/Intrinsics.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetIntrinsicInfo.h"
#include "llvm/CodeGen/PseudoSourceValue.h"
#include "codasip/Target/CodasipBaseMoiLowerer.h"
#include "CodasipInstructionSemantics.h"
#include "Codasip.h"
#include "CodasipISelLowering.h"
#include "CodasipTargetMachine.h"
#include "CodasipMachineFunction.h"
#include "CodasipInstrInfo.h"

#include <cstdio>
#include <iostream>
#include <cassert>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>

#include <inttypes.h>
// on windows redefinition of macros
#undef PRId64
#undef PRIi64
#undef PRIo64
#undef PRIu64
#undef PRIx64
#undef PRIX64

using namespace llvm;
using namespace Codasip;

#define MOI_GROUP_MAP_SIZE  0

static cl::opt<bool> UseLongCalls("long-calls", cl::init(false),
  cl::desc("Pick the longest call where available"));

static cl::opt<bool> UseShortCalls("no-long-calls", cl::init(false),
  cl::desc("Pick the shortest call where available"));


namespace {

// wrapper class for BaseDagPattern, so it has access
// to some methods from backend of particular core
class DagPattern: public BaseDagPattern
{
protected:
  CodasipTargetMachine &CTM;
public:
  DagPattern(SelectionDAG *DAG, int *pattInfo, CodasipTargetMachine &TM, ValueVec &roots)
  : BaseDagPattern(DAG, pattInfo, TM, roots), CTM(TM) {}
  ImmInfo GetImmInfo(unsigned opcode, unsigned opNum) override
  {
    ImmInfo info = {0,false,0};
    CTM.getInstrInfo()->GetImmProperties(opcode, opNum, info.width, info.sign, info.trunc);
    return info;
  }
  bool CheckImmWidth(int64_t val, int width, bool sign, int trunc) override
  {
    return CheckImmImpl(val, width, sign, trunc);
  }
  const TargetRegisterClass *GetRegClass(int rc) override
  {
    return CTM.getRegisterInfo()->getRegClass(rc);
  }
};

class CodasipGenDAGToDAGISel: public SelectionDAGISel
{
protected:
  CodasipTargetMachine &TM;

public:
  explicit CodasipGenDAGToDAGISel(CodasipTargetMachine &tm):
  SelectionDAGISel(tm, tm.getOptLevel()), TM(tm) {}
  bool SelectInlineAsmMemoryOperand(const SDValue &Op, unsigned ConstraintCode, std::vector<SDValue> &OutOps) override;
  void PreprocessISelDAG() override;
  void PostprocessISelDAG() override;
  void adjustCallLengths();
  StringRef getPassName() const override {return "Codasip DAG2DAG Pattern Instruction Selection";}

  

protected:
  #include "CodasipGenDAGISel.inc"

  void Select(SDNode *Node) override;
  bool SelectOffsettable(const SDValue &Op, std::vector<SDValue> &OutOps);
  /** Checks a value for imm oper.
   * \param width  The real width. */
  bool CheckImm(int64_t Imm, int width, bool sign, int trunc) const;
  /// Same as CheckImm
  virtual bool CheckSymbol(SDNode *n, int width, bool sign, int trunc) const;
  /** Checks align and address space of a load/store.
   * \param space  Address space index.   */
  bool CheckLoadStore(const MemSDNode *n, int align, int space) const;
  /** Make checks if FI.
   * \param rc Class index. */
  bool CheckFI(SDNode *n, int rc) const;

  /// Mapping of instructions on MOI groups (instruction -> group)
  static int InstrGrpMap[][2];

  void LowerMoiPatterns(SelectionDAG *DAG);
};

// moi map
int CodasipGenDAGToDAGISel::InstrGrpMap[MOI_GROUP_MAP_SIZE+1][2] = {

};

}

// rudimentary check for (lowered) dynallocs
static inline bool IsIndirectADDRSPACECAST(SDValue op, unsigned space)
{
  // look through AND inserted for alignment
  if (op->getOpcode() == ISD::AND) {
    op = op.getOperand(0);
  }
  if (op->getOpcode() != ISD::SUB && op->getOpcode() != ISD::ADD) {
    return false;
  }
  op = op->getOperand(0);
  if (op->getOpcode() != ISD::CopyFromReg) {
    return false;
  }
  return true;
}

// invoked before the selection
// note: space cast nodes represent a meta-information
void CodasipGenDAGToDAGISel::PreprocessISelDAG()
{
  MachineFrameInfo& MFI = MF->getFrameInfo();
  // these FIs are explicitly specified
  FISet explASCs;
  // remove all address space casts
  for (SelectionDAG::allnodes_iterator I = CurDAG->allnodes_begin();  I != CurDAG->allnodes_end(); ++I)
  {
    SDNode *N = &(*I);
    if (N->getOpcode()==ISD::ADDRSPACECAST)
    {
      assert(N->getNumOperands()==1);
      const AddrSpaceCastSDNode *asc = cast<AddrSpaceCastSDNode>(N);
      const unsigned space = asc->getDestAddressSpace();
      SDValue op = N->getOperand(0);
      // remember space (source doesn't matter)
      if (op->getOpcode()==ISD::FrameIndex)
      {
        const FrameIndexSDNode *fin = cast<FrameIndexSDNode>(op.getNode());
        const int FI = fin->getIndex();
        if (MFI.getStackID(FI))
        {
          assert(MFI.getStackID(FI)==space && "unexpected address space conflict");
        }
        else
        {
          MFI.setStackID(FI, space);
        }
        explASCs.insert(FI);
      }
      else if (IsIndirectADDRSPACECAST(op,space))
      {
        // no action at the moment
      }
      else
      {
        errs() << "It's forbidden to use address space casts. They are reserved for internal usage only (marking of multi-stack local variables).\n";
        errs() << "This could be caused by casting pointer from one address space to pointer from another.\n";
        exit(1);
      }
      // replace
      ReplaceUses(N,op.getNode());
    }
  }
  // handle implicit FIs (all explicit are marked now)
  for (SelectionDAG::allnodes_iterator I = CurDAG->allnodes_begin();  I != CurDAG->allnodes_end(); ++I)
  {
    SDNode *N = &(*I);
    if (MemSDNode::classof(N))
    {
      MemSDNode *MN = cast<MemSDNode>(N);
      // has FI?
      SDNode *base = MN->getBasePtr().getNode();
      if (base->getOpcode() != ISD::FrameIndex)
      {
        continue;
      }
      const FrameIndexSDNode *fin = cast<FrameIndexSDNode>(base);
      const int FI = fin->getIndex();
      // has "explicit" setting?
      if (explASCs.count(FI))
      {
        continue;
      }
      // desired space
      EVT vt = MN->getMemoryVT();
      unsigned space = GetSpace4Vt(vt);
      // is set to a space >0 already?
      const unsigned space2 = MFI.getStackID(FI);
      if (space2)
      {
        if (space != space2)
        {
          // prioritize higher, keep orig otherwise
          if (space < space2) {
            space = space2;
          }
        }
      }
      else
      {
        MFI.setStackID(FI, space);
      }
    }
  }
  // prepare nodes for MOIs
  if (TM.getOptLevel() >= CodeGenOpt::Default)
  {
    LowerMoiPatterns(CurDAG);
  }
  // go through the nodes and find all frame indexes
  for (SelectionDAG::allnodes_iterator I = CurDAG->allnodes_begin();  I != CurDAG->allnodes_end(); ++I)
  {
    SDNode *N = &(*I);
    SDLoc dl(N);
    if (N->getOpcode()==ISD::FrameIndex)
    {
      // === turn (fi) into (add tfi,0)
      // prepare vt list
      SDVTList vts = N->getVTList();
      // make a copy (target version)
      FrameIndexSDNode *fi = cast<FrameIndexSDNode>(N);
      SDValue tfi = CurDAG->getTargetFrameIndex(fi->getIndex(), fi->getValueType(0));
      // prepare zero
      SDValue zr = CurDAG->getConstant(0, dl, fi->getValueType(0));
      // morph the original into (add tfi,0)
      SDValue ops[2] = {tfi,zr};
      ArrayRef<SDValue> aref(ops,2);
      N = CurDAG->MorphNodeTo(N, ISD::ADD, vts, aref);
      // === now handle the case, when there already was an add
      //     original: (add fi,imm)   preprocessed: (add (add tfi,0),imm)   desired: (add tfi,0) & (add tfi,imm)
      // go through all uses of the add node (the original fi)
      for (SDNode::use_iterator i=N->use_begin(); !i.atEnd(); ++i)
      {
        // is it an add?
        if (i->getOpcode()==ISD::ADD)
        {
          // and is adding an imm/const?
          if (i->getOperand(1).getOpcode()==ISD::Constant) {
            // redirect the first operand of this add to the newly created tfi
            CurDAG->UpdateNodeOperands(*i,tfi,i->getOperand(1));
          }
        }
      }
    }
  }
  //CurDAG->viewGraph();
  // tidy up
  CurDAG->RemoveDeadNodes();
}

// adds support for long-call / short-call attributes.
void CodasipGenDAGToDAGISel::adjustCallLengths() {
  // Attributes take precedence to flags. Putting both flags or both attributes
  // is undefined behavior.
  bool LongCall = UseLongCalls;
  bool ShortCall = UseShortCalls;
  const CodasipInstrInfo *CII = static_cast<const CodasipInstrInfo *>(TII);

  SelectionDAG::allnodes_iterator Position = CurDAG->allnodes_begin();
  while (Position != CurDAG->allnodes_end()) {
    SDNode *N = &*Position++;

    // Skip dead nodes and any non-machine opcodes.
    if (N->use_empty() || !N->isMachineOpcode())
      continue;

    const auto &OrigDesc = CII->get(N->getMachineOpcode());
    if (!OrigDesc.isCall())
      continue;

    // Check callee function attributes:
    for (const auto &Val : N->ops()) {
      if (const auto *N = dyn_cast<GlobalAddressSDNode>(Val.get())) {
        const Function *CalleeF = dyn_cast<Function>(N->getGlobal());
        if (CalleeF) {
          if (CalleeF->hasFnAttribute("long-call")) {
            LongCall = true;
            ShortCall = false;
          } else if (CalleeF->hasFnAttribute("short-call")) {
            LongCall = false;
            ShortCall = true;
          }
        }
      }
    }
    // no flags or attributes - move on.
    if (!LongCall && !ShortCall)
      continue;
    
    unsigned NewOpc = 0;
    if (OrigDesc.isTerminator())
      NewOpc = (LongCall) ? CII->getLongTailCallOpcode()
                          : CII->getShortTailCallOpcode();
    else
      NewOpc = (LongCall) ? CII->getLongCallOpcode()
                          : CII->getShortCallOpcode();

    const JumpInfo OrigJI = CII->GetJumpInfo(N->getMachineOpcode());
    const auto &NewDesc = CII->get(NewOpc);
    const JumpInfo NewJI = CII->GetJumpInfo(NewOpc);

    // Confirm the calls are actually the same and all we need to do is switch
    // the opcode:
    if (OrigDesc.getNumOperands() != NewDesc.getNumOperands())
      continue;

    bool Continue = false;
    for (unsigned i = 0; i < OrigDesc.getNumOperands(); ++i) {
      if (OrigDesc.OpInfo[i].OperandType != NewDesc.OpInfo[i].OperandType) {
        Continue = true;
        break;
      }
    }
    if (Continue)
        continue;
    if (OrigJI.IsAbsolute != NewJI.IsAbsolute ||
        OrigJI.Direction != NewJI.Direction)
      continue;
 
    // finally, only do this if the length is different:
    if (LongCall && NewJI.Length <= OrigJI.Length)
      continue;
    if (!LongCall && NewJI.Length >= OrigJI.Length) 
      continue;

    if (NewOpc) {
      SmallVector<SDValue, 8> Ops(N->op_begin(), N->op_end());
      LLVM_DEBUG(dbgs() << "Adjusting call length: opc #" << N->getMachineOpcode() << " --> opc #" << NewOpc << "\n";);
      CurDAG->MorphNodeTo(N, ~NewOpc, N->getVTList(), Ops);
    }
  }
}

void CodasipGenDAGToDAGISel::PostprocessISelDAG()
{
  // adding support for attribute long-call / short-call:
  // for simplicity this is done in a separate function, this eases the merge
  // with e.g. Bk that has a lot going on in this method already
  adjustCallLengths();
}


// we should try to leave this on automatic processes of llvm
void CodasipGenDAGToDAGISel::Select(SDNode *Node)
{
  if (Node->isMachineOpcode()) return;
  SelectCode(Node);
}

// return true if failed
bool CodasipGenDAGToDAGISel::SelectOffsettable(const SDValue &Op, std::vector<SDValue> &OutOps)
{
  // is it an add? (anything local is)
  if (Op.getOpcode() != ISD::ADD) return true;
  assert(Op.getNumOperands()==2);
  // are ops tfi and a constant?
  const SDValue &op1 = Op.getOperand(0);
  const SDValue &op2 = Op.getOperand(1);
  if (op1.getOpcode() != ISD::TargetFrameIndex) return true;
  if (op2.getOpcode() != ISD::Constant) return true;
  ConstantSDNode *imm = static_cast<ConstantSDNode*>(op2.getNode());
  SDValue timm = CurDAG->getTargetConstant(*imm->getConstantIntValue(), imm, imm->getValueType(0));
  // all is ok
  OutOps.push_back(op1);
  OutOps.push_back(timm);
  return false;
}

// select an address
bool CodasipGenDAGToDAGISel::
SelectInlineAsmMemoryOperand(const SDValue& Op, unsigned ConstraintCode, std::vector<SDValue>& OutOps)
{
  switch (ConstraintCode)
  {
    // general
    case InlineAsm::Constraint_m:
    {
      bool check = SelectOffsettable(Op,OutOps);
      if (check) {
        OutOps.push_back(Op);
      }
      break;
    }
    // only offsetable
    case InlineAsm::Constraint_o:
      return SelectOffsettable(Op,OutOps);
    // non-offsetable
    case InlineAsm::Constraint_v:
      OutOps.push_back(Op);
      break;
    // unsupported
    default:
      return SelectionDAGISel::SelectInlineAsmMemoryOperand(Op,ConstraintCode,OutOps);
  }
  // all ok
  return false;
}

bool CodasipGenDAGToDAGISel::CheckSymbol(SDNode *n, int width, bool sign, int trunc) const
{
  // get the address node
  assert(n->getNumOperands()==1);
  SDValue op = n->getOperand(0);
  // is the address data or code?
  bool isData = true;
  // name of the symbol
  std::string name;
  // analyze the symbol
  switch (op.getOpcode())
  {
    case ISD::TargetExternalSymbol:
      name = cast<ExternalSymbolSDNode>(op)->getSymbol();
      isData = false; // should be an external function 
      break;
    case ISD::TargetGlobalAddress:
    {
      const GlobalValue *gv = cast<GlobalAddressSDNode>(op)->getGlobal();
      if (gv->hasName())
      {
        name = gv->getName().str();
      }
      // var or func?
      if (GlobalObject::classof(gv)) {
        isData = GlobalVariable::classof(gv);
      }
      else {
        // don't analyse for now
        return true;
      }
      break;
    }
    default:
      // allow anything else for now
      return true;
  }
  // analyze name to get a width
  int dw = 32;
  int cw = dw;
  if (false) {}
  else if (true) dw = 32;
  if (true) cw = 32;
  
  // if signed, then width is simply one bit smaller
  // note: what about relative addresses?
  if (sign) --width;
  // fits?
  if (isData) {
      return dw <= width;
  }
  else {
      return cw <= width;
  }
}

bool CodasipGenDAGToDAGISel::CheckImm(int64_t Imm, int width, bool sign, int trunc) const
{
  return CheckImmImpl(Imm,width,sign,trunc);
}

// move this to ins.inf.cpp?
bool llvm::CheckImmImpl(int64_t Imm, int width, bool sign, int trunc)
{
  const int MAX = 64;
  assert(width<MAX && "unsupported imm operand");
  if (width>MAX) return false;
  uint64_t imm = Imm;
  // check MSB
  uint64_t mask = -1;
  if (sign)
  {
    mask <<= (width-1);
    if ((imm&mask) != mask && (imm&mask)) {
      return false;
    }
  }
  else
  {
    mask >>= (MAX-width);
    if ((imm&mask) != imm) {
      return false;
    }
  }
  // check LSB
  if (trunc)
  {
    mask = -1;
    mask >>= (MAX-trunc);
    if (imm&mask) {
      return false;
    }
  }
  // all ok
  return true;
}

bool CodasipGenDAGToDAGISel::CheckLoadStore(const MemSDNode *n, int align, int space) const
{
  assert(n);
  const MachineFrameInfo &MFI = MF->getFrameInfo();
  const MachinePointerInfo &pi = n->getPointerInfo();
  int al = n->getAlignment();
  int as = 0;
  // note: see MachinePointerInfo::getAddrSpace()
  // (which is called from MemSDNode::getAddrSpace())
  // normal value
  if (pi.V.is<const Value*>())
  {
    as = pi.getAddrSpace();
  }
  // custom handling
  else
  {
    // note: MemSDNode::getAddrSpace() would simply return 0 in this case
    const PseudoSourceValue *psv = pi.V.get<const llvm::PseudoSourceValue*>();
    assert(psv && "is neither a Value nor a PseudoValue");
    const FixedStackPseudoSourceValue *fpsv = dyn_cast<const FixedStackPseudoSourceValue>(psv);
    // remove this completely?
    if (fpsv)
    {
      int FI = fpsv->getFrameIndex();
      as = MFI.getStackID(FI);
    }
    else
    {
      // get type
      EVT vt = n->getMemoryVT();
      as = GetSpace4Vt(vt);
    }
  }
  return align<=al && as==space;
}

bool CodasipGenDAGToDAGISel::CheckFI(SDNode *N, int rci) const
{
  // is rci a dummy class?
  bool isOnlyFI = false;
  switch (rci)
  {
    default: break;
    
      isOnlyFI = true;
  }
  // is FI?
  const bool isFI = FrameIndexSDNode::classof(N);
  // dummy class operand can be only FI
  if (isOnlyFI && !isFI) return false;
  // normal case: nothing to check if not FI 
  if (!isFI) return true;
  FrameIndexSDNode *fin = cast<FrameIndexSDNode>(N);
  int FI = fin->getIndex();
  // get space
  MachineFrameInfo& MFI = MF->getFrameInfo();
  int space = MFI.getStackID(FI);
  // get FP
  const TargetRegisterInfo *RI = TM.getRegisterInfo();
  const CodasipRegisterInfo *CRI = static_cast<const CodasipRegisterInfo*>(RI);
  unsigned FP = CRI->getFrameRegister(*MF,space);
  // is call param?
  CodasipFunctionInfo *info = MF->getInfo<CodasipFunctionInfo>();
  const bool callParam = info->IsOutFI(FI);
  if (callParam) {
    FP = CRI->GetSP(space);
  }
  // does the reg class contain FP?
  const TargetRegisterClass *RC = RI->getRegClass(rci);
  return RC->contains(FP);
}

void CodasipGenDAGToDAGISel::LowerMoiPatterns(SelectionDAG *DAG)
{
  bool was_change = false;
  std::vector<SDValue> roots;
  for (int i = 0; i <  MOI_GROUP_MAP_SIZE; ++i)
  {
    SelectionDAG *Pattern = GetCodasipPattern(TM, *MF, InstrGrpMap[i][0], roots);
    if (roots.empty())
    {
      continue;
    }
    DagPattern MoiPattern(Pattern, InstrGrpMap[i], TM, roots);
    do {
      was_change = false;
      was_change |= MoiPattern.BaseTryMatch(DAG);
    } while (was_change);
    roots.clear();
    delete Pattern;
  }
  LLVM_DEBUG(dbgs() << "\n======= after MOI lowering =======\n";
             DAG->dump();
             dbgs() << "==================================\n");
}

// user's reimplementation
#include "CodasipCustSelDAG.inc"

/// Creates this pass.
FunctionPass *llvm::createCodasipISelDag(CodasipTargetMachine &TM) {
  return new CodasipDAGToDAGISel(TM);
}
