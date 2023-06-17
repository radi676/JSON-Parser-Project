#include <stdexcept>
#include "../Parser/Path/JsonPath.h"

class PathAlreadyExistsException : public std::exception
{
    JsonPath path;
    MyString desc;

public:
    PathAlreadyExistsException(const JsonPath &path, const MyString &desc = "Unknown") : path(path), desc(desc) {}

    const char *what() const noexcept override
    {
        MyString msg = "Path already exists " + path.toString() + "\Details: " + desc;

        return msg.c_str();
    }
};