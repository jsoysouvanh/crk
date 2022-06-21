/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <array>
#include <cstddef>		//std::byte

#include "crk/Archives/ArchiveBase.h"
#include "crk/Misc/EEndianness.h"

namespace crk
{
	/**
	*	
	*/
	template <std::size_t Size, EEndianness Endianness = EEndianness::Little>
	class BinaryArchive : public ArchiveBase
	{
		protected:
			std::array<std::byte, Size>	_data;
	};
}