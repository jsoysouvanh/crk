cmake_minimum_required(VERSION 3.13.5)

project(RefurekuTests)

###########################################
#		Configure the tests
###########################################

set(crkTestsTarget crkTests)
add_executable(${crkTestsTarget}
					"main.cpp")

# Fetch GTest
include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Link libraries
target_link_libraries(${crkTestsTarget} PUBLIC gtest)

# Add include directories
target_include_directories(${crkTestsTarget} PRIVATE Include)

#refureku_setup_target(
#	TARGET ${RefurekuTestsTarget}
#	RFK_SETTINGS_FILENAME "RefurekuTestsSettings.toml"
#)

target_link_libraries(${crkTestsTarget} PUBLIC crk)

if (MSVC)
	target_compile_options(${crkTestsTarget} PRIVATE /MP /bigobj)
endif()

add_test(NAME ${crkTestsTarget} COMMAND ${crkTestsTarget})