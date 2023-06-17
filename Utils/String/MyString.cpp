#include "MyString.h"
#include <cstring>
#pragma warning(disable:4996)

void MyString::copyFrom(const MyString& other)
{
	this->length = other.length;
	this->data = new char[length + 1];
	strcpy(this->data, other.data);
}

void MyString::moveFrom(MyString&& other)
{
	this->data = other.data;
	other.data = nullptr;
	this->length = other.length;
}

void MyString::free()
{
	delete[] this->data;
	this->data = nullptr;
}

MyString::MyString(size_t capacity) : length(0)
{
	data = new char[capacity];
}

MyString::MyString() : MyString(1)
{
	length = 0;
	data[0] = '\0';
}

MyString::MyString(const char* data) : MyString(strlen(data) + 1)
{
	strcpy(this->data, data);
	length = strlen(data);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString::MyString(MyString&& other) noexcept
{
	moveFrom(std::move(other));
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

MyString::~MyString()
{
	free();
}

size_t MyString::getLength() const
{
	return this->length;
}
const char* MyString::c_str() const
{
	return this->data;
}

MyString& MyString::operator+=(const MyString& other)
{
	char* result = new char[length + other.length + 1];
	result[0] = '\0';
	strcat(result, this->data);
	strcat(result, other.data);

	delete[] this->data;
	this->data = result;
	length = length + other.length;

	return *this;
}

MyString MyString::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > this->length)
	{
		throw std::length_error("Error, Substr out of range");
	}
	MyString result(howMany + 1);
	for (size_t i = 0; i < howMany; i++)
	{
		result.data[i] = this->data[i + begin];
	}
	result[howMany] = '\0';
	result.length = howMany;

	return result;
}

char& MyString::operator[](size_t index)
{
	return this->data[index];
}

char MyString::operator[](size_t index) const
{
	return this->data[index];
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString result(lhs.length + rhs.length + 1);
	result[0] = '\0';
	strcat(result.data, lhs.data);
	strcat(result.data, rhs.data);
	result.length = lhs.length + rhs.length;
	return result;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	std::cin >> buff;

	delete[] str.data;
	str.length = strlen(buff);
	str.data = new char[str.length + 1];
	strcpy(str.data, buff);
	return is;
}

void MyString::getline(std::istream& is, size_t len)
{
	delete data;
	data = new char[len + 1];
	is.getline(data, len);
	length = strlen(data);
}


std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	std::cout << str.c_str();
	return os;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

MyString& MyString::trim()
{
	size_t startIndex = 0;
	while (data[startIndex] == ' ' || data[startIndex] == '\t' || data[startIndex] == '\n')
	{
		startIndex++;
	}

	size_t endIndex = length - 1;
	while (startIndex <= endIndex && data[endIndex] == ' ' || data[endIndex] == '\t' || data[endIndex] == '\n')
	{
		endIndex--;
	}

	if (startIndex != 0 || endIndex != length - 1)
	{
		MyString res = substr(startIndex, endIndex - startIndex + 1);
		*this = res;
	}

	return *this;
}


List<MyString> MyString::split(char c)const
{
	List<MyString> res;

	size_t startIndex = 0, endIndex = 0;
	while (endIndex < length)
	{
		startIndex = endIndex;

		while (data[endIndex] != c && data[endIndex] != '\0')
		{
			endIndex++;
		}

		res.pushBack(substr(startIndex, endIndex - startIndex));

		endIndex++;
	}

	return std::move(res);
}

void MyString::replace(char what, char with)
{
	for (size_t i = 0; i < length; i++)
	{
		if (data[i] == what)
		{
			data[i] = with;
		}
	}

}