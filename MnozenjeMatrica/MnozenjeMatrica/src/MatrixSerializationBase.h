#pragma once

#include <fstream>
#include <mutex>

template <typename T>class MatrixSerializationBase
{
public:
	MatrixSerializationBase() = default;

	virtual ~MatrixSerializationBase() noexcept
	{
		close();
	}

	void open(const std::string& filePath) noexcept(false)
	{
		if (fileStream.is_open())
		{
			close();
		}

		fileStream.open(filePath);

		if (!fileStream)
		{
			throw std::runtime_error("WrongFileName"); // dodati exception
		}
	}

	void close() noexcept
	{
		if (fileStream.is_open())
		{
			fileStream.close();
		}
	}

protected:
	std::mutex lockForFileAccess;
	T fileStream;
};