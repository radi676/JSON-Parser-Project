#pragma once
#include "String/MyString.h"

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

	if (!(quotes == 0 && parenthasis == 0 && currlyBraces == 0))
	{
		MyString msg = "Error parsing json, got an extra ";
		if (quotes < 0)
		{
			msg += " closing quote(\") without opening; ";
		}
		if (quotes > 0)
		{
			msg += " opening quote(\") without closing; ";
		}
		if (currlyBraces < 0)
		{
			msg += " closing curly brace(}) without opening; ";
		}
		if (currlyBraces > 0)
		{
			msg += " opening curly brace({) without closing; ";
		}
		if (parenthasis < 0)
		{
			msg += " closing parenthesis(]) without opening; ";
		}
		if (parenthasis > 0)
		{
			msg += " opening parenthesis([) without closing; ";
		}

		msg += " which lead to incorrect syntax!";
		throw std::invalid_argument(msg.c_str());
	}

	return startIndex;

}

//function to extract the context(the previous and the next n characters) by index
MyString safeContextSubstr(const MyString& str, size_t index, size_t contextLen)
{
	size_t startIndex = index < contextLen ? 0 : index - contextLen;
	size_t endIndex = str.getLength() > index + contextLen ? index + contextLen : str.getLength() - 1;

	return str.substr(startIndex, endIndex - startIndex + 1);
}