#include <filesystem>
#include <unordered_map>

#include <gtest/gtest.h>
#include <crk/Archives/Binary/InBinaryArchive.h>

#include "TestHelpers/EndiannessHelpers.h"
#include "TestHelpers/ReadWriteSharedData.h"

namespace fs = std::filesystem;

namespace crk::tests
{
	class Environment : public testing::Environment
	{
		private:
			fs::path _serializedDataDir;

			std::unordered_map<std::string, crk::InBinaryArchive<crk::tests::defaultBinArchiveSize, crk::EEndianness::Little>>	_littleEndianFiles;
			std::unordered_map<std::string, crk::InBinaryArchive<crk::tests::defaultBinArchiveSize, crk::EEndianness::Big>>		_bigEndianFiles;
			std::unordered_map<std::string, crk::InBinaryArchive<crk::tests::defaultBinArchiveSize, crk::EEndianness::Mixed>>	_mixedEndianFiles;

		public:
			Environment(fs::path const& serializedDataDirectory) noexcept:
				_serializedDataDir(serializedDataDirectory)
			{
				printEndianness();
			}

			void SetUp() override
			{
				ASSERT_TRUE(fs::exists(_serializedDataDir) && fs::is_directory(_serializedDataDir));

				//Fill archive vectors
				for (auto const& dir_entry : fs::directory_iterator(_serializedDataDir))
				{
					if (dir_entry.path().filename().string().find(crk::tests::getArchiveEndiannessPrefix(crk::EEndianness::Big)) != std::string::npos) //Big endian
					{
						_bigEndianFiles.emplace(dir_entry.path().string(), crk::InBinaryArchive<crk::tests::defaultBinArchiveSize, crk::EEndianness::Big>()).first->second.loadFromFile(dir_entry.path().string().c_str());
					}
					else if (dir_entry.path().filename().string().find(crk::tests::getArchiveEndiannessPrefix(crk::EEndianness::Little)) != std::string::npos) //Little endian
					{
						_littleEndianFiles.emplace(dir_entry.path().string(), crk::InBinaryArchive<crk::tests::defaultBinArchiveSize, crk::EEndianness::Little>()).first->second.loadFromFile(dir_entry.path().string().c_str());
					}
					else if (dir_entry.path().filename().string().find(crk::tests::getArchiveEndiannessPrefix(crk::EEndianness::Mixed)) != std::string::npos) //Mixed endian
					{
						_mixedEndianFiles.emplace(dir_entry.path().string(), crk::InBinaryArchive<crk::tests::defaultBinArchiveSize, crk::EEndianness::Mixed>()).first->second.loadFromFile(dir_entry.path().string().c_str());
					}
					else
					{
						continue;
					}
				}

				GTEST_LOG_(INFO) << "Discovered " << _bigEndianFiles.size() << " big endian files.";
				GTEST_LOG_(INFO) << "Discovered " << _littleEndianFiles.size() << " little endian files.";
				GTEST_LOG_(INFO) << "Discovered " << _mixedEndianFiles.size() << " mixed endian files.";
			}

			auto& getLEArchives() noexcept
			{
				return _littleEndianFiles;
			}

			auto& getBEArchives() noexcept
			{
				return _bigEndianFiles;
			}

			auto& getMEArchives() noexcept
			{
				return _mixedEndianFiles;
			}
	};
}

crk::tests::Environment* environment = nullptr;

#define CRK_TESTS_UNPACK_NEXT_DATA(dataType, expectedValue)			\
	TEST(InBinaryArchive_unpack_##dataType, FromBigEndian)			\
	{																\
		for (auto& archive : environment->getBEArchives())			\
		{															\
			dataType readData;										\
																	\
			archive.second.unpack(readData);						\
																	\
			EXPECT_EQ(readData, expectedValue) << archive.first;	\
		}															\
	}																\
																	\
	TEST(InBinaryArchive_unpack_##dataType, FromLittleEndian)		\
	{																\
		for (auto& archive : environment->getLEArchives())			\
		{															\
			dataType readData;										\
																	\
			archive.second.unpack(readData);						\
																	\
			EXPECT_EQ(readData, expectedValue) << archive.first;	\
		}															\
	}																\
																
	//TEST(InBinaryArchive_unpack_##dataType, FromMixedEndian)	\
	//{															\
	//	for (auto& archive : environment->getMEArchives())		\
	//	{														\
	//		dataType readData;									\
	//															\
	//		archive.second.unpack(readData);					\
	//															\
	//		EXPECT_EQ(readData, expectedValue);					\
	//	}														\
	//}

//=======================================================
//======== InBinaryArchive::unpack(bool types) ==========
//=======================================================

CRK_TESTS_UNPACK_NEXT_DATA(bool, CRK_TESTS_ARITHMETIC_DATA_BOOL)

//=======================================================
//======== InBinaryArchive::unpack(char types) ==========
//=======================================================

//Alias to avoid space in typename
using schar = signed char;
using uchar = unsigned char;

CRK_TESTS_UNPACK_NEXT_DATA(char, CRK_TESTS_ARITHMETIC_DATA_CHAR)
CRK_TESTS_UNPACK_NEXT_DATA(schar, CRK_TESTS_ARITHMETIC_DATA_SCHAR)
CRK_TESTS_UNPACK_NEXT_DATA(uchar, CRK_TESTS_ARITHMETIC_DATA_UCHAR)

//=======================================================
//======== InBinaryArchive::unpack(int types) ===========
//=======================================================

//Alias to avoid space in typename
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using longlong = long long;
using ulonglong = unsigned long long;

CRK_TESTS_UNPACK_NEXT_DATA(short, CRK_TESTS_ARITHMETIC_DATA_SHORT)
CRK_TESTS_UNPACK_NEXT_DATA(ushort, CRK_TESTS_ARITHMETIC_DATA_USHORT)
CRK_TESTS_UNPACK_NEXT_DATA(int, CRK_TESTS_ARITHMETIC_DATA_INT)
CRK_TESTS_UNPACK_NEXT_DATA(uint, CRK_TESTS_ARITHMETIC_DATA_UINT)
CRK_TESTS_UNPACK_NEXT_DATA(long, CRK_TESTS_ARITHMETIC_DATA_LONG)
CRK_TESTS_UNPACK_NEXT_DATA(ulong, CRK_TESTS_ARITHMETIC_DATA_ULONG)
CRK_TESTS_UNPACK_NEXT_DATA(longlong, CRK_TESTS_ARITHMETIC_DATA_LONGLONG)
CRK_TESTS_UNPACK_NEXT_DATA(ulonglong, CRK_TESTS_ARITHMETIC_DATA_ULONGLONG)

//=======================================================
//======= InBinaryArchive::unpack(floating types) =======
//=======================================================

//Alias to avoid space in typename
using longdouble = long double;

CRK_TESTS_UNPACK_NEXT_DATA(float, CRK_TESTS_ARITHMETIC_DATA_FLOAT)
CRK_TESTS_UNPACK_NEXT_DATA(double, CRK_TESTS_ARITHMETIC_DATA_DOUBLE)
CRK_TESTS_UNPACK_NEXT_DATA(longdouble, CRK_TESTS_ARITHMETIC_DATA_LONGDOUBLE)

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	environment = new crk::tests::Environment((argc > 1) ? fs::absolute(argv[1]) : fs::current_path() / "OutputDir");
	testing::AddGlobalTestEnvironment(environment);

	return RUN_ALL_TESTS();
}