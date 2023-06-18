#pragma once
#include <fstream>
#include "../String/MyString.h"

class FileUtils
{
public:
	FileUtils() = delete;
	static size_t getFileSize(std::ifstream& ifs);
	static MyString readFile(std::ifstream& ifs);
};