#include <iostream>
#include <type_traits>
#include <typeinfo>

#include <crk/Archives/Binary/FundamentalTypes/IntegerTraits.h>
#include <crk/Archives/Binary/FundamentalTypes/Formats/Integer/IntegerFormatConversions.h>

int main()
{
	static_assert(std::is_same_v<int8_t, crk::IntegerType_t<1, false>>, "Wrong integer type.");
	static_assert(std::is_same_v<uint8_t, crk::IntegerType_t<1, true>>, "Wrong integer type.");
	static_assert(std::is_same_v<int16_t, crk::IntegerType_t<2, false>>, "Wrong integer type.");
	static_assert(std::is_same_v<uint16_t, crk::IntegerType_t<2, true>>, "Wrong integer type.");
	static_assert(std::is_same_v<int32_t, crk::IntegerType_t<4, false>>, "Wrong integer type.");
	static_assert(std::is_same_v<uint32_t, crk::IntegerType_t<4, true>>, "Wrong integer type.");
	static_assert(std::is_same_v<int64_t, crk::IntegerType_t<8, false>>, "Wrong integer type.");
	static_assert(std::is_same_v<uint64_t, crk::IntegerType_t<8, true>>, "Wrong integer type.");

	return EXIT_SUCCESS;
}