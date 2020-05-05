#include "Matrix.h"

#include <algorithm>
#include <iostream>

#include "MatrixExceptions.h"

Matrix::Matrix(const size_t numberOfRows_, const size_t numberOfColumns_, const int defaultElementValue) :
	matrixElements(new int[numberOfRows_ * numberOfColumns_]()),
	numberOfRows(numberOfRows_),
	numberOfColumns(numberOfColumns_)
{
	if (!validateDimensionsForParametarizedConstructor(numberOfRows_, numberOfColumns_))
	{
		throw MatrixHaveBadDimensions("Matrix must have at lease one row and one column!");
	}

	if (defaultElementValue)
	{
		const size_t numberOfElements = numberOfRows_ * numberOfColumns_;
		std::fill(matrixElements, matrixElements + numberOfElements, defaultElementValue);
	}
}

bool Matrix::validateDimensionsForParametarizedConstructor(const size_t numberOfRows, const size_t numberOfColumns) const
{
	const bool hasAtLeastOneRow = numberOfRows > 0;
	const bool hasAtLeastOneColumn = numberOfColumns > 0;
	const bool areDimenstionsGood = hasAtLeastOneRow & hasAtLeastOneColumn;

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
	if (!validateDimensionsForInitializerListConstructor(matrixElements_))
	{
		throw MatrixHaveBadDimensions("Matrix must have at lease one row and one column!");
	}

	numberOfRows = matrixElements_.size();
	numberOfColumns = matrixElements_.begin()->size();
	matrixElements = new int[numberOfRows * numberOfColumns]();

	for (auto rowIt = matrixElements_.begin(); rowIt != matrixElements_.end(); ++rowIt)
	{
		const size_t rowIndex = rowIt - matrixElements_.begin();

		for (auto columnIt = rowIt->begin(); columnIt != rowIt->end(); ++columnIt)
		{
			const size_t columnIndex = columnIt - rowIt->begin();

			matrixElements[rowIndex * numberOfColumns + columnIndex] = *columnIt;
		}
	}
}

bool Matrix::validateDimensionsForInitializerListConstructor(const std::initializer_list<std::initializer_list<int>>& matrixElements) const
{
	const bool areAllColumnsSameSize = areAllColumnsInListInitializerSameSize(matrixElements);
	const bool hasAtLeastOneColumn = doesListInitializerHaveAtLeastOneColumn(matrixElements);
	const bool areDimensionsGood = areAllColumnsSameSize & hasAtLeastOneColumn;

	return areDimensionsGood;
}

bool Matrix::areAllColumnsInListInitializerSameSize(const std::initializer_list<std::initializer_list<int>>& matrixElements) const
{
	auto firstColumnPtr = matrixElements.begin();
	const size_t sizeOfFirstColumn = firstColumnPtr->size();

	auto compareColumnSizeToSizeOfFirstColumn = [&sizeOfFirstColumn](std::initializer_list<int> columnPtr)
	{
		const size_t sizeOfColumn = columnPtr.size();

		return sizeOfFirstColumn == sizeOfColumn;
	};

	const bool allColumnsHaveSameSize = std::all_of(matrixElements.begin(), matrixElements.end(), compareColumnSizeToSizeOfFirstColumn);

	return allColumnsHaveSameSize;
}

bool Matrix::doesListInitializerHaveAtLeastOneColumn(const std::initializer_list<std::initializer_list<int>>& matrixElements) const
{
	const auto firstColumnPtr = matrixElements.begin();
	const size_t sizeOfFirstColumn = firstColumnPtr->size();
	bool hasMoreThenOneColumn = sizeOfFirstColumn > 0;

	return hasMoreThenOneColumn;
}

Matrix::~Matrix() noexcept
{
	delete matrixElements;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	//if(this != &m) // test prvo
	const int oldNumberOfElements = getSize();
	const int newNumberOfElements = m.getSize();

	const bool matricesDontHaveSameSize = oldNumberOfElements != newNumberOfElements;
	if (matricesDontHaveSameSize)
	{
		int* newMemoryForMatrixElements = new int[newNumberOfElements];

		delete matrixElements;

		matrixElements = newMemoryForMatrixElements;
	}

	std::copy(m.matrixElements, m.matrixElements + newNumberOfElements, matrixElements);
}

Matrix& Matrix::operator=(Matrix&& m) noexcept
{
	//if(this != &m) // test prvo
	delete matrixElements;

	matrixElements = m.matrixElements;
	numberOfRows = m.numberOfRows;
	numberOfColumns = m.numberOfColumns;

	m.matrixElements = nullptr;
	m.numberOfRows = 0;
	m.numberOfColumns = 0;
}

MatrixRow Matrix::operator[](size_t rowIndex)
{
	int* const startOfIndexedRowPrt = matrixElements + rowIndex * numberOfColumns;

	return MatrixRow(startOfIndexedRowPrt, numberOfColumns);
}

const MatrixRow Matrix::operator[](size_t rowIndex) const
{
	int* const startOfIndexedRowPrt = matrixElements + rowIndex * numberOfColumns;

	return MatrixRow(matrixElements + rowIndex * numberOfColumns, numberOfColumns);
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