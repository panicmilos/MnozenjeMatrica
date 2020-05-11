#pragma once

#include <initializer_list>
#include <string>

#include "MatrixRow.h"

constexpr int DEFAULT_ELEMENT_VALUE = 0;

class Matrix
{
public:
	Matrix() = default;
	Matrix(const size_t numberOfRows_, const size_t numberOfColumns_, const int defaultElementValue = DEFAULT_ELEMENT_VALUE) noexcept(false);
	Matrix(const Matrix& m) noexcept(false);
	Matrix(Matrix&& m) noexcept;
	Matrix(const std::initializer_list<std::initializer_list<int>>& matrixElements_) noexcept(false);
	~Matrix() noexcept;

	Matrix& operator=(const Matrix& m) noexcept(false);
	Matrix& operator=(Matrix&& m) noexcept;
	friend bool operator==(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;
	friend bool operator!=(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;

	[[nodiscard]] MatrixRow operator[](const size_t rowIndex) noexcept(false);
	[[nodiscard]] const MatrixRow operator[](const size_t rowIndex) const noexcept(false);

	[[nodiscard]] size_t getNumberOfRows() const noexcept;
	[[nodiscard]] size_t getNumberOfColumns() const noexcept;
	[[nodiscard]] size_t getSize() const noexcept;
	[[nodiscard]] int* const getMatrixElements() const noexcept;

private:
	void throwIfRowIndexIsOutOfBounds(const size_t rowIndex) const noexcept(false);

	[[nodiscard]] bool validateDimensionsForParametarizedConstructor(const size_t numberOfRows, const size_t numberOfColumns) const noexcept;
	[[nodiscard]] bool validateDimensionsForInitializerListConstructor(const std::initializer_list<std::initializer_list<int>>& matrixElements) const noexcept;
	[[nodiscard]] bool areAllColumnsInListInitializerSameSize(const std::initializer_list<std::initializer_list<int>>& matrixElements) const noexcept;
	[[nodiscard]] bool doesListInitializerHaveAtLeastOneColumn(const std::initializer_list<std::initializer_list<int>>& matrixElements) const noexcept;
	[[nodiscard]] bool validateRowIndex(const size_t rowIndex) const noexcept;

	int* matrixElements = nullptr;
	size_t numberOfRows = 0;
	size_t numberOfColumns = 0;
};

[[nodiscard]] bool operator==(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;
[[nodiscard]] bool operator!=(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;
