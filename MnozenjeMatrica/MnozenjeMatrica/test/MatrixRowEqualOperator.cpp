#include "MatrixRowEqualOperator.h"

#include "DSTLAssertions.h"
#include "../src/Matrix.h"
#include "../src/MatrixRow.h"

TEST_P(MatrixRowEqualOperatorDimensionsTest, DifferentNumberOfElements)
{
	auto params = GetParam();
	const auto [numberOfLeftRowsElements, numberOfRightRowsElements, isSame] = params;
	int elements[] = { 1, 2, 3, 4 };

	MatrixRow leftRow(elements, numberOfLeftRowsElements);
	MatrixRow rightRow(elements, numberOfRightRowsElements);

	ROWS_EQ(leftRow, rightRow, isSame);
}

INSTANTIATE_TEST_CASE_P(MatrixRowEqualOperator, MatrixRowEqualOperatorDimensionsTest,
	testing::Values(
		MatrixRowOperatorTest{ 1, 2, false },
		MatrixRowOperatorTest{ 1, 1, true }
));

TEST(MatrixEqualOperator, DifferentElementsInRow)
{
	const size_t numberOfElementsInRow = 4;
	int leftRowElements[] = { 1, 2, 3, 4 };
	int rightRowElements[] = { 1, 2, 6, 4 };

	MatrixRow leftRow(leftRowElements, numberOfElementsInRow);
	MatrixRow rightRow(rightRowElements, numberOfElementsInRow);

	ROWS_EQ(leftRow, rightRow, false);
}

TEST(MatrixEqualOperator, RowsAreSame)
{
	const size_t numberOfElementsInRow = 4;
	int leftRowElements[] = { 1, 2, 3, 4 };
	int rightRowElements[] = { 1, 2, 3, 4 };

	MatrixRow leftRow(leftRowElements, numberOfElementsInRow);
	MatrixRow rightRow(rightRowElements, numberOfElementsInRow);

	ROWS_EQ(leftRow, rightRow);
}