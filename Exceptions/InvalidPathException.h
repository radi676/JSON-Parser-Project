#pragma once

#include <stdexcept>
#include "../Utils/String/MyString.h"

class InvalidPathException : public std::exception
{
	MyString msg;
public:
	InvalidPathException(const MyString& context, const MyString& desc = "Unknown")
	{
		msg = "Couldn't parse json path around " + context + " \nProblem:" + desc;
	}

	const char* what() const noexcept override
	{
		return msg.c_str();
	}
};