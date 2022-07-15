project(crkLibrary)

# Add Refureku library
set(crkLibraryTarget crk)
add_library(${crkLibraryTarget}
				STATIC
					"Source/Serialize.cpp"
				)

# Setup language requirements
if (NOT CRK_MIN_CXX_STD_VERSION)
	set(CRK_MIN_CXX_STD_VERSION cxx_std_20)	# Default to c++20
elseif(CRK_MIN_CXX_STD_VERSION EQUAL 20)
	set(CRK_MIN_CXX_STD_VERSION cxx_std_20)
endif()

target_compile_features(${crkLibraryTarget} PUBLIC ${CRK_MIN_CXX_STD_VERSION})

target_include_directories(${crkLibraryTarget}
							PUBLIC	Include/Public
							PRIVATE Include/Internal)

# Setup compilation flags
if (MSVC)

	target_compile_options(${crkLibraryTarget}
							PRIVATE
								/MP					# Multithread compilation
							PUBLIC
								/Zc:__cplusplus		# Enable MSVC to report an updated value for recent C++ language standards support.
							)

	string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Replace the default flag /W3 by /W4

else()	# Clang or GCC

	target_compile_options(${crkLibraryTarget} PRIVATE -Wall -Wextra -Wpedantic)
	
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CRK_GEN_CODECOV_REPORT)
		target_compile_options(${crkLibraryTarget} PUBLIC --coverage)
		target_link_options(${crkLibraryTarget} PUBLIC --coverage)
	endif()
	
endif()

# Dev specific flags
if (CRK_DEV)

	target_compile_definitions(${crkLibraryTarget} PUBLIC CRK_DEV=1)

	if (NOT MSVC) # Clang or GCC
		target_compile_options(${crkLibraryTarget} PUBLIC -fsanitize=address -fno-omit-frame-pointer)
		target_link_options(${crkLibraryTarget} PUBLIC -fsanitize=address -fno-omit-frame-pointer)
	endif()

endif()

if (BUILD_TESTING)
	add_subdirectory(Tests)
endif()