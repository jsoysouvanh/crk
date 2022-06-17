#include <filesystem>

#include <gtest/gtest.h>

#include "TestHelpers/EndiannessHelpers.h"

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	printEndianness();

	if (argc > 1)
	{
		std::cout << "Read from directory: " << fs::absolute(argv[1]) << std::endl;

		for (auto const& dir_entry : std::filesystem::directory_iterator(argv[1]))
		{
			std::cout << "Entry: " << dir_entry << std::endl;
		}
	}

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}