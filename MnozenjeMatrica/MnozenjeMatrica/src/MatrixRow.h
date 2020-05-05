#pragma once

#include <ostream>

class MatrixRow
{
public:
	MatrixRow(int* const startOfRowPtr_, const size_t numberOfElements_) noexcept;

	[[nodiscard]] int& operator[](const size_t elementIndex);
	[[nodiscard]] const int& operator[](const size_t elementIndex) const;

	friend std::ostream& operator << (std::ostream& out, const MatrixRow& mr) noexcept;

private:
	void throwIfColumnIndexIsOutOfBounds(const size_t elementIndex) const;
	[[nodiscard]] bool validateColumnIndex(const size_t elementIndex) const noexcept;

	int* const startOfRowPtr;
	size_t numberOfElements;
};

std::ostream& operator << (std::ostream& out, const MatrixRow& mr) noexcept;
