link_directories(${CMAKE_BINARY_DIR}/lib/ ${CUSTOM_LIB_PATH}/ ${CODASIP_INSTALL}/lib/)

add_llvm_tool(codasip-llvm-mc dummy.cpp)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(codasip-llvm-mc PRIVATE mcarch LLVMCodasipGenAsmParser LLVMCodasipGenDesc LLVMCodasipGenAsmPrinter LLVMCodasipGenCodeGen LLVMCodasipGenDisassembler LLVMCodasipGenInfo LLVMExtractorDesc LLVMExtractorInfo
    LLVMSelectionDAG LLVMCodeGen LLVMCodasipMisc LLVMScalarOpts LLVMProfileData LLVMTransformUtils LLVMAnalysis LLVMMCParser LLVMMC LLVMCore LLVMRemarks LLVMTarget LLVMSupport LLVMDemangle LLVMDebugInfoDWARF
    LLVMBitstreamReader)

if (UNIX)
    target_link_libraries(codasip-llvm-mc PRIVATE tinfo ncurses dl pthread m z)
else()
    # shell32 too?
    target_link_libraries(codasip-llvm-mc PRIVATE psapi imagehlp)
endif()

target_link_libraries(codasip-llvm-mc PRIVATE CodasipTools::protectorl CodasipTools::utility)

set_target_properties(codasip-llvm-mc PROPERTIES OUTPUT_NAME llvm-mc)
