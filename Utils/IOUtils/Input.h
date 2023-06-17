#pragma once

#include "../List/List.hpp"
#include "../String/MyString.h"
#include "../Helpers.h"

List<MyString> getFields(const MyString& str)
{
	List<MyString> fields;

	size_t startIndex = 0;
	bool isInQuotes = false;

	while (str[startIndex = skipWithespace(str, startIndex)] != '\0')
	{
		isInQuotes = str[startIndex] == '"';
		char delim = isInQuotes ? '"' : ' ';

		if (isInQuotes)
		{
			startIndex++;
		}

		List<char> word;
		while (str[startIndex] != '\0')
		{
			if (!isInQuotes && str[startIndex] == ' ')
			{
				break;
			}
			else if (isInQuotes && str[startIndex] == '"' && (startIndex == 0 || str[startIndex - 1] != '\\'))
			{
				startIndex++;
				break;
			}

			if (isInQuotes && str[startIndex] == '"' && startIndex > 0 && str[startIndex - 1] == '\\')
			{
				word.getLast() = '"';
			}
			else
			{
				word.pushBack(str[startIndex]);
			}

			startIndex++;
		}

		char* f = new char[word.getCount() + 1];

		for (size_t i = 0; i < word.getCount(); i++)
		{
			f[i] = word[i];
		}
		f[word.getCount()] = '\0';

		MyString strVal = f;
		delete[] f;

		if (!isInQuotes)
		{
			strVal.trim();
			if (strVal.getLength() == 0)
			{
				continue;
			}
		}

		fields.pushBack(strVal);
	}

	return fields;
}