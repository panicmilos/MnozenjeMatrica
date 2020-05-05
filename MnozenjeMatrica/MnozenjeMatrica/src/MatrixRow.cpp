#include "MatrixRow.h"

#include "MatrixExceptions.h"

MatrixRow::MatrixRow(int* const startOfRowPtr_, const size_t numberOfElements_) noexcept :
	startOfRowPtr(startOfRowPtr_),
	numberOfElements(numberOfElements_)
{
}

int& MatrixRow::operator[](const size_t elementIndex)
{
	throwIfColumnIndexIsOutOfBounds(elementIndex);

	return startOfRowPtr[elementIndex];
}

const int& MatrixRow::operator[](const size_t elementIndex) const
{
	throwIfColumnIndexIsOutOfBounds(elementIndex);

	return startOfRowPtr[elementIndex];
}

void MatrixRow::throwIfColumnIndexIsOutOfBounds(const size_t elementIndex) const
{
	if (!validateColumnIndex(elementIndex))
	{
		throw MatrixIndexOutOfBounds("Given columnIndex is out of bounds.\n");
	}
}

bool MatrixRow::validateColumnIndex(const size_t elementIndex) const noexcept
{
	const bool isElementIndexOutOfBounds = elementIndex >= numberOfElements;
	if (isElementIndexOutOfBounds)
	{
		return false;
	}

	return true;
}

std::ostream& operator << (std::ostream& out, const MatrixRow& mr) noexcept
{
	return out << mr.startOfRowPtr;
}