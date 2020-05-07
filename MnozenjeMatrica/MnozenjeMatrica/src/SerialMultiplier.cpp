#include "SerialMultiplier.h"

#include "MatrixRow.h"

Matrix SerialMultiplier::doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept
{
	const size_t numberOfColumnsInFirstMatrix = leftMatrix.getNumberOfColumns();
	const size_t numberOfRowsInFirstMatrix = leftMatrix.getNumberOfRows();
	const size_t numberOfColumnsInSecondMatrix = rightMatrix.getNumberOfColumns();

	Matrix resultOfMultiplying(numberOfRowsInFirstMatrix, numberOfColumnsInSecondMatrix);
	for (size_t rowIndex = 0; rowIndex < numberOfRowsInFirstMatrix; ++rowIndex)
	{
		for (size_t columnIndex = 0; columnIndex < numberOfColumnsInSecondMatrix; ++columnIndex)
		{
			for (size_t sharedIndex = 0; sharedIndex < numberOfColumnsInFirstMatrix; ++sharedIndex)
			{
				resultOfMultiplying[rowIndex][columnIndex] += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
			}
		}
	}

	return resultOfMultiplying;
}