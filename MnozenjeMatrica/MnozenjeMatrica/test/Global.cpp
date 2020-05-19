#include "Global.h"

#include "../src/Matrix.h"
#include "../src/MatrixReader.h"

void readAllMultiplicationElementsFromFiles()
{
	for (size_t i = 0; i < numberOfTestCasesForMultipliers; ++i)
	{
		MatrixReader mr(testCasesFiles[i]);

		Matrix& leftMatrix = *new Matrix();
		Matrix& rightMatrix = *new Matrix();
		Matrix& resultMatrix = *new Matrix();

		mr >> leftMatrix >> rightMatrix >> resultMatrix;

		testCases.push_back({ leftMatrix, rightMatrix, resultMatrix });
	}
}