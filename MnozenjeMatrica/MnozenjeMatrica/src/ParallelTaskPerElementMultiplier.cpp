#include "ParallelTaskPerElementMultiplier.h"

ParallelTaskPerElement::ParallelTaskPerElement(MultiplicationElements multiplicationElements_, ElementIndex element_) noexcept :
	ParallelTask(multiplicationElements_),
	element(element_)
{
}

tbb::task* ParallelTaskPerElement::execute()
{
	auto [leftMatrix, rightMatrix, resultOfMultiplication] = multiplicationElements;
	auto [rowIndex, columnIndex] = element;
	const size_t numberOfElements = leftMatrix.getNumberOfColumns();

	int element = 0;
	for (size_t sharedIndex = 0; sharedIndex < numberOfElements; ++sharedIndex)
	{
		element += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
	}
	resultOfMultiplication[rowIndex][columnIndex] = element;

	return nullptr;
}

void ParallelTaskPerElementMultiplier::fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept
{
	Matrix& resultOfMultiplication = multiplicationElements.resultOfMultiplication;
	const size_t numberOfRows = resultOfMultiplication.getNumberOfRows();
	const size_t numberOfColumns = resultOfMultiplication.getNumberOfColumns();

	for (size_t rowIndex = 0; rowIndex < numberOfRows; ++rowIndex)
	{
		for (size_t columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex)
		{
			ElementIndex elementIndex = { rowIndex, columnIndex };
			tbb::task& elementCalculation = *new(parent.allocate_child()) ParallelTaskPerElement(multiplicationElements, elementIndex);
			parentsTasks.push_back(elementCalculation);
		}
	}

	const int totalNumberOfRefCount = getTotalNumberOfRefCount(resultOfMultiplication);
	parent.set_ref_count(totalNumberOfRefCount);
}

int ParallelTaskPerElementMultiplier::getTotalNumberOfRefCount(Matrix& resultOfMultiplication) const noexcept
{
	const int numberOfParentsTasks = resultOfMultiplication.getSize();
	const int additionalRefCountForWait = 1;
	const int totalNumberOfRefCount = numberOfParentsTasks + additionalRefCountForWait;

	return totalNumberOfRefCount;
}