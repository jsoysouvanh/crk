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
#include "crk/Misc/Endianness.h"

namespace crk
{
	template <std::size_t Size, EEndianness Endianness = EEndianness::Little>
	class InBinaryArchive : public BinaryArchive<Size, Endianness>
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
					std::memcpy(target, BinaryArchive<Size, Endianness>::_data.data() + offset, chunkSize);

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
				file.read(reinterpret_cast<char*>(BinaryArchive<Size, Endianness>::_data.data()), fileSize);

				file.close();

				return true;
			}
	};

	template <typename T, std::size_t Size, EEndianness Endianness, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void deserialize(InBinaryArchive<Size, Endianness>& archive, T& object)
	{
		archive.readNextBinaryChunk(sizeof(T), reinterpret_cast<std::byte*>(std::addressof(object)));
		object = Endianness::convert<Endianness, Endianness::getNativeEndianness()>(object);
	}
}