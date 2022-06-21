#include <string>
#include <filesystem>

//#include <gtest/gtest.h>
#include <crk/Archives/Binary/OutBinaryArchive.h>

#include "TestHelpers/EndiannessHelpers.h"

namespace fs = std::filesystem;

void serializeToFile(char const* filePath)
{
	crk::OutBinaryArchive<256> archive;

	//Serialize data to archive
	archive((uint8_t)1, (uint16_t)2, (uint32_t)3, (uint64_t)4, (float)5, (double)6);
	archive.finish();

	//Save archive's binary data to file
	archive.saveToFile(filePath);
}

/**
*	1st param -> path to output file
*/
int main(int argc, char** argv)
{
	printEndianness();

	//Create output directory if it doesn't exist yet
	fs::path outputFile = (argc > 1) ? fs::absolute(argv[1]) : fs::current_path() / "OutputDir" / "testOutput.bin";
	fs::create_directories(outputFile.parent_path());

	//Serialize data to file
	serializeToFile(outputFile.string().c_str());
	std::cout << "Saved file: " << outputFile << std::endl;

	return EXIT_SUCCESS;
}