/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "crk/Config.h"

#if defined(_WIN32)
#include "intrin.h"	//_byteswap_ushort, _byteswap_ulong, _byteswap_uint64
#endif

#if CRK_CPP20
#include <bit> //std::endian
#endif

#include "crk/Misc/EEndianness.h"

namespace crk
{
	/**
	*	@brief Static class containing all helper functions related to endianness.
	*/
	class Endianness
	{
		private:
			template <EEndianness SourceEndianness, EEndianness TargetEndianness>
			_NODISCARD static constexpr bool isLittleBigConversion() noexcept
			{
				return (SourceEndianness | TargetEndianness) == (EEndianness::Little | EEndianness::Big);
			}

			template <EEndianness SourceEndianness, EEndianness TargetEndianness>
			_NODISCARD static constexpr bool isLittleMixedConversion() noexcept
			{
				return (SourceEndianness | TargetEndianness) == (EEndianness::Little | EEndianness::Mixed);
			}

			template <EEndianness SourceEndianness, EEndianness TargetEndianness>
			_NODISCARD static constexpr bool isBigMixedConversion() noexcept
			{
				return (SourceEndianness | TargetEndianness) == (EEndianness::Big | EEndianness::Mixed);
			}

		public:
			Endianness() = delete;

			/**
			*	@brief Get the endianness used by the compiled program.
			* 
			*	@return The endianness used by the compiled program.
			*/
			CRK_NODISCARD static constexpr EEndianness getNativeEndianness() noexcept;

			///////// TODO: Move impl to .inl + doc //////////
			template <EEndianness SourceEndianness, EEndianness TargetEndianness>
			_NODISCARD static uint8_t convertEndianness(uint8_t v) noexcept
			{
				//No conversion necessary for 8 bits values
				return v;
			}

			template <EEndianness SourceEndianness, EEndianness TargetEndianness>
			_NODISCARD static uint16_t convertEndianness(uint16_t v) noexcept
			{
				if constexpr (SourceEndianness != TargetEndianness)
				{
#if defined(_WIN32)
					if constexpr (isLittleBigConversion<SourceEndianness, TargetEndianness>())
					{
						return _byteswap_ushort(v);
					}
					else
					{
						//Not supported yet
					}
#elif defined(GCC)
					//TODO
					return v;
#else
					//TODO: Call generic (unoptimized) bytes swap
					return v;
#endif
				}
				else
				{
					return v;
				}
			}
	};

	#include "crk/Misc/Endianness.inl"
}