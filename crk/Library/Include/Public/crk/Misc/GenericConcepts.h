/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits>

namespace crk
{
	template <typename T, typename U>
	concept SameAs = std::is_same_v<T, U>;

	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	template <class From, class To>
	concept ConvertibleTo = std::is_convertible_v<From, To> &&
							requires
							{
								static_cast<To>(std::declval<From>());
							};
}