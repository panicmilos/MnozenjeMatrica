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
	try
	{
		Matrix m3(2000, 2000, 2);
		Matrix m4(2000, 2000, 1);
		Profiling::beginSession("profile.json");

		MatrixMultiplierBase* multiplier = MultiplierFactory::get().createMultiplier(MultiplierFactory::OPTIONS::ParallelFor);
		Matrix res = multiplier->multiply(m3, m4);
		Profiling::endSession();

		MatrixWritter ms("matrixRes.txt");
		ms << res;
		ms.close();
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
}
#endif // !TESTING