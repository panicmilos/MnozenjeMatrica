#pragma once

#include "InstrumentationTimer.h"
#include "Instrumentor.h"

constexpr char DEFAULT_RESULT_FILE_PATH[] = "profilingResults.json";

#define PROFILE_SCOPE(functionName) InstrumentationTimer timer##__LINE__(functionName)
#define PROFILE_FUNCTION()  PROFILE_SCOPE(__FUNCTION__)
#define PROFILE_FUNCSIG()  PROFILE_SCOPE(__FUNCSIG__)

namespace Profiling
{
	__declspec(dllexport) void beginSession(const std::string& filePath = DEFAULT_RESULT_FILE_PATH);
	__declspec(dllexport) void endSession();
} // namespace Profiling