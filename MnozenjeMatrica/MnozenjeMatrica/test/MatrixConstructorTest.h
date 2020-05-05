#pragma once

#include <initializer_list>

#include "gtest\gtest.h"
#include "StructuresForTests.h"

struct MatrixConstructorWithBadParams : public ::testing::TestWithParam<Dimensions>
{
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
