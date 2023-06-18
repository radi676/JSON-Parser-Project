#pragma once

#include "../String/MyString.h"

class Parser {

public:
	Parser() = delete;

	static bool isInteger(MyString elementString);
	static int parseInt(MyString elementString);
	static bool parseDecimal(MyString elementString);
	static double isDecimal(MyString elementString);
	static size_t parseUInt(const MyString& str);
	static MyString parseToString(size_t n);
};