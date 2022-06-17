#include <filesystem>

#include <gtest/gtest.h>
#include <crk/Archives/Binary/InBinaryArchive.h>

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

				crk::InBinaryArchive<256> archive;
				archive.loadFromFile(dir_entry.path().string().c_str());

				uint8_t int1;
				uint16_t int2;
				uint32_t int3;
				uint64_t int4;
				float float1;
				double double1;

				archive(int1, int2, int3, int4, float1, double1);

				std::cout << (int)int1 << ", " << int2 << ", " << int3 << ", " << int4 << ", " << float1 << ", " << double1 << std::endl;
			}
		}
	}

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}