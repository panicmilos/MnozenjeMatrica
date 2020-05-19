#pragma once

#include <utility>
#include <vector>

#include "StructuresForTests.h"
#include "../src/Matrix.h"
#include "../src/MatrixRow.h"

#define MATRIX_EXPECT_THROW(statements, exceptionType, exceptionMessage)		\
	EXPECT_THROW({																\
		try                                                                     \
		{																		\
			statements; 														\
		}																		\
		catch (const exceptionType & e)											\
		{																		\
			EXPECT_STREQ(exceptionMessage, e.what());							\
			throw;																\
		}																		\
	}, exceptionType)															\

#define MATRIX_DIMENSIONS_EQ MatrixAssertions::MATRIX_DIMENSIONS_EQ_
#define MATRIX_DIMENSIONS_NOT_EQ MatrixAssertions::MATRIX_DIMENSIONS_NOT_EQ_
#define MATRIX_ELEMENTS_EQ MatrixAssertions::MATRIX_ELEMENTS_EQ_
#define MATRIX_CONTAINS_ELEMENT MatrixAssertions::MATRIX_CONTAINS_ELEMENT_
#define MATRIX_FILE_CONTENT_EQ_TO MatrixAssertions::MATRIX_FILE_CONTENT_EQ_TO_
#define MATRICES_EQ MatrixAssertions::MATRICES_EQ_
#define ROWS_EQ MatrixAssertions::ROWS_EQ_

namespace MatrixAssertions
{
	void MATRIX_DIMENSIONS_EQ_(const Matrix& m, std::pair<size_t, size_t> dimensions);
	void MATRIX_DIMENSIONS_NOT_EQ_(const Matrix& m, std::pair<size_t, size_t> dimensions);

	void MATRIX_ELEMENTS_EQ_(const Matrix& m, const std::vector<int>& elements);
	void MATRIX_CONTAINS_ELEMENT_(const Matrix& m, const Element& e);

	void MATRICES_EQ_(const Matrix& leftMatrix, const Matrix& rightMatrix, const bool areSame = true);
	void ROWS_EQ_(const MatrixRow& leftRow, const MatrixRow& rightRow, const bool areSame = true);

	void MATRIX_FILE_CONTENT_EQ_TO_(const std::string& filePath, const std::string& expectedContent);
} // MatrixAssertions