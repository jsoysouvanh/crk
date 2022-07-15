/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstdint>	//int8_t

#include "crk/Config.h"

#include "crk/Archives/Binary/FundamentalTypes/Formats/Integer/IntegerFormat.h"

namespace crk
{
	/**
	*	@brief Class representing the 1's complement integer format.
	*/
	struct OnesComplementIntegerFormat : public IntegerFormat {};

	namespace internal
	{
		template <typename = int>
		constexpr OnesComplementIntegerFormat getNativeIntegerFormatImpl()
			requires (static_cast<int8_t>(-1) == static_cast<int8_t>(0b11111110));
	}
}