#include "ParallelTaskPerThreadMultiplier.h"

#include "tbb\task_scheduler_init.h"

ParallelTaskPerThread::ParallelTaskPerThread(const MultiplicationElements multiplicationElements_, const ElementsRange elements_) noexcept :
	ParallelTask(multiplicationElements_),
	elements(elements_)
{
}

tbb::task* ParallelTaskPerThread::execute()
{
	auto [leftMatrix, rightMatrix, resultOfMultiplication] = multiplicationElements;
	const auto [firstElementPosition, lastElementsPosition] = elements;
	const size_t numberOfElementsInResultMatrixRow = resultOfMultiplication.getNumberOfColumns();
	const size_t numberOfElementsInLeftMatrixColumn = leftMatrix.getNumberOfColumns();

	for (size_t elementIndexIn1D = firstElementPosition; elementIndexIn1D < lastElementsPosition; ++elementIndexIn1D)
	{
		const auto [rowIndex, columnIndex] = get2DElementIndexFrom1D(elementIndexIn1D, numberOfElementsInResultMatrixRow);
		int sumOfRowColumnPairs = 0;
		for (size_t sharedIndex = 0; sharedIndex < numberOfElementsInLeftMatrixColumn; ++sharedIndex)
		{
			sumOfRowColumnPairs += leftMatrix[rowIndex][sharedIndex] * rightMatrix[sharedIndex][columnIndex];
		}
		resultOfMultiplication[rowIndex][columnIndex] = sumOfRowColumnPairs;
	}
	return nullptr;
}

ElementIndex ParallelTaskPerThread::get2DElementIndexFrom1D(const size_t elementIndexIn1D, const size_t numberOfElementsInRow) const noexcept
{
	const size_t rowIndex = elementIndexIn1D / numberOfElementsInRow;
	const size_t columnIndex = elementIndexIn1D % numberOfElementsInRow;

	const ElementIndex elementIndexIn2d = {
		rowIndex,
		columnIndex
	};

	return elementIndexIn2d;
}

MatrixMultiplierBase* ParallelTaskPerThreadMultiplier::create() noexcept
{
	return new ParallelTaskPerThreadMultiplier();
}

void ParallelTaskPerThreadMultiplier::fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept
{
	fillListWithAllTasksExceptLastOne(parentsTasks, parent, multiplicationElements);
	fillListWithLastTask(parentsTasks, parent, multiplicationElements);

	const int totalNumberOfRefCount = getTotalNumberOfRefCount();
	parent.set_ref_count(totalNumberOfRefCount);
}

void ParallelTaskPerThreadMultiplier::fillListWithAllTasksExceptLastOne(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept
{
	const Matrix& resultOfMultiplication = multiplicationElements.resultOfMultiplication;
	const size_t numberOfElements = resultOfMultiplication.getSize();
	const int numberOfThreads = getNumberOfProcessorThreads();
	const size_t numberOfElementsPerThread = getNumberOfElementsPerThread(numberOfElements);
	const int numberOfThreadsWithoutLastOne = numberOfThreads - 1;

	for (int threadIndex = 0; threadIndex < numberOfThreadsWithoutLastOne; ++threadIndex)
	{
		// racuna se range elemenata
		const size_t firstElementInRange = threadIndex * numberOfElementsPerThread;
		const size_t lastElementInRange = (threadIndex + 1) * numberOfElementsPerThread;
		const ElementsRange elements = { firstElementInRange, lastElementInRange };
		tbb::task& elementsCalculation = *new(parent.allocate_child()) ParallelTaskPerThread(multiplicationElements, elements);
		parentsTasks.push_back(elementsCalculation);
	}
}

void ParallelTaskPerThreadMultiplier::fillListWithLastTask(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept
{
	const Matrix& resultOfMultiplication = multiplicationElements.resultOfMultiplication;
	const size_t numberOfElements = resultOfMultiplication.getSize();
	const size_t numberOfElementsPerThread = getNumberOfElementsPerThread(numberOfElements);
	const int numberOfThreads = getNumberOfProcessorThreads();
	const size_t lastThreadIndex = numberOfThreads - 1;

	const size_t firstElementInRange = lastThreadIndex * numberOfElementsPerThread;
	const size_t lastElementInRangeWithoutError = (lastThreadIndex + 1) * numberOfElementsPerThread;
	const size_t dividingError = getDividingElementsPerThreadError(numberOfElements);
	const size_t lastElementInRangeWithError = lastElementInRangeWithoutError + dividingError;

	const ElementsRange elements = { firstElementInRange, lastElementInRangeWithError };
	tbb::task& elementsCalculation = *new(parent.allocate_child()) ParallelTaskPerThread(multiplicationElements, elements);
	parentsTasks.push_back(elementsCalculation);
}

size_t ParallelTaskPerThreadMultiplier::getNumberOfElementsPerThread(const size_t numberOfElements) const noexcept
{
	const int numberOfThreads = getNumberOfProcessorThreads();
	const size_t numberOfElementsPerThread = numberOfElements / numberOfThreads;

	return numberOfElementsPerThread;
}

int ParallelTaskPerThreadMultiplier::getNumberOfProcessorThreads() const noexcept
{
	const int numberOfThreads = tbb::task_scheduler_init::default_num_threads();

	return numberOfThreads;
}

size_t ParallelTaskPerThreadMultiplier::getDividingElementsPerThreadError(const size_t numberOfElements) const noexcept
{
	const int numberOfThreads = getNumberOfProcessorThreads();
	const size_t numberOfElementsPerThread = getNumberOfElementsPerThread(numberOfElements);
	const size_t numberOfElementsWithError = numberOfThreads * numberOfElementsPerThread;
	const size_t dividingError = numberOfElements - numberOfElementsWithError;

	return dividingError;
}

int ParallelTaskPerThreadMultiplier::getTotalNumberOfRefCount() const noexcept
{
	const int numberOfParentsTasks = getNumberOfProcessorThreads();
	const int additionalRefCountForWait = 1;
	const int totalNumberOfRefCount = numberOfParentsTasks + additionalRefCountForWait;

	return totalNumberOfRefCount;
}