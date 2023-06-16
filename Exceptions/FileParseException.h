#pragma once

#include <stdexcept>
#include "../Utils/String/MyString.h"

class FileParseException : public std::exception
{
	MyString fileName;
	MyString desc;

public:
	FileParseException(const MyString& fileName, const MyString& desc = "") : fileName(fileName), desc(desc) {}

	const char* what() const noexcept override
	{
		MyString msg = "Couldn't parse file: " + fileName + " \nProblem:" + desc;
		return msg.c_str();
	}
};