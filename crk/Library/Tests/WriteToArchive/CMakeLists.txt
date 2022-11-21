cmake_minimum_required(VERSION 3.13.5)

project(crkWriteToArchiveTests)

########################################
########### Write to archive ###########
########################################

set(crkWriteToArchiveTestsTarget crkWriteToArchiveTests)
add_executable(${crkWriteToArchiveTestsTarget} "WriteToArchive.cpp")

target_include_directories(${crkWriteToArchiveTestsTarget} PRIVATE "../Shared/Include")

# Link gtest
target_link_libraries(${crkWriteToArchiveTestsTarget} PUBLIC gtest)

# Link crk
target_link_libraries(${crkWriteToArchiveTestsTarget} PUBLIC crk)

if (MSVC)
	target_compile_options(${crkWriteToArchiveTestsTarget} PRIVATE /MP /bigobj)
endif()

add_test(NAME ${crkWriteToArchiveTestsTarget}
		 COMMAND ${crkWriteToArchiveTestsTarget} ${CRK_TESTS_OUTPUT_DIR}/${CRK_TESTS_OUTPUT_FILENAME})