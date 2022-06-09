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
	#define CRK_CPP20_SUPPORT 1
#else
	#define CRK_CPP20_SUPPORT 0
#endif

//Attributes
#define CRK_NODISCARD	[[nodiscard]]
#define CRK_NORETURN	[[noreturn]]