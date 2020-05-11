#pragma once

#include "Matrix.h"
#include "MatrixMultiplierBase.h"

class SerialMultiplier : public MatrixMultiplierBase
{
public:
	[[nodiscard]] static MatrixMultiplierBase* create() noexcept;

private:
	[[nodiscard]] Matrix doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept override;
};