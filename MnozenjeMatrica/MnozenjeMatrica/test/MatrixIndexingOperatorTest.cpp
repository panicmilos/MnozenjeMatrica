#include "MatrixIndexingOperatorTest.h"

#include "DSTLAssertions.h"
#include "../src/MatrixExceptions.h"

TEST_P(MatrixIndexingOperatorWithParamsInBound, IndexesInBound)
{
	auto parameters = GetParam();

	const int elementValue = m[parameters.rowIndex][parameters.columnIndex];
	const int expectedValue = parameters.value;

	ASSERT_EQ(elementValue, expectedValue);
}

INSTANTIATE_TEST_CASE_P(MatrixIndexingOperatorWithParams, MatrixIndexingOperatorWithParamsInBound,
	testing::Values(
		Element{ 2, 0u, 0u },
		Element{ -4, 0u, 2u },
		Element{ 6, 1u, 2u }
));

TEST_P(MatrixIndexingOperatorWithParamsRowOutOfBound, rowIndexOutOfBound)
{
	auto parameters = GetParam();
	MATRIX_EXPECT_THROW(m[parameters.rowIndex][parameters.columnIndex], MatrixIndexOutOfBounds, "Given rowIndex is out of bounds!");
}

INSTANTIATE_TEST_CASE_P(MatrixIndexingOperatorWithParams, MatrixIndexingOperatorWithParamsRowOutOfBound,
	testing::Values(
		Element{ 0, (size_t)-1, 0u },
		Element{ 0, 5u, 2u },
		Element{ 0, 2u, 2u }
));

TEST_P(MatrixIndexingOperatorWithParamsColumnOutOfBound, columnIndexOutOfBound)
{
	auto parameters = GetParam();
	MATRIX_EXPECT_THROW(m[parameters.rowIndex][parameters.columnIndex], MatrixIndexOutOfBounds, "Given columnIndex is out of bounds!");
}

INSTANTIATE_TEST_CASE_P(MatrixIndexingOperatorWithParams, MatrixIndexingOperatorWithParamsColumnOutOfBound,
	testing::Values(
		Element{ 0, 1u, 4u },
		Element{ 0, 0u, 3u },
		Element{ 0, 1u, (size_t)-1 }
));