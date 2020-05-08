#include <iostream>

#include "Matrix.h"
#include "MatrixWritter.h"
#include "MatrixReader.h"
#include "SerialMultiplier.h"
#include "ParallelForMultiplier.h"
#include "Profiling.h"
#include "ParallelTaskPerRowMultiplier.h"
#include "ParallelTaskPerElementMultiplier.h"

#include <iostream> // remove
#define TESTING 0

#if TESTING == 0

int main()
{
	try
	{
		Matrix m3(3000, 3000, 2);
		Matrix m4(3000, 3000, 1);

		Profiling::beginSession("profile.json");

		Matrix res2 = ParallelTaskPerRowMultiplier().multiply(m3, m4);
		//Matrix res2 = ParallelForMultiplier().multiply(m3, m4);
		Profiling::endSession();

		MatrixWritter ms("matrixRes.txt");
		ms << res2;
		ms.close();
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
}
#endif // !TESTING