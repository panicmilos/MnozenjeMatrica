#pragma once

#include "gtest\gtest.h"
#include "StructuresForTests.h"

struct MatrixIndexingOperatorWithParamsInBound : public MatrixForTest, public testing::WithParamInterface<Element>
{
};

struct MatrixIndexingOperatorWithParamsRowOutOfBound : public MatrixForTest, public testing::WithParamInterface<Element>
{
};

struct MatrixIndexingOperatorWithParamsColumnOutOfBound : public MatrixForTest, public testing::WithParamInterface<Element>
{
};
