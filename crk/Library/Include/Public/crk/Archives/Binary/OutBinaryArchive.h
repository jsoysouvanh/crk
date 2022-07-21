/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstring>		//std::memcpy
#include <utility>		//std::forward
#include <fstream>		//std::ofstream

#include "crk/Archives/Binary/BinaryArchive.h"
#include "crk/Archives/Binary/FundamentalTypes/IntegerTraits.h"
#include "crk/Archives/Binary/DataModel/DataModelTypeMapping.h"
#include "crk/Archives/Binary/FundamentalTypes/Formats/Integer/IntegerFormatConversions.h"
#include "crk/Misc/Endianness.h"
#include "crk/Misc/TypeConcepts.h"

namespace crk
{
	template <std::size_t Size, EEndianness Endianness = EEndianness::Little, DataModel DataModel = LLP64DataModel>
	class OutBinaryArchive : public BinaryArchive<Size, Endianness, DataModel>
	{
		private:
			using ParentBinaryArchiveType = BinaryArchive<Size, Endianness, DataModel>;

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
					std::memcpy(BinaryArchive<Size, Endianness, DataModel>::_data.data() + offset, chunkStart, chunkSize);

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

				file.write(reinterpret_cast<char const*>(ParentBinaryArchiveType::_data.data()), getWriteOffset());

				file.close();
			}
	};

	template <Integer T, std::size_t Size, EEndianness Endianness, DataModel _DataModel>
	void serialize(OutBinaryArchive<Size, Endianness, _DataModel>& archive, T const& object)
	{
		//Retrieve the integer type from the DataModel
		using SerializedIntegerType = decltype(DataModelTypeMapping<_DataModel>::template getMappedType<T>());

		//Cast the provided integer to another integer matching the size of the DataModel
		SerializedIntegerType serializedObject = static_cast<SerializedIntegerType>(object);

		//Perform encoding conversion
		serializedObject = convertIntegerFormat<NativeIntegerFormat, typename decltype(_DataModel)::UsedIntegerFormat>(serializedObject);

		//Convert endianness
		serializedObject = Endianness::convert<Endianness::getNativeEndianness(), Endianness>(serializedObject);

		//Write binary to archive
		archive.appendBinaryChunk(reinterpret_cast<std::byte const*>(std::addressof(serializedObject)), sizeof(SerializedIntegerType));
	}

	template <FixedWidthInteger T, std::size_t Size, EEndianness Endianness, DataModel _DataModel>
	void serialize(OutBinaryArchive<Size, Endianness, _DataModel>& archive, T const& object)
	{
		using UnderlyingIntegerType = typename T::WrappedType;

		//Perform encoding conversion
		UnderlyingIntegerType serializedObject = convertIntegerFormat<NativeIntegerFormat, typename decltype(_DataModel)::UsedIntegerFormat>(static_cast<UnderlyingIntegerType>(object));

		//Convert endianness
		serializedObject = Endianness::convert<Endianness::getNativeEndianness(), Endianness>(serializedObject);

		//Write binary to archive
		archive.appendBinaryChunk(reinterpret_cast<std::byte const*>(std::addressof(serializedObject)), sizeof(UnderlyingIntegerType));
	}

	template <Character T, std::size_t Size, EEndianness Endianness, DataModel DataModel>
	void serialize(OutBinaryArchive<Size, Endianness, DataModel>& archive, T const& object)
	{
		T endiannessSwappedObject = Endianness::convert<Endianness::getNativeEndianness(), Endianness>(object);

		archive.appendBinaryChunk(reinterpret_cast<std::byte const*>(std::addressof(endiannessSwappedObject)), sizeof(T));
	}

	template <Boolean T, std::size_t Size, EEndianness Endianness, DataModel DataModel>
	void serialize(OutBinaryArchive<Size, Endianness, DataModel>& archive, T const& object)
	{
		T endiannessSwappedObject = Endianness::convert<Endianness::getNativeEndianness(), Endianness>(object);

		//TODO: Write (char)1 for true and (char)0 for false.

		archive.appendBinaryChunk(reinterpret_cast<std::byte const*>(std::addressof(endiannessSwappedObject)), sizeof(T));
	}

	template <FloatingPoint T, std::size_t Size, EEndianness Endianness, DataModel DataModel>
	void serialize(OutBinaryArchive<Size, Endianness, DataModel>& archive, T const& object)
	{
		T endiannessSwappedObject = Endianness::convert<Endianness::getNativeEndianness(), Endianness>(object);

		//TODO: Might have to consider float endianness if it differs from classic CPU endianness

		archive.appendBinaryChunk(reinterpret_cast<std::byte const*>(std::addressof(endiannessSwappedObject)), sizeof(T));
	}
}