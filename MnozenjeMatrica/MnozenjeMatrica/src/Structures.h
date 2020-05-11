#pragma once

#include "Matrix.h"

struct ElementIndex
{
	size_t rowIndex = 0;
	size_t columnIndex = 0;
};

struct ElementsRange
{
	size_t firstElement = 0;
	size_t lastElement = 0;
};

struct MultiplicationElements
{
	const Matrix& leftMatrix;
	const Matrix& rightMatrix;
	Matrix& resultOfMultiplication;
};