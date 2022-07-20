/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <string>
#include <cstdint>

#include <crk/Misc/Endianness.h>
#include <crk/Misc/System.h>

//Data model
#define CRK_TESTS_DATAMODEL						crk::LLP64DataModel

//Boolean
#define CRK_TESTS_ARITHMETIC_DATA_BOOL			true

//Characters
#define CRK_TESTS_ARITHMETIC_DATA_CHAR			(char)'a'
#define CRK_TESTS_ARITHMETIC_DATA_SCHAR			(signed char)'b'
#define CRK_TESTS_ARITHMETIC_DATA_UCHAR			(unsigned char)'c'
//TODO: add char8, char16, char32, wchar_t

//Integers
#define CRK_TESTS_ARITHMETIC_DATA_SHORT			(short)-1
#define CRK_TESTS_ARITHMETIC_DATA_USHORT		(unsigned short)1u
#define CRK_TESTS_ARITHMETIC_DATA_INT			-2
#define CRK_TESTS_ARITHMETIC_DATA_UINT			2u
#define CRK_TESTS_ARITHMETIC_DATA_LONG			3l
#define CRK_TESTS_ARITHMETIC_DATA_ULONG			4ul
#define CRK_TESTS_ARITHMETIC_DATA_LONGLONG		-5ll
#define CRK_TESTS_ARITHMETIC_DATA_ULONGLONG		5ull

//Fixed-width integers
#define CRK_TESTS_ARITHMETIC_DATA_INT8			(int8_t)-127
#define CRK_TESTS_ARITHMETIC_DATA_UINT8			(uint8_t)128
#define CRK_TESTS_ARITHMETIC_DATA_INT16			(int16_t)-512
#define CRK_TESTS_ARITHMETIC_DATA_UINT16		(uint16_t)512
#define CRK_TESTS_ARITHMETIC_DATA_INT32			(int32_t)-1024
#define CRK_TESTS_ARITHMETIC_DATA_UINT32		(uint32_t)1024
#define CRK_TESTS_ARITHMETIC_DATA_INT64			(int64_t)-2048
#define CRK_TESTS_ARITHMETIC_DATA_UINT64		(uint64_t)2048

//Real floating
#define CRK_TESTS_ARITHMETIC_DATA_FLOAT			0.42f
#define CRK_TESTS_ARITHMETIC_DATA_DOUBLE		3.14
#define CRK_TESTS_ARITHMETIC_DATA_LONGDOUBLE	1.61803398875l

namespace crk::tests
{
	static constexpr std::size_t defaultBinArchiveSize = 4096u;

	std::string getEndiannessPrefix(crk::EEndianness archiveEndianness)
	{
		switch (archiveEndianness)
		{
			case crk::EEndianness::Big:
				return "BE";

			case crk::EEndianness::Little:
				return "LE";

			case crk::EEndianness::Mixed:
				return "ME";

			default:
				return "UE";
		}
	}

	std::string getArchiveEndiannessPrefix(crk::EEndianness archiveEndianness)
	{
		return getEndiannessPrefix(archiveEndianness) + "AR"; //AR stands for Archive
	}

	std::string getSystemEndiannessPrefix()
	{
		return getEndiannessPrefix(crk::Endianness::getNativeEndianness()) + "SYS"; //SYS stands for System
	}

	void printSystemBit()
	{
		std::cout << "Current machine is " << crk::System::bits << "-bit." << std::endl;
	}
}