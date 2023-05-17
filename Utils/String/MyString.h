#pragma once
#include <iostream>

class MyString
{
    char *data;
    size_t length;

    void copyFrom(const MyString &other);
    void free();
    void moveFrom(MyString &&other);
    explicit MyString(size_t capacity);

public:
    MyString();
    MyString(const char *data);
    MyString(const MyString &other);
    MyString(MyString &&other) noexcept;
    MyString &operator=(const MyString &other);
    MyString &operator=(MyString &&other) noexcept; 
    ~MyString();

    size_t getLength() const;
    const char *c_str() const;

    MyString &operator+=(const MyString &other);
    MyString substr(size_t begin, size_t howMany) const;

    char &operator[](size_t index);
    char operator[](size_t index) const;

    friend MyString operator+(const MyString &lhs, const MyString &rhs);
    friend std::istream &operator>>(std::istream &, MyString &str);
};

std::ostream &operator<<(std::ostream &os, const MyString &str);
bool operator<(const MyString &lhs, const MyString &rhs);
bool operator<=(const MyString &lhs, const MyString &rhs);
bool operator>=(const MyString &lhs, const MyString &rhs);
bool operator>(const MyString &lhs, const MyString &rhs);
bool operator==(const MyString &lhs, const MyString &rhs);
bool operator!=(const MyString &lhs, const MyString &rhs);