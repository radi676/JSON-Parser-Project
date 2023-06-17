#include <stdexcept>
#include "../Utils/String/MyString.h"

class FileWriteException : public std::exception
{
	MyString msg;
public:
	FileWriteException(const MyString& file, const MyString& desc = "Unknown")
	{
		msg = "Couldn't write to file: " + file + " \nProblem:" + desc;
	}

	const char* what() const noexcept override
	{
		return msg.c_str();
	}
};