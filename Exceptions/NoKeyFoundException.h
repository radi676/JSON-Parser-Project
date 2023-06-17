#include <stdexcept>
#include "../Utils/String/MyString.h"

class NoKeyFoundException : public std::exception
{
    MyString key;
    MyString desc;

public:
    NoKeyFoundException(const MyString &key, const MyString &desc = "Unknown") : key(key), desc(desc) {}

    const char *what() const noexcept override
    {
        MyString msg = "Couldn't find key " + key + " Details: " + desc;
        return msg.c_str();
    }
};