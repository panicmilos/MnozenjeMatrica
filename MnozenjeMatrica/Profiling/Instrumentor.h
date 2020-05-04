#pragma once

#include <string>

#include "ProfilingFileWritter.h"
#include "ProfileResult.h"

class Instrumentor
{
public:
	[[nodiscard]] static  __declspec(dllexport) Instrumentor& getInstance() noexcept;
	~Instrumentor() noexcept;

	void __declspec(dllexport) beginSession(const std::string& filePath) noexcept;
	void __declspec(dllexport) endSession() noexcept;

	void profileGivenResult(const ProfileResult& profilingResult) noexcept;

private:
	Instrumentor() = default;

	ProfilingFileWritter profilingFile;
	bool hasActiveSession = false;
};
