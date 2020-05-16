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

	profilingFile.open(filePath);
	hasActiveSession = true;
}

void Instrumentor::endSession() noexcept
{
	if (hasActiveSession)
	{
		writeAllProfileResultsToFile();
		profilingFile.close();
		hasActiveSession = false;
	}
}

void Instrumentor::writeAllProfileResultsToFile() noexcept
{
	for (const auto& profilingResult : unwrittenProfilingResults)
	{
		profilingFile << profilingResult;
	}

	unwrittenProfilingResults.clear();
}

void Instrumentor::addProfileResult(const ProfileResult& profilingResult) noexcept
{
	std::lock_guard<decltype(lockForAddingToVector)> lockGuard(lockForAddingToVector);
	unwrittenProfilingResults.push_back(profilingResult);

	size_t numberOfUnwrittenProfilingResult = unwrittenProfilingResults.size();
	if (numberOfUnwrittenProfilingResult >= 100000)
	{
		writeAllProfileResultsToFile();
	}
}