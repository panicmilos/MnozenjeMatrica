#include "ParallelTaskPerRowMultiplierTest.h"

#include "DSTLAssertions.h"
#include "gtest\gtest.h"
#include "../src/MultiplierFactory.h"

TEST(ParallelTaskPerRowMultiplierTest, MatricesWithDifferentDimensions)
{
	MatrixMultiplierBase* multiplier = MultiplierFactory::get().createMultiplier(MultiplierFactory::OPTIONS::ParallelTaskPerRow);

	for (const auto& testCase : testCases)
	{
		auto [leftMatrix, rightMatrix, expectedResult] = testCase;

		Matrix result = multiplier->multiply(leftMatrix, rightMatrix);

		MATRICES_EQ(result, expectedResult);
	}

	delete multiplier;
}