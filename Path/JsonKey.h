#pragma once

#include "../Utils/String/MyString.h"

//If a union contains a non-static data member with a non-trivial special member function (copy/move constructor, copy/move assignment, or destructor), that function is deleted by default in the union and needs to be defined explicitly by the programmer.
//If a union contains a non-static data member with a non-trivial default constructor, the default constructor of the union is deleted by default unless a variant member of the union has a default member initializer .
class JsonKey
{
	union data
	{
		MyString key;
		size_t arrayIndex;
		data() : key() {}
		~data() {}
	} _data;

	bool _isArray;

	// Needed _data key is not primitive data type
	void copyFrom(const JsonKey& other);

public:
	JsonKey() = default;
	JsonKey(const MyString& key);
	JsonKey(const char* key);
	JsonKey(size_t index);

	// Needed _data key is not primitive data type
	JsonKey(const JsonKey& other);
	JsonKey& operator=(const JsonKey& other);
	const MyString& key() const;
	size_t arrayIndex() const;
	void setArray(size_t index);
	void setKey(const MyString& key);
	bool isArray() const;
};