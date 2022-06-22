#include <string>
#include <filesystem>

//#include <gtest/gtest.h>
#include <crk/Archives/Binary/OutBinaryArchive.h>

#include "TestHelpers/EndiannessHelpers.h"
#include "TestHelpers/DataModelHelpers.h"
#include "TestHelpers/ReadWriteSharedData.h"

namespace fs = std::filesystem;

//Add some tags in the filename depending on the target of the compiled program (endianness, CPU architecture etc..) 
fs::path tagFileName(fs::path const& filepath, crk::EEndianness archiveEndianness)
{
	fs::path result = filepath;

	result.replace_filename(crk::tests::getArchiveEndiannessPrefix(archiveEndianness) + "_" + crk::tests::getSystemEndiannessPrefix() + "_" + filepath.filename().stem().string());

	return result;
}

//=======================================================
//======= OutBinaryArchive::pack(Arithmetic) ============
//=======================================================

template <std::size_t ArchiveSize, crk::EEndianness ArchiveEndianness>
void serializeArithmetic(crk::OutBinaryArchive<ArchiveSize, ArchiveEndianness>& archive)
{
	//Bool
	archive(CRK_TESTS_ARITHMETIC_DATA_BOOL);

	//Chars
	archive(CRK_TESTS_ARITHMETIC_DATA_CHAR, CRK_TESTS_ARITHMETIC_DATA_SCHAR, CRK_TESTS_ARITHMETIC_DATA_UCHAR);

	//Integer
	archive(CRK_TESTS_ARITHMETIC_DATA_SHORT, CRK_TESTS_ARITHMETIC_DATA_USHORT);
	archive(CRK_TESTS_ARITHMETIC_DATA_INT, CRK_TESTS_ARITHMETIC_DATA_UINT);
	archive(CRK_TESTS_ARITHMETIC_DATA_LONG, CRK_TESTS_ARITHMETIC_DATA_ULONG);
	archive(CRK_TESTS_ARITHMETIC_DATA_LONGLONG, CRK_TESTS_ARITHMETIC_DATA_ULONGLONG);

	//Real floating
	archive(CRK_TESTS_ARITHMETIC_DATA_FLOAT, CRK_TESTS_ARITHMETIC_DATA_DOUBLE, CRK_TESTS_ARITHMETIC_DATA_LONGDOUBLE);
}

template <std::size_t ArchiveSize, crk::EEndianness ArchiveEndianness>
void serializeArchiveToFile(fs::path const& filepath)
{
	crk::OutBinaryArchive<ArchiveSize, ArchiveEndianness> archive;

	//Serialize data to archive
	serializeArithmetic(archive);
	//TODO...

	archive.finish();

	//Save archive's binary data to file
	fs::path outputFile = tagFileName(filepath, ArchiveEndianness);

	archive.saveToFile(outputFile.string().c_str());
	std::cout << "Saved file: " << outputFile << std::endl;
}

/**
*	1st param -> path to output file
*/
int main(int argc, char** argv)
{
	printEndianness();
	printArithmeticTypesSize();

	//Create output directory if it doesn't exist yet
	fs::path outputFile = (argc > 1) ? fs::absolute(argv[1]) : fs::current_path() / "OutputDir" / "testOutput";
	fs::create_directories(outputFile.parent_path());

	//Serialize data to file
	serializeArchiveToFile<crk::tests::defaultBinArchiveSize, crk::EEndianness::Little>(outputFile);
	serializeArchiveToFile<crk::tests::defaultBinArchiveSize, crk::EEndianness::Big>(outputFile);

	return EXIT_SUCCESS;
}