#pragma once

#include <initializer_list>

class Matrix
{
public:
	Matrix() = default;
	Matrix(const size_t numberOfRows_, const size_t numberOfColumns_);
	Matrix(const Matrix& m);
	Matrix(Matrix&& m) noexcept;
	Matrix(const std::initializer_list<std::initializer_list<int>>& matrixElements_);
	~Matrix();

	size_t getNumberOfRows() const;
	size_t getNumberOfColumns() const;
	size_t getSize() const;
	const int* const getMatrixElements() const;

	void print();

private:
	bool validateMatrixDimensionsForInitializerListConstructor(const std::initializer_list<std::initializer_list<int>>& matrixElements);
	bool areAllColumnsInListInitializerSameSize(const std::initializer_list<std::initializer_list<int>>& matrixElements);
	bool doesListInitializerHasMoreThenOneColumn(const std::initializer_list<std::initializer_list<int>>& matrixElements);

	int* matrixElements = nullptr;
	size_t numberOfRows = 0;
	size_t numberOfColumns = 0;
};
