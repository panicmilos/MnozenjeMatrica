#include "Global.h"

#include "../src/Matrix.h"
#include "../src/MatrixReader.h"

void readAllMultiplicationElementsFromFiles()
{
	for (const auto& testCaseFile : testCasesFiles)
	{
		MatrixReader mr(testCaseFile);

		Matrix& leftMatrix = *new Matrix();
		Matrix& rightMatrix = *new Matrix();
		Matrix& resultMatrix = *new Matrix();

		mr >> leftMatrix >> rightMatrix >> resultMatrix;

		testCases.push_back({ leftMatrix, rightMatrix, resultMatrix });
	}
}