#
# this config creates two targets, one is for the customer to compile, the model-simulator_cosimulator_type
# the other is already installed and exported and is only linked to model-simulator_cosimulator_type
#

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was CodasipCosimulatorConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(COSIM_TARGET_NAME ia_riscv32i-ia-cpp)
set(COSIM_TARGET_NAMESAPCE ia_riscv32i)
set(COSIM_TARGET_NAME_FULL "${COSIM_TARGET_NAMESAPCE}::${COSIM_TARGET_NAME}")
set(wrapper_sources ia_riscv32i_cpp.cpp)
set_and_check(targets_file_path ${CMAKE_CURRENT_LIST_DIR}/ia_riscv32iTargets.cmake)
include(${targets_file_path})

# Compute the installation prefix relative to this file.
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
if("${_IMPORT_PREFIX}" STREQUAL "/")
  set(_IMPORT_PREFIX "")
endif()
# filter foreign files for cpp and h files to compile in the wrapper target
foreach(source_file ${wrapper_sources})
    list(APPEND wrapper_sources_full "${_IMPORT_PREFIX}/src/${source_file}")
endforeach()
# cleanup
unset(_IMPORT_PREFIX)

# set exported sources variable
set("${COSIM_TARGET_NAME}_SOURCE_FILES" ${wrapper_sources_full})
# unset temp var
unset(targets_file_path)
unset(source_file)
unset(wrapper_sources)
unset(wrapper_sources_full)
