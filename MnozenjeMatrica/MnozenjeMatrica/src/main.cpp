#include <iostream>

#include "Matrix.h"
#include "MatrixWritter.h"
#include "MatrixReader.h"
#include "SerialMultiplier.h"

#include "tbb\tbb.h"

#define TESTING 0

#if TESTING == 0

int main()
{
	try
	{
		Matrix m3(30, 1000, 2);
		Matrix m4(1000, 30, 6);
		Matrix res = SerialMultiplier().multiply(m3, m4);

		MatrixWritter ms("matrix.txt");
		ms << res;
		ms.close();
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
}

#endif // !TESTING