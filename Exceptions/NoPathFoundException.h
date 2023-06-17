#include <stdexcept>
#include "../Path/JsonPath.h"

class NoPathFoundException : public std::exception
{
    MyString msg;
public:
    NoPathFoundException(const JsonPath& path, const MyString& desc = "Unknown")
    {
        msg = "Couldn't find path: " + path.toString() + "\nDetails: " + desc;
    }

    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};