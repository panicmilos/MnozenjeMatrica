#include "ParallelTaskPerRowMultiplier.h"

ParallelTaskPerRow::ParallelTaskPerRow(const MultiplicationElements multiplicationElements_, const int rowIndex_) noexcept :
	ParallelTask(multiplicationElements_),
	rowIndex(rowIndex_)
{
}

tbb::task* ParallelTaskPerRow::execute()
{
	auto [leftMatrix, rightMatrix, resultOfMultiplication] = multiplicationElements;
	const size_t numberOfElements = rightMatrix.getNumberOfColumns();

	for (size_t columnIndex = 0; columnIndex < numberOfElements; ++columnIndex)
	{
		int element = 0;
		for (size_t sharedIndex = 0; sharedIndex < numberOfElements; ++sharedIndex)
		{
			element += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
		}
		resultOfMultiplication[rowIndex][columnIndex] = element;
	}

	return nullptr;
}

void ParallelTaskPerRowMultiplier::fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept
{
	const Matrix& resultOfMultiplication = multiplicationElements.resultOfMultiplication;
	const size_t numberOfRows = resultOfMultiplication.getNumberOfRows();

	for (size_t rowIndex = 0; rowIndex < numberOfRows; ++rowIndex)
	{
		tbb::task& elementCalculation = *new(parent.allocate_child()) ParallelTaskPerRow(multiplicationElements, rowIndex);
		parentsTasks.push_back(elementCalculation);
	}

	const int totalNumberOfRefCount = getTotalNumberOfRefCount(resultOfMultiplication);
	parent.set_ref_count(totalNumberOfRefCount);
}

int ParallelTaskPerRowMultiplier::getTotalNumberOfRefCount(const Matrix& resultOfMultiplication) const noexcept
{
	const int numberOfParentsTasks = resultOfMultiplication.getNumberOfRows();
	const int additionalRefCountForWait = 1;
	const int totalNumberOfRefCount = numberOfParentsTasks + additionalRefCountForWait;

	return totalNumberOfRefCount;
}