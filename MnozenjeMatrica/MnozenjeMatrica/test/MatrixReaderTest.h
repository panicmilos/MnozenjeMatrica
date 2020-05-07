#pragma once

#include <string>

#include "gtest\gtest.h"

struct MatrixReaderWithBadFormat : public ::testing::TestWithParam<std::string>
{
};