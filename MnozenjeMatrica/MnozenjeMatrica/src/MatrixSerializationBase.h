#pragma once

#include <fstream>
#include <mutex>

#include "MatrixExceptions.h"

template <typename T>class MatrixSerializationBase
{
public:
	MatrixSerializationBase() = default;
	MatrixSerializationBase(const MatrixSerializationBase&) = delete;
	MatrixSerializationBase(MatrixSerializationBase&&) = delete;
	MatrixSerializationBase& operator=(const MatrixSerializationBase&) = delete;
	MatrixSerializationBase& operator=(MatrixSerializationBase&&) = delete;

	virtual ~MatrixSerializationBase() noexcept
	{
		closeStreamIfItIsAlreadyOpen();
	}

	void open(const std::string& filePath) noexcept(false)
	{
		std::lock_guard<decltype(lockForFileAccess)> lockGuard(lockForFileAccess);

		closeStreamIfItIsAlreadyOpen();

		openStreamOnGivenPath(filePath);

		throwIfStreamCouldNotBeOpened();
	}

	void close() noexcept
	{
		std::lock_guard<decltype(lockForFileAccess)> lockGuard(lockForFileAccess);

		closeStreamIfItIsAlreadyOpen();
	}

protected:
	void throwIfStreamIsClosed() noexcept(false)
	{
		if (const bool streamIsClosed = !fileStream.is_open(); streamIsClosed)
		{
			throw FileStreamIsClosed("You have to open the stream first!");
		}
	}

	std::mutex lockForFileAccess;
	T fileStream;

private:
	void openStreamOnGivenPath(const std::string& filePath) noexcept
	{
		fileStream.open(filePath);
	}

	void throwIfStreamCouldNotBeOpened() const noexcept(false)
	{
		if (const bool streamIsClosed = !fileStream.is_open(); streamIsClosed)
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