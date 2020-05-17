#include <iostream>

#include "Matrix.h"
#include "MatrixWritter.h"
#include "MatrixReader.h"
#include "Profiling.h"
#include "MultiplierFactory.h"
#include <iostream> // remove
#include <time.h>

#define TESTING 0

#if TESTING == 0

int main()
{
	/*srand(time(NULL));

	Matrix m(154, 70);
	Matrix m1(70, 81);

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

	Matrix res = SerialMultiplier().multiply(m, m1);

	MatrixWritter ms("smallMatrices2.txt");
	ms << m;
	ms << m1;
	ms << res;
	ms.close();

	for (int i = 1; i <= 3; ++i) {
		Matrix m;
		Matrix m1;
		Matrix m2;
		MatrixReader mr("smallMatrices" + std::to_string(i) + ".txt");
		mr >> m >> m1 >> m2;
		Matrix res = ParallelTaskPerRowMultiplier()(m, m1);

		if (m2 == res)
		{
			std::cout << "Isto je\n";
		}
	}*/

	try
	{
		Matrix m3(1000, 1000, 2);
		Matrix m4(1000, 1000, 1);

		Profiling::beginSession("profile.json");
		MatrixMultiplierBase* multiplier = MultiplierFactory::get().createMultiplier(MultiplierFactory::OPTIONS::ParallelFor);
		Matrix res2 = multiplier->multiply(m3, m4);
		Profiling::endSession();

		//MatrixWritter ms("matrixRes.txt");
		//ms << res2;
		//ms.close();
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
}
#endif // !TESTING