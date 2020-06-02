#include "ParallelTaskPerRowMultiplier.h"

ParallelTaskPerRow::ParallelTaskPerRow(const MultiplicationElements multiplicationElements_, const size_t rowIndex_) noexcept :
	ParallelTask(multiplicationElements_),
	rowIndex(rowIndex_)
{
}

tbb::task* ParallelTaskPerRow::execute()
{
	auto [leftMatrix, rightMatrix, resultOfMultiplication] = multiplicationElements;
	const size_t numberOfElementsInResultMatrixRow = resultOfMultiplication.getNumberOfColumns();
	const size_t numberOfElementsInLeftMatrixColumn = leftMatrix.getNumberOfColumns();

	for (size_t columnIndex = 0; columnIndex < numberOfElementsInResultMatrixRow; ++columnIndex)
	{
		int sumOfRowColumnPairs = 0;
		for (size_t sharedIndex = 0; sharedIndex < numberOfElementsInLeftMatrixColumn; ++sharedIndex)
		{
			sumOfRowColumnPairs += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
		}
		resultOfMultiplication[rowIndex][columnIndex] = sumOfRowColumnPairs;
	}

	return nullptr;
}

MatrixMultiplierBase* ParallelTaskPerRowMultiplier::create() noexcept
{
	return new ParallelTaskPerRowMultiplier();
}

void ParallelTaskPerRowMultiplier::fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept
{
	// Pravi se task za svaki red
	const Matrix& resultOfMultiplication = multiplicationElements.resultOfMultiplication;
	const size_t numberOfRows = resultOfMultiplication.getNumberOfRows();

	for (size_t rowIndex = 0; rowIndex < numberOfRows; ++rowIndex)
	{
		tbb::task& elementsCalculation = *new(parent.allocate_child()) ParallelTaskPerRow(multiplicationElements, rowIndex);
		parentsTasks.push_back(elementsCalculation);
	}

	const int totalNumberOfRefCount = getTotalNumberOfRefCount(resultOfMultiplication);
	parent.set_ref_count(totalNumberOfRefCount);
}

int ParallelTaskPerRowMultiplier::getTotalNumberOfRefCount(const Matrix& resultOfMultiplication) const noexcept
{
	const size_t numberOfParentsTasks = resultOfMultiplication.getNumberOfRows();
	const int additionalRefCountForWait = 1;
	const int totalNumberOfRefCount = (int)numberOfParentsTasks + additionalRefCountForWait;

	return totalNumberOfRefCount;
}