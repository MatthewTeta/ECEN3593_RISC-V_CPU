add_llvm_library(LLVMCodasipGenDisassembler
  CodasipDebundleFunctionGen.cpp
  CodasipDisassembler.cpp
)

target_link_libraries(
    LLVMCodasipGenDisassembler
    PRIVATE
    LLVMBinaryFormat
    LLVMMCDisassembler
    CodasipTools::utility
)
