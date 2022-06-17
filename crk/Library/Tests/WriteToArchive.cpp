#include <string>
#include <filesystem>

#include <gtest/gtest.h>

#include "TestHelpers/EndiannessHelpers.h"

#include "crk/Archives/BinaryArchive.h"

namespace fs = std::filesystem;

/**
*	1st param -> path to output file
*/
int main(int argc, char** argv)
{
	printEndianness();

	crk::OutBinaryArchive<256> archive;

	archive((uint8_t)1, (uint16_t)2, (uint32_t)3, (uint64_t)4, (float)5, (double)6);

	archive.finish();

	std::string outputFile = (argc > 1) ? std::string(argv[1]) : "testOutput.bin";
	archive.saveToFile(outputFile.c_str());
	std::cout << "Saved file: " << fs::absolute(fs::path(outputFile)) << std::endl;

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}