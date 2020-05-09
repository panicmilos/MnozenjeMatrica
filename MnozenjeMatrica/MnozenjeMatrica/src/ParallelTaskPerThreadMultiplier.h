#pragma once

#include "Matrix.h"
#include "ParallelTaskMultiplierBase.h"
#include "Structures.h"
#include "tbb/task.h"

class ParallelTaskPerThread : public ParallelTask
{
public:
	ParallelTaskPerThread(const MultiplicationElements multiplicationElements_, const ElementRange elements_) noexcept;

	tbb::task* execute() override;
private:
	[[nodiscard]] ElementIndex get2DElementIndexFrom1D(const size_t elementIndexIn1D, const size_t numberOfElementsInColumn) const noexcept;

	const ElementRange elements;
};

class ParallelTaskPerThreadMultiplier : public ParalellTaskMultiplierBase
{
private:
	void fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept override;
	void fillListWithAllTasksExceptLastOne(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept;
	void fillListWithLastTask(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept;

	[[nodiscard]] size_t getNumberOfElementsPerThread(const size_t numberOfColumns) const noexcept;
	[[nodiscard]] int getNumberOfProcessorThreads() const noexcept;
	[[nodiscard]] size_t getDividingElementsPerThreadError(const size_t numberOfElements) const noexcept;

	[[nodiscard]] int getTotalNumberOfRefCount() const noexcept;
};