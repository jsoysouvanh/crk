#include <gtest/gtest.h>

#include "TestHelpers/EndiannessHelpers.h"

#include "crk/Archives/BinaryArchive.h"

int main(int argc, char** argv)
{
	printEndianness();

	crk::OutBinaryArchive<256> archive;

	archive(1, 2, 3, 4, 5);

	archive.finish();

	archive.saveToFile("binaryTest.bin");


	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}