#include "MatrixWritterTest.h"

#include "DSTLAssertions.h"
#include "../src/Matrix.h"
#include "../src/MatrixWritter.h"

TEST(MatrixWritter, WrittingSquaredMatrix)
{
	Matrix m(2, 2, 2);

	MatrixWritter mw("res\\SavedSquaredMatrix.txt");
	mw << m;
	mw.close();

	MATRIX_FILE_CONTENT_EQ_TO("res\\SavedSquaredMatrix.txt", "[2,2]\n2 2\n2 2;\n");
}

TEST_F(MatrixWritterWithTestMatrix, WrittingNonSquaredMatrix)
{
	MatrixWritter mw("res\\SavedNonSquaredMatrix.txt");
	mw << m;
	mw.close();

	MATRIX_FILE_CONTENT_EQ_TO("res\\SavedNonSquaredMatrix.txt", "[2,3]\n2 23 -4\n55 0 6;\n");
}

TEST_F(MatrixWritterWithTestMatrix, WrittingTwoMatrices)
{
	Matrix m2(2, 2, 2);

	MatrixWritter mw("res\\SavedTwoMatrices.txt");
	mw << m;
	mw << m2;
	mw.close();

	MATRIX_FILE_CONTENT_EQ_TO("res\\SavedTwoMatrices.txt", "[2,3]\n2 23 -4\n55 0 6;\n[2,2]\n2 2\n2 2;\n");
}