#include "InstrumentationTimer.h"

#include <thread>

#include "Instrumentor.h"
#include "Utils.h"

InstrumentationTimer::InstrumentationTimer(const std::string& functionName) noexcept :
	profilingResult({ functionName }),
	startTimePoint(std::chrono::high_resolution_clock::now())
{
}

InstrumentationTimer::~InstrumentationTimer() noexcept
{
	collectProfilingResult();
	profileResult();
}

void InstrumentationTimer::collectProfilingResult() noexcept
{
	endTimePoint = std::chrono::high_resolution_clock::now();

	profilingResult.startTime = Utils::getTimeSinceEpochInMicroseconds(startTimePoint);
	profilingResult.endTime = Utils::getTimeSinceEpochInMicroseconds(endTimePoint);
	profilingResult.threadID = Utils::getU_Int32_TFromThreadId();
}

void InstrumentationTimer::profileResult() noexcept
{
	Instrumentor& instrumentorInstance = Instrumentor::getInstance();
	instrumentorInstance.addProfileResult(profilingResult);
}