#include "MatrixAssignmentOperatorTest.h"

#include "DSTLAssertions.h"
#include "../src/Matrix.h"

TEST_P(MatrixAssignmentOperatorCopyWithParams, CopyingWithMatrixSizeAsParams)
{
	auto dimensions = GetParam();
	Matrix mCopied(dimensions.numberOfRows, dimensions.numberOfColumns);
	mCopied = m;

	MATRIX_DIMENSIONS_EQ(m, { 2, 3 });
	MATRIX_ELEMENTS_EQ(m, { 2, 23, -4, 55, 0, 6 });

	MATRIX_DIMENSIONS_EQ(mCopied, { 2, 3 });
	MATRIX_ELEMENTS_EQ(mCopied, { 2, 23, -4, 55, 0, 6 });
}

INSTANTIATE_TEST_CASE_P(MatrixAssignmentOperatorCopy, MatrixAssignmentOperatorCopyWithParams,
	testing::Values(
		Dimensions{ 1, 1 },
		Dimensions{ 2, 3 },
		Dimensions{ 10, 10 }
));

TEST_F(MatrixAssignmentOperatorCopy, CopyingMatrixToItself)
{
	Matrix mCopied(m);
	mCopied = mCopied;

	MATRIX_DIMENSIONS_EQ(mCopied, { 2, 3 });
	MATRIX_ELEMENTS_EQ(mCopied, { 2, 23, -4, 55, 0, 6 });
}

TEST_F(MatrixAssignmentOperatorMove, MovingMatrix)
{
	Matrix mMoved(m);
	mMoved = std::move(m);

	MATRIX_DIMENSIONS_EQ(m, { 0, 0 });
	MATRIX_ELEMENTS_EQ(m, { });

	MATRIX_DIMENSIONS_EQ(mMoved, { 2, 3 });
	MATRIX_ELEMENTS_EQ(mMoved, { 2, 23, -4, 55, 0, 6 });
}

TEST_F(MatrixAssignmentOperatorMove, MovingMatrixToItself)
{
	Matrix mMoved(m);
	mMoved = std::move(mMoved);

	MATRIX_DIMENSIONS_EQ(mMoved, { 2, 3 });
	MATRIX_ELEMENTS_EQ(mMoved, { 2, 23, -4, 55, 0, 6 });
}