#pragma once

class Validators
{
public:
	Validators() = delete;

	static bool isWhitespace(char c)
	{
		return c == ' ' || c == '\t' || c == '\n' || c == '\r';
	}

	static bool isDigit(char c)
	{
		return c >= '0' && c <= '9';
	}
};