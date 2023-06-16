#include <stdexcept>
#include "../Utils/String/MyString.h"

class InvalidPathException : public std::exception
{
    MyString context;
    MyString desc;

public:
    InvalidPathException(const MyString& context, const MyString& desc = "") : context(context), desc(desc) {}

    const char* what() const noexcept override
    {
        MyString msg = "Couldn't parse json path around " + context + " \nProblem:" + desc;
        return msg.c_str();
    }
};