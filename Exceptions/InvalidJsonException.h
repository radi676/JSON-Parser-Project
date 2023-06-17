#include <stdexcept>
#include "../Utils/String/MyString.h"

class InvalidJsonException : public std::exception
{
	MyString msg;
public:
	InvalidJsonException(const MyString& context, const MyString& desc = "Unknown")
	{
		msg = "Couldn't parse json value around " + context + " \nProblem:" + desc;
	}

	const char* what() const noexcept override
	{
		return msg.c_str();
	}
};