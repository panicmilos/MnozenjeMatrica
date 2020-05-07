#pragma once

#include "../src/Matrix.h"
#include "../src/MatrixMultiplyBase.h"

class MatrixMultiplyBaseTest : public MatrixMultiplyBase
{
protected:
	Matrix doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept override
	{
		return Matrix();
	}
};