#pragma once

#include <FileValueReader.h>

#include <vector>
#include <functional>
#include <string>

class __declspec(dllexport)  BasicParser
{
public:
	BasicParser(BasicParser&& other);
	BasicParser(std::string const& filename);
	void loadFile(std::string const& filename);
	void unloadFile();
	std::string getFileName() const noexcept;

protected:
	FileValueReader<Endianess::little> reader_;
	std::vector<std::function<void()>> events_;
};