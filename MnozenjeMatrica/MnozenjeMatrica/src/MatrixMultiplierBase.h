#pragma once

#include "Matrix.h"

class MatrixMultiplierBase
{
public:
	MatrixMultiplierBase() = default;
	virtual ~MatrixMultiplierBase() = default;

	[[nodiscard]] Matrix multiply(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false);

protected:
	[[nodiscard]] virtual Matrix doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept = 0;

private:
	void throwIfDimensionsAreBad(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept(false);

	// Proverava da li broj kolona prve je isti kao broj redova druge matrice
	[[nodiscard]] bool validateDimensionsForMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept;
};