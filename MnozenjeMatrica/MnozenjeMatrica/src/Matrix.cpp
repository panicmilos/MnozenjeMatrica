#include "Matrix.h"

#include <algorithm>
#include <iostream>

MatrixHaveBadDimensions::MatrixHaveBadDimensions(const char* exceptionMessage) :
	std::runtime_error(exceptionMessage)
{
}

Matrix::Matrix(const size_t numberOfRows_, const size_t numberOfColumns_, const int defaultElementValue) :
	matrixElements(new int[numberOfRows_ * numberOfColumns_]()),
	numberOfRows(numberOfRows_),
	numberOfColumns(numberOfColumns_)
{
	if (!ValidateDimensionsForParametarizedConstructor(numberOfRows_, numberOfColumns_))
	{
		throw MatrixHaveBadDimensions("Matrix must have at lease one row and one column!");
	}

	if (defaultElementValue != 0)
	{
		const size_t numberOfElements = numberOfRows_ * numberOfColumns_;
		std::fill(matrixElements, matrixElements + numberOfElements, defaultElementValue);
	}
}

bool Matrix::ValidateDimensionsForParametarizedConstructor(const size_t numberOfRows, const size_t numberOfColumns) const
{
	bool haveAtLeastOneRow = numberOfRows > 0;
	bool haveAtLeastOneColumn = numberOfColumns > 0;

	bool areDimenstionsGood = haveAtLeastOneRow & haveAtLeastOneColumn;

	return areDimenstionsGood;
}

Matrix::Matrix(const Matrix& m) :
	matrixElements(new int[m.numberOfRows * m.numberOfColumns]()),
	numberOfRows(m.numberOfRows),
	numberOfColumns(m.numberOfColumns)
{
	const size_t numberOfElements = m.numberOfRows * m.numberOfColumns;
	std::copy(m.matrixElements, m.matrixElements + numberOfElements, matrixElements);
}

Matrix::Matrix(Matrix&& m) noexcept :
	matrixElements(m.matrixElements),
	numberOfRows(m.numberOfRows),
	numberOfColumns(m.numberOfColumns)
{
	m.matrixElements = nullptr;
	m.numberOfRows = 0;
	m.numberOfColumns = 0;
}

Matrix::Matrix(const std::initializer_list<std::initializer_list<int>>& matrixElements_)
{
	if (!validateMatrixDimensionsForInitializerListConstructor(matrixElements_))
	{
		throw MatrixHaveBadDimensions("Matrix must have at lease one row and one column!");
	}

	numberOfRows = matrixElements_.size();
	numberOfColumns = matrixElements_.begin()->size();
	matrixElements = new int[numberOfRows * numberOfColumns]();

	for (auto rowIt = matrixElements_.begin(); rowIt != matrixElements_.end(); ++rowIt)
	{
		size_t rowIndex = rowIt - matrixElements_.begin();
		for (auto columnIt = rowIt->begin(); columnIt != rowIt->end(); ++columnIt)
		{
			size_t columnIndex = columnIt - rowIt->begin();
			matrixElements[rowIndex * numberOfColumns + columnIndex] = *columnIt;
		}
	}
}

bool Matrix::validateMatrixDimensionsForInitializerListConstructor(const std::initializer_list<std::initializer_list<int>>& matrixElements) const
{
	if (!areAllColumnsInListInitializerSameSize(matrixElements) || !doesListInitializerHasMoreThenOneColumn(matrixElements))
	{
		return false;
	}

	return true;
}

bool Matrix::areAllColumnsInListInitializerSameSize(const std::initializer_list<std::initializer_list<int>>& matrixElements) const
{
	auto firstColumnPtr = matrixElements.begin();
	size_t sizeOfFirstColumn = firstColumnPtr->size();

	auto compareColumnSizeToSizeOfFirstColumn = [&sizeOfFirstColumn](std::initializer_list<int> columnPtr)
	{
		size_t sizeOfColumn = columnPtr.size();

		return sizeOfFirstColumn == sizeOfColumn;
	};

	bool allColumnsHaveSameSize = std::all_of(matrixElements.begin(), matrixElements.end(), compareColumnSizeToSizeOfFirstColumn);

	return allColumnsHaveSameSize;
}

bool Matrix::doesListInitializerHasMoreThenOneColumn(const std::initializer_list<std::initializer_list<int>>& matrixElements) const
{
	auto firstColumnPtr = matrixElements.begin();
	size_t sizeOfFirstColumn = firstColumnPtr->size();

	return sizeOfFirstColumn != 0;
}

Matrix::~Matrix()
{
	delete matrixElements;
}

size_t Matrix::getNumberOfRows() const
{
	return numberOfRows;
}

size_t Matrix::getNumberOfColumns() const
{
	return numberOfColumns;
}

size_t Matrix::getSize() const
{
	return numberOfRows * numberOfColumns;
}

int* const Matrix::getMatrixElements() const
{
	return matrixElements;
}

void Matrix::print()
{
	for (size_t i = 0; i < numberOfRows; ++i)
	{
		for (size_t j = 0; j < numberOfColumns; ++j)
		{
			std::cout << matrixElements[i * numberOfColumns + j] << ' ';
		}
		std::cout << '\n';
	}
}