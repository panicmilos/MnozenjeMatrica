#pragma once

#include "Matrix.h"
#include "ParallelTaskMultiplierBase.h"
#include "Structures.h"
#include "tbb/task.h"

class ParallelTaskPerRow : public ParallelTask
{
public:
	ParallelTaskPerRow(const MultiplicationElements multiplicationElements_, const int rowIndex_) noexcept;

	tbb::task* execute() override;
private:
	const int rowIndex;
};

class ParallelTaskPerRowMultiplier : public ParalellTaskMultiplierBase
{
private:
	void fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept override;
	[[nodiscard]] int getTotalNumberOfRefCount(const Matrix& resultOfMultiplication) const noexcept;
};