#include "MatrixExceptions.h"

#define DefineExceptionClass(exceptionName)											\
exceptionName::exceptionName(const char* exceptionMessage) :						\
	std::runtime_error(exceptionMessage)											\
{																					\
}																					\

DefineExceptionClass(MatrixHaveBadDimensions);
DefineExceptionClass(MatrixIndexOutOfBounds);
DefineExceptionClass(FileCouldNotBeOpened);
DefineExceptionClass(FileStreamIsClosed);
DefineExceptionClass(BadMatrixFormatInFile);
DefineExceptionClass(BadMatricesDimensionsForMultiplying);