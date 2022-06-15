/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits> //std::underlying_type_t

#define CRK_GENERATE_ENUM_OPERATORS(EnumName)																	\
constexpr EnumName operator|(EnumName flags1, EnumName flags2) noexcept											\
{																												\
	using UnderlyingType = std::underlying_type_t<EnumName>;													\
																												\
	return static_cast<EnumName>(static_cast<UnderlyingType>(flags1) | static_cast<UnderlyingType>(flags2));	\
}																												\
																												\
constexpr EnumName operator&(EnumName flags1, EnumName flags2) noexcept											\
{																												\
	using UnderlyingType = std::underlying_type_t<EnumName>;													\
																												\
	return static_cast<EnumName>(static_cast<UnderlyingType>(flags1) & static_cast<UnderlyingType>(flags2));	\
}

