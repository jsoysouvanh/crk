#include <gtest/gtest.h>

#include <cstring>	//std::memcpy, std::memcmp
#include <array>
#include <iostream>
#include <iomanip>	//std::setfill, std::setw
#include <ios>		//std::hex, std::dec

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

//--- Debug

template <typename T>
class HexaPrintWrapper
{
	private:
		T const& _wrappedValue;

	public:
		HexaPrintWrapper(T const& value):
			_wrappedValue{ value }
		{}

		T const& getWrappedValue() const noexcept
		{
			return _wrappedValue;
		}
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, HexaPrintWrapper<T> const& wrapper) noexcept
{
	std::byte const* bytes = reinterpret_cast<std::byte const*>(&wrapper.getWrappedValue());

	for (int i = 0; i < sizeof(T); ++i)
		stream << std::hex << std::setfill('0') << std::setw(2) << (int)bytes[i] << " ";

	stream << std::dec;

	return stream;
}

//----

#define INSTANTIATE_ENDIANNESS_CONVERT_TEST(type, fromEndianness, toEndianness, fromValue, expectedValue)															\
	TEST_F(type##EndiannessConversion, fromEndianness##To##toEndianness)																							\
	{																																								\
		EXPECT_TRUE(equalBinary(crk::Endianness::convert<crk::EEndianness::fromEndianness, crk::EEndianness::toEndianness>(fromValue), expectedValue)) <<			\
			HexaPrintWrapper(fromValue) << " <- From" << std::endl <<																								\
			HexaPrintWrapper(crk::Endianness::convert<crk::EEndianness::fromEndianness, crk::EEndianness::toEndianness>(fromValue)) << "<- Result" << std::endl <<	\
			HexaPrintWrapper(expectedValue) << " <- Expected" << std::endl;																							\
	}

#define INSTANTIATE_ENDIANNESS_CONVERTREF_TEST(type, fromEndianness, toEndianness, fromValue, expectedValue)			\
	TEST_F(type##EndiannessConversionRef, fromEndianness##To##toEndianness)												\
	{																													\
		type fromValueCopy;																								\
		std::memcpy(&fromValueCopy, &fromValue, sizeof(type));															\
		crk::Endianness::convertRef<crk::EEndianness::fromEndianness, crk::EEndianness::toEndianness>(fromValueCopy);	\
																														\
		EXPECT_TRUE(equalBinary(fromValueCopy, expectedValue)) <<														\
			HexaPrintWrapper(fromValue) << " <- From" << std::endl <<													\
			HexaPrintWrapper(fromValueCopy) << "<- Result" << std::endl <<												\
			HexaPrintWrapper(expectedValue) << " <- Expected" << std::endl;												\
	}


#define INSTANTIATE_ENDIANNESS_TESTS_FOR_TYPE(type)																								\
	class type##EndiannessConversion : public FundamentalTypeEndiannessConversion<type> {};														\
																																				\
	INSTANTIATE_ENDIANNESS_CONVERT_TEST(type, Little, Big, data, dataReversed)																	\
	INSTANTIATE_ENDIANNESS_CONVERT_TEST(type, Big, Little, data, dataReversed)																	\
	INSTANTIATE_ENDIANNESS_CONVERT_TEST(type, Big, Big, data, data)																				\
	INSTANTIATE_ENDIANNESS_CONVERT_TEST(type, Little, Little, data, data)

#define INSTANTIATE_ENDIANNESS_TESTS_FOR_FLOATING_TYPE(type)																					\
	class type##EndiannessConversionRef : public FundamentalTypeEndiannessConversion<type> {};													\
																																				\
	INSTANTIATE_ENDIANNESS_CONVERTREF_TEST(type, Little, Big, data, dataReversed)																\
	INSTANTIATE_ENDIANNESS_CONVERTREF_TEST(type, Big, Little, data, dataReversed)																\
	INSTANTIATE_ENDIANNESS_CONVERTREF_TEST(type, Big, Big, data, data)																			\
	INSTANTIATE_ENDIANNESS_CONVERTREF_TEST(type, Little, Little, data, data)

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

INSTANTIATE_ENDIANNESS_TESTS_FOR_FLOATING_TYPE(float)
INSTANTIATE_ENDIANNESS_TESTS_FOR_FLOATING_TYPE(double)
INSTANTIATE_ENDIANNESS_TESTS_FOR_FLOATING_TYPE(longdouble)

int main(int argc, char** argv)
{
	crk::tests::printEndianness();

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}