#include "MatrixReader.h"

#include <algorithm>

#include "MatrixExceptions.h"
#include "MatrixRow.h"

MatrixReader::MatrixReader(const std::string& filePath) noexcept(false)
{
	open(filePath);
}

MatrixReader& MatrixReader::operator>>(Matrix& m) noexcept(false)
{
	std::lock_guard<decltype(lockForFileAccess)> lockGuard(lockForFileAccess);

	readMatrixFromFile();

	m = std::move(matrixFromFile);

	return *this;
}

void MatrixReader::readMatrixFromFile() noexcept(false)
{
	readMatrixHeader();
	throwIfMatrixFormatInFileIsBad();
	createMatrixWithReadDimensionsFromFile();

	readMatrixBody();
	throwIfMatrixFormatInFileIsBad();

	readEndOfFormatCharacter();
	throwIfMatrixFormatInFileIsBad();
}

void MatrixReader::readMatrixHeader() noexcept
{
	char randomFormatCharFromFile;

	fileStream >> randomFormatCharFromFile >> Dimensions.numberOfRows >> randomFormatCharFromFile >> Dimensions.numberOfColumns >> randomFormatCharFromFile;
}

void MatrixReader::throwIfMatrixFormatInFileIsBad() noexcept(false)
{
	if (const bool somethingBadHappenedWhileReading = !fileStream.good(); somethingBadHappenedWhileReading)
	{
		throw BadMatrixFormatInFile("File contains matrix with bad format!");
	}
}

void MatrixReader::createMatrixWithReadDimensionsFromFile() noexcept
{
	Matrix m(Dimensions.numberOfRows, Dimensions.numberOfColumns);
	matrixFromFile = std::move(m);
}

void MatrixReader::readMatrixBody() noexcept
{
	int matrixElement;

	for (size_t i = 0; i < Dimensions.numberOfRows; ++i)
	{
		for (size_t j = 0; j < Dimensions.numberOfColumns; ++j)
		{
			fileStream >> matrixElement;

			matrixFromFile[i][j] = matrixElement;
		}
	}
}

void MatrixReader::readEndOfFormatCharacter() noexcept
{
	char characterFromFile;

	fileStream >> characterFromFile;

	if (const bool readCharIsNotEndOfFormatChar = characterFromFile != ';'; readCharIsNotEndOfFormatChar)
	{
		fileStream.setstate(std::ios::failbit);
	}
}