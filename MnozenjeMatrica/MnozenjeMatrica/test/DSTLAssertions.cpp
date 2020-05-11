#include "DSTLAssertions.h"

#include <algorithm>
#include <vector>

#include "gtest\gtest.h"
#include "UtilsForTests.h"

void MatrixAssertions::MATRIX_DIMENSIONS_EQ_(const Matrix& m, std::pair<size_t, size_t> dimensions)
{
	const auto [numberOfRowsExpected, numberOfColumnsExpected] = dimensions;
	const auto [numberOfRows, numberOfColumns] = std::pair{ m.getNumberOfRows(), m.getNumberOfColumns() };

	ASSERT_EQ(numberOfRows, numberOfRowsExpected);
	ASSERT_EQ(numberOfColumns, numberOfColumnsExpected);
}

void MatrixAssertions::MATRIX_DIMENSIONS_NOT_EQ_(const Matrix& m, std::pair<size_t, size_t> dimensions)
{
	const auto [numberOfRowsExpected, numberOfColumnsExpected] = dimensions;
	const auto [numberOfRows, numberOfColumns] = std::pair{ m.getNumberOfRows(), m.getNumberOfColumns() };

	const bool numberOfRowsAreNotSame = numberOfRows != numberOfRowsExpected;
	const bool numberOfColumnsAreNotSame = numberOfColumns != numberOfColumnsExpected;

	ASSERT_EQ(numberOfRowsAreNotSame, true);
	ASSERT_EQ(numberOfColumnsAreNotSame, true);
}

void MatrixAssertions::MATRIX_ELEMENTS_EQ_(const Matrix& m, const std::vector<int>& elements)
{
	const size_t matrixSize = m.getSize();

	ASSERT_EQ(matrixSize, elements.size());

	const int* const matrixElements = m.getMatrixElements();

	const bool allElementsAreSame = std::equal(elements.begin(), elements.end(), matrixElements);

	ASSERT_EQ(allElementsAreSame, true);
}

void MatrixAssertions::MATRIX_CONTAINS_ELEMENT_(const Matrix& m, const Element& e)
{
	const int elementValueInMatrix = m[e.rowIndex][e.columnIndex];
	const int expectedValue = e.value;

	ASSERT_EQ(elementValueInMatrix, expectedValue);
}

void MatrixAssertions::MATRICES_EQ_(const Matrix& leftMatrix, const Matrix& rightMatrix, const bool areSame)
{
	const bool matricesAreSame = leftMatrix == rightMatrix;

	ASSERT_EQ(matricesAreSame, areSame);
}

void MatrixAssertions::ROWS_EQ_(const MatrixRow& leftRow, const MatrixRow& rightRow, const bool areSame)
{
	const bool rowsAreSame = leftRow == rightRow;

	ASSERT_EQ(rowsAreSame, areSame);
}

void MatrixAssertions::MATRIX_FILE_CONTENT_EQ_TO_(const std::string& filePath, const std::string& expectedContent)
{
	std::string fileContent = UtilsForTests::getContentOfFile(filePath);

	ASSERT_EQ(fileContent, expectedContent);
}