#pragma once

#include <string>

#include "ProfilingFileWritter.h"
#include "ProfileResult.h"

class Instrumentor
{
public:
	[[nodiscard]] static Instrumentor& getInstance() noexcept;
	~Instrumentor() noexcept;

	void beginSession(const std::string& filePath) noexcept;
	void endSession() noexcept;

	void profileGivenResult(const ProfileResult& profilingResult) noexcept;

private:
	Instrumentor() = default;

	ProfilingFileWritter profilingFile;
	bool hasActiveSession = false;
};
