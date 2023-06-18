#pragma once

#include "../List/List.hpp"
#include "../String/MyString.h"

class InputUtils
{
public:
	InputUtils() = delete;
	static List<MyString> getFields(const MyString& str);
};