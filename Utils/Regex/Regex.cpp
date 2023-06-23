#include "Regex.h"

int Regex::matchSequence(const MyString &where, const MyString &what, size_t startIndex) const
{
	if (what.getLength() + startIndex > where.getLength())
	{
		return -1;
	}

	for (size_t i = startIndex; i < where.getLength(); i++)
	{
		size_t ind;
		for (ind = 0; ind < what.getLength(); ind++)
		{
			if (where[ind + i] != what[ind])
			{
				break;
			}
		}

		if (ind == what.getLength())
		{
			return i;
		}
	}

	return -1;
}

Regex::Regex(const MyString &key) : key(key)
{
}

bool Regex::match(const MyString &str) const
{
	size_t startIndex = 0;
	size_t matchedIndex = 0;

	bool isAsterix = false;

	while (key[startIndex] != '\0')
	{
		size_t endIndex = startIndex;

		while (key[endIndex] != '\0' && !((key[endIndex] == '*' || key[endIndex] == '?') && (endIndex == 0 || key[endIndex - 1] != '\\')))
		{
			endIndex++;
		}

		MyString toMatch = key.substr(startIndex, endIndex - startIndex);

		int m = matchSequence(str, toMatch, matchedIndex);

		if (m == -1)
		{
			return false;
		}

		if (!isAsterix && m != matchedIndex)
		{
			return false;
		}

		matchedIndex = m + toMatch.getLength();

		startIndex = endIndex;

		isAsterix = key[startIndex] == '*';

		if (!isAsterix)
		{
			if (key[startIndex] == '\0')
			{
				return matchedIndex > str.getLength() - 1;
			}
			matchedIndex++;
		}

		if (key[startIndex] == '\0')
		{
			return true;
		}

		startIndex++;
	}

	return true;
}