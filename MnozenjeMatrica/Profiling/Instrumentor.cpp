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
		writeAllProfileResultsToFile();
		unwrittenProfilingResults.clear();
		profilingFile.close();
	}
}

void Instrumentor::writeAllProfileResultsToFile() noexcept
{
	for (const auto& profilingResult : unwrittenProfilingResults)
	{
		profilingFile << profilingResult;
	}
}

void Instrumentor::addProfileResult(const ProfileResult& profilingResult) noexcept
{
	std::lock_guard<decltype(lockForAddingToVector)> lockGuard(lockForAddingToVector);
	unwrittenProfilingResults.push_back(profilingResult);
}