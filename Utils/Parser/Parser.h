#pragma once

#include "../String/MyString.h"

#include <sstream>

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
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

MyString parseToString(size_t n)
{
	std::stringstream ss;
	ss << n;
	return ss.str().c_str();
}

