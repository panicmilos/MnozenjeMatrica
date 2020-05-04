#pragma once

#include <string>

struct ProfileResult
{
	const std::string functionName;
	long long startTime;
	long long endTime;
	uint32_t threadID;
};