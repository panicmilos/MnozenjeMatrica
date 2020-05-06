#include "MatrixRow.h"

#include <iterator>

#include "MatrixExceptions.h"
#include "Utils.h"

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
		throw MatrixIndexOutOfBounds("Given columnIndex is out of bounds!");
	}
}

bool MatrixRow::validateColumnIndex(const size_t elementIndex) const noexcept
{
	const bool isElementIndexInBounds = elementIndex < numberOfElements;

	return isElementIndexInBounds;
}

std::ostream& operator << (std::ostream& out, const MatrixRow& mr) noexcept
{
	const int numberOfElementsInRow = mr.numberOfElements;
	const int* const startOfRowPtr = mr.startOfRowPtr;
	const int* const endOfRowPtr = startOfRowPtr + numberOfElementsInRow;

	std::ostream_iterator<int> outIt(out, " ");
	std::copy(startOfRowPtr, endOfRowPtr, outIt);

	Utils::deleteLastNCharInStream(out, 1ll);

	return out;
}