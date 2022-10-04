include_directories(${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_library(LLVMCodasipGenDesc
  CodasipAsmBackend.cpp
  CodasipBundleFunction.cpp
  CodasipBundleFunctionGen.cpp
  CodasipCustomFixupEncoder.cpp
  CodasipCustomFixupEncoderGen.cpp
  CodasipELFObjectWriter.cpp
  CodasipELFStreamer.cpp
  CodasipGenAsmBackend.cpp                                       
  CodasipMCAsmInfo.cpp
  CodasipMCCodeEmitter.cpp
  CodasipMCELFStreamer.cpp
  CodasipMCTargetDesc.cpp
  CodasipTargetStreamer.cpp
)

add_dependencies(LLVMCodasipGenDesc CodasipCommonTableGen)
