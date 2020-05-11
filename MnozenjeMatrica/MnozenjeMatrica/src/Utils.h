#pragma once

#include <ostream>

namespace Utils
{
	void deleteLastNCharsInStream(std::ostream& stream, const long long numberOfCharsForDeletion) noexcept;
}
