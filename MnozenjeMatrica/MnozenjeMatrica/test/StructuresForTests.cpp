#include "StructuresForTests.h"

#include "../src/MatrixRow.h"

MatrixForTest::MatrixForTest() : m(2, 3)
{
	m[0][0] = 2;
	m[0][1] = 23;
	m[0][2] = -4;
	m[1][0] = 55;
	m[1][2] = 6;
}