#pragma once

#include "Matrix.h"
#include "MatrixMultiplierBase.h"
#include "ParallelTaskMultiplierBase.h"
#include "Structures.h"
#include "tbb/task.h"

class ParallelTaskPerElement : public ParallelTask
{
public:
	ParallelTaskPerElement(MultiplicationElements multiplicationElements_, ElementIndex element_) noexcept;

	tbb::task* execute() override;
private:
	ElementIndex element;
};

class ParallelTaskPerElementMultiplier : public ParalellTaskMultiplierBase
{
private:
	void fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept override;
	[[nodiscard]] int getTotalNumberOfRefCount(Matrix& resultOfMultiplication) const noexcept;
};