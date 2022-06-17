cmake_minimum_required(VERSION 3.13.5)

project(RefurekuTests)

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
#		Configure the tests
###########################################

set(crkWriteToArchiveTestsTarget crkWriteToArchiveTests)
add_executable(${crkWriteToArchiveTestsTarget} "WriteToArchive.cpp")

set(crkReadFromArchiveTestsTarget crkReadFromArchiveTests)
add_executable(${crkReadFromArchiveTestsTarget} "ReadFromArchive.cpp")

# Link libraries
target_link_libraries(${crkWriteToArchiveTestsTarget} PUBLIC gtest)
target_link_libraries(${crkReadFromArchiveTestsTarget} PUBLIC gtest)

# Add include directories
target_include_directories(${crkWriteToArchiveTestsTarget} PRIVATE Include)
target_include_directories(${crkReadFromArchiveTestsTarget} PRIVATE Include)

#refureku_setup_target(
#	TARGET ${RefurekuTestsTarget}
#	RFK_SETTINGS_FILENAME "RefurekuTestsSettings.toml"
#)

target_link_libraries(${crkWriteToArchiveTestsTarget} PUBLIC crk)
target_link_libraries(${crkReadFromArchiveTestsTarget} PUBLIC crk)

if (MSVC)
	target_compile_options(${crkWriteToArchiveTestsTarget} PRIVATE /MP /bigobj)
	target_compile_options(${crkReadFromArchiveTestsTarget} PRIVATE /MP /bigobj)
endif()

#Setup parameters for tests
if (NOT CRK_TESTS_OUTPUT_DIR)
	set(CRK_TESTS_OUTPUT_DIR TestsOutput)
endif()

if (NOT CRK_TESTS_OUTPUT_FILENAME)
	set(CRK_TESTS_OUTPUT_FILENAME TestsOutput_${CMAKE_CXX_COMPILER_ID}${CMAKE_CXX_COMPILER_VERSION})
endif()

add_test(NAME ${crkWriteToArchiveTestsTarget}
		 COMMAND ${crkWriteToArchiveTestsTarget} ${CRK_TESTS_OUTPUT_FILENAME})

add_test(NAME ${crkReadFromArchiveTestsTarget}
		 COMMAND ${crkReadFromArchiveTestsTarget} ${CRK_TESTS_OUTPUT_DIR})