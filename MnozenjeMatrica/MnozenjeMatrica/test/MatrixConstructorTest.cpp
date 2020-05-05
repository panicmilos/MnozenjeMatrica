#include "MatrixConstructorTest.h"

#include "DSTLAssertions.h"
#include "gtest\gtest.h"
#include "../src/Matrix.h"
#include "../src/MatrixExceptions.h"

TEST(MatrixConstructorDefault, SuccessfulConstructing)
{
	Matrix m;

	MATRIX_DIMENSIONS_EQ(m, { 0, 0 });
	MATRIX_ELEMENTS_EQ(m, { });
}

TEST(MatrixConstructorWithParams, SuccessfulConstructingWithDefaultValue)
{
	Matrix m(2, 3);

	MATRIX_DIMENSIONS_EQ(m, { 2, 3 });
	MATRIX_ELEMENTS_EQ(m, { 0, 0, 0, 0, 0, 0 });
}

TEST(MatrixConstructorWithParams, SuccessfulConstructingWithNonDefaultValue)
{
	Matrix m(2, 3, 5);

	MATRIX_DIMENSIONS_EQ(m, { 2, 3 });
	MATRIX_ELEMENTS_EQ(m, { 5, 5, 5, 5, 5, 5 });
}

TEST_P(MatrixConstructorWithBadParams, ShouldThrowBecauseOfBadDimensions)
{
	auto parametes = GetParam();

	MATRIX_EXPECT_THROW(Matrix m(parametes.numberOfRows, parametes.numberOfColumns), MatrixHaveBadDimensions, "Matrix must have at lease one row and one column!");
}

INSTANTIATE_TEST_CASE_P(MatrixConstructorWithParams, MatrixConstructorWithBadParams,
	testing::Values(
		MatrixDimensions{ 0u, 0u },
		MatrixDimensions{ 0u, 1u },
		MatrixDimensions{ 1u, 0u }
));

TEST_F(MatrixConstructorCopy, SuccessfulConstructing)
{
	Matrix mCopy(m);

	MATRIX_DIMENSIONS_EQ(m, { 2, 3 });
	MATRIX_ELEMENTS_EQ(m, { 2, 23, -4, 55, 0, 6 });

	MATRIX_DIMENSIONS_EQ(mCopy, { 2, 3 });
	MATRIX_ELEMENTS_EQ(mCopy, { 2, 23, -4, 55, 0, 6 });
}

TEST_F(MatrixConstructorMove, SuccessfulConstructing)
{
	Matrix mMoved(std::move(m));

	MATRIX_DIMENSIONS_EQ(m, { 0, 0 });
	MATRIX_ELEMENTS_EQ(m, { });

	MATRIX_DIMENSIONS_EQ(mMoved, { 2, 3 });
	MATRIX_ELEMENTS_EQ(mMoved, { 2, 23, -4, 55, 0, 6 });
}

TEST(MatrixConstructorInitializerList, SuccessfulConstructing)
{
	Matrix m =
	{
		{2, 23, -4},
		{55, 0, 6}
	};

	MATRIX_DIMENSIONS_EQ(m, { 2, 3 });
	MATRIX_ELEMENTS_EQ(m, { 2, 23, -4, 55, 0, 6 });
}

TEST_P(MatrixConstructorWithBadInitializerList, ShouldThrowBecauseOfBadDimensions)
{
	auto parameters = GetParam();
	MATRIX_EXPECT_THROW(Matrix m(parameters), MatrixHaveBadDimensions, "Matrix must have at lease one row and one column!");
}

INSTANTIATE_TEST_CASE_P(MatrixConstructorInitializerList, MatrixConstructorWithBadInitializerList,
	testing::Values(
		InitializerListCase1,
		InitializerListCase2,
		InitializerListCase3
	));