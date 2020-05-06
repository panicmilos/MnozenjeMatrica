#pragma once

#include <fstream>

#include "Matrix.h"
#include "MatrixSerializationBase.h"

class MatrixWritter : public MatrixSerializationBase<std::ofstream>
{
public:
	MatrixWritter() = default;
	~MatrixWritter() = default; // proveriti copy i move?

	MatrixWritter& operator<<(const Matrix& m) noexcept;

private:
	void writeMatrixHeader(const Matrix& m) noexcept;
	void writeMatrixBody(const Matrix& m) noexcept;
	void writeEndOfFormatCharacter() noexcept;
};