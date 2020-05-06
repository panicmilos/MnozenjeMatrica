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

		openFileStreamOnGivenPath(filePath);

		throwIfFileCouldNotBeOpened();
	}

	void close() noexcept
	{
		closeStreamIfItIsAlreadyOpen();
	}

protected:
	std::mutex lockForFileAccess;
	T fileStream;

private:
	void openFileStreamOnGivenPath(const std::string& filePath) noexcept
	{
		fileStream.open(filePath);
	}

	void throwIfFileCouldNotBeOpened() noexcept(false)
	{
		if (const bool fileIsNotOpened = !fileStream.is_open(); fileIsNotOpened)
		{
			throw FileCouldNotBeOpened("The file cannot be opened!");
		}
	}

	void closeStreamIfItIsAlreadyOpen() noexcept
	{
		if (const bool fileIsAlreadyOpen = fileStream.is_open(); fileIsAlreadyOpen)
		{
			fileStream.close();
		}
	}
};