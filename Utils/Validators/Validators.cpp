#include "./Validators.h"

bool Validators::isWhitespace(char c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool Validators::isDigit(char c)
{
	return c >= '0' && c <= '9';
}