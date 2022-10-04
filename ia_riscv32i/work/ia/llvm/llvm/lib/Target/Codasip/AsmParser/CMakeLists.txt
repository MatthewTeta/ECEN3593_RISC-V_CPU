add_llvm_library(LLVMCodasipGenAsmParser
  CodasipAsmParser.cpp
  CodasipAsmParserHooks.cpp
  CodasipAsmParserHooksGen.cpp
  merged_parser_gen.cpp
  merged_scanner_gen.cpp
  )

# turn off the variable tracking on all the optimizations
# this should speed up the process, but also reduce memory footprint
target_compile_options(LLVMCodasipGenAsmParser
    PRIVATE
    "$<$<CXX_COMPILER_ID:GNU>:-fno-var-tracking;-O0>"
    "$<$<CXX_COMPILER_ID:MSVC>:/Od;/Ob0>"
)

# Suppress unsolveable warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
set_source_files_properties(merged_parser_gen.cpp PROPERTIES COMPILE_FLAGS "-Wno-implicit-fallthrough -Wno-covered-switch-default")
set_source_files_properties(merged_scanner_gen.cpp PROPERTIES COMPILE_FLAGS "-Wno-pedantic -Wno-unused-label")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
set_source_files_properties(merged_scanner_gen.cpp PROPERTIES COMPILE_FLAGS "/wd4102")
endif ()

if (WIN32)
target_link_libraries(
    LLVMCodasipGenAsmParser
    PRIVATE
        CodasipTools::asmbasel
        CodasipTools::filesysteml
        CodasipTools::threadsl
        CodasipTools::utility
        reflex::reflex
)
else ()
target_link_libraries(
    LLVMCodasipGenAsmParser
    PRIVATE
        CodasipTools::asmbasel
        CodasipTools::filesysteml
        CodasipTools::threadsl
        CodasipTools::utility
        reflex::reflex
        rt
)
endif ()
