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

	/**
	*	@brief Concept that accepts only (direct or indirect) child classes of a given class (doesn't accept the parent class itself).
	*/
	template <typename Child, typename Parent>
	concept ChildOf = std::is_base_of_v<Parent, Child> && !std::is_same_v<Child, Parent>;
}