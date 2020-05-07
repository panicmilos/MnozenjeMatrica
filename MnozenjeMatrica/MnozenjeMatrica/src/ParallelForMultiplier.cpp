#include "ParallelForMultiplier.h"

#include "tbb\parallel_for.h"
#include "tbb\blocked_range2d.h"

Matrix ParallelForMultiplier::doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept
{
	const size_t numberOfColumnsInFirstMatrix = leftMatrix.getNumberOfColumns();
	const size_t numberOfRowsInFirstMatrix = leftMatrix.getNumberOfRows();
	const size_t numberOfColumnsInSecondMatrix = rightMatrix.getNumberOfColumns();

	Matrix resultOfMultiplying(numberOfRowsInFirstMatrix, numberOfColumnsInSecondMatrix);

	const auto calculateBlockOfResultMatrix = [&](const tbb::blocked_range2d<size_t, size_t>& range)
	{
		for (size_t rowIndex = range.rows().begin(); rowIndex != range.rows().end(); ++rowIndex)
		{
			for (size_t columnIndex = range.cols().begin(); columnIndex != range.cols().end(); ++columnIndex)
			{
				for (size_t sharedIndex = 0; sharedIndex < numberOfColumnsInFirstMatrix; ++sharedIndex)
				{
					resultOfMultiplying[rowIndex][columnIndex] += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
				}
			}
		}
	};

	tbb::parallel_for(tbb::blocked_range2d<size_t>(0, numberOfRowsInFirstMatrix, 0, numberOfColumnsInSecondMatrix), calculateBlockOfResultMatrix);

	return resultOfMultiplying;
}