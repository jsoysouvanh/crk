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

	return EXIT_SUCCESS;
}