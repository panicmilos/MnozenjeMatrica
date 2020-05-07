#pragma once

#include <fstream>

#include "Matrix.h"
#include "MatrixSerializationBase.h"

class MatrixReader : public MatrixSerializationBase<std::ifstream>
{
public:
	MatrixReader() = default;
	MatrixReader(const MatrixReader&) = delete;
	MatrixReader(MatrixReader&&) = delete;
	MatrixReader& operator=(const MatrixReader&) = delete;
	MatrixReader& operator=(MatrixReader&&) = delete;
	~MatrixReader() = default;

	MatrixReader& operator>>(Matrix& m) noexcept(false);

private:
	void readMatrixFromFile() noexcept(false);
	void readMatrixHeader() noexcept;
	void readMatrixBody() noexcept;
	void readEndOfFormatCharacter() noexcept;

	void throwIfMatrixFormatInFileIsBad() noexcept(false);

	void createMatrixWithReadDimensionsFromFile() noexcept;

	Matrix matrixFromFile;

	struct
	{
		size_t numberOfRows = 0;
		size_t numberOfColumns = 0;
	} Dimensions;
};
