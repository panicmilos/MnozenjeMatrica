#include "Utils.h"

void Utils::deleteLastNCharInStream(std::ostream& stream, const long long N)
{
	std::streamoff lastCharPos = stream.tellp();

	if (lastCharPos < N)
	{
		return;
	}

	stream.seekp(lastCharPos - N);
}