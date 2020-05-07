#include "MatrixMultiplierBase.h"

#include "MatrixExceptions.h"

Matrix MatrixMultiplierBase::multiply(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false)
{
	throwIfDimensionsAreBad(leftMatrix, rightMatrix);

	Matrix resultOfMultiplying = doMultiplying(leftMatrix, rightMatrix);

	return resultOfMultiplying;
}

void MatrixMultiplierBase::throwIfDimensionsAreBad(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false)
{
	if (!validateDimensionsForMultiplying(leftMatrix, rightMatrix))
	{
		throw BadMatricesDimensionsForMultiplying("Number of first matrix columns must be same as number of second matrix rows!");
	}
}

bool MatrixMultiplierBase::validateDimensionsForMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept
{
	const size_t numberOfColumnsInFirstMatrix = leftMatrix.getNumberOfColumns();
	const size_t numberOfRowsInSecondMatrix = rightMatrix.getNumberOfRows();
	const bool numberOfRowsAndColumnsAreSame = numberOfColumnsInFirstMatrix == numberOfRowsInSecondMatrix;

	return numberOfRowsAndColumnsAreSame;
}