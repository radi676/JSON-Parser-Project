#pragma once

#include "../String/MyString.h"

class Regex
{
	MyString key;

	int matchSequence(const MyString& where, const MyString& what, size_t startIndex) const;

public:

	Regex(const MyString& key);

	bool match(const MyString& str) const;
};