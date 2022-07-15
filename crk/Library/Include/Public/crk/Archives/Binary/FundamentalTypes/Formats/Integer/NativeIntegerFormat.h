/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "crk/Archives/Binary/FundamentalTypes/Formats/Integer/OnesComplementIntegerFormat.h"
#include "crk/Archives/Binary/FundamentalTypes/Formats/Integer/TwosComplementIntegerFormat.h"
#include "crk/Archives/Binary/FundamentalTypes/Formats/Integer/SignMagnitudeIntegerFormat.h"

namespace crk
{
	/**
	*	@brief Native integer format for the target platform.
	*/
	using NativeIntegerFormat = decltype(internal::getNativeIntegerFormatImpl());
}

static_assert(std::is_base_of_v<crk::IntegerFormat, crk::NativeIntegerFormat> &&
			  !std::is_same_v<crk::IntegerFormat, crk::NativeIntegerFormat>,
			  "[crk] getNativeIntegerFormatImpl must return a type inheriting from crk::IntegerFormat.");