#include <gtest/gtest.h>

#include "TestHelpers/EndiannessHelpers.h"

//It's complicated to test getNativeEndianness, so skip this test

//=======================================================
//============= Endianness::convert(bool) ===============
//=======================================================

TEST(Endianness_convert_bool, LittleToBig)
{
	//bool size is implementation defined so it's complicated to test, but consider sizeof(bool) == 1 for this test
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((bool)0x01)), (bool)0x01);
}

TEST(Endianness_convert_bool, BigToLittle)
{
	//bool size is implementation defined so it's complicated to test, but consider sizeof(bool) == 1 for this test
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>((bool)0x01)), (bool)0x01);
}

TEST(Endianness_convert_bool, BigToBig)
{
	//bool size is implementation defined so it's complicated to test, but consider sizeof(bool) == 1 for this test
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>((bool)0x01)), (bool)0x01);
}

TEST(Endianness_convert_bool, LittleToLittle)
{
	//bool size is implementation defined so it's complicated to test, but consider sizeof(bool) == 1 for this test
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>((bool)0x01)), (bool)0x01);
}

//=======================================================
//============= Endianness::convert(char) ===============
//=======================================================

TEST(Endianness_convert_char, LittleToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((char)0x01)), (char)0x01);
}

TEST(Endianness_convert_char, BigToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>((char)0x01)), (char)0x01);
}

TEST(Endianness_convert_char, BigToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>((char)0x01)), (char)0x01);
}

TEST(Endianness_convert_char, LittleToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>((char)0x01)), (char)0x01);
}

//=======================================================
//=========== Endianness::convert(int16_t) ==============
//=======================================================

TEST(Endianness_convert_int16, LittleToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int16_t)0x0123)), (int16_t)0x2301);
}

TEST(Endianness_convert_int16, BigToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>((int16_t)0x0123)), (int16_t)0x2301);
}

TEST(Endianness_convert_int16, BigToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>((int16_t)0x0123)), (int16_t)0x0123);
}

TEST(Endianness_convert_int16, LittleToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>((int16_t)0x0123)), (int16_t)0x0123);
}

//=======================================================
//=========== Endianness::convert(uint16_t) =============
//=======================================================

TEST(Endianness_convert_uint16, LittleToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint16_t)0x0123)), (uint16_t)0x2301);
}

TEST(Endianness_convert_uint16, BigToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>((uint16_t)0x0123)), (uint16_t)0x2301);
}

TEST(Endianness_convert_uint16, BigToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>((uint16_t)0x0123)), (uint16_t)0x0123);
}

TEST(Endianness_convert_uint16, LittleToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>((uint16_t)0x0123)), (uint16_t)0x0123);
}

//=======================================================
//=========== Endianness::convert(int32_t) ==============
//=======================================================

TEST(Endianness_convert_int32, LittleToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int32_t)0x01234567)), (int32_t)0x67452301);
}

TEST(Endianness_convert_int32, BigToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>((int32_t)0x01234567)), (int32_t)0x67452301);
}

TEST(Endianness_convert_int32, BigToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>((int32_t)0x01234567)), (int32_t)0x01234567);
}

TEST(Endianness_convert_int32, LittleToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>((int32_t)0x01234567)), (int32_t)0x01234567);
}

//=======================================================
//=========== Endianness::convert(uint32_t) =============
//=======================================================

TEST(Endianness_convert_uint32, LittleToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint32_t)0x01234567)), (uint32_t)0x67452301);
}

TEST(Endianness_convert_uint32, BigToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint32_t)0x01234567)), (uint32_t)0x67452301);
}

TEST(Endianness_convert_uint32, BigToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>((uint32_t)0x01234567)), (uint32_t)0x01234567);
}

TEST(Endianness_convert_uint32, LittleToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>((int32_t)0x01234567)), (int32_t)0x01234567);
}

//=======================================================
//========== Endianness::convert(int64_t) ==============
//=======================================================

TEST(Endianness_convert_int64, LittleToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((int64_t)0x0123456789ABCDEF)), (int64_t)0xEFCDAB8967452301);
}

TEST(Endianness_convert_int64, BigToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>((int64_t)0x0123456789ABCDEF)), (int64_t)0xEFCDAB8967452301);
}

TEST(Endianness_convert_int64, BigToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>((int64_t)0x0123456789ABCDEF)), (int64_t)0x0123456789ABCDEF);
}

TEST(Endianness_convert_int64, LittleToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>((int64_t)0x0123456789ABCDEF)), (int64_t)0x0123456789ABCDEF);
}

//=======================================================
//========== Endianness::convert(uint64_t) ==============
//=======================================================

TEST(Endianness_convert_uint64, LittleToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>((uint64_t)0x0123456789ABCDEF)), (uint64_t)0xEFCDAB8967452301);
}

TEST(Endianness_convert_uint64, BigToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>((uint64_t)0x0123456789ABCDEF)), (uint64_t)0xEFCDAB8967452301);
}

TEST(Endianness_convert_uint64, BigToBig)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>((uint64_t)0x0123456789ABCDEF)), (uint64_t)0x0123456789ABCDEF);
}

TEST(Endianness_convert_uint64, LittleToLittle)
{
	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>((int64_t)0x0123456789ABCDEF)), (int64_t)0x0123456789ABCDEF);
}

//=======================================================
//============ Endianness::convert(float) ===============
//=======================================================

TEST(Endianness_convert_float, LittleToBig)
{
	int32_t asInt = 0x01234567;
	float f = *reinterpret_cast<float*>(&asInt);

	int32_t asInt2 = 0x67452301;
	float f2 = *reinterpret_cast<float*>(&asInt2);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>(f)), f2);
}

TEST(Endianness_convert_float, BigToLittle)
{
	int32_t asInt = 0x01234567;
	float f = *reinterpret_cast<float*>(&asInt);

	int32_t asInt2 = 0x67452301;
	float f2 = *reinterpret_cast<float*>(&asInt2);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>(f)), f2);
}

TEST(Endianness_convert_float, BigToBig)
{
	int32_t asInt = 0x01234567;
	float f = *reinterpret_cast<float*>(&asInt);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>(f)), f);
}

TEST(Endianness_convert_float, LittleToLittle)
{
	int32_t asInt = 0x01234567;
	float f = *reinterpret_cast<float*>(&asInt);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>(f)), f);
}

//=======================================================
//============ Endianness::convert(double) ==============
//=======================================================

TEST(Endianness_convert_double, LittleToBig)
{
	int64_t asInt = 0x0123456789ABCDEF;
	double d = *reinterpret_cast<double*>(&asInt);

	int64_t asInt2 = 0xEFCDAB8967452301;
	double d2 = *reinterpret_cast<double*>(&asInt2);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Big>(d)), d2);
}

TEST(Endianness_convert_double, BigToLittle)
{
	int64_t asInt = 0x0123456789ABCDEF;
	double d = *reinterpret_cast<double*>(&asInt);

	int64_t asInt2 = 0xEFCDAB8967452301;
	double d2 = *reinterpret_cast<double*>(&asInt2);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Little>(d)), d2);
}

TEST(Endianness_convert_double, BigToBig)
{
	int64_t asInt = 0x0123456789ABCDEF;
	double d = *reinterpret_cast<double*>(&asInt);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Big, crk::EEndianness::Big>(d)), d);
}

TEST(Endianness_convert_double, LittleToLittle)
{
	int64_t asInt = 0x0123456789ABCDEF;
	double d = *reinterpret_cast<double*>(&asInt);

	int64_t asInt2 = 0xEFCDAB8967452301;
	double d2 = *reinterpret_cast<double*>(&asInt2);

	EXPECT_EQ((crk::Endianness::convert<crk::EEndianness::Little, crk::EEndianness::Little>(d)), d);
}

//=======================================================
//========== Endianness::convert(long double) ===========
//=======================================================

//TEST(Endianness_convert_longdouble, LittleToBig)
//{
//}

//TEST(Endianness_convert_longdouble, BigToLittle)
//{
//}
//
//TEST(Endianness_convert_longdouble, BigToBig)
//{
//}
//
//TEST(Endianness_convert_longdouble, LittleToLittle)
//{
//}

int main(int argc, char** argv)
{
	crk::tests::printEndianness();

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}