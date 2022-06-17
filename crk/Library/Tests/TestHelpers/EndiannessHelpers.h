/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <iostream>

#include <crk/Misc/Endianness.h>

void printEndianness()
{
	std::cout << "Current machine is ";

	if constexpr (crk::Endianness::getNativeEndianness() == crk::EEndianness::Little)
		std::cout << "Little endian" << std::endl;
	else if constexpr (crk::Endianness::getNativeEndianness() == crk::EEndianness::Big)
		std::cout << "Big endian" << std::endl;
	else if constexpr (crk::Endianness::getNativeEndianness() == crk::EEndianness::Mixed)
		std::cout << "Mixed endian" << std::endl;
}