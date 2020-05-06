#include "MatrixReader.h"

#include "MatrixRow.h"

#include <iostream> // remove

MatrixReader& MatrixReader::operator>>(Matrix& m)
{
	std::lock_guard<decltype(lockForFileAccess)> lockGuard(lockForFileAccess);

	readMatrixHeader(m);
	readMatrixBody(m);

	if (!fileStream.good())
	{
		std::cout << "GRESKA\n";
	}
	return *this;
}

void MatrixReader::readMatrixHeader(Matrix& m)
{
	char randomFormatCharFromFile;
	size_t numberOfRows;
	size_t numberOfColumns;

	fileStream >> randomFormatCharFromFile >> numberOfRows >> randomFormatCharFromFile >> numberOfRows >> randomFormatCharFromFile;

	if (!fileStream.good())
	{
		std::cout << "LOSE?\n";
	}
}

void MatrixReader::readMatrixBody(Matrix& m)
{
	int value;
	for (size_t i = 0; i < 900; i++)
	{
		fileStream >> value;
		//std::cout << value << '\n';
	}

	char c;
	fileStream >> c;
	if (c == ';')
	{
		std::cout << "DOBRO JE\n";
	}
}