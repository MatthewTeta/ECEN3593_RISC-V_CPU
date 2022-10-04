#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ia_riscv32i::ia_riscv32i-ia-cpp" for configuration "Release"
set_property(TARGET ia_riscv32i::ia_riscv32i-ia-cpp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ia_riscv32i::ia_riscv32i-ia-cpp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libia_riscv32i-ia-cpp.so"
  IMPORTED_SONAME_RELEASE "libia_riscv32i-ia-cpp.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS ia_riscv32i::ia_riscv32i-ia-cpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_ia_riscv32i::ia_riscv32i-ia-cpp "${_IMPORT_PREFIX}/bin/libia_riscv32i-ia-cpp.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
