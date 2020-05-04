#pragma once

#include <chrono>
#include <thread>

namespace Utils
{
	[[nodiscard]] uint32_t getU_Int32_TFromThreadId() noexcept;
	[[nodiscard]] long long getTimeSinceEpochInMicroseconds(const std::chrono::time_point<std::chrono::high_resolution_clock>& timePoint) noexcept;
} // namespace Utils
