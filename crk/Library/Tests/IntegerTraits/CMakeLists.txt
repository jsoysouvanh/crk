cmake_minimum_required(VERSION 3.13.5)

project(crkIntegerTraitsTests)

######################################
########### Integer traits ###########
######################################

set(crkIntegerTraitsTestsTarget crkIntegerTraitsTests)
add_executable(${crkIntegerTraitsTestsTarget} "IntegerTraitsTests.cpp")

target_include_directories(${crkIntegerTraitsTestsTarget} PRIVATE "../Shared/Include")

# Link crk
target_link_libraries(${crkIntegerTraitsTestsTarget} PUBLIC crk)

add_test(NAME ${crkIntegerTraitsTestsTarget}
		 COMMAND ${crkIntegerTraitsTestsTarget})