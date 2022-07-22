#include <gtest/gtest.h>

#include <cstring>	//std::memcpy, std::memcmp
#include <array>

#include "TestHelpers/EndiannessHelpers.h"

//It's complicated to test getNativeEndianness, so skip this test

constexpr std::array<std::byte, 32> const byteArray =
{
	std::byte{0x00}, std::byte{0x01}, std::byte{0x02}, std::byte{0x03},
	std::byte{0x04}, std::byte{0x05}, std::byte{0x06}, std::byte{0x07},
	std::byte{0x08}, std::byte{0x09}, std::byte{0x0A}, std::byte{0x0B},
	std::byte{0x0C}, std::byte{0x0D}, std::byte{0x0E}, std::byte{0x0F},
	std::byte{0x10}, std::byte{0x11}, std::byte{0x12}, std::byte{0x13},
	std::byte{0x14}, std::byte{0x15}, std::byte{0x16}, std::byte{0x17},
	std::byte{0x18}, std::byte{0x19}, std::byte{0x1A}, std::byte{0x1B},
	std::byte{0x1C}, std::byte{0x1D}, std::byte{0x1E}, std::byte{0x1F}
};

constexpr std::array<std::byte, 32> const byteArrayReversed = 
{
	std::byte{0x1F}, std::byte{0x1E}, std::byte{0x1D}, std::byte{0x1C},
	std::byte{0x1B}, std::byte{0x1A}, std::byte{0x19}, std::byte{0x18},
	std::byte{0x17}, std::byte{0x16}, std::byte{0x15}, std::byte{0x14},
	std::byte{0x13}, std::byte{0x12}, std::byte{0x11}, std::byte{0x10},
	std::byte{0x0F}, std::byte{0x0E}, std::byte{0x0D}, std::byte{0x0C},
	std::byte{0x0B}, std::byte{0x0A}, std::byte{0x09}, std::byte{0x08},
	std::byte{0x07}, std::byte{0x06}, std::byte{0x05}, std::byte{0x04},
	std::byte{0x03}, std::byte{0x02}, std::byte{0x01}, std::byte{0x00}
};

template <typename T>
void initData(T* data)
{
	static_assert(sizeof(T) <= byteArray.size(), "T is bigger than the reference array, must increase byteArray size.");

	std::memcpy(data, byteArray.data(), sizeof(T));
}

template <typename T>
void initReversedData(T* data)
{
	static_assert(sizeof(T) <= byteArrayReversed.size(), "T is bigger than the reference array, must increase byteArrayReversed size.");

	std::memcpy(data, &byteArrayReversed[byteArrayReversed.size() - sizeof(T)], sizeof(T));
}

template <typename T>
bool equalBinary(T const& d1, T const& d2) noexcept
{
	return std::memcmp(&d1, &d2, sizeof(T)) == 0;
}

template <typename T>
class FundamentalTypeEndiannessConversion : public ::testing::Test
{
	protected:
		T data;
		T dataReversed;

		virtual void SetUp() override
		{
			initData(&data);
			initReversedData(&dataReversed);
		}
};

#define INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(type)																					\
	class type##EndiannessConversion : public FundamentalTypeEndiannessConversion<type> {};											\
																																	\
	TEST_F(type##EndiannessConversion, LittleToBig)																					\
	{																																\
		EXPECT_TRUE(equalBinary(crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>(data), dataReversed));	\
	}																																\
																																	\
	TEST_F(type##EndiannessConversion, BigToLittle)																					\
	{																																\
		EXPECT_TRUE(equalBinary(crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>(data), dataReversed));	\
	}																																\
																																	\
	TEST_F(type##EndiannessConversion, BigToBig)																					\
	{																																\
		EXPECT_TRUE(equalBinary(crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>(data), data));				\
	}																																\
																																	\
	TEST_F(type##EndiannessConversion, LittleToLittle)																				\
	{																																\
		EXPECT_TRUE(equalBinary(crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>(data), data));			\
	}																																\

//=======================================================
//=========== Endianness::convert(boolean) ==============
//=======================================================

INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(bool)

//=======================================================
//========== Endianness::convert(character) =============
//=======================================================

using schar = signed char;
using uchar = unsigned char;

INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(char)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(schar)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(uchar)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(char8_t)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(char16_t)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(char32_t)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(wchar_t)

//=======================================================
//=========== Endianness::convert(integer) ==============
//=======================================================

using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using longlong = long long;
using ulonglong = unsigned long long;

INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(short)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(ushort)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(int)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(uint)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(long)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(ulong)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(longlong)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(ulonglong)

//=======================================================
//======== Endianness::convert(floating-point) ==========
//=======================================================

using longdouble = long double;

INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(float)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(double)
INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(longdouble)

int main(int argc, char** argv)
{
	crk::tests::printEndianness();

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}