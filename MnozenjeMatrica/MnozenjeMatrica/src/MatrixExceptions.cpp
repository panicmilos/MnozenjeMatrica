#include "MatrixExceptions.h"

MatrixHaveBadDimensions::MatrixHaveBadDimensions(const char* exceptionMessage) :
	std::runtime_error(exceptionMessage)
{
}

MatrixIndexOutOfBounds::MatrixIndexOutOfBounds(const char* exceptionMessage) :
	std::runtime_error(exceptionMessage)
{
}