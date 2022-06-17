#include <filesystem>

#include <gtest/gtest.h>

#include "TestHelpers/EndiannessHelpers.h"

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	printEndianness();

	if (argc > 1)
	{
		fs::path dir = fs::absolute(argv[1]);

		if (fs::exists(dir) && fs::is_directory(dir))
		{
			std::cout << "Read from directory: " << dir << std::endl;

			for (auto const& dir_entry : fs::directory_iterator(dir))
			{
				std::cout << "Entry: " << dir_entry.path() << std::endl;
			}
		}
	}

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}