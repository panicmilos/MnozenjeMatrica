#include "MatrixWritterTest.h"

#include "DSTLAssertions.h"
#include "gtest\gtest.h"
#include "../src/Matrix.h"
#include "../src/MatrixExceptions.h"
#include "../src/MatrixWritter.h"

TEST(MatrixWritter, StreamIsClosed)
{
	MatrixWritter mr;

	Matrix m;

	MATRIX_EXPECT_THROW(mr << m, FileStreamIsClosed, "You have to open the stream first!");
}

TEST(MatrixWritter, WrittingSquaredMatrix)
{
	Matrix m(2, 2, 2);

	MatrixWritter mw("res\\tests\\SavedSquaredMatrix.txt");
	mw << m;
	mw.close();

	MATRIX_FILE_CONTENT_EQ_TO("res\\tests\\SavedSquaredMatrix.txt", "[2,2]\n2 2\n2 2;\n");
}

TEST_F(MatrixWritterWithTestMatrix, WrittingNonSquaredMatrix)
{
	MatrixWritter mw("res\\tests\\SavedNonSquaredMatrix.txt");
	mw << m;
	mw.close();

	MATRIX_FILE_CONTENT_EQ_TO("res\\tests\\SavedNonSquaredMatrix.txt", "[2,3]\n2 23 -4\n55 0 6;\n");
}

TEST_F(MatrixWritterWithTestMatrix, WrittingTwoMatrices)
{
	Matrix m2(2, 2, 2);

	MatrixWritter mw("res\\tests\\SavedTwoMatrices.txt");
	mw << m;
	mw << m2;
	mw.close();

	MATRIX_FILE_CONTENT_EQ_TO("res\\tests\\SavedTwoMatrices.txt", "[2,3]\n2 23 -4\n55 0 6;\n[2,2]\n2 2\n2 2;\n");
}