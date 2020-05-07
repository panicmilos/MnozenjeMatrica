#include "Matrix.h"

#include <algorithm>
#include <iostream>

#include "MatrixExceptions.h"

Matrix::Matrix(const size_t numberOfRows_, const size_t numberOfColumns_, const int defaultElementValue) noexcept(false) :
	matrixElements(new int[numberOfRows_ * numberOfColumns_]()),
	numberOfRows(numberOfRows_),
	numberOfColumns(numberOfColumns_)
{
	if (!validateDimensionsForParametarizedConstructor(numberOfRows_, numberOfColumns_))
	{
		throw MatrixHaveBadDimensions("Matrix must have at lease one row and one column!");
	}

	if (defaultElementValue != DEFAULT_ELEMENT_VALUE)
	{
		const size_t numberOfElements = getSize();
		std::fill(matrixElements, matrixElements + numberOfElements, defaultElementValue);
	}
}

bool Matrix::validateDimensionsForParametarizedConstructor(const size_t numberOfRows, const size_t numberOfColumns) const noexcept
{
	const bool hasAtLeastOneRow = numberOfRows > 0;
	const bool hasAtLeastOneColumn = numberOfColumns > 0;
	const bool areDimenstionsGood = hasAtLeastOneRow & hasAtLeastOneColumn;

	return areDimenstionsGood;
}

Matrix::Matrix(const Matrix& m) noexcept(false) :
	matrixElements(new int[m.numberOfRows * m.numberOfColumns]()),
	numberOfRows(m.numberOfRows),
	numberOfColumns(m.numberOfColumns)
{
	const size_t numberOfElements = getSize();
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

Matrix::Matrix(const std::initializer_list<std::initializer_list<int>>& matrixElements_) noexcept(false)
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

bool Matrix::validateDimensionsForInitializerListConstructor(const std::initializer_list<std::initializer_list<int>>& matrixElements) const noexcept
{
	const bool areAllColumnsSameSize = areAllColumnsInListInitializerSameSize(matrixElements);
	const bool hasAtLeastOneColumn = doesListInitializerHaveAtLeastOneColumn(matrixElements);
	const bool areDimensionsGood = areAllColumnsSameSize & hasAtLeastOneColumn;

	return areDimensionsGood;
}

bool Matrix::areAllColumnsInListInitializerSameSize(const std::initializer_list<std::initializer_list<int>>& matrixElements) const noexcept
{
	const auto firstColumnPtr = matrixElements.begin();
	const size_t sizeOfFirstColumn = firstColumnPtr->size();

	auto compareColumnSizeToSizeOfFirstColumn = [&sizeOfFirstColumn](std::initializer_list<int> columnPtr)
	{
		const size_t sizeOfColumn = columnPtr.size();

		return sizeOfFirstColumn == sizeOfColumn;
	};

	const bool allColumnsHaveSameSize = std::all_of(matrixElements.begin(), matrixElements.end(), compareColumnSizeToSizeOfFirstColumn);

	return allColumnsHaveSameSize;
}

bool Matrix::doesListInitializerHaveAtLeastOneColumn(const std::initializer_list<std::initializer_list<int>>& matrixElements) const noexcept
{
	const auto firstColumnPtr = matrixElements.begin();
	const size_t sizeOfFirstColumn = firstColumnPtr->size();
	const bool hasMoreThenOneColumn = sizeOfFirstColumn > 0;

	return hasMoreThenOneColumn;
}

Matrix::~Matrix() noexcept
{
	delete matrixElements;
}

Matrix& Matrix::operator=(const Matrix& m) noexcept(false)
{
	if (this != &m)
	{
		const size_t oldNumberOfElements = getSize();
		const size_t newNumberOfElements = m.getSize();

		if (const bool matricesDontHaveSameSize = oldNumberOfElements != newNumberOfElements; matricesDontHaveSameSize)
		{
			int* newMemoryForMatrixElements = new int[newNumberOfElements];

			delete matrixElements;

			matrixElements = newMemoryForMatrixElements;
			numberOfRows = m.numberOfRows;
			numberOfColumns = m.numberOfColumns;
		}

		std::copy(m.matrixElements, m.matrixElements + newNumberOfElements, matrixElements);
	}

	return *this;
}

Matrix& Matrix::operator=(Matrix&& m) noexcept
{
	if (this != &m)
	{
		delete matrixElements;

		matrixElements = m.matrixElements;
		numberOfRows = m.numberOfRows;
		numberOfColumns = m.numberOfColumns;

		m.matrixElements = nullptr;
		m.numberOfRows = 0;
		m.numberOfColumns = 0;
	}

	return *this;
}

MatrixRow Matrix::operator[](const size_t rowIndex) noexcept(false)
{
	throwIfRowIndexIsOutOfBounds(rowIndex);

	int* const startOfIndexedRowPrt = matrixElements + rowIndex * numberOfColumns;

	return MatrixRow(startOfIndexedRowPrt, numberOfColumns);
}

const MatrixRow Matrix::operator[](const size_t rowIndex) const noexcept(false)
{
	throwIfRowIndexIsOutOfBounds(rowIndex);

	int* const startOfIndexedRowPrt = matrixElements + rowIndex * numberOfColumns;

	return MatrixRow(startOfIndexedRowPrt, numberOfColumns);
}

void Matrix::throwIfRowIndexIsOutOfBounds(const size_t rowIndex) const noexcept(false)
{
	if (!validateRowIndex(rowIndex))
	{
		throw MatrixIndexOutOfBounds("Given rowIndex is out of bounds!");
	}
}

bool Matrix::validateRowIndex(const size_t rowIndex) const noexcept
{
	const bool isRowIndexInBounds = rowIndex < numberOfRows;

	return isRowIndexInBounds;
}

size_t Matrix::getNumberOfRows() const noexcept
{
	return numberOfRows;
}

size_t Matrix::getNumberOfColumns() const noexcept
{
	return numberOfColumns;
}

size_t Matrix::getSize() const noexcept
{
	const size_t numberOfElements = numberOfRows * numberOfColumns;

	return numberOfElements;
}

int* const Matrix::getMatrixElements() const noexcept
{
	return matrixElements;
}