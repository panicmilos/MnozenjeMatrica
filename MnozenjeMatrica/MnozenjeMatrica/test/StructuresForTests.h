#pragma once

#include "gtest\gtest.h"
#include "../src/Matrix.h"

struct Dimensions
{
	size_t numberOfRows;
	size_t numberOfColumns;
};

struct Element
{
	int value;
	size_t rowIndex;
	size_t columnIndex;
};

struct MatrixEqualOperatorTest
{
	Dimensions leftMatrixDimensions;
	Dimensions rightMatrixDimensions;
	bool areSame;
};

struct MatrixForTest : public ::testing::Test
{
public:
	MatrixForTest();

protected:
	Matrix m;
};
