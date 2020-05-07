#include "ParallelForMultiplier.h"

#include "Profiling.h"
#include "tbb\parallel_for.h"
#include "tbb\blocked_range2d.h"

Matrix ParallelForMultiplier::doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept
{
	PROFILE_SCOPE("ParallelForMultiplier");
	const size_t numberOfColumnsInLeftMatrix = leftMatrix.getNumberOfColumns();
	const size_t numberOfRowsInLeftMatrix = leftMatrix.getNumberOfRows();
	const size_t numberOfColumnsInRightMatrix = rightMatrix.getNumberOfColumns();

	Matrix resultOfMultiplying(numberOfRowsInLeftMatrix, numberOfColumnsInRightMatrix);

	const auto calculateBlockOfResultMatrix = [&](const tbb::blocked_range2d<size_t>& range)
	{
		PROFILE_SCOPE("");
		for (size_t rowIndex = range.rows().begin(); rowIndex != range.rows().end(); ++rowIndex)
		{
			for (size_t columnIndex = range.cols().begin(); columnIndex != range.cols().end(); ++columnIndex)
			{
				for (size_t sharedIndex = 0; sharedIndex < numberOfColumnsInLeftMatrix; ++sharedIndex)
				{
					resultOfMultiplying[rowIndex][columnIndex] += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
				}
			}
		}
	};

	tbb::parallel_for(tbb::blocked_range2d<size_t>(0, numberOfRowsInLeftMatrix, 0, numberOfColumnsInRightMatrix), calculateBlockOfResultMatrix);

	return resultOfMultiplying;
}