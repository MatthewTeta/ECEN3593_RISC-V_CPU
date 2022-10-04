add_llvm_library(LLVMCodasipGenAsmPrinter
  CodasipInstPrinter.cpp
  )

target_link_libraries(
    LLVMCodasipGenAsmPrinter
    PRIVATE
        LLVMAsmPrinter
)
