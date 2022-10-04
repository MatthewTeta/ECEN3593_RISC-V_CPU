# This file provides information and services to the final user.


# LLVM_BUILD_* values available only from LLVM build tree.
set(LLVM_BUILD_BINARY_DIR "/home/project/ia_riscv32i/work/ia/llvm/build")
set(LLVM_BUILD_LIBRARY_DIR "/home/project/ia_riscv32i/work/ia/llvm/build/./lib")
set(LLVM_BUILD_MAIN_INCLUDE_DIR "/home/project/ia_riscv32i/work/ia/llvm/llvm/include")
set(LLVM_BUILD_MAIN_SRC_DIR "/home/project/ia_riscv32i/work/ia/llvm/llvm")


set(LLVM_VERSION_MAJOR 9)
set(LLVM_VERSION_MINOR 0)
set(LLVM_VERSION_PATCH 0)
set(LLVM_VERSION_SUFFIX )
set(LLVM_PACKAGE_VERSION 1.2.0)

set(LLVM_BUILD_TYPE Release)

set(LLVM_COMMON_DEPENDS )

set(LLVM_AVAILABLE_LIBS LLVMCodasipGenCodeGen;LLVMCodasipGenAsmParser;LLVMCodasipGenDisassembler;LLVMCodasipGenAsmPrinter;LLVMCodasipGenInfo;LLVMCodasipGenDesc;LLVMCodasipCustomModules;LLVMGengold)



set(LLVM_DYLIB_COMPONENTS all)

set(LLVM_ALL_TARGETS AArch64;AMDGPU;ARM;BPF;Hexagon;Lanai;Mips;MSP430;NVPTX;PowerPC;RISCV;Sparc;SystemZ;WebAssembly;X86;XCore;Codasip;Extractor)

set(LLVM_TARGETS_TO_BUILD Codasip)

set(LLVM_TARGETS_WITH_JIT X86;PowerPC;AArch64;ARM;Mips;SystemZ)


set_property(GLOBAL PROPERTY LLVMBUILD_LIB_DEPS_LLVMCodasipGenCodeGen LLVMCodasipCustomModules;LLVMCodasipGenAsmPrinter;LLVMCodasipGenDesc;LLVMCodasipGenInfo;LLVMTarget)
set_property(GLOBAL PROPERTY LLVMBUILD_LIB_DEPS_LLVMCodasipGenAsmParser )
set_property(GLOBAL PROPERTY LLVMBUILD_LIB_DEPS_LLVMCodasipGenDisassembler )
set_property(GLOBAL PROPERTY LLVMBUILD_LIB_DEPS_LLVMCodasipGenAsmPrinter LLVMTarget)
set_property(GLOBAL PROPERTY LLVMBUILD_LIB_DEPS_LLVMCodasipGenInfo )
set_property(GLOBAL PROPERTY LLVMBUILD_LIB_DEPS_LLVMCodasipGenDesc LLVMCodasipGenAsmPrinter;LLVMCodasipGenInfo)
set_property(GLOBAL PROPERTY LLVMBUILD_LIB_DEPS_LLVMCodasipCustomModules LLVMTarget)
set_property(GLOBAL PROPERTY LLVMBUILD_LIB_DEPS_LLVMGengold )

set(TARGET_TRIPLE "x86_64-unknown-linux-gnu")

set(LLVM_ABI_BREAKING_CHECKS WITH_ASSERTS)

set(LLVM_ENABLE_ASSERTIONS ON)

set(LLVM_ENABLE_EH ON)

set(LLVM_ENABLE_RTTI ON)

set(LLVM_ENABLE_TERMINFO ON)

set(LLVM_ENABLE_THREADS ON)

set(LLVM_ENABLE_ZLIB ON)

set(LLVM_LIBXML2_ENABLED 0)

set(LLVM_WITH_Z3 )

set(LLVM_ENABLE_DIA_SDK 0)

set(LLVM_NATIVE_ARCH X86)

set(LLVM_ENABLE_PIC ON)

set(LLVM_BUILD_32_BITS OFF)

if (NOT "-lpthread" STREQUAL "")
  set(LLVM_PTHREAD_LIB "-lpthread")
endif()

set(LLVM_ENABLE_PLUGINS ON)
set(LLVM_EXPORT_SYMBOLS_FOR_PLUGINS OFF)
set(LLVM_PLUGIN_EXT .so)

set(LLVM_ON_UNIX 1)

set(LLVM_LIBDIR_SUFFIX )

set(LLVM_INCLUDE_DIRS "/home/project/ia_riscv32i/work/ia/llvm/llvm/include;/home/project/ia_riscv32i/work/ia/llvm/build/include")
set(LLVM_LIBRARY_DIRS "/home/project/ia_riscv32i/work/ia/llvm/build/./lib")

# These variables are duplicated for install tree but they have different
# values for build tree.  LLVM_INCLUDE_DIRS contains both source
# and generated include directories while the following variables have
# them split.
set(LLVM_INCLUDE_DIR "/home/project/ia_riscv32i/work/ia/llvm/build/include")
set(LLVM_MAIN_INCLUDE_DIR "/home/project/ia_riscv32i/work/ia/llvm/llvm/include")
set(LLVM_LIBRARY_DIR "/home/project/ia_riscv32i/work/ia/llvm/build/./lib")

set(LLVM_DEFINITIONS "-D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS")
set(LLVM_CMAKE_DIR "/home/project/ia_riscv32i/work/ia/llvm/llvm/cmake/modules")
set(LLVM_BINARY_DIR "/home/project/ia_riscv32i/work/ia/llvm/build")
set(LLVM_TOOLS_BINARY_DIR "/home/project/ia_riscv32i/work/ia/llvm/build/./bin")
set(LLVM_TOOLS_INSTALL_DIR "bin")
set(LLVM_HAVE_OPT_VIEWER_MODULES 0)
set(LLVM_CONFIGURATION_TYPES )

if(NOT TARGET LLVMSupport)
  set(LLVM_EXPORTED_TARGETS "LLVMCodasipGenCodeGen;LLVMCodasipGenAsmParser;LLVMCodasipGenDisassembler;LLVMCodasipGenAsmPrinter;LLVMCodasipGenInfo;LLVMCodasipGenDesc;LLVMCodasipCustomModules;LLVMGengold;codasip-llc;codasip-llvm-mc;codasip-llvm-objdump;")
  include("/home/project/ia_riscv32i/work/ia/llvm/build/lib/cmake/llvm/LLVMExports.cmake")
  include("/home/project/ia_riscv32i/work/ia/llvm/build/lib/cmake/llvm/LLVMBuildTreeOnlyTargets.cmake")
endif()

# By creating intrinsics_gen here, subprojects that depend on LLVM's
# tablegen-generated headers can always depend on this target whether building
# in-tree with LLVM or not.
if(NOT TARGET intrinsics_gen)
  add_custom_target(intrinsics_gen)
endif()

set_property(GLOBAL PROPERTY LLVM_TARGETS_CONFIGURED On)
include(${LLVM_CMAKE_DIR}/LLVM-Config.cmake)
