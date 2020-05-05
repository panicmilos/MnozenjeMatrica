#include "ProfilingFileWritter.h"

#include "Utils.h"

ProfilingFileWritter::~ProfilingFileWritter() noexcept
{
	close();
}

void ProfilingFileWritter::open(const std::string& filePath) noexcept
{
	if (outputFile.is_open())
	{
		close();
	}

	outputFile.open(filePath);
	writeHeader();
}

void ProfilingFileWritter::writeHeader() noexcept
{
	outputFile << "{\"otherData\": {},\"traceEvents\":[";
}

void ProfilingFileWritter::close() noexcept
{
	if (outputFile.is_open())
	{
		profileCount = 0;
		writeFooter();
		outputFile.close();
	}
}

void ProfilingFileWritter::writeFooter() noexcept
{
	outputFile << "]}";
}

ProfilingFileWritter& ProfilingFileWritter::operator<<(const ProfileResult& profilingResult) noexcept
{
	std::lock_guard<decltype(lockForWritingInFile)> lockGuard(lockForWritingInFile);

	writeCommaIfNotFirstProfiling();
	writeJsonData(profilingResult);

	return *this;
}

void ProfilingFileWritter::writeJsonData(const ProfileResult& profilingResult) noexcept
{
	std::string functionName = profilingResult.functionName;
	Utils::replaceAllDoubleQuotesWithSingleInString(functionName);

	outputFile << "{";
	outputFile << "\"cat\":\"function\",";
	outputFile << "\"dur\":" << (profilingResult.endTime - profilingResult.startTime) << ',';
	outputFile << "\"name\":\"" << functionName << "\",";
	outputFile << "\"ph\":\"X\",";
	outputFile << "\"pid\":0,";
	outputFile << "\"tid\":" << profilingResult.threadID << ",";
	outputFile << "\"ts\":" << profilingResult.startTime;
	outputFile << "}";
}

void ProfilingFileWritter::writeCommaIfNotFirstProfiling() noexcept
{
	if (profileCount++ > 0)
	{
		outputFile << ",";
	}
}