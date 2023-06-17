#pragma once

#include <stdexcept>
#include "../Path/JsonPath.h"

class PathAlreadyExistsException : public std::exception
{
	MyString msg;

public:
	PathAlreadyExistsException(const JsonPath& path, const MyString& desc = "Unknown")
	{
		msg = "Path already exists " + path.toString() + "\nDetails: " + desc;
	}

	const char* what() const noexcept override
	{
		return msg.c_str();
	}
};