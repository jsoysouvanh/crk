#include <iostream>

#include "Misc/Endianness.h"

int main()
{
	if constexpr (crk::getNativeEndianness() == crk::EEndianness::Little)
		std::cout << "Little endian" << std::endl;
	else if constexpr (crk::getNativeEndianness() == crk::EEndianness::Big)
		std::cout << "Big endian" << std::endl;
	else if constexpr (crk::getNativeEndianness() == crk::EEndianness::Mixed)
		std::cout << "Mixed endian" << std::endl;

#if defined(_MSC_VER)
	std::cout << "MSVC version: " << _MSC_VER << std::endl;
#endif

	return EXIT_SUCCESS;
}