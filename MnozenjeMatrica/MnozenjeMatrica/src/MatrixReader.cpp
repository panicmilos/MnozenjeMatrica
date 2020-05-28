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

	throwIfStreamIsClosed();

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

void MatrixReader::throwIfMatrixFormatInFileIsBad() const noexcept(false)
{
	if (const bool somethingBadHappenedWhileReading = !fileStream.good(); somethingBadHappenedWhileReading)
	{
		throw BadMatrixFormatInFile("File contains matrix with bad format!");
	}
}

void MatrixReader::createMatrixWithReadDimensionsFromFile() noexcept
{
	const auto [numberOfRows, numberOfColumns] = Dimensions;

	Matrix m(numberOfRows, numberOfColumns);
	matrixFromFile = std::move(m);
}

void MatrixReader::readMatrixBody() noexcept
{
	const auto [numberOfRows, numberOfColumns] = Dimensions;
	int matrixElement;

	for (size_t rowIndex = 0; rowIndex < numberOfRows; ++rowIndex)
	{
		for (size_t columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex)
		{
			fileStream >> matrixElement;

			matrixFromFile[rowIndex][columnIndex] = matrixElement;
		}
	}
}

void MatrixReader::readEndOfFormatCharacter() noexcept
{
	char characterFromFile;

	fileStream >> characterFromFile;

	// Postavlja flag toka na fail u slucaju da nije ';' na kraju formata kako bi throw posle bacio izuzetak
	if (const bool readCharIsNotEndOfFormatChar = characterFromFile != ';'; readCharIsNotEndOfFormatChar)
	{
		fileStream.setstate(std::ios::failbit);
	}
}