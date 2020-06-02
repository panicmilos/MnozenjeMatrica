#include "Utils.h"

void Utils::deleteLastNCharsInStream(std::ostream& stream, const long long numberOfCharsForDeletion) noexcept
{
	// proverava da se ne pokusava brisati vise karaktera nego sto ima u strimu
	if (const std::streamoff positionOfLastChar = stream.tellp(); positionOfLastChar >= numberOfCharsForDeletion)
	{
		// "brise" n karaktera tako sto pomera pokazivas u toku
		stream.seekp(positionOfLastChar - numberOfCharsForDeletion);
	}
}