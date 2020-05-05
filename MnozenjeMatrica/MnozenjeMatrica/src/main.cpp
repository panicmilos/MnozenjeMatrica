#include <iostream>

#include "Matrix.h"

#define TESTING 0

#if TESTING == 1

int main()
{
	Matrix m3{ {1, 2}, {1, 3} };

	try {
		m3[1][0] = 5;
		std::cout << m3[1][0] << '\n';
		m3 = std::move(m3);

		m3.print();
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}
	Matrix m4{ m3 };
	Matrix m5{ std::move(m4) };
	std::cout << "M4\n";
	m4.print();
	std::cout << "M5\n";
}
#endif // !TESTING