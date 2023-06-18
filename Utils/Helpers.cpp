#include "./Helpers.h"
#include "./Validators/Validators.h"

size_t Helpers::skipWithespace(const MyString& str, size_t startIndex)
{
	while (Validators::isWhitespace(str[startIndex]))
	{
		startIndex++;
	}

	return startIndex;
}

MyString Helpers::safeContextSubstr(const MyString& str, size_t index, size_t contextLen)
{
	size_t startIndex = index < contextLen ? 0 : index - contextLen;
	size_t endIndex = str.getLength() > index + contextLen ? index + contextLen : str.getLength() - 1;

	return str.substr(startIndex, endIndex - startIndex + 1);
}
