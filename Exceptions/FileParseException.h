#pragma once

#include <stdexcept>
#include "../Utils/String/MyString.h"

class FileParseException : public std::exception
{
	MyString msg;

public:
	FileParseException(const MyString& fileName, const MyString& desc = "")
	{
		msg = "Couldn't parse file: " + fileName + " \nProblem:" + desc;
	}

	const char* what() const noexcept override
	{
		return msg.c_str();
	}
};