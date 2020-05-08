#include "ParallelTaskMultiplierBase.h"

#include "Profiling.h"

ParallelTask::ParallelTask(MultiplicationElements multiplicationElements_) noexcept :
	multiplicationElements(multiplicationElements_)
{
}

Matrix ParalellTaskMultiplierBase::doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept
{
	PROFILE_SCOPE("ParallelTask");
	const size_t numberOfRowsInLeftMatrix = leftMatrix.getNumberOfRows();
	const size_t numberOfColumnsInRightMatrix = rightMatrix.getNumberOfColumns();

	Matrix resultOfMultiplication(numberOfRowsInLeftMatrix, numberOfColumnsInRightMatrix);
	MultiplicationElements multiplicationElements = { leftMatrix, rightMatrix, resultOfMultiplication };

	tbb::empty_task& parent = *new(tbb::task::allocate_root()) tbb::empty_task();
	tbb::task_list parentsTasks;
	fillTaskListForParent(parentsTasks, parent, multiplicationElements);

	handleParentsTasks(parent, parentsTasks);

	return resultOfMultiplication;
}

void ParalellTaskMultiplierBase::handleParentsTasks(tbb::empty_task& parent, tbb::task_list& parentsTasks) const noexcept
{
	parent.spawn_and_wait_for_all(parentsTasks);
	parent.destroy(parent);
}