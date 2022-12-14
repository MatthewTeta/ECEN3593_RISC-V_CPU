//===-Config.h - LLVM Link Time Optimizer Configuration -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the lto::Config data structure, which allows clients to
// configure LTO.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LTO_CONFIG_H
#define LLVM_LTO_CONFIG_H

#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#include <functional>

namespace llvm {

class Error;
class Module;
class ModuleSummaryIndex;
class raw_pwrite_stream;

namespace lto {

/// LTO configuration. A linker can configure LTO by setting fields in this data
/// structure and passing it to the lto::LTO constructor.
struct Config {
  // Note: when adding fields here, consider whether they need to be added to
  // computeCacheKey in LTO.cpp.
  std::string CPU;
  TargetOptions Options;
  std::vector<std::string> MAttrs;
  Optional<Reloc::Model> RelocModel = Reloc::PIC_;
  Optional<CodeModel::Model> CodeModel = None;
  CodeGenOpt::Level CGOptLevel = CodeGenOpt::Default;
  TargetMachine::CodeGenFileType CGFileType = TargetMachine::CGFT_ObjectFile;
  unsigned OptLevel = 2;
  bool DisableVerify = false;

  /// Use the new pass manager
  bool UseNewPM = false;

  /// Flag to indicate that the optimizer should not assume builtins are present
  /// on the target.
  bool Freestanding = false;

  /// Disable entirely the optimizer, including importing for ThinLTO
  bool CodeGenOnly = false;

  /// Run PGO context sensitive IR instrumentation.
  bool RunCSIRInstr = false;

  /// If this field is set, the set of passes run in the middle-end optimizer
  /// will be the one specified by the string. Only works with the new pass
  /// manager as the old one doesn't have this ability.
  std::string OptPipeline;

  // If this field is set, it has the same effect of specifying an AA pipeline
  // identified by the string. Only works with the new pass manager, in
  // conjunction OptPipeline.
  std::string AAPipeline;

  /// Setting this field will replace target triples in input files with this
  /// triple.
  std::string OverrideTriple;

  /// Setting this field will replace unspecified target triples in input files
  /// with this triple.
  std::string DefaultTriple;

  /// Context Sensitive PGO profile path.
  std::string CSIRProfile;

  /// Sample PGO profile path.
  std::string SampleProfile;

  /// Name remapping file for profile data.
  std::string ProfileRemapping;

  /// The directory to store .dwo files.
  std::string DwoDir;

  /// The name for the split debug info file used for the DW_AT_[GNU_]dwo_name
  /// attribute in the skeleton CU. This should generally only be used when
  /// running an individual backend directly via thinBackend(), as otherwise
  /// all objects would use the same .dwo file. Not used as output path.
  std::string SplitDwarfFile;

  /// The path to write a .dwo file to. This should generally only be used when
  /// running an individual backend directly via thinBackend(), as otherwise
  /// all .dwo files will be written to the same path. Not used in skeleton CU.
  std::string SplitDwarfOutput;

  /// Optimization remarks file path.
  std::string RemarksFilename = "";

  /// Optimization remarks pass filter.
  std::string RemarksPasses = "";

  /// Whether to emit optimization remarks with hotness informations.
  bool RemarksWithHotness = false;

  /// The format used for serializing remarks (default: YAML).
  std::string RemarksFormat = "";

  /// Whether to emit the pass manager debuggging informations.
  bool DebugPassManager = false;

  /// Statistics output file path.
  std::string StatsFile;

  bool ShouldDiscardValueNames = true;
  DiagnosticHandlerFunction DiagHandler;

  /// If this field is set, LTO will write input file paths and symbol
  /// resolutions here in llvm-lto2 command line flag format. This can be
  /// used for testing and for running the LTO pipeline outside of the linker
  /// with llvm-lto2.
  std::unique_ptr<raw_ostream> ResolutionFile;

  /// The following callbacks deal with tasks, which normally represent the
  /// entire optimization and code generation pipeline for what will become a
  /// single native object file. Each task has a unique identifier between 0 and
  /// getMaxTasks()-1, which is supplied to the callback via the Task parameter.
  /// A task represents the entire pipeline for ThinLTO and regular
  /// (non-parallel) LTO, but a parallel code generation task will be split into
  /// N tasks before code generation, where N is the parallelism level.
  ///
  /// LTO may decide to stop processing a task at any time, for example if the
  /// module is empty or if a module hook (see below) returns false. For this
  /// reason, the client should not expect to receive exactly getMaxTasks()
  /// native object files.

  /// A module hook may be used by a linker to perform actions during the LTO
  /// pipeline. For example, a linker may use this function to implement
  /// -save-temps. If this function returns false, any further processing for
  /// that task is aborted.
  ///
  /// Module hooks must be thread safe with respect to the linker's internal
  /// data structures. A module hook will never be called concurrently from
  /// multiple threads with the same task ID, or the same module.
  ///
  /// Note that in out-of-process backend scenarios, none of the hooks will be
  /// called for ThinLTO tasks.
  using ModuleHookFn = std::function<bool(unsigned Task, const Module &)>;

  /// This module hook is called after linking (regular LTO) or loading
  /// (ThinLTO) the module, before modifying it.
  ModuleHookFn PreOptModuleHook;

  /// This hook is called after promoting any internal functions
  /// (ThinLTO-specific).
  ModuleHookFn PostPromoteModuleHook;

  /// This hook is called after internalizing the module.
  ModuleHookFn PostInternalizeModuleHook;

  /// This hook is called after importing from other modules (ThinLTO-specific).
  ModuleHookFn PostImportModuleHook;

  /// This module hook is called after optimization is complete.
  ModuleHookFn PostOptModuleHook;

  /// This module hook is called before code generation. It is similar to the
  /// PostOptModuleHook, but for parallel code generation it is called after
  /// splitting the module.
  ModuleHookFn PreCodeGenModuleHook;

  /// A combined index hook is called after all per-module indexes have been
  /// combined (ThinLTO-specific). It can be used to implement -save-temps for
  /// the combined index.
  ///
  /// If this function returns false, any further processing for ThinLTO tasks
  /// is aborted.
  ///
  /// It is called regardless of whether the backend is in-process, although it
  /// is not called from individual backend processes.
  using CombinedIndexHookFn =
      std::function<bool(const ModuleSummaryIndex &Index)>;
  CombinedIndexHookFn CombinedIndexHook;

  /// This is a convenience function that configures this Config object to write
  /// temporary files named after the given OutputFileName for each of the LTO
  /// phases to disk. A client can use this function to implement -save-temps.
  ///
  /// FIXME: Temporary files derived from ThinLTO backends are currently named
  /// after the input file name, rather than the output file name, when
  /// UseInputModulePath is set to true.
  ///
  /// Specifically, it (1) sets each of the above module hooks and the combined
  /// index hook to a function that calls the hook function (if any) that was
  /// present in the appropriate field when the addSaveTemps function was
  /// called, and writes the module to a bitcode file with a name prefixed by
  /// the given output file name, and (2) creates a resolution file whose name
  /// is prefixed by the given output file name and sets ResolutionFile to its
  /// file handle.
  Error addSaveTemps(std::string OutputFileName,
                     bool UseInputModulePath = false);
  //=================== CODASIP =====================
  Error CodasipSaveOptBc(std::string OutputFileName);
  //=================================================
};

struct LTOLLVMDiagnosticHandler : public DiagnosticHandler {
  DiagnosticHandlerFunction *Fn;
  LTOLLVMDiagnosticHandler(DiagnosticHandlerFunction *DiagHandlerFn)
      : Fn(DiagHandlerFn) {}
  bool handleDiagnostics(const DiagnosticInfo &DI) override {
    (*Fn)(DI);
    return true;
  }
};
/// A derived class of LLVMContext that initializes itself according to a given
/// Config object. The purpose of this class is to tie ownership of the
/// diagnostic handler to the context, as opposed to the Config object (which
/// may be ephemeral).
// FIXME: This should not be required as diagnostic handler is not callback.
struct LTOLLVMContext : LLVMContext {

  LTOLLVMContext(const Config &C) : DiagHandler(C.DiagHandler) {
    setDiscardValueNames(C.ShouldDiscardValueNames);
    enableDebugTypeODRUniquing();
    setDiagnosticHandler(
        llvm::make_unique<LTOLLVMDiagnosticHandler>(&DiagHandler), true);
  }
  DiagnosticHandlerFunction DiagHandler;
};

}
}

#endif
