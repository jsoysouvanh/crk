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

	/**
	*	@brief Struct that maps a size (in bits) to the corresponding integer type.
	* 
	*	@tparam IntegerSize Size in bits of the target integer.
	*	@tparam IsUnsigned	Target the unsigned integer version?
	*/
	template <std::size_t IntegerSize, bool IsUnsigned>
	struct IntegerType;

	template <>
	struct IntegerType<8u, false>
	{
		using type = int8_t;
	};

	template <>
	struct IntegerType<8u, true>
	{
		using type = uint8_t;
	};

	template <>
	struct IntegerType<16u, false>
	{
		using type = int16_t;
	};

	template <>
	struct IntegerType<16u, true>
	{
		using type = uint16_t;
	};

	template <>
	struct IntegerType<32u, false>
	{
		using type = int32_t;
	};

	template <>
	struct IntegerType<32u, true>
	{
		using type = uint32_t;
	};

	template <>
	struct IntegerType<64u, false>
	{
		using type = int64_t;
	};

	template <>
	struct IntegerType<64u, true>
	{
		using type = uint64_t;
	};

	template <std::size_t IntegerSize, bool IsUnsigned>
	using IntegerType_t = typename IntegerType<IntegerSize, IsUnsigned>::type;
}