/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cassert>
#include <type_traits>	//std::is_arithmetic_v, std::enable_if_t...
#include <fstream>		//std::ifstream
#include <cstring>		//std::memcpy

#include "crk/Archives/Binary/BinaryArchive.h"
#include "crk/Archives/Binary/FundamentalTypes/IntegerTraits.h"
#include "crk/Archives/Binary/DataModel/DataModelTypeMapping.h"
#include "crk/Misc/Endianness.h"
#include "crk/Misc/Concepts.h"

namespace crk
{
	template <std::size_t Size, EEndianness Endianness = EEndianness::Little, DataModel DataModel = LLP64DataModel>
	class InBinaryArchive : public BinaryArchive<Size, Endianness, DataModel>
	{
		private:
			std::size_t	_readOffset = 0u;

		public:
			template <typename FirstObjectType, typename... NextObjectsTypes>
			void unpack(FirstObjectType& firstObject, NextObjectsTypes&... nextObjects) noexcept
			{
				unpack(firstObject);
				unpack(nextObjects...);
			}

			template <typename T>
			void unpack(T& obj) noexcept
			{
				//Write dataHeader

				deserialize(*this, obj);

				//Write dataFooter?
			}

			template <typename FirstObjectType, typename... NextObjectsTypes>
			void operator()(FirstObjectType& firstObject, NextObjectsTypes&... nextObjects) noexcept
			{
				unpack(firstObject, nextObjects...);
			}

			inline std::size_t getReadOffset() const noexcept
			{
				return _readOffset;
			}

			inline void setReadOffset(std::size_t newReadOffset) noexcept
			{
				assert(newReadOffset < Size);

				_readOffset = newReadOffset;
			}

			bool readNextBinaryChunk(std::size_t chunkSize, std::byte* target)
			{
				if (readBinaryChunk(getReadOffset(), chunkSize, target))
				{
					_readOffset += chunkSize;
					return true;
				}

				return false;
			}

			bool readBinaryChunk(std::size_t offset, std::size_t chunkSize, std::byte* target)
			{
				//Can't read more memory than we have
				if (chunkSize > Size - offset)
				{
					return false;
				}
				else
				{
					std::memcpy(target, BinaryArchive<Size, Endianness, DataModel>::_data.data() + offset, chunkSize);

					return true;
				}
			}

			bool loadFromFile(char const* filepath)
			{
				std::ifstream file;
				
				file.open(filepath, std::ios_base::binary | std::ios_base::ate);
				auto fileSize = file.tellg();

				//File is bigger than this buffer, abort
				if (fileSize > Size)
				{
					return false;
				}

				file.seekg(0);
				file.read(reinterpret_cast<char*>(BinaryArchive<Size, Endianness, DataModel>::_data.data()), fileSize);

				file.close();

				return true;
			}
	};

	template <Integer T, std::size_t Size, EEndianness Endianness, DataModel DataModel>
	void deserialize(InBinaryArchive<Size, Endianness, DataModel>& archive, T& object)
	{
		using SerializedIntegerType = decltype(DataModelTypeMapping<DataModel>::template getMappedType<T>());

		SerializedIntegerType readInteger;

		archive.readNextBinaryChunk(sizeof(SerializedIntegerType), reinterpret_cast<std::byte*>(std::addressof(readInteger)));
		object = Endianness::convert<Endianness, Endianness::getNativeEndianness()>(readInteger);
	}

	template <FixedWidthInteger T, std::size_t Size, EEndianness Endianness, DataModel DataModel>
	void deserialize(InBinaryArchive<Size, Endianness, DataModel>& archive, T& object)
	{
		T readInteger;

		archive.readNextBinaryChunk(sizeof(T), reinterpret_cast<std::byte*>(std::addressof(readInteger)));
		object = Endianness::convert<Endianness, Endianness::getNativeEndianness()>(readInteger);
	}

	template <Boolean T, std::size_t Size, EEndianness Endianness, DataModel DataModel>
	void deserialize(InBinaryArchive<Size, Endianness, DataModel>& archive, T& object)
	{
		archive.readNextBinaryChunk(sizeof(T), reinterpret_cast<std::byte*>(std::addressof(object)));
		object = Endianness::convert<Endianness, Endianness::getNativeEndianness()>(object);
	}

	template <Character T, std::size_t Size, EEndianness Endianness, DataModel DataModel>
	void deserialize(InBinaryArchive<Size, Endianness, DataModel>& archive, T& object)
	{
		archive.readNextBinaryChunk(sizeof(T), reinterpret_cast<std::byte*>(std::addressof(object)));
		object = Endianness::convert<Endianness, Endianness::getNativeEndianness()>(object);
	}

	template <FloatingPoint T, std::size_t Size, EEndianness Endianness, DataModel DataModel>
	void deserialize(InBinaryArchive<Size, Endianness, DataModel>& archive, T& object)
	{
		archive.readNextBinaryChunk(sizeof(T), reinterpret_cast<std::byte*>(std::addressof(object)));
		object = Endianness::convert<Endianness, Endianness::getNativeEndianness()>(object);
	}
}