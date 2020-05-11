#include "MatrixEqualOperator.h"

#include "DSTLAssertions.h"
#include "../src/Matrix.h"
#include "../src/MatrixRow.h"

TEST_P(MatrixEqualOperatorDimensionsTest, DifferentDimensions)
{
	auto params = GetParam();
	const auto [numberOfLeftMatrixRows, numberOfLeftMatrixColumns] = params.leftMatrixDimensions;
	const auto [numberOfRightMatrixRows, numberOfRightMatrixColumns] = params.rightMatrixDimensions;
	const auto isSame = params.areSame;

	Matrix leftMatrix(numberOfLeftMatrixRows, numberOfLeftMatrixColumns);
	Matrix rightMatrix(numberOfRightMatrixRows, numberOfRightMatrixColumns);

	MATRICES_EQ(leftMatrix, rightMatrix, isSame);
}

INSTANTIATE_TEST_CASE_P(MatrixEqualOperator, MatrixEqualOperatorDimensionsTest,
	testing::Values(
		MatrixEqualOperatorTest{ { 1, 1 }, { 2, 2}, false },
		MatrixEqualOperatorTest{ { 1, 2 }, { 2, 2}, false },
		MatrixEqualOperatorTest{ { 1, 2 }, { 1, 3}, false },
		MatrixEqualOperatorTest{ { 1, 2 }, { 1, 2}, true }
));

TEST(MatrixEqualOperator, DifferentElements)
{
	Matrix leftMatrix{ {1, 2, 6, 4} };
	Matrix rightMatrix{ {1, 2, 2, 4} };

	MATRICES_EQ(leftMatrix, rightMatrix, false);
}

TEST(MatrixEqualOperator, MatricesAreSame)
{
	Matrix leftMatrix{ {1, 2, 6, 4} };
	Matrix rightMatrix{ {1, 2, 6, 4} };

	MATRICES_EQ(leftMatrix, rightMatrix, true);
}