#include <stdexcept>
#include "../Utils/String/MyString.h"

class NoKeyFoundException : public std::exception
{
	MyString msg;
public:
	NoKeyFoundException(const MyString& key, const MyString& desc = "Unknown")
	{
		msg = "Couldn't find key: " + key + "\nDetails: " + desc;
	}

	const char* what() const noexcept override
	{
		return msg.c_str();
	}
};