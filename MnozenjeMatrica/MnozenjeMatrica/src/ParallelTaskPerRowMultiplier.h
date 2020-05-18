#pragma once

#include "Matrix.h"
#include "ParallelTaskMultiplierBase.h"
#include "Structures.h"
#include "tbb/task.h"

class ParallelTaskPerRow : public ParallelTask
{
public:
	ParallelTaskPerRow(const MultiplicationElements multiplicationElements_, const size_t rowIndex_) noexcept;
	~ParallelTaskPerRow() = default;

	tbb::task* execute() override;
private:
	const size_t rowIndex;
};

class ParallelTaskPerRowMultiplier : public ParalellTaskMultiplierBase
{
public:
	ParallelTaskPerRowMultiplier() = default;
	~ParallelTaskPerRowMultiplier() = default;

	[[nodiscard]] static MatrixMultiplierBase* create() noexcept;

private:
	void fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept override;
	[[nodiscard]] int getTotalNumberOfRefCount(const Matrix& resultOfMultiplication) const noexcept;
};