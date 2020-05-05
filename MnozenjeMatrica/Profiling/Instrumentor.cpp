#include "Instrumentor.h"

Instrumentor& Instrumentor::getInstance() noexcept
{
	static Instrumentor instance;

	return instance;
}

Instrumentor::~Instrumentor() noexcept
{
	endSession();
}

void Instrumentor::beginSession(const std::string& filePath) noexcept
{
	if (hasActiveSession)
	{
		endSession();
	}

	hasActiveSession = true;
	profilingFile.open(filePath);
}

void Instrumentor::endSession() noexcept
{
	if (hasActiveSession)
	{
		hasActiveSession = false;
		profilingFile.close();
	}
}

void Instrumentor::profileGivenResult(const ProfileResult& profilingResult) noexcept
{
	profilingFile << profilingResult;
}