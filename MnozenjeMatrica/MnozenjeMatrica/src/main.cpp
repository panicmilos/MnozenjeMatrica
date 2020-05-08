#include <iostream>

#include "Matrix.h"
#include "MatrixWritter.h"
#include "MatrixReader.h"
#include "SerialMultiplier.h"
#include "ParallelForMultiplier.h"
#include "Profiling.h"
#include "ParallelTaskPerRowMultiplier.h"

#include <iostream> // remove
#define TESTING 0

#if TESTING == 0

int main()
{
	try
	{
		Matrix m3(2000, 2000, 2);
		Matrix m4(2000, 2000, 2);

		Profiling::beginSession("profile.json");

		//	Matrix res = SerialMultiplier().multiply(m3, m4);
		Matrix res2 = ParallelTaskPerRowMultiplier().multiply(m3, m4);
		//std::cout << "HI\n";
		Profiling::endSession();

		MatrixWritter ms("matrix.txt");
		//ms << res;
		ms << res2;
		ms.close();
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
}
#endif // !TESTING