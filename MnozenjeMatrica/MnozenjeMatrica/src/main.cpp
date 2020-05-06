#include <iostream>

#include "Matrix.h"
#include "MatrixWritter.h"
#include "Profiling.h"

#define TESTING 0

#if TESTING == 0

Matrix multiply(Matrix& m1, Matrix& m2)
{
	const size_t numberOfColumnsInFirstMatrix = m1.getNumberOfColumns();
	const size_t numberOfRowsInSecondMatrix = m2.getNumberOfRows();

	bool numberOfRowsAndColumnsAreSame = numberOfColumnsInFirstMatrix == numberOfRowsInSecondMatrix;
	if (!numberOfRowsAndColumnsAreSame)
	{
		throw std::exception();
	}

	PROFILE_FUNCSIG();

	const size_t numberOfRowsInFirstMatrix = m1.getNumberOfRows();
	const size_t numberOfColumnsInSecondMatrix = m2.getNumberOfColumns();

	Matrix res(numberOfRowsInFirstMatrix, numberOfColumnsInSecondMatrix);
	for (size_t i = 0; i < numberOfRowsInFirstMatrix; ++i)
	{
		for (size_t j = 0; j < numberOfColumnsInSecondMatrix; ++j)
		{
			for (size_t k = 0; k < numberOfColumnsInFirstMatrix; ++k)
				res[i][j] += (m1[i][k]) * (m2[k][j]);
		}
	}

	return res;
}
int main()
{
	try {
		Profiling::beginSession();
		Matrix m3(30, 1000, 2);
		Matrix m4(1000, 30, 1);
		Matrix res = multiply(m3, m4);

		Profiling::endSession();
		MatrixWritter ms;
		ms.open("matrix.txt");
		ms << res;
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
}
#endif // !TESTING