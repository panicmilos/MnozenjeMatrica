#include "Utils.h"

void Utils::deleteLastNCharInStream(std::ostream& stream, const long long N) noexcept
{
	if (std::streamoff lastCharPos = stream.tellp(); lastCharPos >= N)
	{
		stream.seekp(lastCharPos - N);
	}
}