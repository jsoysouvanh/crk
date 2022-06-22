/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t
#include <climits>	//CHAR_BIT

namespace crk
{
	struct System
	{
		static constexpr std::size_t bits = sizeof(void*) * CHAR_BIT;
	};
}