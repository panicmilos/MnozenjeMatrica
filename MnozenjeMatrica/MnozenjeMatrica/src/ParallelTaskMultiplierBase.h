#pragma once

#include "Matrix.h"
#include "MatrixMultiplierBase.h"
#include "Structures.h"
#include "tbb/task.h"

class ParallelTask : public tbb::task
{
public:
	ParallelTask(const MultiplicationElements multiplicationElements_) noexcept;
	virtual ~ParallelTask() = default;

	virtual task* execute() = 0;

protected:
	const MultiplicationElements multiplicationElements;
};

class ParalellTaskMultiplierBase : public MatrixMultiplierBase
{
public:
	ParalellTaskMultiplierBase() = default;
	virtual ~ParalellTaskMultiplierBase() = default;

protected:
	[[nodiscard]] Matrix doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept override;

	virtual void fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept = 0;

private:
	void handleParentsTasks(tbb::empty_task& parent, tbb::task_list& parentsTasks) const noexcept;
};