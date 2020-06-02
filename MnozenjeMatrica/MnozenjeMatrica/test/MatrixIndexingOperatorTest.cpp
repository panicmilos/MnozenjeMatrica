#include "MatrixIndexingOperatorTest.h"

#include "DSTLAssertions.h"
#include "../src/MatrixExceptions.h"

TEST_P(MatrixIndexingOperatorWithParamsInBound, IndexesInBound)
{
	auto elemment = GetParam();

	MATRIX_CONTAINS_ELEMENT(m, elemment);
}

INSTANTIATE_TEST_SUITE_P(MatrixIndexingOperatorWithParams, MatrixIndexingOperatorWithParamsInBound,
	testing::Values(
		Element{ 2, 0u, 0u },
		Element{ -4, 0u, 2u },
		Element{ 6, 1u, 2u }
));

TEST_P(MatrixIndexingOperatorWithParamsRowOutOfBound, rowIndexOutOfBound)
{
	auto element = GetParam();
	MATRIX_EXPECT_THROW(int elementValueInMatrix = m[element.rowIndex][element.columnIndex], MatrixIndexOutOfBounds, "Given rowIndex is out of bounds!");
}

INSTANTIATE_TEST_SUITE_P(MatrixIndexingOperatorWithParams, MatrixIndexingOperatorWithParamsRowOutOfBound,
	testing::Values(
		Element{ 0, (size_t)-1, 0u },
		Element{ 0, 5u, 2u },
		Element{ 0, 2u, 2u }
));

TEST_P(MatrixIndexingOperatorWithParamsColumnOutOfBound, columnIndexOutOfBound)
{
	auto element = GetParam();
	MATRIX_EXPECT_THROW(int elementValueInMatrix = m[element.rowIndex][element.columnIndex], MatrixIndexOutOfBounds, "Given columnIndex is out of bounds!");
}

INSTANTIATE_TEST_SUITE_P(MatrixIndexingOperatorWithParams, MatrixIndexingOperatorWithParamsColumnOutOfBound,
	testing::Values(
		Element{ 0, 1u, 4u },
		Element{ 0, 0u, 3u },
		Element{ 0, 1u, (size_t)-1 }
));