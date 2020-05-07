#include "MatrixMultiplyBase.h"

#include "MatrixExceptions.h"

Matrix MatrixMultiplyBase::multiply(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false)
{
	throwIfNumberOfFirstMatrixColumnsIsNotSameAsNumberOfSecondMatrixRows(leftMatrix, rightMatrix);

	Matrix resultOfMultiplying = doMultiplying(leftMatrix, rightMatrix);

	return resultOfMultiplying;
}

void MatrixMultiplyBase::throwIfNumberOfFirstMatrixColumnsIsNotSameAsNumberOfSecondMatrixRows(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false)
{
	if (!isNumberOfFirstMatrixColumnsSameAsNumberOfSecondMatrixRows(leftMatrix, rightMatrix))
	{
		throw BadMatricesDimensionsForMultiplying("Number of first matrix columns must be same as number of second matrix rows!");
	}
}

bool MatrixMultiplyBase::isNumberOfFirstMatrixColumnsSameAsNumberOfSecondMatrixRows(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept
{
	const size_t numberOfColumnsInFirstMatrix = leftMatrix.getNumberOfColumns();
	const size_t numberOfRowsInSecondMatrix = rightMatrix.getNumberOfRows();
	const bool numberOfRowsAndColumnsAreSame = numberOfColumnsInFirstMatrix == numberOfRowsInSecondMatrix;

	return numberOfRowsAndColumnsAreSame;
}