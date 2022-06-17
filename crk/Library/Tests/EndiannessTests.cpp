#include <gtest/gtest.h>

#include "TestHelpers/EndiannessHelpers.h"

//It's complicated to test getNativeEndianness, so skip this test

//=======================================================
//============= Endianness::convert(bool) ===============
//=======================================================

TEST(Endianness_convert_bool, Generic)
{
	//bool size is implementation defined so it's complicated to test
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((bool)0x01)), (bool)0x01);
}

//=======================================================
//============= Endianness::convert(char) ===============
//=======================================================

TEST(Endianness_convert_char, One)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((char)0x01)), (char)0x01);
}

TEST(Endianness_convert_char, Zero)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((char)0)), (char)0);
}

//=======================================================
//=========== Endianness::convert(int16_t) ==============
//=======================================================

TEST(Endianness_convert_int16, Negative)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int16_t)0x8001)), (int16_t)0x0180);
}

TEST(Endianness_convert_int16, Negative_Max)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int16_t)0xFFFF)), (int16_t)0xFFFF);
}

TEST(Endianness_convert_int16, Positive)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int16_t)0x0001)), (int16_t)0x0100);
}

TEST(Endianness_convert_int16, Positive_Max)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int16_t)0x7FFF)), (int16_t)0xFF7F);
}

TEST(Endianness_convert_int16, Zero)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int16_t)0)), (int16_t)0);
}

//=======================================================
//=========== Endianness::convert(uint16_t) =============
//=======================================================

TEST(Endianness_convert_uint16, Positive)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint16_t)0x0001)), (uint16_t)0x0100);
}

TEST(Endianness_convert_uint16, Positive_Max)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint16_t)0xFFFF)), (uint16_t)0xFFFF);
}

TEST(Endianness_convert_uint16, zero)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint16_t)0)), (uint16_t)0);
}

//=======================================================
//=========== Endianness::convert(int32_t) ==============
//=======================================================

TEST(Endianness_convert_int32, Negative)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int32_t)0x80000001)), (int32_t)0x01000080);
}

TEST(Endianness_convert_int32, Negative_Max)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int32_t)0xFFFFFFFF)), (int32_t)0xFFFFFFFF);
}

TEST(Endianness_convert_int32, Positive)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int32_t)0x00000001)), (int32_t)0x01000000);
}

TEST(Endianness_convert_int32, Positive_Max)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int32_t)0x7FFFFFFF)), (int32_t)0xFFFFFF7F);
}

TEST(Endianness_convert_int32, Zero)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int32_t)0)), (int32_t)0);
}

//=======================================================
//=========== Endianness::convert(uint32_t) =============
//=======================================================

TEST(Endianness_convert_uint32, Positive)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint32_t)0x00000001)), (uint32_t)0x01000000);
}

TEST(Endianness_convert_uint32, Positive_Max)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint32_t)0xFFFFFFFF)), (uint32_t)0xFFFFFFFF);
}

TEST(Endianness_convert_uint32, Zero)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint32_t)0)), (uint32_t)0);
}

//=======================================================
//========== Endianness::convert(int64_t) ==============
//=======================================================

TEST(Endianness_convert_int64, Negative)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int64_t)0x8000000000000001)), (int64_t)0x0100000000000080);
}

TEST(Endianness_convert_int64, Negative_Max)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int64_t)0xFFFFFFFFFFFFFFFF)), (int64_t)0xFFFFFFFFFFFFFFFF);
}

TEST(Endianness_convert_int64, Positive)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int64_t)0x0000000000000001)), (int64_t)0x0100000000000000);
}

TEST(Endianness_convert_int64, Positive_Max)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int64_t)0x7FFFFFFFFFFFFFFF)), (int64_t)0xFFFFFFFFFFFFFF7F);
}

TEST(Endianness_convert_int64, Zero)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int64_t)0)), (int64_t)0);
}

//=======================================================
//========== Endianness::convert(uint64_t) ==============
//=======================================================

TEST(Endianness_convert_uint64, Positive)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint64_t)0x0000000000000001)), (uint64_t)0x0100000000000000);
}

TEST(Endianness_convert_uint64, Positive_Max)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint64_t)0xFFFFFFFFFFFFFFFF)), (uint64_t)0xFFFFFFFFFFFFFFFF);
}

TEST(Endianness_convert_uint64, Zero)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint64_t)0)), (uint64_t)0);
}

//=======================================================
//============ Endianness::convert(float) ===============
//=======================================================

TEST(Endianness_convert_float, Generic)
{
	int32_t asInt = 0xAABBCCDD;
	float f = *reinterpret_cast<float*>(&asInt);

	int32_t asInt2 = 0xDDCCBBAA;
	float f2 = *reinterpret_cast<float*>(&asInt2);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>(f)), f2);
}

//=======================================================
//============ Endianness::convert(double) ==============
//=======================================================

TEST(Endianness_convert_double, Generic)
{
	int64_t asInt = 0x0011223344556677;
	double d = *reinterpret_cast<double*>(&asInt);

	int64_t asInt2 = 0x7766554433221100;
	double d2 = *reinterpret_cast<double*>(&asInt2);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>(d)), d2);
}

//TODO: Add tests for long double / int128

int main(int argc, char** argv)
{
	printEndianness();

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}