#pragma once

#include "gtest\gtest.h"
#include "StructuresForTests.h"

struct MatrixAssignmentOperatorCopy : public MatrixForTest
{
};

struct MatrixAssignmentOperatorCopyWithParams : public MatrixForTest, public testing::WithParamInterface<Dimensions>
{
};

struct MatrixAssignmentOperatorMove : public MatrixForTest
{
};