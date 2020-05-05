#pragma once

#include <stdexcept>
#include <initializer_list>
#include <string>

constexpr int DEFAULT_ELEMENT_VALUE = 0;

class MatrixHaveBadDimensions : public std::runtime_error
{
public:
	explicit MatrixHaveBadDimensions(const char* exceptionMessage);
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
