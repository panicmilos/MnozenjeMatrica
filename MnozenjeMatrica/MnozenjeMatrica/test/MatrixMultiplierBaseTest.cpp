#include "MatrixMultiplierBaseTest.h"

#include "DSTLAssertions.h"
#include "gtest\gtest.h"
#include "..\src\MatrixExceptions.h"

TEST(MatrixMultiplyBase, WrongMatricesDimensions)
{
	Matrix leftMatrix(2, 2, 2);
	Matrix rightMatrix(3, 2, 6);

	MatrixMultiplierBaseTest mmbt;
	MATRIX_EXPECT_THROW(Matrix result = mmbt.multiply(leftMatrix, rightMatrix), BadMatricesDimensionsForMultiplying, "Number of first matrix columns must be same as number of second matrix rows!");
}