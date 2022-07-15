/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>
#include <cstdint>

namespace crk
{
	// IntegerType
	// ======================

	template <std::size_t IntegerSize, bool IsUnsigned>
	struct IntegerType;

	template <>
	struct IntegerType<1, false>
	{
		using type = int8_t;
	};

	template <>
	struct IntegerType<1, true>
	{
		using type = uint8_t;
	};

	template <>
	struct IntegerType<2, false>
	{
		using type = int16_t;
	};

	template <>
	struct IntegerType<2, true>
	{
		using type = uint16_t;
	};

	template <>
	struct IntegerType<4, false>
	{
		using type = int32_t;
	};

	template <>
	struct IntegerType<4, true>
	{
		using type = uint32_t;
	};

	template <>
	struct IntegerType<8, false>
	{
		using type = int64_t;
	};

	template <>
	struct IntegerType<8, true>
	{
		using type = uint64_t;
	};

	template <std::size_t IntegerSize, bool IsUnsigned>
	using IntegerType_t = typename IntegerType<IntegerSize, IsUnsigned>::type;
}