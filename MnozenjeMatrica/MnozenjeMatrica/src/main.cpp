#include <iostream>

#include "Matrix.h"
#include "MatrixWritter.h"
#include "MatrixReader.h"
#include "Profiling.h"
#include "MultiplierFactory.h"
#include <iostream> // remove
#include <time.h>

#ifndef TESTING

int main()
{
	/*srand(time(NULL));
	int n1 = rand() % 1001;
	int n2 = rand() % 1001;
	int n3 = rand() % 1001;

	Matrix m(n1, n2);
	Matrix m1(n2, n3);

	for (int i = 0; i < m.getNumberOfRows(); ++i)
	{
		for (int j = 0; j < m.getNumberOfColumns(); ++j)
		{
			m[i][j] = rand() % 21 - 10;
		}
	}

	for (int i = 0; i < m1.getNumberOfRows(); ++i)
	{
		for (int j = 0; j < m1.getNumberOfColumns(); ++j)
		{
			m1[i][j] = rand() % 21 - 10;
		}
	}

	MatrixWritter ms("TestCase1.txt");
	ms << m << m1;*/
	Profiling::beginSession("profile.json");

	for (int j = 1; j <= 5; ++j)
	{
		Matrix m;
		Matrix m2;
		Matrix res;

		MatrixReader mr("TestCase" + std::to_string(j) + ".txt");

		mr >> m;
		mr >> m2;
		mr >> res;

		for (int i = 1; i <= 5; ++i)
		{
			MatrixMultiplierBase* multiplier = MultiplierFactory::get().createMultiplier(i);
			Matrix res2 = multiplier->multiply(m, m2);

			if (res == res2)
			{
				std::cout << "Dobro je!\n";
			}
		}
	}
	Profiling::endSession();

	/*try
	{
		Matrix m3(2000, 2000, 2);
		Matrix m4(2000, 2000, 1);

		MatrixMultiplierBase* multiplier = MultiplierFactory::get().createMultiplier(MultiplierFactory::OPTIONS::ParallelFor);
		Matrix res = multiplier->multiply(m3, m4);

		MatrixWritter ms("matrixRes.txt");
		ms << res;
		ms.close();
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}*/
}
#endif // !TESTING