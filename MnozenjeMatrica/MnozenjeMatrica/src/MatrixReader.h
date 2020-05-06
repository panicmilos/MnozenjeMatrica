#pragma once

#include <fstream>

#include "Matrix.h"
#include "MatrixSerializationBase.h"

class MatrixReader : public MatrixSerializationBase<std::ifstream>
{
public:
	MatrixReader() = default;
	~MatrixReader() = default;

	MatrixReader& operator>>(Matrix& m) { return *this; }
};
