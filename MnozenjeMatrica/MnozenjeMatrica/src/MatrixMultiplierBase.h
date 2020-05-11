#pragma once

#include "Matrix.h"

class MatrixMultiplierBase
{
public:
	[[nodiscard]] Matrix operator()(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false);

protected:
	[[nodiscard]] virtual Matrix doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept = 0;

private:
	void throwIfDimensionsAreBad(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false);

	[[nodiscard]] bool validateDimensionsForMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept;
};