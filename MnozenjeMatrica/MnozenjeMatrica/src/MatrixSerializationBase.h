#pragma once

#include <fstream>
#include <mutex>

#include "MatrixExceptions.h"

template <typename T>class MatrixSerializationBase
{
public:
	MatrixSerializationBase() = default;

	virtual ~MatrixSerializationBase() noexcept
	{
		closeStreamIfItIsAlreadyOpen();
	}

	void open(const std::string& filePath) noexcept(false)
	{
		closeStreamIfItIsAlreadyOpen();

		openStreamOnGivenPath(filePath);

		throwIfStreamCouldNotBeOpened();
	}

	void close() noexcept
	{
		closeStreamIfItIsAlreadyOpen();
	}

protected:
	std::mutex lockForFileAccess;
	T fileStream;

private:
	void openStreamOnGivenPath(const std::string& filePath) noexcept
	{
		fileStream.open(filePath);
	}

	void throwIfStreamCouldNotBeOpened() noexcept(false)
	{
		if (const bool streamIsNotOpened = !fileStream.is_open(); streamIsNotOpened)
		{
			throw FileCouldNotBeOpened("The file can not be opened!");
		}
	}

	void closeStreamIfItIsAlreadyOpen() noexcept
	{
		if (const bool streamIsAlreadyOpen = fileStream.is_open(); streamIsAlreadyOpen)
		{
			fileStream.close();
		}
	}
};