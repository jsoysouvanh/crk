#include <gtest/gtest.h>

#include "TestHelpers/EndiannessHelpers.h"

#include "crk/Archives/BinaryArchive.h"

int main(int argc, char** argv)
{
	printEndianness();

	crk::OutBinaryArchive<256> archive;

	archive((uint8_t)1, (uint16_t)2, (uint32_t)3, (uint64_t)4, (float)5, (double)6);

	archive.finish();

	archive.saveToFile("binaryTest.bin");


	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}