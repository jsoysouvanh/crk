/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <concepts>

#include "crk/Archives/Binary/FundamentalTypes/Formats/Integer/NativeIntegerFormat.h"

namespace crk
{
	template <typename FromIntegerFormat, typename ToIntegerFormat>
	auto convertIntegerFormat(std::integral auto integer);

	//No format conversion, return the passed value as is
	template <typename FromIntegerFormat, typename ToIntegerFormat>
	auto convertIntegerFormat(std::integral auto integer)
		requires std::same_as<FromIntegerFormat, ToIntegerFormat>
	{
		return integer;
	}

	//Specialize convertIntegerFormat for a defined FromIntegerFormat and ToIntegerFormat here
	//TODO
}