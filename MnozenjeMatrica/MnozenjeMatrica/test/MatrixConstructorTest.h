#pragma once

#include <initializer_list>

#include "gtest\gtest.h"
#include "../src/Matrix.h"
#include "../src/MatrixRow.h"

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
		m[0][0] = 2;
		m[0][1] = 23;
		m[0][2] = -4;
		m[1][0] = 55;
		m[1][2] = 6;
	}
};

struct MatrixConstructorCopy : public MatrixForTest
{
};

struct MatrixConstructorMove : public MatrixForTest
{
};

const std::initializer_list<std::initializer_list<int>> InitializerListCase1 = { {} };
const std::initializer_list<std::initializer_list<int>> InitializerListCase2 = { {}, {} };
const std::initializer_list<std::initializer_list<int>> InitializerListCase3 = { {1, 2}, {3} };

struct MatrixConstructorWithBadInitializerList : public ::testing::TestWithParam<std::initializer_list<std::initializer_list<int>>>
{
};
