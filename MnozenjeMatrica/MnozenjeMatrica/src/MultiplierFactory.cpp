#include "MultiplierFactory.h"

#include <functional>

#include "ParallelForMultiplier.h"
#include "ParallelTaskPerElementMultiplier.h"
#include "ParallelTaskPerRowMultiplier.h"
#include "ParallelTaskPerThreadMultiplier.h"
#include "SerialMultiplier.h"

MultiplierFactory::MultiplierFactory() noexcept
{
	registerMultiplier(OPTIONS::Serial, &SerialMultiplier::create);
	registerMultiplier(OPTIONS::ParallelFor, &ParallelForMultiplier::create);
	registerMultiplier(OPTIONS::ParallelTaskPerElement, &ParallelTaskPerElementMultiplier::create);
	registerMultiplier(OPTIONS::ParallelTaskPerRow, &ParallelTaskPerRowMultiplier::create);
	registerMultiplier(OPTIONS::ParallelTaskPerThread, &ParallelTaskPerThreadMultiplier::create);
}

MultiplierFactory& MultiplierFactory::get() noexcept
{
	static MultiplierFactory factory;

	return factory;
}

void MultiplierFactory::registerMultiplier(const int methodNumber, createFunctionPtr creationMethod) noexcept
{
	creationMethods[methodNumber] = creationMethod;
}

MatrixMultiplierBase* MultiplierFactory::createMultiplier(const int methodNumber) noexcept
{
	if (const bool methodIsNotInMap = creationMethods.find(methodNumber) == creationMethods.end(); methodIsNotInMap)
	{
		return nullptr;
	}

	return std::invoke(creationMethods[methodNumber]);
}