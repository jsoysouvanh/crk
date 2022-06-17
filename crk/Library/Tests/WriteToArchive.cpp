#include <string>
#include <filesystem>

#include <gtest/gtest.h>
#include <crk/Archives/Binary/OutBinaryArchive.h>

#include "TestHelpers/EndiannessHelpers.h"

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

	fs::path outputFile = fs::absolute((argc > 1) ? std::string(argv[1]) : "testOutput.bin");

	fs::create_directories(outputFile.parent_path());
	archive.saveToFile(outputFile.string().c_str());
	std::cout << "Saved file: " << outputFile << std::endl;

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}