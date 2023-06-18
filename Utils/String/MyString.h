#pragma once
#include <iostream>

#include "../List/List.hpp"

class MyString
{
	char* data;
	size_t length;

	void copyFrom(const MyString& other);
	void free();
	void moveFrom(MyString&& other);

public:
	MyString();

	// memory allocation
	explicit MyString(size_t capacity);

	MyString(const char* data);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept; // move copy constructor
	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept; // move operator= constructor
	~MyString();

	MyString& trim();
	List<MyString> split(char c)const;

	size_t getLength() const;
	const char* c_str() const;
	void replace(char what, char with);

	MyString& operator+=(const MyString& other);
	MyString substr(size_t begin, size_t howMany) const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	void getline(std::istream&, size_t len);

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream&, MyString& str);
};

std::ostream& operator<<(std::ostream& os, const MyString& str);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
