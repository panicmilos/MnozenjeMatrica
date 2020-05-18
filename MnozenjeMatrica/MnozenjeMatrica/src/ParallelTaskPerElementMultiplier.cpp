#include "ParallelTaskPerElementMultiplier.h"

#include "Profiling.h"

ParallelTaskPerElement::ParallelTaskPerElement(const MultiplicationElements multiplicationElements_, const ElementIndex element_) noexcept :
	ParallelTask(multiplicationElements_),
	element(element_)
{
}

tbb::task* ParallelTaskPerElement::execute()
{
	auto [leftMatrix, rightMatrix, resultOfMultiplication] = multiplicationElements;
	const auto [rowIndex, columnIndex] = element;
	const size_t numberOfElements = leftMatrix.getNumberOfColumns();

	int sumOfRowColumnPairs = 0;
	for (size_t sharedIndex = 0; sharedIndex < numberOfElements; ++sharedIndex)
	{
		sumOfRowColumnPairs += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
	}
	resultOfMultiplication[rowIndex][columnIndex] = sumOfRowColumnPairs;

	return nullptr;
}

MatrixMultiplierBase* ParallelTaskPerElementMultiplier::create() noexcept
{
	return new ParallelTaskPerElementMultiplier();
}

void ParallelTaskPerElementMultiplier::fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept
{
	const Matrix& resultOfMultiplication = multiplicationElements.resultOfMultiplication;
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

int ParallelTaskPerElementMultiplier::getTotalNumberOfRefCount(const Matrix& resultOfMultiplication) const noexcept
{
	const size_t numberOfParentsTasks = resultOfMultiplication.getSize();
	const int additionalRefCountForWait = 1;
	const int totalNumberOfRefCount = (int)numberOfParentsTasks + additionalRefCountForWait;

	return totalNumberOfRefCount;
}