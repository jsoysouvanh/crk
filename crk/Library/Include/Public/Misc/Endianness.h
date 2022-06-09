/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Config.h"

#include <cstdint> //uint8_t

#if CRK_CPP20_SUPPORT
#include <bit> //std::endian
#endif

namespace crk
{
	/**
	*	@brief Value defining the different endiannesses supported by the library.
	*/
	enum class EEndianness : uint8_t
	{
		/**
		*	Little endian (least significant byte of a word first).
		*/
		Little	= 0u,

		/**
		*	Big endian (most significant byte of a word first).
		*/
		Big		= 1u,

		/**
		*	Mixed endian (bytes in 16-bit words are laid out in a little-endian fashion,
		*	whereas the 16-bit subwords of a 32-bit quantity are laid out in big-endian fashion).
		*/
		Mixed
	};

	/**
	*	@brief Get the endianness of the 
	*/
	CRK_NODISCARD constexpr EEndianness getNativeEndianness() noexcept;

	#include "Misc/Endianness.inl"
}