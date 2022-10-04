# Codasip s.r.o.
#
# CONFIDENTIAL
#
# Copyright 2020 Codasip s.r.o.
#
# All Rights Reserved.
# This file is part of the Codasip Studio product. No part of the Studio product, including this
# file, may be use, copied, modified, or distributed except in accordance with the terms contained
# in Codasip license agreement under which you obtained this file.

cmake_minimum_required(VERSION 3.9)

project(
    codasip_ttigen
    LANGUAGES CXX
)

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${TOOLS_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake/CodasipTools")

include(CodasipBuildHelpers)

find_package(LLVM REQUIRED CONFIG HINTS "${TOOLS_DIR}" NO_DEFAULT_PATH)

codasip_add_library(
    codasip_tti
    DO_INSTALL ON
    TYPE MODULE
    SOURCES
        CodasipTTI.cpp
        llvm_CodasipTTIImpl.cpp
        llvm_CodasipGenTTIImpl.cpp
)

set_target_properties(
    codasip_tti
    PROPERTIES
        OUTPUT_NAME "${OUTPUT_PREFIX}tti"
)

target_link_libraries(
    codasip_tti
    PRIVATE
        "$<$<PLATFORM_ID:Windows>:LLVMCodeGen>"
)

target_include_directories(
    codasip_tti
    PRIVATE
        "${LLVM_INCLUDE_DIRS}"
)

