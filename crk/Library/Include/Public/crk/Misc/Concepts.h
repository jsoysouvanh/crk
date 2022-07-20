/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "crk/Types/FixedWidthIntegers.h"

namespace crk
{
	template <typename T>
	concept Integer = std::is_same_v<T, short> ||
					  std::is_same_v<T, unsigned short> ||
					  std::is_same_v<T, int> ||
					  std::is_same_v<T, unsigned int> ||
					  std::is_same_v<T, long> ||
					  std::is_same_v<T, unsigned long> ||
					  std::is_same_v<T, long long> ||
					  std::is_same_v<T, unsigned long long>;

	template <typename T>
	concept FixedWidthInteger = std::is_same_v<T, crk::int8> ||
								std::is_same_v<T, crk::uint8> ||
								std::is_same_v<T, crk::int16> ||
								std::is_same_v<T, crk::uint16> ||
								std::is_same_v<T, crk::int32> ||
								std::is_same_v<T, crk::uint32> ||
								std::is_same_v<T, crk::int64> ||
								std::is_same_v<T, crk::uint64>;

	template <typename T>
	concept FloatingPoint = std::is_same_v<T, float> ||
							std::is_same_v<T, double> ||
							std::is_same_v<T, long double>;

	template <typename T>
	concept Character = std::is_same_v<T, char> ||
						std::is_same_v<T, signed char> ||
						std::is_same_v<T, unsigned char> ||
						std::is_same_v<T, wchar_t> ||
						std::is_same_v<T, char8_t> ||
						std::is_same_v<T, char16_t> ||
						std::is_same_v<T, char32_t>;

	template <typename T>
	concept Boolean = std::is_same_v<T, bool>;

	template <typename T, typename U>
	concept SameAs = std::is_same_v<T, U>;

	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;
}