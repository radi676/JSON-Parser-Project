#pragma once

class Validators
{
public:
	Validators() = delete;

	static bool isWhitespace(char c);
	static bool isDigit(char c);
};