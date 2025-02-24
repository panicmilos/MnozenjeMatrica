#pragma once

#include "Matrix.h"
#include "MatrixMultiplierBase.h"

class ParallelForMultiplier : public MatrixMultiplierBase
{
public:
	ParallelForMultiplier() = default;
	~ParallelForMultiplier() = default;

	[[nodiscard]] static MatrixMultiplierBase* create() noexcept;

private:
	[[nodiscard]] Matrix doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept override;
};