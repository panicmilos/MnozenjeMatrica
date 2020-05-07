#pragma once

#include "../src/Matrix.h"
#include "../src/MatrixMultiplierBase.h"

class MatrixMultiplierBaseTest : public MatrixMultiplierBase
{
protected:
	Matrix doMultiplying(const Matrix& leftMatrix, const Matrix& rightMatrix) const noexcept override
	{
		return Matrix();
	}
};