#pragma once

#include "Matrix.h"

struct ElementIndex
{
	size_t rowIndex = 0;
	size_t columnIndex = 0;
};

struct ElementsRange
{
	size_t firstElementPosition = 0;
	size_t lastElementPosition = 0;
};

struct MultiplicationElements
{
	const Matrix& leftMatrix;
	const Matrix& rightMatrix;
	Matrix& resultOfMultiplication;
};