/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <iostream>
#include <string>

#include <crk/Misc/Endianness.h>

namespace crk::tests
{
	std::string toString(crk::EEndianness endianness) noexcept
	{
		switch (endianness)
		{
			case crk::EEndianness::Little:
				return "Little endian";

			case crk::EEndianness::Big:
				return "Big endian";

			case crk::EEndianness::Mixed:
				return "Mixed endian";

			case crk::EEndianness::Unknown:
				return "Unknown endian";
		}
	}

	void printEndianness()
	{
		std::cout << "Current machine is " << toString(crk::Endianness::getNativeEndianness()) << std::endl;
	}
}