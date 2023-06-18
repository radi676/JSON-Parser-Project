#pragma once
#include "./Parser.h"
#include "../Validators/Validators.h"
#include <sstream>

bool Parser::isInteger(MyString elementString)
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
		if (!Validators::isDigit(elementString[ind]))
		{
			return false;
		}

		ind++;
	}

	return true;
}

int Parser::parseInt(MyString elementString)
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
		if (!Validators::isDigit(elementString[ind]))
		{
			throw std::invalid_argument("Invalid integer number character found!");
		}
		result = result * 10 + elementString[ind] - '0';
		ind++;
	}

	return result * negative;
}

bool Parser::parseDecimal(MyString elementString)
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
		throw std::invalid_argument("String is empty!");
	}

	if (!Validators::isDigit(elementString[ind]))
	{
		throw std::invalid_argument("String contains non-digit characters!");
	}

	bool isValidPoint = false;
	double beforeDot = 0;
	double afterDot = 0;

	while (ind < elementString.getLength())
	{
		if (!Validators::isDigit(elementString[ind]))
		{
			if (!isValidPoint && elementString[ind] == '.')
			{
				isValidPoint = true;
				ind++;
				continue;
			}
			else
			{
				throw std::invalid_argument("Invalid decimal number fomat!");

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

double Parser::isDecimal(MyString elementString)
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

	if (!Validators::isDigit(elementString[ind]))
	{
		return false;
	}

	bool isValidPoint = false;

	while (ind < elementString.getLength())
	{
		if (!Validators::isDigit(elementString[ind]))
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

size_t Parser::parseUInt(const MyString& str)
{
	int res = parseInt(str);
	if (res < 0)
	{
		throw std::invalid_argument("Invalid unsigned number fomat!");
	}

	return res;
}

MyString Parser::parseToString(size_t n)
{
	std::stringstream ss;
	ss << n;
	return ss.str().c_str();
}