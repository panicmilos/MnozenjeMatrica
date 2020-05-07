#include <iostream>

#include "Matrix.h"
#include "MatrixWritter.h"
#include "MatrixReader.h"
#include "SerialMultiplier.h"
#include "ParallelForMultiplier.h"
#include "Profiling.h"
//#include "MatrixMultiplierBase.h"

#include <iostream> // remove
#define TESTING 0

#if TESTING == 0

int main()
{
	try
	{
		Matrix m3(4000, 3000, 2);
		Matrix m4(3000, 4000, 2);

		Profiling::beginSession("profile.json");

		//	Matrix res = SerialMultiplier().multiply(m3, m4);
		Matrix res2 = ParallelForMultiplier().multiply(m3, m4);
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