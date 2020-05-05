#pragma once

#include <stdexcept>

class MatrixHaveBadDimensions : public std::runtime_error
{
public:
	explicit MatrixHaveBadDimensions(const char* exceptionMessage);
};

class MatrixIndexOutOfBounds : public std::runtime_error
{
public:
	explicit MatrixIndexOutOfBounds(const char* exceptionMessage);
};