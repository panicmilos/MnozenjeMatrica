#include "MatrixRow.h"

#include "MatrixExceptions.h"

MatrixRow::MatrixRow(int* const startOfRowPtr_, const size_t numberOfElements_) noexcept :
	startOfRowPtr(startOfRowPtr_),
	numberOfElements(numberOfElements_)
{
}

int& MatrixRow::operator[](const size_t elementIndex) noexcept(false)
{
	throwIfColumnIndexIsOutOfBounds(elementIndex);

	return startOfRowPtr[elementIndex];
}

const int& MatrixRow::operator[](const size_t elementIndex) const noexcept(false)
{
	throwIfColumnIndexIsOutOfBounds(elementIndex);

	return startOfRowPtr[elementIndex];
}

void MatrixRow::throwIfColumnIndexIsOutOfBounds(const size_t elementIndex) const noexcept(false)
{
	if (!validateColumnIndex(elementIndex))
	{
		throw MatrixIndexOutOfBounds("Given columnIndex is out of bounds.\n");
	}
}

bool MatrixRow::validateColumnIndex(const size_t elementIndex) const noexcept
{
	const bool isElementIndexInBounds = elementIndex < numberOfElements;

	return isElementIndexInBounds;
}

std::ostream& operator << (std::ostream& out, const MatrixRow& mr) noexcept
{
	return out << mr.startOfRowPtr;
}