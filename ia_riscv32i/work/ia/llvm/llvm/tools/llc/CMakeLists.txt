link_directories(${CMAKE_BINARY_DIR}/lib/ ${CUSTOM_LIB_PATH}/ ${CODASIP_INSTALL}/lib/)

message(STATUS "TOOLS DIR : ${TOOLS_DIR}")

set(standardConfigFolderPath ${TOOLS_DIR})
# Function add_llvm_tool is used with renamed target to handle conflicts with bootstrap LLVM exports
add_llvm_tool(codasip-llc dummy.cpp)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(codasip-llc PRIVATE llcarch LLVMCodasipGenAsmParser LLVMCodasipGenDesc LLVMCodasipGenAsmPrinter LLVMCodasipGenCodeGen LLVMCodasipGenInfo LLVMExtractorCodeGen LLVMExtractorDesc LLVMExtractorInfo
    LLVMIRReader LLVMAsmPrinter LLVMAsmParser LLVMBitReader LLVMBitWriter LLVMSelectionDAG LLVMipo LLVMAnalysis LLVMMCParser LLVMCodeGen LLVMInstrumentation LLVMMIRParser LLVMScalarOpts LLVMInstCombine LLVMTransformUtils LLVMAnalysis LLVMTarget LLVMCore LLVMMC LLVMDebugInfoCodeView LLVMCodasipMisc
    LLVMDebugInfoMSF LLVMDemangle LLVMVectorize LLVMObject LLVMProfileData LLVMCodasipJumpThreading LLVMRemarks LLVMTarget LLVMDebugInfoDWARF LLVMBitstreamReader LLVMBinaryFormat LLVMSupport)

add_dependencies(codasip-llc LLVMCodasipGenCodeGen)

if (UNIX)
    target_link_libraries(codasip-llc PRIVATE tinfo ncurses dl pthread m z)
else()
    # shell32 too?
    target_link_libraries(codasip-llc PRIVATE psapi imagehlp)
endif()

target_link_libraries(codasip-llc PRIVATE CodasipTools::protectorl CodasipTools::utility)

set_target_properties(codasip-llc PROPERTIES OUTPUT_NAME llc)
