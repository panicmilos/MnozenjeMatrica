#include "Utils.h"

void Utils::deleteLastNCharsInStream(std::ostream& stream, const long long numberOfCharsForDeletion) noexcept
{
	if (const std::streamoff positionOfLastChar = stream.tellp(); positionOfLastChar >= numberOfCharsForDeletion)
	{
		stream.seekp(positionOfLastChar - numberOfCharsForDeletion);
	}
}