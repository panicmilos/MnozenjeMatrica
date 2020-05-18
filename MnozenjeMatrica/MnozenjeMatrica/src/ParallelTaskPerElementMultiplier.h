#pragma once

#include "Matrix.h"
#include "ParallelTaskMultiplierBase.h"
#include "Structures.h"
#include "tbb/task.h"

class ParallelTaskPerElement : public ParallelTask
{
public:
	ParallelTaskPerElement(const MultiplicationElements multiplicationElements_, const ElementIndex element_) noexcept;
	~ParallelTaskPerElement() = default;

	tbb::task* execute() override;
private:
	const ElementIndex element;
};

class ParallelTaskPerElementMultiplier : public ParalellTaskMultiplierBase
{
public:
	ParallelTaskPerElementMultiplier() = default;
	~ParallelTaskPerElementMultiplier() = default;

	[[nodiscard]] static MatrixMultiplierBase* create() noexcept;

private:
	void fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept override;
	[[nodiscard]] int getTotalNumberOfRefCount(const Matrix& resultOfMultiplication) const noexcept;
};