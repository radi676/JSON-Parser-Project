#include <stdexcept>
#include "../Utils/String/MyString.h"

class FileWriteException : public std::exception
{
    MyString file;
    MyString desc;

public:
    FileWriteException(const MyString& file, const MyString& desc = "Unknown") : file(file), desc(desc) {}

    const char* what() const noexcept override
    {
        MyString msg = "Couldn't write to file: " + file + " \nProblem:" + desc;
        return msg.c_str();
    }
};