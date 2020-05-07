#include "SerialMultiplier.h"

#include "MatrixRow.h"

Matrix SerialMultiplier::doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept
{
	const size_t numberOfColumnsInLeftMatrix = leftMatrix.getNumberOfColumns();
	const size_t numberOfRowsInLeftMatrix = leftMatrix.getNumberOfRows();
	const size_t numberOfColumnsInRightMatrix = rightMatrix.getNumberOfColumns();

	Matrix resultOfMultiplying(numberOfRowsInLeftMatrix, numberOfColumnsInRightMatrix);
	for (size_t rowIndex = 0; rowIndex < numberOfRowsInLeftMatrix; ++rowIndex)
	{
		for (size_t columnIndex = 0; columnIndex < numberOfColumnsInRightMatrix; ++columnIndex)
		{
			for (size_t sharedIndex = 0; sharedIndex < numberOfColumnsInLeftMatrix; ++sharedIndex)
			{
				resultOfMultiplying[rowIndex][columnIndex] += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
			}
		}
	}

	return resultOfMultiplying;
}