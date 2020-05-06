#include <iostream>

#include "Matrix.h"
#include "MatrixSerializator.h"

#define TESTING 0

#if TESTING == 0

int main()
{
	Matrix m3{
	{1, 2, 4, 6, 1, 2, 6},
	{1, 3, 4, 2, 6, 7, 1},
	{1, 3, -55, 2, 63, 7, 1},
	{1, 3, 4, 2, 6124412, 7, 1} };

	MatrixWritter ms;
	ms.open("matrix.txt");
	ms << m3;
}
#endif // !TESTING