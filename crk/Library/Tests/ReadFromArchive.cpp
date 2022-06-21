#include <filesystem>

//#include <gtest/gtest.h>
#include <crk/Archives/Binary/InBinaryArchive.h>

#include "TestHelpers/EndiannessHelpers.h"

namespace fs = std::filesystem;

void deserializeAndPrintContent(char const* filePath)
{
	//Load the content of the file in a binary archive
	crk::InBinaryArchive<256> archive;
	archive.loadFromFile(filePath);

	uint8_t int1;
	uint16_t int2;
	uint32_t int3;
	uint64_t int4;
	float float1;
	double double1;

	//Deserialize values
	archive(int1, int2, int3, int4, float1, double1);

	//Print values
	std::cout << (int)int1 << ", " << int2 << ", " << int3 << ", " << int4 << ", " << float1 << ", " << double1 << std::endl;
}

int main(int argc, char** argv)
{
	printEndianness();

	fs::path dirContainingSerializedFiles = (argc > 1) ? fs::absolute(argv[1]) : fs::current_path() / "OutputDir";

	//Make sure the input directory exists
	if (fs::exists(dirContainingSerializedFiles) && fs::is_directory(dirContainingSerializedFiles))
	{
		std::cout << "Read from directory: " << dirContainingSerializedFiles << std::endl;

		//Iterate over each file of the directory
		for (auto const& dir_entry : fs::directory_iterator(dirContainingSerializedFiles))
		{
			std::cout << "Entry: " << dir_entry.path() << std::endl;

			deserializeAndPrintContent(dir_entry.path().string().c_str());
		}
	}

	return EXIT_SUCCESS;
}