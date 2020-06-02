#pragma once

#include <initializer_list>
#include <ostream>
#include <string>

#include "MatrixRow.h"

constexpr int DEFAULT_ELEMENT_VALUE = 0;

class Matrix
{
public:
	Matrix() = default;
	Matrix(const size_t numberOfRows_, const size_t numberOfColumns_, const int elementsValue = DEFAULT_ELEMENT_VALUE) noexcept(false);
	Matrix(const Matrix& m) noexcept(false);
	Matrix(Matrix&& m) noexcept;
	Matrix(const std::initializer_list<std::initializer_list<int>>& matrixElements_) noexcept(false);
	~Matrix() noexcept;

	Matrix& operator=(const Matrix& m) noexcept(false);
	Matrix& operator=(Matrix&& m) noexcept;
	friend bool operator==(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;
	friend bool operator!=(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;

	friend std::ostream& operator << (std::ostream& out, const Matrix& m) noexcept;
	friend bool matricesHaveSameDimensions(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;
	friend bool matricesHaveSameElements(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;

	[[nodiscard]] MatrixRow operator[](const size_t rowIndex) noexcept(false);
	[[nodiscard]] const MatrixRow operator[](const size_t rowIndex) const noexcept(false);

	[[nodiscard]] size_t getNumberOfRows() const noexcept;
	[[nodiscard]] size_t getNumberOfColumns() const noexcept;
	[[nodiscard]] size_t getSize() const noexcept;
	[[nodiscard]] int* const getMatrixElements() const noexcept;

private:
	void throwIfRowIndexIsOutOfBounds(const size_t rowIndex) const noexcept(false);

	// Proverava da li je broj redova i kolona veci od 0
	[[nodiscard]] bool validateDimensionsForParametarizedConstructor(const size_t numberOfRows, const size_t numberOfColumns) const noexcept;
	// Poziva dve provere ispod
	[[nodiscard]] bool validateDimensionsForInitializerListConstructor(const std::initializer_list<std::initializer_list<int>>& matrixElements) const noexcept;
	// Proverava da li su velicine svih kolona iste posto kolone mogu biti tipa { {1, 2}, {1}, {1, 2, 4, 5}, {} }
	[[nodiscard]] bool areAllColumnsInListInitializerSameSize(const std::initializer_list<std::initializer_list<int>>& matrixElements) const noexcept;
	// Proverava da nije { {} }
	[[nodiscard]] bool doesListInitializerHaveAtLeastOneColumn(const std::initializer_list<std::initializer_list<int>>& matrixElements) const noexcept;
	[[nodiscard]] bool validateRowIndex(const size_t rowIndex) const noexcept;

	int* matrixElements = nullptr;
	size_t numberOfRows = 0;
	size_t numberOfColumns = 0;
};

[[nodiscard]] bool operator==(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;
[[nodiscard]] bool operator!=(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;

std::ostream& operator << (std::ostream& out, const Matrix& m) noexcept;
[[nodiscard]] bool matricesHaveSameDimensions(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;
[[nodiscard]] bool matricesHaveSameElements(const Matrix& leftMatrix, const Matrix& rightMatrix) noexcept;