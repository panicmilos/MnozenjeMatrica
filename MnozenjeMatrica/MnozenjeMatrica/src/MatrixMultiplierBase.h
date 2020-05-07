#pragma once

#include "Matrix.h"

class MatrixMultiplierBase
{
public:
	[[nodiscard]] Matrix multiply(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false);

protected:
	[[nodiscard]] virtual Matrix doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept = 0;

private:
	void throwIfNumberOfFirstMatrixColumnsIsNotSameAsNumberOfSecondMatrixRows(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false);

	[[nodiscard]] bool isNumberOfFirstMatrixColumnsSameAsNumberOfSecondMatrixRows(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept;
};
