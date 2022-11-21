project(crkGenerator)

# Build dependencies
add_subdirectory(ThirdParty/Kodgen)

set(crkGeneratorExeTarget crkGenerator)
add_executable(${crkGeneratorExeTarget} Source/main.cpp)

target_include_directories(${crkGeneratorExeTarget} PRIVATE Include)

target_link_libraries(${crkGeneratorExeTarget} PRIVATE Kodgen)

if (CRK_DEV)

	# Setup compilation definitions
	target_compile_definitions(${crkGeneratorExeTarget} PUBLIC CRK_DEV=1)

	if (NOT MSVC) # Clang or GCC
		target_compile_options(${crkGeneratorExeTarget} PUBLIC -fsanitize=address -fno-omit-frame-pointer)
		target_link_options(${crkGeneratorExeTarget} PUBLIC -fsanitize=address -fno-omit-frame-pointer)
	endif()

endif()

if (MSVC)

	# Setup warning level
	string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Remove the default flag /W3
	target_compile_options(${crkGeneratorExeTarget} PRIVATE /W4 /MP)

else ()	# Clang or GCC

	target_compile_options(${crkGeneratorExeTarget} PRIVATE -Wall -Wextra -Wpedantic)
	
endif()


# Copy the RefurekuSettings template file next to the generated binary
add_custom_command(	TARGET ${crkGeneratorExeTarget} PRE_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					${PROJECT_SOURCE_DIR}/crkSettings.toml
					$<IF:$<BOOL:${MSVC}>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/crkSettings.toml,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/crkSettings.toml>)