cmake_minimum_required(VERSION 3.17.0) # 3.17 introduces Ninja Multi-Config generator

project(crk)

# Information messages about cmake version and compiler
message("Cmake:		${CMAKE_VERSION}")
message("Compiler:	${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Enable tests
include(CTest)

# Include crk CMake helper functions
include(CMake/crkHelpers.cmake)

add_subdirectory(crk)