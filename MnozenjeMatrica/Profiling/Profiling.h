#pragma once

#include "InstrumentationTimer.h"
#include "Instrumentor.h"

constexpr char DEFAULT_RESULT_FILE_PATH[] = "results.json";

#define PROFILE_SCOPE(functionName) InstrumentationTimer timer##__LINE__(functionName)
#define PROFILE_FUNCTION()  PROFILE_SCOPE(__FUNCTION__)
#define PROFILE_FUNCSIG()  PROFILE_SCOPE(__FUNCSIG__)

namespace Profiling
{
	__declspec(dllexport) void beginProfiling(const std::string& filePath = DEFAULT_RESULT_FILE_PATH)
	{
		Instrumentor& instrumentorInstance = Instrumentor::getInstance();
		instrumentorInstance.beginSession(filePath);
	}

	__declspec(dllexport) void endProfiling()
	{
		Instrumentor& instrumentorInstance = Instrumentor::getInstance();
		instrumentorInstance.endSession();
	}
}