#pragma once
#include "String/MyString.h"

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool isWhitespace(char c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

size_t skipWithespace(const MyString& str, size_t startIndex)
{
	while (isWhitespace(str[startIndex]))
	{
		startIndex++;
	}

	return startIndex;
}



size_t skipObjectTillComma(const MyString& str, int startIndex)
{
	int currlyBraces = 0;
	int parenthasis = 0;
	int quotes = 0;
	while (str[startIndex = skipWithespace(str, startIndex)] != '\0')
	{
		switch (str[startIndex])
		{
		case '{':
			if (quotes == 0)
				currlyBraces++;
			break;
		case '}':
			if (quotes == 0)
				currlyBraces--;
			if (currlyBraces < 0)
				throw std::exception();
			break;
		case '[':
			if (quotes == 0)
				parenthasis++;
			break;
		case ']':
			if (quotes == 0)
				parenthasis--;
			if (parenthasis < 0)
				throw std::exception();
			break;
		case '"':
			if (str[startIndex - 1] == '\\')
			{
				break;
			}

			if (quotes == 0)
			{
				quotes++;
			}
			else
			{
				quotes--;
			}
			break;
		default:
			break;
		}


		if (quotes == 0 && parenthasis == 0 && currlyBraces == 0 && str[startIndex] == ',')
		{
			return startIndex - 1;
		}

		startIndex++;
	}

	if (str[startIndex] == '\0')
	{
		startIndex--;
	}

	//quotes == 0 && parenthasis == 0 && currlyBraces == 0 is not true->exception
	// TODO: any other case ?
	return startIndex;

}

bool isInteger(MyString elementString)
{
	size_t ind = 0;
	if (elementString[ind] == '-')
	{
		ind++;
	}

	if (elementString.getLength() - ind == 0)
	{
		return false;
	}

	while (ind < elementString.getLength())
	{
		if (!isDigit(elementString[ind]))
		{
			return false;
		}

		ind++;
	}

	return true;
}

int parseInt(MyString elementString)
{
	size_t ind = 0;
	int result = 0;
	int negative = 1;

	if (elementString[ind] == '-')
	{
		ind++;
		negative = -1;
	}

	while (ind < elementString.getLength())
	{
		if (!isDigit(elementString[ind]))
		{
			throw std::exception();
		}
		result = result * 10 + elementString[ind] - '0';
		ind++;
	}

	return result * negative;
}

// TODO: support e syntax
bool parseDecimal(MyString elementString)
{
	size_t ind = 0;
	double negative = 1;

	if (elementString[ind] == '-')
	{
		ind++;
		negative = -1;
	}

	if (elementString.getLength() - ind == 0)
	{
		throw std::exception();
	}

	if (!isDigit(elementString[ind]))
	{
		throw std::exception();
	}

	bool isValidPoint = false;
	double beforeDot = 0;
	double afterDot = 0;

	while (ind < elementString.getLength())
	{
		if (!isDigit(elementString[ind]))
		{
			if (!isValidPoint && elementString[ind] == '.')
			{
				isValidPoint = true;
				ind++;
				continue;
			}
			else
			{
				throw std::exception();
			}
		}

		if (isValidPoint)
		{
			afterDot = afterDot / 10 + (double)(elementString[ind] - '0') / 10;
		}
		else
		{
			beforeDot = beforeDot * 10 + elementString[ind] - '0';
		}

		ind++;
	}

	return negative * (afterDot + beforeDot);
}

// TODO: support e syntax
double isDecimal(MyString elementString)
{
	size_t ind = 0;

	if (elementString[ind] == '-')
	{
		ind++;
	}

	if (elementString.getLength() - ind == 0)
	{
		return false;
	}

	if (!isDigit(elementString[ind]))
	{
		return false;
	}

	bool isValidPoint = false;

	while (ind < elementString.getLength())
	{
		if (!isDigit(elementString[ind]))
		{
			if (!isValidPoint && elementString[ind] == '.')
			{
				isValidPoint = true;
			}
			else
			{
				return false;
			}
		}

		ind++;
	}

	return true;
}

size_t parseUInt(const MyString& str)
{
	int res = parseInt(str);
	if (res < 0)
	{
		throw std::exception();
	}

	return res;
}

//function to extract the context(the previous and the next n characters) by index
MyString safeContextSubstr(const MyString& str, size_t index, size_t contextLen)
{
	size_t startIndex = index < contextLen ? 0 : index - contextLen;
	size_t endIndex = str.getLength() > index + contextLen ? index + contextLen : str.getLength() - 1;

	return str.substr(startIndex, endIndex - startIndex + 1);
}

MyString parseToString(size_t n)
{
	std::stringstream ss;
	ss << n;
	return ss.str().c_str();
}

MyString jsonToString(const JsonElement* element)
{
	std::stringstream ss;
	element->print(ss, 0, 0);
	return ss.str().c_str();
}