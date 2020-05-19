#pragma once

#include "gtest\gtest.h"
#include "StructuresForTests.h"

struct MatrixEqualOperatorTest
{
	Dimensions leftMatrixDimensions;
	Dimensions rightMatrixDimensions;
	bool areSame;
};

struct MatrixEqualOperatorDimensionsTest : public testing::TestWithParam <MatrixEqualOperatorTest>
{
};