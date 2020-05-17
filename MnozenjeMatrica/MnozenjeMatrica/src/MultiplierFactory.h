#pragma once

#include <unordered_map>

#include "MatrixMultiplierBase.h"

class MultiplierFactory
{
private:
	typedef MatrixMultiplierBase* (*createFunctionPtr)();

public:
	enum OPTIONS
	{
		Serial = 1,
		ParallelFor,
		ParallelTaskPerElement,
		ParallelTaskPerRow,
		ParallelTaskPerThread
	};

	[[nodiscard]] static MultiplierFactory& get() noexcept;

	void registerMultiplier(const int methodNumber, createFunctionPtr creationMethod) noexcept;
	[[nodiscard]] MatrixMultiplierBase* createMultiplier(const int methodNumber) noexcept;

private:
	MultiplierFactory() noexcept;
	MultiplierFactory(const MultiplierFactory&) = delete;
	MultiplierFactory& operator=(const MultiplierFactory&) = delete;

	std::unordered_map<int, createFunctionPtr> creationMethods;
};