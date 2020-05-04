#include "ProfilingFileWritter.h"

#include <algorithm>

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

void ProfilingFileWritter::writeProfile(const ProfileResult& profilingResult) noexcept
{
	std::lock_guard<decltype(lockForWritingInFile)> lockGuard(lockForWritingInFile);

	writeCommaIfNotFirstProfiling();
	writeJsonData(profilingResult);
}

void ProfilingFileWritter::writeJsonData(const ProfileResult& profilingResult) noexcept
{
	std::string functionName = profilingResult.functionName;
	std::replace(functionName.begin(), functionName.end(), '"', '\'');

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