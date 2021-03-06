#include <stdafx.h>

#include <FileValueWriter.h>

FileValueWriterBase::FileValueWriterBase(const std::string& filename, std::ios::ios_base::openmode flags) : Base(filename, flags)
{}

void FileValueWriterBase::checkWrite() const
{
	if (!fstream_->good())
	{
		throw std::ios_base::failure(std::string("Error when writing data to the file '") + getCurrentFileName() + "' !");
	}
}

void FileValueWriterBase::writeRawDataAt(const std::vector<char>& data, std::streampos position)
{
	write(data, position, data.size());
	checkWrite();
}

void FileValueWriterBase::writeRawDataAt(const char* const data, std::streamsize size, std::streampos position)
{
	write(data, position, size);
	checkWrite();
}