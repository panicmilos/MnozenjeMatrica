#include "MatrixReaderTest.h"

#include "DSTLAssertions.h"
#include "../src/Matrix.h"
#include "../src/MatrixExceptions.h"
#include "../src/MatrixReader.h"

TEST(MatrixReader, WrongFilePath)
{
	MatrixReader mr;

	MATRIX_EXPECT_THROW(mr.open("Wrong File Path.png"), FileCouldNotBeOpened, "The file can not be opened!");
}

TEST(MatrixReader, GoodSquaredMatrix)
{
	MatrixReader mr;
	mr.open("res\\SquaredMatrixGood.txt");

	Matrix m;
	mr >> m;

	MATRIX_DIMENSIONS_EQ(m, { 3, 3 });
	MATRIX_ELEMENTS_EQ(m, { 123, 3, -4, 12, 241, -512342, 123, 541, 513 });
}

TEST(MatrixReader, TwoGoodSquaredMatrix)
{
	MatrixReader mr;
	mr.open("res\\2SquaredMatrixGood.txt");

	Matrix m1;
	mr >> m1;

	MATRIX_DIMENSIONS_EQ(m1, { 3, 3 });
	MATRIX_ELEMENTS_EQ(m1, { 123, 3, -4, 12, 241, -512342, 123, 541, 513 });

	Matrix m2;
	mr >> m2;

	MATRIX_DIMENSIONS_EQ(m2, { 2, 2 });
	MATRIX_ELEMENTS_EQ(m2, { 2, 2, 2, 2 });
}

TEST(MatrixReader, GoodNonSquaredMatrix)
{
	MatrixReader mr;
	mr.open("res\\NonSquaredMatrixGood.txt");

	Matrix m;
	mr >> m;

	MATRIX_DIMENSIONS_EQ(m, { 3, 2 });
	MATRIX_ELEMENTS_EQ(m, { 3, -4, 12, -512342, 123, 541 });
}

TEST_P(MatrixReaderWithBadFormat, ReadingMatrixWithBadFormat)
{
	auto path = GetParam();

	MatrixReader mr;
	mr.open("res\\" + path);

	Matrix m;

	MATRIX_EXPECT_THROW(mr >> m, BadMatrixFormatInFile, "File contains matrix with bad format!");
}

INSTANTIATE_TEST_CASE_P(MatrixReader, MatrixReaderWithBadFormat,
	testing::Values(
		std::string("BadHeader - CharInsteadOfFirstNumber.txt"),
		std::string("BadHeader - CharInsteadOfSecondNumber.txt"),
		std::string("BadHeader - NoFirstChar.txt"),
		std::string("BadHeader - NoSecondChar.txt"),
		std::string("BadHeader - NoThirdChar.txt"),
		std::string("BadHeader - NoFirstNumber.txt"),
		std::string("BadHeader - NoSecondNumber.txt"),
		std::string("BadBody - CharInsteadOfNumber.txt"),
		std::string("BadBody - NoEnoughNumbers.txt"),
		std::string("BadBody - TooManyNumbers.txt"),
		std::string("BadEnd - NoEndOfFormatChar.txt")
	));