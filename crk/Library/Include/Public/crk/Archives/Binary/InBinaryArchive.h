/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cassert>
#include <fstream>		//std::ifstream
#include <cstring>		//std::memcpy

#include "crk/Archives/Binary/BinaryArchive.h"
#include "crk/Archives/Binary/FundamentalTypes/IntegerTraits.h"
#include "crk/Archives/Binary/DataModel/DataModelTypeMapping.h"
#include "crk/Archives/Binary/FundamentalTypes/Formats/Integer/IntegerFormatConversions.h"
#include "crk/Misc/Endianness.h"
#include "crk/Misc/TypeConcepts.h"

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

	template <Integer T, std::size_t Size, EEndianness Endianness, DataModel _DataModel>
	void deserialize(InBinaryArchive<Size, Endianness, _DataModel>& archive, T& object)
	{
		using SerializedIntegerType = decltype(DataModelTypeMapping<_DataModel>::template getMappedType<T>());

		//Read raw binary into readInteger
		SerializedIntegerType readInteger;
		archive.readNextBinaryChunk(sizeof(SerializedIntegerType), reinterpret_cast<std::byte*>(std::addressof(readInteger)));
		
		/////// WARNING: May need to invert encoding conversion and endianness conversion
		//Perform encoding conversion
		readInteger = convertIntegerFormat<typename decltype(_DataModel)::UsedIntegerFormat, NativeIntegerFormat>(readInteger);

		//Implicit cast from SerializedIntegerType to deserialized integer type
		object = Endianness::convert<Endianness, Endianness::getNativeEndianness()>(readInteger);
	}

	template <FixedWidthInteger T, std::size_t Size, EEndianness Endianness, DataModel _DataModel>
	void deserialize(InBinaryArchive<Size, Endianness, _DataModel>& archive, T& object)
	{
		using WrappedType = typename T::WrappedType;

		//Read raw binary into readInteger
		WrappedType readInteger;
		archive.readNextBinaryChunk(sizeof(WrappedType), reinterpret_cast<std::byte*>(std::addressof(readInteger)));
		
		/////// WARNING: May need to invert encoding conversion and endianness conversion
		//Perform encoding conversion
		readInteger = convertIntegerFormat<typename decltype(_DataModel)::UsedIntegerFormat, NativeIntegerFormat>(readInteger);

		//Implicit cast from WrappedType to deserialized integer type
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

		//Use convertRef to avoid float copies that may result in a modification of the binary representation of the float
		Endianness::convertRef<Endianness, Endianness::getNativeEndianness()>(object);
	}
}