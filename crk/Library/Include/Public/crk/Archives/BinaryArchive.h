/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

////////////

#include <vector>
#include <array>
#include <cstddef>

////////////


#include <cstddef>		//std::byte
#include <cstring>		//std::memcpy
#include <utility>		//std::forward
#include <type_traits>	//std::is_arithmetic_v, std::enable_if_t...

#include <fstream>		//std::ofstream

#include "crk/Archives/ArchiveBase.h"
#include "crk/Misc/Endianness.h"

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

	template <std::size_t Size, EEndianness Endianness = EEndianness::Little>
	class OutBinaryArchive : public BinaryArchive<Size, Endianness>
	{
		private:
			std::size_t	_writeOffset = 0u;

		public:
			OutBinaryArchive()
			{
				//TODO: Write archive header?
			}

			~OutBinaryArchive() = default;

			template <typename FirstObjectType, typename... NextObjectsTypes>
			void pack(FirstObjectType const&& firstObject, NextObjectsTypes const&&... nextObjects)
			{
				pack(std::forward<FirstObjectType const>(firstObject));
				pack(std::forward<NextObjectsTypes const>(nextObjects)...);
			}

			template <typename T>
			void pack(T const&& obj)
			{
				//Write dataHeader

				serialize(*this, obj);

				//Write dataFooter?
			}

			template <typename FirstObjectType, typename... NextObjectsTypes>
			void operator()(FirstObjectType const&& firstObject, NextObjectsTypes const&&... nextObjects)
			{
				pack(std::forward<FirstObjectType const>(firstObject), std::forward<NextObjectsTypes const>(nextObjects)...);
			}

			bool appendBinaryChunk(std::byte const* chunkStart, std::size_t chunkSize)
			{
				if (writeBinaryChunk(_writeOffset, chunkStart, chunkSize))
				{
					setWriteOffset(getWriteOffset() + chunkSize);
					return true;
				}

				return false;
			}

			bool writeBinaryChunk(std::size_t offset, std::byte const* chunkStart, std::size_t chunkSize)
			{
				//No reallocations possible to fail if chunkSize > remaining memory
				if (chunkSize > Size - offset)
				{
					return false;
				}
				else
				{
					std::memcpy(BinaryArchive<Size, Endianness>::_data.data() + offset, chunkStart, chunkSize);

					return true;
				}
			}

			inline std::size_t getWriteOffset() const noexcept
			{
				return _writeOffset;
			}

			inline void setWriteOffset(std::size_t newWriteOffset)
			{
				//TODO: check for reallocations if newWriteOffset > capacity

				_writeOffset = newWriteOffset;
			}

			//Advantage of () over <<:
			//with (), we can have variadic parameters AND a return value
			//with <<, we can have single parameter + no return value (must return Archive& to chain << calls)

			void finish() noexcept
			{
				//TODO: Write archive footer?
			}

			void saveToFile(char const* filepath)
			{
				std::ofstream file;

				file.open(filepath, std::ios_base::binary);

				file.write(reinterpret_cast<char const*>(BinaryArchive<Size, Endianness>::_data.data()), getWriteOffset());
			}
	};


	template <typename T, std::size_t Size, EEndianness Endianness, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void serialize(OutBinaryArchive<Size, Endianness>& archive, T const& object)
	{
		T endiannessSwappedObject = Endianness::convert<Endianness::getNativeEndianness(), Endianness>(object);

		archive.appendBinaryChunk(reinterpret_cast<std::byte const*>(std::addressof(endiannessSwappedObject)), sizeof(T));
	}
}