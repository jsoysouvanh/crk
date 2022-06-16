/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <EEndianness SourceEndianness, EEndianness TargetEndianness>
constexpr bool Endianness::isLittleBigConversion() noexcept
{
	return (SourceEndianness | TargetEndianness) == (EEndianness::Little | EEndianness::Big);
}

template <EEndianness SourceEndianness, EEndianness TargetEndianness>
constexpr bool Endianness::isLittleMixedConversion() noexcept
{
	return (SourceEndianness | TargetEndianness) == (EEndianness::Little | EEndianness::Mixed);
}

template <EEndianness SourceEndianness, EEndianness TargetEndianness>
constexpr bool Endianness::isBigMixedConversion() noexcept
{
	return (SourceEndianness | TargetEndianness) == (EEndianness::Big | EEndianness::Mixed);
}

template <EEndianness SourceEndianness, EEndianness TargetEndianness>
constexpr bool Endianness::isUnknownConversion() noexcept
{
	return SourceEndianness == EEndianness::Unknown || TargetEndianness == EEndianness::Unknown;
}

constexpr uint16_t Endianness::bitshiftByteSwap16(uint16_t v) noexcept
{
	return	(v >> 8) | (v << 8);
}

constexpr uint32_t Endianness::bitshiftByteSwap32(uint32_t v) noexcept
{
	return	( v					>> 24)	|
			((v & 0x00FF0000u)	>> 8)	|
			((v & 0x0000FF00u)	<< 8)	|
			( v					<< 24);
}

constexpr uint64_t Endianness::bitshiftByteSwap64(uint64_t v) noexcept
{
	return	( v								>> 56)	|
			((v & 0x00FF000000000000ull)	>> 40)	|
			((v & 0x0000FF0000000000ull)	>> 24)	|
			((v & 0x000000FF00000000ull)	>> 8)	|
			((v & 0x00000000FF000000ull)	<< 8)	|
			((v & 0x0000000000FF0000ull)	<< 24)	|
			((v & 0x000000000000FF00ull)	<< 40)	|
			( v								<< 56);
}

inline uint16_t Endianness::byteSwap16(uint16_t v) noexcept
{
#if defined(CRK_MSVC_COMPILER)
	return _byteswap_ushort(v);
#elif defined(__has_builtin)				//
	#if __has_builtin(__builtin_bswap16)	//Must split in 2 lines so that __has_builtin() call is not evaluated when it doesn't exist
		return __builtin_bswap16(v);
	#else
		return bitshiftByteSwap16(v);
	#endif
#else //Fallback implementation
	return bitshiftByteSwap16(v);
#endif
}

inline uint32_t Endianness::byteSwap32(uint32_t v) noexcept
{
#if defined(CRK_MSVC_COMPILER)
	return _byteswap_ulong(v);
#elif defined(__has_builtin)				//
	#if __has_builtin(__builtin_bswap32)	//Must split in 2 lines so that __has_builtin() call is not evaluated when it doesn't exist
		return __builtin_bswap32(v);
	#else
		return bitshiftByteSwap32(v);
	#endif
#else //Fallback implementation
	return bitshiftByteSwap32(v);
#endif
}

inline uint64_t Endianness::byteSwap64(uint64_t v) noexcept
{
#if defined(CRK_MSVC_COMPILER)
	return _byteswap_uint64(v);
#elif defined(__has_builtin)				//
	#if __has_builtin(__builtin_bswap64)	//Must split in 2 lines so that __has_builtin() call is not evaluated when it doesn't exist
		return __builtin_bswap64(v);
	#else
		return bitshiftByteSwap64(v);
	#endif
#else //Fallback implementation
	return bitshiftByteSwap64(v);
#endif
}

template <typename T>
T Endianness::byteSwap(T v) noexcept
{
	if constexpr (sizeof(T) == 1u)			//8 bits
	{
		return v;
	}
	//use memcpy to avoid breaking strict-aliasing rules for C++ with reinterpret_cast
	else if constexpr (sizeof(T) == 2u)		//16 bits
	{
		uint16_t tmp;
		std::memcpy(&tmp, &v, sizeof(uint16_t));
		tmp = byteSwap16(tmp);
		std::memcpy(&v, &tmp, sizeof(uint16_t));
		return v;
	}
	else if constexpr (sizeof(T) == 4u)		//32 bits
	{
		uint32_t tmp;
		std::memcpy(&tmp, &v, sizeof(uint32_t));
		tmp = byteSwap32(tmp);
		std::memcpy(&v, &tmp, sizeof(uint32_t));
		return v;
	}
	else if constexpr (sizeof(T) == 8u)	//32 bits
	{
		uint64_t tmp;
		std::memcpy(&tmp, &v, sizeof(uint64_t));
		tmp = byteSwap64(tmp);
		std::memcpy(&v, &tmp, sizeof(uint64_t));
		return v;
	}
	//TODO: Add support for 128 byteswap? with _mm_shuffle_epi8?
	else
	{
		//TODO: Fallback implementation for any size type
		return v;
	}
}

constexpr EEndianness Endianness::getNativeEndianness() noexcept
{
	//Get endianness using the standard library if possible (C++20~)
#if defined(CRK_CPP20)
	if constexpr (std::endian::native == std::endian::little)
	{
		return EEndianness::Little;
	}
	else if constexpr (std::endian::native == std::endian::big)
	{
		return EEndianness::Big;
	}
	else
	{
		return EEndianness::Mixed;
	}

	/**
	*	Take advantage of environment dependant macros (OS, Compiler, CPU etc...)
	*	https://stackoverflow.com/questions/4239993/determining-endianness-at-compile-time
	*/

	//GNU compilers (GCC, Clang...)
#elif defined(__BYTE_ORDER__)
	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		return EEndianness::Little;
	#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		return EEndianness::Big;
	#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
		return EEndianness::Mixed;
	#else
		return EEndianness::Unknown;
	#endif

	//Linux headers
#elif defined(__BYTE_ORDER)
	#if __BYTE_ORDER == __LITTLE_ENDIAN
		return EEndianness::Little;
	#elif __BYTE_ORDER == __BIG_ENDIAN
		return EEndianness::Big;
	#elif __BYTE_ORDER == __PDP_ENDIAN
		return EEndianness::Mixed;
	#else
		return EEndianness::Unknown;
	#endif

	//MINGW / OpenBSD
#elif defined(BYTE_ORDER)
	#if BYTE_ORDER == LITTLE_ENDIAN
		return EEndianness::Little;
	#elif BYTE_ORDER == BIG_ENDIAN
		return EEndianness::Big;
	#elif BYTE_ORDER == PDP_ENDIAN
		return EEndianness::Mixed;
	#else
		return EEndianness::Unknown;
	#endif

	//Solaris
#elif (__sun) && defined(__SVR4)
	#if defined(_LITTLE_ENDIAN)
		return EEndianness::Little;
	#elif defined(_BIG_ENDIAN)
		return EEndianness::Big;
	#elif defined(_PDP_ENDIAN)
		return EEndianness::Mixed;
	#else
		return EEndianness::Unknown;
	#endif

	//MSVC
#elif defined(CRK_MSVC_COMPILER)
	#if defined(_M_PPC)
		return EEndianness::Big;
	#elif defined(_M_IX86) || defined(_M_X64) || defined(_M_IA64) || defined(_M_ARM)
		return EEndianness::Little;
	#else
		return EEndianness::Unknown;
	#endif

#elif defined(__LITTLE_ENDIAN__)	||
	  defined(__ARMEL__)			||
	  defined(__THUMBEL__)			||
	  defined(__AARCH64EL__)		||
	  defined(_MIPSEL)				||
	  defined(__MIPSEL)				||
	  defined(__MIPSEL__)

	return EEndianness::Little;

#elif defined(__BIG_ENDIAN__)	||
	  defined(__ARMEB__)		||
	  defined(__THUMBEB__)		||
	  defined(__AARCH64EB__)	||
	  defined(_MIPSEB)			||
	  defined(__MIPSEB)			||
	  defined(__MIPSEB__)

	return EEndianness::Big;

	//Use an implementation-defined way with multicharacter literal int initialization.
	//WARNING: Since the following is implementation-defined, it might not generate the correct result with some compilers.
	//		   However, relatively few systems should fallback to this implementation.
	//Can't use the reinterpret-cast way since reinterpret_cast can't be used in constexpr context
	//Can't use union since type-punning is UB in C++ and throws a compilation error on some compilers (clang)
#else
	//Init an uint32 from multicharacter literal https://en.cppreference.com/w/cpp/language/character_literal
	constexpr uint32_t const nativeEndian = 'ABCD';

	//ASCII codes: 'A' = 41, 'B' = 42, 'C' = 43, 'D' = 44
	if constexpr (nativeEndian == 0x41424344u)
	{
		return EEndianness::Little;
	}
	else if constexpr (nativeEndian == 0x44434241u)
	{
		return EEndianness::Big;
	}
	else if constexpr (nativeEndian == 0x43444142)
	{
		return EEndianness::Mixed;
	}
	else
	{
		return EEndianness::Unknown;
	}
#endif
}

template <EEndianness SourceEndianness, EEndianness TargetEndianness, typename T, typename>
T Endianness::convert(T v) noexcept
{
	static_assert(!(isUnknownConversion<SourceEndianness, TargetEndianness>()	||
				    isBigMixedConversion<SourceEndianness, TargetEndianness>()	||
					isLittleMixedConversion<SourceEndianness, TargetEndianness>()),
				  "[crk] Don't support endianness conversions from/to mixed or unknown endianness.");

	if constexpr (SourceEndianness == TargetEndianness)
	{
		//No conversion necessary if source and target endianness are the same
		return v;
	}
	else if constexpr (isLittleBigConversion<SourceEndianness, TargetEndianness>())
	{
		return byteSwap(v);
	}

	return v;
}