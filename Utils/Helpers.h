#pragma once
#include "./String/MyString.h"

class Helpers
{
public:
	Helpers() = delete;
	static size_t skipWithespace(const MyString& str, size_t startIndex);

	//function to extract the context(the previous and the next n characters) by index
	static MyString safeContextSubstr(const MyString& str, size_t index, size_t contextLen);

};
