#include "MatrixWritter.h"

#include "MatrixRow.h"
#include "Utils.h"

MatrixWritter::MatrixWritter(const std::string& filePath) noexcept(false)
{
	open(filePath);
}

MatrixWritter& MatrixWritter::operator<<(const Matrix& m) noexcept
{
	std::lock_guard<decltype(lockForFileAccess)> lockGuard(lockForFileAccess);

	writeMatrixHeader(m);
	writeMatrixBody(m);
	writeEndOfFormatCharacter();

	return *this;
}

void MatrixWritter::writeMatrixHeader(const Matrix& m) noexcept
{
	const size_t numberOfRows = m.getNumberOfRows();
	const size_t numberOfColumns = m.getNumberOfColumns();

	fileStream << '[' << numberOfRows << ',' << numberOfColumns << "]\n";
}

void MatrixWritter::writeMatrixBody(const Matrix& m) noexcept
{
	fileStream << m;

	Utils::deleteLastNCharsInStream(fileStream, 2ll);
}

void MatrixWritter::writeEndOfFormatCharacter() noexcept
{
	fileStream << ";\n";
}