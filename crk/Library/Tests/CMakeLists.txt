cmake_minimum_required(VERSION 3.13.5)

project(crkTests)

###########################################
#		        Fetch GTest
###########################################

include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

###########################################
####          Configure tests          ####
###########################################

#Setup parameters for tests
if (NOT CRK_TESTS_OUTPUT_DIR)
	set(CRK_TESTS_OUTPUT_DIR TestsOutput)
endif()

if (NOT CRK_TESTS_OUTPUT_FILENAME)
	set(CRK_TESTS_OUTPUT_FILENAME TestsOutput_${CMAKE_CXX_COMPILER_ID}${CMAKE_CXX_COMPILER_VERSION})
endif()

#######################
###### Add tests ######
#######################

add_subdirectory(Endianness)
add_subdirectory(IntegerTraits)
add_subdirectory(WriteToArchive)
add_subdirectory(ReadFromArchive)

##########################

#crk_setup_target(
#	TARGET ${RefurekuTestsTarget}
#	RFK_SETTINGS_FILENAME "RefurekuTestsSettings.toml"
#)