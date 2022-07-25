/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "crk/Config.h"

#include <cstdlib>	//builtin bswaps for both MSVC (_byteswap_ushort...) and GNU compilers (__builtin_bswap16...)
#include <climits>	//CHAR_BIT
#include <bit>		//std::byte
#include <utility>	//std::swap
#include <cstdint>

#if CRK_CPP20
	#include <bit> //std::endian
#elif defined(__has_include)
	#if __has_include(<endian.h>)
		#include <endian.h>			//GNU, Linux
	#elif __has_include(<machine/endian.h>)
		#include <machine/endian.h> //OpenBSD, MacOS
	#elif __has_include(<sys/param.h>)
		#include <sys/param.h>		//MINGW, some BSD
	#elif __has_include(<sys/isadefs.h>)
		#include <sys/isadefs.h>	//Solaris
	#endif
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
			/**
			*	@brief Check if the specified endiannesses are Little & Big regardless of the conversion order.
			* 
			*	@tparam SourceEndianness Source endianness.
			*	@tparam TargetEndianness Target endianness.
			* 
			*	@return true if (SourceEndianness, TargetEndianness) is (Big, Little) or (Little, Big), else false.
			*/
			template <EEndianness SourceEndianness, EEndianness TargetEndianness>
			CRK_NODISCARD static constexpr bool		isLittleBigConversion()			noexcept;

			/**
			*	@brief Check if the specified endiannesses are Little & Mixed regardless of the conversion order.
			* 
			*	@tparam SourceEndianness Source endianness.
			*	@tparam TargetEndianness Target endianness.
			* 
			*	@return true if (SourceEndianness, TargetEndianness) is (Little, Mixed) or (Mixed, Little), else false.
			*/
			template <EEndianness SourceEndianness, EEndianness TargetEndianness>
			CRK_NODISCARD static constexpr bool		isLittleMixedConversion()		noexcept;

			/**
			*	@brief Check if the specified endiannesses are Big & Mixed regardless of the conversion order.
			* 
			*	@tparam SourceEndianness Source endianness.
			*	@tparam TargetEndianness Target endianness.
			* 
			*	@return true if (SourceEndianness, TargetEndianness) is (Big, Mixed) or (Mixed, Big), else false.
			*/
			template <EEndianness SourceEndianness, EEndianness TargetEndianness>
			CRK_NODISCARD static constexpr bool		isBigMixedConversion()			noexcept;

			/**
			*	@brief Check if one of the provided endiannesses is Unknown.
			* 
			*	@tparam SourceEndianness Source endianness.
			*	@tparam TargetEndianness Target endianness.
			* 
			*	@return true if SourceEndianness or TargetEndianness is Unknown, else false.
			*/
			template <EEndianness SourceEndianness, EEndianness TargetEndianness>
			CRK_NODISCARD static constexpr bool		isUnknownConversion()			noexcept;
			
			/**
			*	@brief Bitshift implementation of bswap16.
			* 
			*	@param v 16-bit unsigned integer to byteswap.
			*
			*	@return The byte-swapped 16-bit unsigned integer.
			*/
			CRK_NODISCARD static constexpr uint16_t	bitshiftByteSwap16(uint16_t v)	noexcept;

			/**
			*	@brief Bitshift implementation of bswap32.
			* 
			*	@param v 32-bit unsigned integer to byteswap.
			*
			*	@return The byte-swapped 32-bit unsigned integer.
			*/
			CRK_NODISCARD static constexpr uint32_t	bitshiftByteSwap32(uint32_t v)	noexcept;

			/**
			*	@brief Bitshift implementation of bswap64.
			* 
			*	@param v 64-bit unsigned integer to byteswap.
			*
			*	@return The byte-swapped 64-bit unsigned integer.
			*/
			CRK_NODISCARD static constexpr uint64_t	bitshiftByteSwap64(uint64_t v)	noexcept;

			/**
			*	@brief	Optimized implementation of bswap16.
			*			Use the builtin instruction if available, and fallbacks to the bitshift implementation otherwise.
			* 
			*	@param v 16-bit unsigned integer to byteswap.
			*
			*	@return The byte-swapped 16-bit unsigned integer.
			*/
			CRK_NODISCARD static inline uint16_t	byteSwap16(uint16_t v)			noexcept;

			/**
			*	@brief	Optimized implementation of bswap32.
			*			Use the builtin instruction if available, and fallbacks to the bitshift implementation otherwise.
			* 
			*	@param v 32-bit unsigned integer to byteswap.
			*
			*	@return The byte-swapped 32-bit unsigned integer.
			*/
			CRK_NODISCARD static inline uint32_t	byteSwap32(uint32_t v)			noexcept;

			/**
			*	@brief	Optimized implementation of bswap64.
			*			Use the builtin instruction if available, and fallbacks to the bitshift implementation otherwise.
			* 
			*	@param v 64-bit unsigned integer to byteswap.
			*
			*	@return The byte-swapped 64-bit unsigned integer.
			*/
			CRK_NODISCARD static inline uint64_t	byteSwap64(uint64_t v)			noexcept;

			/**
			*	@brief Byte-swap object of arbitrary type T.
			* 
			*	@tparam T Type of the object to byteswap.
			* 
			*	@param v Object to byteswap.
			* 
			*	@return The byte-swapped object.
			*/
			template <typename T>
			CRK_NODISCARD static T					byteSwap(T v)					noexcept;

			template <typename T>
			static void								byteSwapRef(T& v)				noexcept;

		public:
			Endianness() = delete;

			/**
			*	@brief Get the endianness used by the compiled program.
			* 
			*	@return The endianness used by the compiled program.
			*/
			CRK_NODISCARD static constexpr EEndianness	getNativeEndianness()	noexcept;

			/**
			*	@brief	Convert an object to a specific endianness.
			* 
			*	@tparam SourceEndianness	Source endianness.
			*	@tparam TargetEndianness	Target endianness.
			*	@tparam T					Type of the object to convert.
			* 
			*	@param v Object to convert.
			* 
			*	@return The object converted to the specified endianness.
			*/
			template <EEndianness SourceEndianness, EEndianness TargetEndianness, typename T>
			CRK_NODISCARD static T						convert(T v)			noexcept;

			template <EEndianness SourceEndianness, EEndianness TargetEndianness, typename T>
			static void									convertRef(T& v)		noexcept;
	};

	#include "crk/Misc/Endianness.inl"
}