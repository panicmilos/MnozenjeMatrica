#pragma once

#include <stdexcept>

#define DeclareExceptionClass(exceptionName)                  \
class exceptionName : public std::runtime_error               \
{                                                             \
public:                                                       \
	explicit exceptionName(const char* exceptionMessage);     \
};															  \

DeclareExceptionClass(MatrixHaveBadDimensions);
DeclareExceptionClass(MatrixIndexOutOfBounds);
DeclareExceptionClass(FileCouldNotBeOpened);
DeclareExceptionClass(BadMatrixFormatInFile);