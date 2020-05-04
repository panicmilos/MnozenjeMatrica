#pragma once

#include <chrono>

#include "ProfileResult.h"

class __declspec(dllexport) InstrumentationTimer
{
public:
	explicit InstrumentationTimer(const std::string& functionName) noexcept;
	~InstrumentationTimer() noexcept;

private:
	void collectProfilingResult() noexcept;
	void profileResult() noexcept;

	ProfileResult profilingResult;
	std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint;
};