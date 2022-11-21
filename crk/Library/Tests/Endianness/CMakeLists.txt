cmake_minimum_required(VERSION 3.13.5)

project(crkEndiannessTests)

##################################
########### Endianness ###########
##################################

set(crkEndiannessTestsTarget crkEndiannessTests)
add_executable(${crkEndiannessTestsTarget} "EndiannessTests.cpp")

target_include_directories(${crkEndiannessTestsTarget} PRIVATE "../Shared/Include")

# Link GTest
target_link_libraries(${crkEndiannessTestsTarget} PUBLIC gtest)
# Link crk
target_link_libraries(${crkEndiannessTestsTarget} PUBLIC crk)

if (MSVC)
	target_compile_options(${crkEndiannessTestsTarget} PRIVATE /MP /bigobj)
endif()

add_test(NAME ${crkEndiannessTestsTarget}
		 COMMAND ${crkEndiannessTestsTarget})