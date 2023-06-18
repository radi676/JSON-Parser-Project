#pragma once

#include "../Path/JsonPath.h"

class JsonPathParser
{
public:
	JsonPathParser() = delete;
	static JsonPath parsePath(MyString path);
};


