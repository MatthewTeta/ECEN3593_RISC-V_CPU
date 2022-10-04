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


// Main td file of Codasip backend.

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Classes used for relation maps.
//===----------------------------------------------------------------------===//
// PredRel - Filter class used to relate non-predicated instructions with their
// predicated forms.
class PredRel;

//===----------------------------------------------------------------------===//
// Generate mapping table to relate non-predicate instructions with their
// predicated formats - true and false.
//
def getPredOpcode : InstrMapping {
  // Choose a FilterClass that is used as a base class for all the
  // instructions modeling this relationship. This is done to reduce the
  // search space only to these set of instructions.
  let FilterClass = "PredRel";
  // Instructions with same values for all the fields in RowFields form a
  // row in the resulting relation table.
  // For example, if we want to relate 'ADD' (non-predicated) with 'Add_pt'
  // (predicated true) and 'Add_pf' (predicated false), then all 3
  // instructions need to have same value for BaseOpcode field. It can be any
  // unique value (Ex: XYZ) and should not be shared with any other
  // instruction not related to 'add'.
  let RowFields = ["BaseOpcode"];
  // List of attributes that can be used to define key and column instructions
  // for a relation. Key instruction is passed as an argument
  // to the function used for querying relation tables. Column instructions
  // are the instructions they (key) can transform into.
  //
  // Here, we choose 'PredSense' as ColFields since this is the unique
  // attribute of the key (non-predicated) and column (true/false)
  // instructions involved in this relationship model.
  let ColFields = ["PredSense"];
  // The key column contains non-predicated instructions.
  let KeyCol = ["none"];
  // Two value columns - first column contains instructions with
  // PredSense=true while second column has instructions with PredSense=false.
  let ValueCols = [["true"], ["false"]];
}

//===----------------------------------------------------------------------===//
// Generate mapping table to relate predicate-true instructions with their
// predicate-false forms
//
def getFalsePredOpcode : InstrMapping {
  let FilterClass = "PredRel";
  let RowFields = ["BaseOpcode"];
  let ColFields = ["PredSense"];
  let KeyCol = ["true"];
  let ValueCols = [["false"]];
}

//===----------------------------------------------------------------------===//
// Generate mapping table to relate predicate-false instructions with their
// predicate-true forms
//
def getTruePredOpcode : InstrMapping {
  let FilterClass = "PredRel";
  let RowFields = ["BaseOpcode"];
  let ColFields = ["PredSense"];
  let KeyCol = ["false"];
  let ValueCols = [["true"]];
}

//===----------------------------------------------------------------------===//
// Content files
//===----------------------------------------------------------------------===//
include "CodasipRegisterInfo.td"
include "CodasipSchedule.td"
include "CodasipInstrInfo.td"
include "CodasipCallingConv.td"

def CodasipInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// Subtarget features
//===----------------------------------------------------------------------===//

// use with -mattr=



// note: these two are used directly (not through subtarget)

def FeatureStdExtC
    : SubtargetFeature<"c", "HasStdExtC", "true",
                       "'C' (Compressed Instructions)">;

def FeatureRelax
    : SubtargetFeature<"relax", "EnableLinkerRelax", "true",
                       "Enable Linker relaxation.">;

//===----------------------------------------------------------------------===//
// Top-level definitions
//===----------------------------------------------------------------------===//

// the one and only cpu of Codasip target - it will be used always

def CodasipProc:  Processor 
<"codasip", CodasipItineraries, [  ]>;

// note: the list of default features declared above is generated merely for formal reasons
// -> don't bother editing it, it's hardcoded in CodasipSubtarget constructor

def CodasipAsmParser : AsmParser {
  let ShouldEmitMatchRegisterAltName = 1;

  let HasMnemonicFirst = 0;
}

def CodasipAsmParserVariant : AsmParserVariant {
  let Variant = 0;
  let Name = "CodasipAsmParserVariant";
  let TokenizingCharacters = "";
}

def Codasip: Target {
  let InstructionSet = CodasipInstrInfo;
  let AssemblyParsers = [CodasipAsmParser];
  let AssemblyParserVariants = [CodasipAsmParserVariant];
}

