#include <iostream>

#include "Matrix.h"
#include "MatrixWritter.h"
#include "MatrixReader.h"
#include "SerialMultiplier.h"
#include "ParallelForMultiplier.h"

#define TESTING 0

#if TESTING == 0

int main()
{
	try
	{
		Matrix m3(40, 1200, 2);
		Matrix m4(1200, 30, 6);
		Matrix res = SerialMultiplier().multiply(m3, m4);
		Matrix res2 = ParallelForMultiplier().multiply(m3, m4);

		MatrixWritter ms("matrix.txt");
		ms << res;
		ms << res2;
		ms.close();
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
}

#endif // !TESTING