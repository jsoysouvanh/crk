/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstdint> //uint8_t

#include "crk/Misc/EnumMacros.h"

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
		Little	= 1u << 0,

		/**
		*	Big endian (most significant byte of a word first).
		*/
		Big		= 1u << 1,

		/**
		*	Mixed endian (bytes in 16-bit words are laid out in a little-endian fashion,
		*	whereas the 16-bit subwords of a 32-bit quantity are laid out in big-endian fashion).
		*	This was used by old machines such as PDP-11 (1970~) or Honeywell 316 (1969~).
		*/
		Mixed	= 1u << 2,

		/**
		*	Any endianness which is none of the above.
		*/
		Unknown	= 1u << 7
	};

	CRK_GENERATE_ENUM_OPERATORS(EEndianness)
}