#include "Matrix.h"

#include <algorithm>
#include <iostream>

#include "MatrixExceptions.h"

Matrix::Matrix(const size_t numberOfRows_, const size_t numberOfColumns_, const int elementsValue) noexcept(false) :
	matrixElements(new int[numberOfRows_ * numberOfColumns_]()),
	numberOfRows(numberOfRows_),
	numberOfColumns(numberOfColumns_)
{
	// Provera da li ima bar jedan red i kolona
	if (!validateDimensionsForParametarizedConstructor(numberOfRows_, numberOfColumns_))
	{
		throw MatrixHaveBadDimensions("Matrix must have at lease one row and one column!");
	}

	// Svi elementi niza su po kontrukciji 0 pa nema potrebe da se ponovo radi fill
	if (elementsValue != 0)
	{
		const size_t numberOfElements = getSize();
		std::fill(matrixElements, matrixElements + numberOfElements, elementsValue);
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
		// Oduzimanjem dva iteratora se dobija brojna razlika u vidu pozicija izmedju njih
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
	// Proverava se velicina svih ostalih kolona sa velicinom prve da se vidi da li sve imaju istu velicinu
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
	matrixElements = nullptr;
}

Matrix& Matrix::operator=(const Matrix& m) noexcept(false)
{
	if (const bool notTryingToCopyMatrixToItself = this != &m; notTryingToCopyMatrixToItself)
	{
		const size_t oldNumberOfElements = getSize();
		const size_t newNumberOfElements = m.getSize();

		// Ako matrice imaju iste dimenzije onda se samo radi kopija a ako ne onda se zauzima memorija za matrice
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
	if (const bool notTryingToMoveMatrixToItself = this != &m; notTryingToMoveMatrixToItself)
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
	// Provera se ne vrsi u Release rezimu
	#ifndef NDEBUG
	throwIfRowIndexIsOutOfBounds(rowIndex);
	#endif

	int* const startOfIndexedRowPrt = matrixElements + rowIndex * numberOfColumns;

	return MatrixRow(startOfIndexedRowPrt, numberOfColumns);
}

const MatrixRow Matrix::operator[](const size_t rowIndex) const noexcept(false)
{
	// Provera se ne vrsi u Release rezimu
	#ifndef NDEBUG
	throwIfRowIndexIsOutOfBounds(rowIndex);
	#endif

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

bool operator==(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept
{
	if (!matricesHaveSameDimensions(leftMatrix, rightMatrix))
	{
		return false;
	}

	const bool allElementsAreSame = matricesHaveSameElements(leftMatrix, rightMatrix);

	return allElementsAreSame;
}

bool matricesHaveSameDimensions(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept
{
	const bool numberOfRowsAreSame = leftMatrix.numberOfRows == rightMatrix.numberOfRows;
	const bool numberOfColumnsAreSame = leftMatrix.numberOfColumns == rightMatrix.numberOfColumns;
	const bool dimensionsAreSame = numberOfRowsAreSame & numberOfColumnsAreSame;

	return dimensionsAreSame;
}

bool matricesHaveSameElements(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept
{
	const size_t numberOfElements = leftMatrix.getSize();
	const int* const startOfLeftMatrixElementsPtr = leftMatrix.matrixElements;
	const int* const endOfLeftMatrixElementsPtr = leftMatrix.matrixElements + numberOfElements;
	const int* const startOfRightMatrixElementsPtr = rightMatrix.matrixElements;
	const bool allElementsAreSame = std::equal(startOfLeftMatrixElementsPtr, endOfLeftMatrixElementsPtr, startOfRightMatrixElementsPtr);

	return allElementsAreSame;
}

bool operator!=(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept
{
	const bool areMatricesSame = leftMatrix == rightMatrix;

	return !areMatricesSame;
}

std::ostream& operator << (std::ostream& out, const Matrix& m) noexcept
{
	const size_t numberOfRows = m.numberOfRows;

	for (size_t rowIndex = 0; rowIndex < numberOfRows; ++rowIndex)
	{
		MatrixRow row = m[rowIndex];
		out << row << '\n';
	}

	return out;
}