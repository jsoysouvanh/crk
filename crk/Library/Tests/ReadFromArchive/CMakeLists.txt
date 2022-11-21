cmake_minimum_required(VERSION 3.13.5)

project(crkReadFromArchiveTests)

#######################################
########## Read from archive ##########
#######################################

set(crkReadFromArchiveTestsTarget crkReadFromArchiveTests)
add_executable(${crkReadFromArchiveTestsTarget} "ReadFromArchive.cpp")

target_include_directories(${crkReadFromArchiveTestsTarget} PRIVATE "../Shared/Include")

# Link gtest
target_link_libraries(${crkReadFromArchiveTestsTarget} PUBLIC gtest)

# Link crk
target_link_libraries(${crkReadFromArchiveTestsTarget} PUBLIC crk)

if (MSVC)
	target_compile_options(${crkReadFromArchiveTestsTarget} PRIVATE /MP /bigobj)
endif()

add_test(NAME ${crkReadFromArchiveTestsTarget}
		 COMMAND ${crkReadFromArchiveTestsTarget} ${CRK_TESTS_OUTPUT_DIR})