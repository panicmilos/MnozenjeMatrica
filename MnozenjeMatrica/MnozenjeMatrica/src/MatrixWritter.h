#pragma once

#include <fstream>

#include "Matrix.h"
#include "MatrixSerializationBase.h"

class MatrixWritter : public MatrixSerializationBase<std::ofstream>
{
public:
	MatrixWritter() = default;
	MatrixWritter(const MatrixWritter&) = delete;
	MatrixWritter(MatrixWritter&&) = delete;
	MatrixWritter& operator=(const MatrixWritter&) = delete;
	MatrixWritter& operator=(MatrixWritter&&) = delete;
	~MatrixWritter() = default;

	MatrixWritter& operator<<(const Matrix& m) noexcept;

private:
	void writeMatrixHeader(const Matrix& m) noexcept;
	void writeMatrixBody(const Matrix& m) noexcept;
	void writeEndOfFormatCharacter() noexcept;
};