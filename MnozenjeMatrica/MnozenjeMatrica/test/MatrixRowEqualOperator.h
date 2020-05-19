#pragma once

#include "gtest\gtest.h"
#include "StructuresForTests.h"

struct MatrixRowOperatorTest
{
	size_t leftRowNumberOfElements;
	size_t rightRowNumberOfElements;
	bool areSame;
};

struct MatrixRowEqualOperatorDimensionsTest : public testing::TestWithParam <MatrixRowOperatorTest>
{
};