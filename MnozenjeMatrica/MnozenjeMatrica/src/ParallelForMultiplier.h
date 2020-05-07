#pragma once

#include "Matrix.h"
#include "MatrixMultiplierBase.h"

class ParallelForMultiplier : public MatrixMultiplierBase
{
private:
	[[nodiscard]] Matrix doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept override;
};