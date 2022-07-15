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
#include "crk/Archives/Binary/DataModel/DataModel.h"
#include "crk/Misc/EEndianness.h"

namespace crk
{
	/**
	*	
	*/
	template <std::size_t Size, EEndianness Endianness = EEndianness::Little, DataModel DataModel = LLP64DataModel>
	class BinaryArchive : public ArchiveBase
	{
		//Check data model validity
		//See https://en.cppreference.com/w/cpp/language/types
		static_assert(DataModel.shortSize >= 2 && DataModel.shortSize <= DataModel.intSize);
		static_assert(DataModel.intSize >= 2 && DataModel.intSize <= DataModel.longSize);
		static_assert(DataModel.longSize >= 4 && DataModel.longSize <= DataModel.longlongSize);
		static_assert(DataModel.longlongSize >= 8);

		protected:
			std::array<std::byte, Size>	_data;
	};
}