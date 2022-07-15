/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits> //std::is_base_of_v, std::is_same_v

#include "crk/Config.h"

#include "crk/Archives/Binary/FundamentalTypes/Formats/BinaryFormat.h"

namespace crk
{
	/**
	*	@brief Base class used to define integer formats.
	*/
	struct IntegerFormat : public BinaryFormat {};

	/**
	*	@brief Fallback integer format returned when no other implemented format is valid.
	*/
	struct IntegerUnknownFormat : public IntegerFormat {};

	namespace internal
	{
		/**
		*	@brief Fallback implementation of the getNativeIntegerEncodingImpl function.
		*/
		template <typename = int>
		constexpr IntegerUnknownFormat getNativeIntegerFormatImpl();
	}
}