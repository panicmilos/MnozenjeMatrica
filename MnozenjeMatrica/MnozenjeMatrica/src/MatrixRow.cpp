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
	#ifndef NDEBUG
	throwIfElementIndexIsOutOfBounds(elementIndex);
	#endif

	return startOfRowPtr[elementIndex];
}

const int& MatrixRow::operator[](const size_t elementIndex) const noexcept(false)
{
	#ifndef NDEBUG
	throwIfElementIndexIsOutOfBounds(elementIndex);
	#endif

	return startOfRowPtr[elementIndex];
}

void MatrixRow::throwIfElementIndexIsOutOfBounds(const size_t elementIndex) const noexcept(false)
{
	if (!validateElementIndex(elementIndex))
	{
		throw MatrixIndexOutOfBounds("Given columnIndex is out of bounds!");
	}
}

bool MatrixRow::validateElementIndex(const size_t elementIndex) const noexcept
{
	const bool isElementIndexInBounds = elementIndex < numberOfElements;

	return isElementIndexInBounds;
}

size_t MatrixRow::getSize() const noexcept
{
	return numberOfElements;
}

int* const MatrixRow::getRowElements() const noexcept
{
	return startOfRowPtr;
}

bool operator==(const MatrixRow& leftRow, const MatrixRow& rightRow) noexcept
{
	if (!rowsHaveSameNumberOfElements(leftRow, rightRow))
	{
		return false;
	}

	const bool allElementsAreSame = rowsHaveSameElements(leftRow, rightRow);

	return allElementsAreSame;
}

bool rowsHaveSameNumberOfElements(const MatrixRow& leftRow, const MatrixRow& rightRow) noexcept
{
	const bool numberOfElementsAreSame = leftRow.numberOfElements == rightRow.numberOfElements;

	return numberOfElementsAreSame;
}

bool rowsHaveSameElements(const MatrixRow& leftRow, const MatrixRow& rightRow) noexcept
{
	const size_t numberOfElementsInRow = leftRow.numberOfElements;
	const int* const startOfLeftRowPtr = leftRow.startOfRowPtr;
	const int* const endOfLeftRowPtr = leftRow.startOfRowPtr + numberOfElementsInRow;
	const int* const startOfRightRowPtr = rightRow.startOfRowPtr;
	const bool allElementsAreSame = std::equal(startOfLeftRowPtr, endOfLeftRowPtr, startOfRightRowPtr);

	return allElementsAreSame;
}

bool operator!=(const MatrixRow& leftRow, const MatrixRow& rightRow) noexcept
{
	const bool areRowSame = leftRow == rightRow;

	return !areRowSame;
}

std::ostream& operator << (std::ostream& out, const MatrixRow& mr) noexcept
{
	const size_t numberOfElementsInRow = mr.numberOfElements;
	const int* const startOfRowPtr = mr.startOfRowPtr;
	const int* const endOfRowPtr = startOfRowPtr + numberOfElementsInRow;

	std::ostream_iterator<int> outIt(out, " ");
	std::copy(startOfRowPtr, endOfRowPtr, outIt);

	Utils::deleteLastNCharsInStream(out, 1ll);

	return out;
}