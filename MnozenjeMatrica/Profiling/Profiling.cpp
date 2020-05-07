#include "Profiling.h"

void Profiling::beginSession(const std::string& filePath)
{
	Instrumentor& instrumentorInstance = Instrumentor::getInstance();
	instrumentorInstance.beginSession(filePath);
}

void Profiling::endSession()
{
	Instrumentor& instrumentorInstance = Instrumentor::getInstance();
	instrumentorInstance.endSession();
}