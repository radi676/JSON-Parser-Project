#include "./JsonPathParser.h"

#include "../Utils/Helpers.h"
#include "../Utils/Parser/Parser.h"

#include "../Exceptions/InvalidPathException.h"

JsonPath JsonPathParser::parsePath(MyString path)
{
	JsonPath res;
	List<MyString> split;

	path.trim();

	if (path.getLength() == 0 || path[0] != '$')
	{
		throw InvalidPathException(Helpers::safeContextSubstr(path, 0, 10), "Path should start from the root($)");
	}

	if (path.getLength() == 1)
	{
		return JsonPath();
	}

	size_t startIndex = 1;
	if (path[startIndex] == '.')
	{
		startIndex++;
	}
	else if (path[startIndex] != '[')
	{
		throw InvalidPathException(Helpers::safeContextSubstr(path, startIndex, 15), "Expected either a point(.) or an opening block([)");
	}

	while (path[startIndex] != '\0')
	{
		bool inQuotes = false;
		bool inBlock = false;

		if (path[startIndex] == '.')
		{
			startIndex++;
		}

		//two consequent ..
		if (path[startIndex] == '.')
		{
			throw InvalidPathException(Helpers::safeContextSubstr(path, startIndex, 15), "Empty path key is not allowed.");
		}

		if (path[startIndex] == '[')
		{
			inBlock = true;
			startIndex++;
			if (path[startIndex] == '\'')
			{
				inQuotes = true;
				startIndex++;
			}
		}

		size_t startOfKey = startIndex;
		size_t endIndex = startIndex;

		while (path[startIndex] != '\0')
		{
			if (inQuotes)
			{
				if (path[startIndex + 1] == '\'' && path[startIndex + 2] == ']')
				{
					endIndex = startIndex;
					startIndex = startIndex + 3;
					res.push(JsonKey(path.substr(startOfKey, endIndex - startOfKey + 1)));
					break;
				}
			}
			else if (inBlock)
			{
				if (path[startIndex + 1] == ']')
				{
					endIndex = startIndex;
					startIndex = startIndex + 2;
					res.push(JsonKey(Parser::parseUInt(path.substr(startOfKey, endIndex - startOfKey + 1))));
					break;
				}
			}
			else
			{
				if (path[startIndex + 1] == '.' || path[startIndex + 1] == '[' || path[startIndex + 1] == '\0')
				{
					endIndex = startIndex;
					startIndex = startIndex + 1;
					res.push(JsonKey(path.substr(startOfKey, endIndex - startOfKey + 1)));
					break;
				}
				else if (path[startIndex + 1] == '\'' || path[startIndex + 1] == ']' || path[startIndex + 1] == ' ')
				{
					throw InvalidPathException(Helpers::safeContextSubstr(path, startIndex, 20), MyString("Not allowed symbol in non-quoted block key. Symbol: ") + MyString(path[startIndex + 1]));

				}
			}

			startIndex++;
		}
	}

	return res;
}