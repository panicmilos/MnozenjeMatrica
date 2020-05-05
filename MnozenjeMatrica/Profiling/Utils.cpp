#include "Utils.h"

#include <algorithm>

constexpr char SINGLE_QUOTES = '\'';
constexpr char DOUBLE_QUOTES = '"';

uint32_t Utils::getU_Int32_TFromThreadId() noexcept
{
	std::thread::id threadId = std::this_thread::get_id();
	uint32_t hashedThreadIt = std::hash<decltype(threadId)>{}(threadId);

	return hashedThreadIt;
}

long long Utils::getTimeSinceEpochInMicroseconds(const std::chrono::time_point<std::chrono::high_resolution_clock>& timePoint) noexcept
{
	auto timeInMicroseconds = std::chrono::time_point_cast<std::chrono::microseconds>(timePoint);
	long long TimeSinceEpochInMicroseconds = timeInMicroseconds.time_since_epoch().count();

	return TimeSinceEpochInMicroseconds;
}

void Utils::replaceAllDoubleQuotesWithSingleInString(std::string& stringForModification) noexcept
{
	std::replace(stringForModification.begin(), stringForModification.end(), DOUBLE_QUOTES, SINGLE_QUOTES);
}