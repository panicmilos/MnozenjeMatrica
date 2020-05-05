#pragma once

#include "gtest\gtest.h"
#include "../src/Matrix.h"

struct Dimensions
{
	size_t numberOfRows;
	size_t numberOfColumns;
};

struct MatrixForTest : public ::testing::Test
{
public:
	MatrixForTest();

protected:
	Matrix m;
};