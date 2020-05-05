#pragma once

#include <fstream>
#include <mutex>
#include <string>

#include "ProfileResult.h"

class ProfilingFileWritter
{
public:
	ProfilingFileWritter() = default;
	~ProfilingFileWritter() noexcept;

	void open(const std::string& filePath) noexcept;
	void close() noexcept;

	ProfilingFileWritter& operator<<(const ProfileResult& profilingResult) noexcept;

private:
	void writeHeader() noexcept;
	void writeFooter() noexcept;
	void writeJsonData(const ProfileResult& profilingResult) noexcept;
	void writeCommaIfNotFirstProfiling() noexcept;

	std::ofstream outputFile;
	std::mutex lockForWritingInFile;
	int profileCount = 0;
};