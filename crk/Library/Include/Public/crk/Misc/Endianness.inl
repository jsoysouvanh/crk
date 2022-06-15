/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

constexpr EEndianness Endianness::getNativeEndianness() noexcept
{
	//Get endianness from the standard if possible (C++20+)
#if CRK_CPP20
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

	//Take advantage of the __BYTE_ORDER__ when it is defined (GCC / Clang define it)
#elif defined(__BYTE_ORDER__)
	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		return EEndianness::Little;
	#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		return EEndianness::Big;
	#else
		return EEndianness::Mixed;
	#endif
	
	//Windows runs exclusively on little-endian architectures
#elif defined(_WIN32)
	return EEndianness::Little;

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
	else
	{
		return EEndianness::Mixed;
	}
#endif
}