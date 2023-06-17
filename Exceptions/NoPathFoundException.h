#include <stdexcept>
#include "../Parser/Path/JsonPath.h"

class NoPathFoundException : public std::exception
{
    JsonPath path;
    MyString desc;

public:
    NoPathFoundException(const JsonPath &path, const MyString &desc = "Unknown") : path(path), desc(desc) {}

    const char *what() const noexcept override
    {
        MyString msg = "Couldn't find path: " + path.toString() + "\nDetails: " + desc;

        return msg.c_str();
    }
};