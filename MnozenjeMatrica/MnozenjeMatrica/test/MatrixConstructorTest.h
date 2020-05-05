#pragma once

#include <initializer_list>

#include "gtest\gtest.h"
#include "../src/Matrix.h"

struct MatrixDimensions
{
	size_t numberOfRows;
	size_t numberOfColumns;
};

struct MatrixConstructorWithBadParams : public ::testing::TestWithParam<MatrixDimensions>
{
};

struct MatrixForTest : public ::testing::Test
{
protected:
	Matrix m;

public:
	MatrixForTest() : m(2, 3)
	{
		int* const matrixElements = m.getMatrixElements();
		matrixElements[0] = 2;
		matrixElements[1] = 23;
		matrixElements[2] = -4;
		matrixElements[3] = 55;
		matrixElements[5] = 6;
	} // promeniti kada se upaci operator ()
};

struct MatrixConstructorCopy : public MatrixForTest
{
};

struct MatrixConstructorMove : public MatrixForTest
{
};
