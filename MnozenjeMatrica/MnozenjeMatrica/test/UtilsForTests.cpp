#include "UtilsForTests.h"

#include <fstream>
#include <streambuf>

std::string UtilsForTests::getContentOfFile(const std::string& filePath) noexcept
{
	std::ifstream fileStream(filePath);
	std::string fileContent;

	fileStream.seekg(0, std::ios::end);
	fileContent.reserve((size_t)fileStream.tellg());
	fileStream.seekg(0, std::ios::beg);

	fileContent.assign((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

	return fileContent;
}