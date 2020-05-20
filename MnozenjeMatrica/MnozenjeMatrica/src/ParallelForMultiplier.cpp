#include "ParallelForMultiplier.h"

#include "MatrixRow.h"
#include "tbb\parallel_for.h"
#include "tbb\blocked_range2d.h"

MatrixMultiplierBase* ParallelForMultiplier::create() noexcept
{
	return new ParallelForMultiplier();
}

Matrix ParallelForMultiplier::doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept
{
	const size_t numberOfColumnsInLeftMatrix = leftMatrix.getNumberOfColumns();
	const size_t numberOfRowsInLeftMatrix = leftMatrix.getNumberOfRows();
	const size_t numberOfColumnsInRightMatrix = rightMatrix.getNumberOfColumns();

	Matrix resultOfMultiplication(numberOfRowsInLeftMatrix, numberOfColumnsInRightMatrix);

	const auto calculateBlockOfElementsInResultMatrix = [&](const tbb::blocked_range2d<size_t>& elementsRange)
	{
		for (size_t rowIndex = elementsRange.rows().begin(); rowIndex != elementsRange.rows().end(); ++rowIndex)
		{
			for (size_t columnIndex = elementsRange.cols().begin(); columnIndex != elementsRange.cols().end(); ++columnIndex)
			{
				int sumOfRowColumnPairs = 0;
				for (size_t sharedIndex = 0; sharedIndex < numberOfColumnsInLeftMatrix; ++sharedIndex)
				{
					sumOfRowColumnPairs += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
				}
				resultOfMultiplication[rowIndex][columnIndex] = sumOfRowColumnPairs;
			}
		}
	};

	tbb::parallel_for(tbb::blocked_range2d<size_t>(0, numberOfRowsInLeftMatrix, 0, numberOfColumnsInRightMatrix), calculateBlockOfElementsInResultMatrix);

	return resultOfMultiplication;
}