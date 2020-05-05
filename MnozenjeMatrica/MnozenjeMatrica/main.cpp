#include <iostream>

#include "Matrix.h"

int main()
{
	Matrix m1{};
	m1.print();

	Matrix m(2, 2);
	m.print();

	/*Matrix m2 =
	{
		{ 1, 2 },
		{ 1, 4 }
	};*/

	Matrix m3{ {1, 2}, {1, 3} };
	Matrix m4{ m3 };
	Matrix m5{ std::move(m4) };
	std::cout << "M4\n";
	m4.print();
	std::cout << "M5\n";
	m5.print();

	//m2.print();
}