#pragma once

#include <initializer_list>
#include <string>

constexpr int DEFAULT_ELEMENT_VALUE = 0;

#include <iostream> // remove;
#include "MatrixExceptions.h"

class MatrixRow
{
public:
	MatrixRow(int* const rowStartPtr_, const size_t numberOfColumns_) :
		rowStartPtr(rowStartPtr_),
		numberOfColumns(numberOfColumns_)
	{
	}

	int& operator[](size_t columnIndex)
	{
		if (!validateColumnIndex(columnIndex))
		{
			std::cout << "GRESKA!\n";

			return rowStartPtr[0];
		}

		return rowStartPtr[columnIndex];
	}

	const int& operator[](size_t columnIndex) const
	{
		if (!validateColumnIndex(columnIndex))
		{
			std::cout << "GRESKA!\n";

			return rowStartPtr[0];
		}

		return rowStartPtr[columnIndex];
	}

	friend std::ostream& operator << (std::ostream& out, const MatrixRow& mr)
	{
		return out << mr.rowStartPtr;
	}

private:
	bool validateColumnIndex(size_t columnIndex) const
	{
		if (columnIndex >= numberOfColumns)
		{
			return false;
		}

		return true;
	}

	int* const rowStartPtr;
	size_t numberOfColumns;
};

class Matrix
{
public:
	Matrix() = default;
	Matrix(const size_t numberOfRows_, const size_t numberOfColumns_, const int defaultElementValue = DEFAULT_ELEMENT_VALUE);
	Matrix(const Matrix& m);
	Matrix(Matrix&& m) noexcept;
	Matrix(const std::initializer_list<std::initializer_list<int>>& matrixElements_);
	~Matrix();

	Matrix& operator=(const Matrix& m);
	Matrix& operator=(Matrix&& m) noexcept;

	MatrixRow operator[](size_t rowIndex)
	{
		return MatrixRow(matrixElements + rowIndex * numberOfColumns, numberOfColumns);
	}

	const MatrixRow operator[](size_t rowIndex) const
	{
		return MatrixRow(matrixElements + rowIndex * numberOfColumns, numberOfColumns);
	}

	size_t getNumberOfRows() const;
	size_t getNumberOfColumns() const;
	size_t getSize() const;
	int* const getMatrixElements() const;

	void print();

private:
	bool ValidateDimensionsForParametarizedConstructor(const size_t numberOfRows, const size_t numberOfColumns) const;
	bool validateMatrixDimensionsForInitializerListConstructor(const std::initializer_list<std::initializer_list<int>>& matrixElements) const;
	bool areAllColumnsInListInitializerSameSize(const std::initializer_list<std::initializer_list<int>>& matrixElements) const;
	bool doesListInitializerHasMoreThenOneColumn(const std::initializer_list<std::initializer_list<int>>& matrixElements) const;

	int* matrixElements = nullptr;
	size_t numberOfRows = 0;
	size_t numberOfColumns = 0;
};
