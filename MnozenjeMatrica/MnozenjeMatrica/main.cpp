#include "Matrix.h"

int main()
{
	Matrix m(2, 2);
	m.print();

	/*Matrix m2 =
	{
		{ 1, 2 },
		{ 1, 4 }
	};*/

	Matrix m3 = { {1, 2}, {1, 3} };
	m3.print();
	//m2.print();
}