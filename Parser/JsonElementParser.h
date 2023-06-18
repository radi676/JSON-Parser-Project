#pragma once

#include "../Utils/String/MyString.h"

#include "../JsonDocument.h"
#include "../Elements/JsonElement.h"
#include "../Elements/Base/JsonElementBase.h"

class JsonElementParser
{
private:
	static size_t skipObjectTillComma(const MyString& str, int startIndex);
	static JsonElementBase* parseObject(MyString elementString);
	static JsonElementBase* parseArray(MyString elementString);
	static JsonElementBase* parsePrimitive(MyString elementString);
	static JsonElementBase* parseUnknownElement(MyString elementString);

public:

	JsonElementParser() = delete;

	static JsonDocument parseFile(const MyString& filePath);
	static JsonElement parseElement(MyString elementString);
};