#pragma once

#include <fstream>
#include <mutex>

#include "Matrix.h"

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
			throw std::runtime_error("WrongFileName");
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

class MatrixReader : public MatrixSerializationBase<std::ifstream>
{
public:
	MatrixReader() = default;
	~MatrixReader() = default;

	MatrixReader& operator>>(Matrix& m) { return *this; }
};

class MatrixWritter : public MatrixSerializationBase<std::ofstream>
{
public:
	MatrixWritter() = default;
	~MatrixWritter() = default;

	MatrixWritter& operator<<(const Matrix& m);

private:
	void writeMatrixHeader(const Matrix& m);
	void writeMatrixBody(const Matrix& m);
	void writeEndOfFormatCharacter();
};