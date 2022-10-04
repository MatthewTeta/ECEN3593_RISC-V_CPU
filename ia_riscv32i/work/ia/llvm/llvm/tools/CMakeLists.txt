add_llvm_tool_subdirectory(gold)
add_llvm_tool_subdirectory(llc)
add_llvm_tool_subdirectory(llvm-mc)
add_llvm_tool_subdirectory(llvm-objdump)

set(LLVM_COMMON_DEPENDS ${LLVM_COMMON_DEPENDS} PARENT_SCOPE)
