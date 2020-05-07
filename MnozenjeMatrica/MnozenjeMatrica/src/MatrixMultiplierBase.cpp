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
		throw BadMatricesDimensionsForMultiplying("Number of left matrix columns must be same as number of right matrix rows!");
	}
}

bool MatrixMultiplierBase::validateDimensionsForMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept
{
	const size_t numberOfColumnsInLeftMatrix = leftMatrix.getNumberOfColumns();
	const size_t numberOfRowsInRightMatrix = rightMatrix.getNumberOfRows();
	const bool numberOfRowsAndColumnsAreSame = numberOfColumnsInLeftMatrix == numberOfRowsInRightMatrix;

	return numberOfRowsAndColumnsAreSame;
}