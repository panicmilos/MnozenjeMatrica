#pragma once

#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <iterator>

class Matrix
{
public:
	Matrix() = default;

	Matrix(const size_t numberOfRows_, const size_t numberOfColumns_) :
		matrixElements(new int[numberOfRows_ * numberOfColumns_]()),
		numberOfRows(numberOfRows_),
		numberOfColumns(numberOfColumns_)
	{
	}

	Matrix(const std::initializer_list<std::initializer_list<int>>& matrixElements_)
	{
		if (!validateMatrixDimensionsForInitializerListConstructor(matrixElements_))
		{
			throw std::runtime_error("Dimenstion are wrong");
		}

		numberOfRows = matrixElements_.size();
		numberOfColumns = matrixElements_.begin()->size();
		matrixElements = new int[numberOfRows * numberOfColumns]();

		for (auto rowIt = matrixElements_.begin(); rowIt != matrixElements_.end(); ++rowIt)
		{
			size_t rowIndex = rowIt - matrixElements_.begin();
			for (auto columnIt = rowIt->begin(); columnIt != rowIt->end(); ++columnIt)
			{
				size_t columnIndex = columnIt - rowIt->begin();

				matrixElements[rowIndex * numberOfRows + columnIndex] = *columnIt;
			}
		}
	}

	~Matrix()
	{
		delete matrixElements;
	}

	void print()
	{
		for (size_t i = 0; i < numberOfRows; ++i)
		{
			for (size_t j = 0; j < numberOfColumns; ++j)
			{
				std::cout << matrixElements[i * numberOfColumns + j] << ' ';
			}
			std::cout << '\n';
		}
	}
private:
	bool validateMatrixDimensionsForInitializerListConstructor(const std::initializer_list<std::initializer_list<int>>& matrixElements)
	{
		if (!areAllColumnsInListInitializerSameSize(matrixElements) || !doesListInitializerHasMoreThenOneColumn(matrixElements))
		{
			return false;
		}

		return true;
	}

	bool areAllColumnsInListInitializerSameSize(const std::initializer_list<std::initializer_list<int>>& matrixElements)
	{
		auto firstColumnPtr = matrixElements.begin();
		size_t sizeOfFirstColumn = firstColumnPtr->size();

		auto compareColumnSizeToSizeOfFirstColumn = [&sizeOfFirstColumn](std::initializer_list<int> columnPtr)
		{
			size_t sizeOfColumn = columnPtr.size();

			return sizeOfFirstColumn == sizeOfColumn;
		};

		bool allColumnsHaveSameSize = std::all_of(matrixElements.begin(), matrixElements.end(), compareColumnSizeToSizeOfFirstColumn);

		return allColumnsHaveSameSize;
	}

	bool doesListInitializerHasMoreThenOneColumn(const std::initializer_list<std::initializer_list<int>>& matrixElements)
	{
		auto firstColumnPtr = matrixElements.begin();
		size_t sizeOfFirstColumn = firstColumnPtr->size();

		return sizeOfFirstColumn != 0;
	}

	int* matrixElements = nullptr;
	size_t numberOfRows = 0;
	size_t numberOfColumns = 0;
};
