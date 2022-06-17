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
	/*
	///////////

	class BinaryDataBase {};
	
	class ResizableBinaryData : public BinaryDataBase
	{
		private:
			std::byte*	_data				= nullptr;
			std::size_t _usedDataSize		= 0u;
			std::size_t _allocatedDataSize	= 0u;

			std::byte* reallocate(std::size_t newCapacity)
			{
				std::byte* newData = new std::byte[newCapacity];

				//Transfer old data
				if (_data != nullptr)
				{
					std::memcpy(newData, _data, _usedDataSize);

					delete[] _data;
				}

				_data = newData;
				_allocatedDataSize = newCapacity;

				return _data;
			}

			std::byte* reallocateIfDataDoesntFit(std::size_t appendedDataSize)
			{
				return (appendedDataSize > _allocatedDataSize - _usedDataSize) ? reallocate(_allocatedDataSize * 2.0f) : _data;
			}

		public:
			ResizableBinaryData(std::size_t initialCapacity = 64u):
				_data{nullptr},
				_usedDataSize{0u},
				_allocatedDataSize{0u}
			{
				reallocate((initialCapacity == 0u) ? 1u : initialCapacity);
			}

			void appendBytes(std::byte const* dataPtr, std::size_t dataSize)
			{
				reallocateIfDataDoesntFit(dataSize);

				std::memcpy(end(), dataPtr, dataSize);
				_usedDataSize += dataSize;
			}

			inline std::byte const* begin() const noexcept
			{
				return _data;
			}

			inline std::byte const* end() const noexcept
			{
				return begin() + _usedDataSize;
			}
	};

	////////////
	*/

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