/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

//Version
#define CRK_VERSION_MAJOR 0
#define CRK_VERSION_MINOR 0
#define CRK_VERSION_PATCH 1
#define CRK_VERSION (CRK_VERSION_MAJOR * 10000 + CRK_VERSION_MINOR * 100 + CRK_VERSION_PATCH)

//Debug / Release flags
#ifndef NDEBUG

	#define CRK_DEBUG	1
	#define CRK_RELEASE	0

#else	//RELEASE

	#define CRK_DEBUG	0
	#define CRK_RELEASE	1

#endif

//C++ version
#if __cplusplus >= 202002L
	#define CRK_CPP20 1
#else
	#error "[crk] Requires C++20 or newer."
#endif

//Compiler
#if defined(__INTEL_COMPILER)
	#define CRK_INTEL_COMPILER	1
#elif defined(__clang__)
	#define CRK_CLANG_COMPILER	1
#elif defined(__GNUC__)
	#define CRK_GCC_COMPILER	1
#elif defined(_MSC_VER)
	#define CRK_MSVC_COMPILER	1
#endif

//OS
#if defined(_WIN64)
	#define CRK_WINDOWS_OS		1
	#define CRK_WINDOWS_64_OS	1
#elif defined(_WIN32)
	#define CRK_WINDOWS_OS		1
	#define CRK_WINDOWS_32_OS	1
#elif defined(__linux__)
	#define CRK_LINUX_OS		1
#elif defined(__APPLE__) && defined(__MACH__)
	#define CRK_MACOSX_OS		1
#elif defined(__ANDROID__)
	#define CRK_ANDROID_OS		1
#endif

//Attributes
#define CRK_NODISCARD	[[nodiscard]]
#define CRK_NORETURN	[[noreturn]]