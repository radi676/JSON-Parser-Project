#include <stdexcept>
#include "../Utils/String/MyString.h"

class InvalidJsonException : public std::exception
{
    MyString context;
    MyString desc;

public:
    InvalidJsonException(const MyString& context, const MyString& desc = "Unknown") : context(context), desc(desc) {}

    const char* what() const noexcept override
    {
        MyString msg = "Couldn't parse json value around " + context + " \nProblem:" + desc;
        return msg.c_str();
    }
};