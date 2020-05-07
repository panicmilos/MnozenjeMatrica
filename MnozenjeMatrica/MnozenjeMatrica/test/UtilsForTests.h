#pragma once

#include <string>

namespace UtilsForTests
{
	[[nodiscard]] std::string getContentOfFile(const std::string& filePath) noexcept;
} // namespace UtilsForTests