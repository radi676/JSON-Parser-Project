#pragma once
#include "../JsonDocument.h"

#include "../Elements/Base/Primitive/Boolean/BooleanJsonElement.h"
#include "../Elements/Base/Primitive/Null/NullJsonElement.h"
#include "../Elements/Base/Primitive/Number/DecimalJsonElement.h"
#include "../Elements/Base/Primitive/Number/IntegerJsonElement.h"
#include "../Elements/Base/Primitive/String/StringJsonElement.h"

#include "../Utils/File/File.h"
#include "../Utils/Pair/Pair.hpp"
#include "../Utils/Helpers.h"

#include "../Exceptions/InvalidJsonException.h"
#include "../Exceptions/FileParseException.h"
#include "../Exceptions/InvalidPathException.h"

class JsonElementParser
{
private:
	static JsonElementBase* parseObject(MyString elementString)
	{
		elementString.trim();

		JsonObject* object = new JsonObject();

		size_t startIndex = 0;

		while ((startIndex = skipWithespace(elementString, startIndex)) < elementString.getLength())
		{
			//in the beginning we need a quote. It is followed by key
			if (elementString[startIndex] != '"')
			{
				throw InvalidJsonException(safeContextSubstr(elementString, startIndex, 30), "Expeced a key surronded in quotes(\"). Missing opening quote.");
			}

			startIndex++;
			size_t endKeyIndex = startIndex;

			while (elementString[endKeyIndex] != '\0' && elementString[endKeyIndex] != '"' && elementString[endKeyIndex - 1] != '\\')
			{
				endKeyIndex++;
			}

			if (elementString[endKeyIndex] != '"')
			{
				throw InvalidJsonException(safeContextSubstr(elementString, endKeyIndex, 30), "Expeced a key surronded in quotes(\"). Missing closing quote.");
			}

			MyString key = elementString.substr(startIndex, endKeyIndex - startIndex);

			startIndex = endKeyIndex + 1;

			startIndex = skipWithespace(elementString, startIndex);

			if (elementString[startIndex] != ':')
			{
				throw InvalidJsonException(safeContextSubstr(elementString, startIndex, 30), "Expeced a semi-column separating key and value.");
			}

			startIndex++;

			startIndex = skipWithespace(elementString, startIndex);

			size_t startUnknownElementIndex = startIndex;
			//get the index where the value ends
			size_t endUnknownElementIndex;
			try
			{
				endUnknownElementIndex = skipObjectTillComma(elementString, startIndex);
			}
			catch (const std::exception& ex)
			{
				throw InvalidJsonException(elementString, ex.what());
			}

			MyString objStr = elementString.substr(startUnknownElementIndex, endUnknownElementIndex - startUnknownElementIndex + 1);
			JsonElementBase* element;

			try
			{
				element = parseUnknownElement(objStr);
			}
			catch (const InvalidJsonException& ex)
			{
				throw InvalidJsonException(objStr, "Error parsing json element: \n" + MyString(ex.what()));
			}
			catch (std::exception& ex)
			{
				throw InvalidJsonException(objStr, "Unknown error occured while parsing json element. \nDetails: "+ MyString(ex.what()));
			}

			if (!object->pushBack(key, element))
			{
				throw InvalidJsonException(objStr, "Key already exists in json object.");
			}

			//skip comma
			startIndex = endUnknownElementIndex + 2;
		}

		return object;
	}

	static JsonElementBase* parseArray(MyString elementString)
	{
		elementString.trim();

		JsonArray* array = new JsonArray();

		size_t startIndex = 0;

		while (startIndex < elementString.getLength())
		{
			startIndex = skipWithespace(elementString, startIndex);

			size_t startUnknownElementIndex = startIndex;
			size_t endUnknownElementIndex;
			try
			{
				endUnknownElementIndex = skipObjectTillComma(elementString, startIndex);
			}
			catch (const std::exception& ex)
			{
				throw InvalidJsonException(elementString, ex.what());
			}

			MyString arrStr = elementString.substr(startUnknownElementIndex, endUnknownElementIndex - startUnknownElementIndex + 1);
			try
			{
				array->pushBack(parseUnknownElement(arrStr));

			}
			catch (const InvalidJsonException& ex)
			{
				throw InvalidJsonException(arrStr, "Error parsing json element: \n" + MyString(ex.what()));
			}
			catch (std::exception& ex)
			{
				throw InvalidJsonException(arrStr, "Unknown error occured while parsing json element. \nDetails:"+ MyString(ex.what()));
			}

			// skip comma
			startIndex = endUnknownElementIndex + 2;
		}

		return array;
	}

	static JsonElementBase* parsePrimitive(MyString elementString)
	{
		elementString.trim();
		if (elementString == "true")
		{
			return new BooleanJsonElement(true);
		}
		else if (elementString == "false")
		{
			return new BooleanJsonElement(false);
		}
		else if (elementString == "null")
		{
			return new NullJsonElement();
		}
		else if (elementString[0] == '"' && elementString[elementString.getLength() - 1] == '"')
		{
			return new StringJsonElement(elementString.substr(1, elementString.getLength() - 2));
		}
		else if (isInteger(elementString))
		{
			return new IntegerJsonElement(parseInt(elementString));
		}
		else if (isDecimal(elementString))
		{
			return new DecimalJsonElement(parseDecimal(elementString));
		}
		else
		{
			throw InvalidJsonException(elementString, "Unknown json element value. Could not determine element type.");
		}
	}

	static JsonElementBase* parseUnknownElement(MyString elementString)
	{
		elementString.trim();
		if (elementString.getLength() == 0)
		{
			throw InvalidJsonException("", "Expected a non-empty value.");
		}

		size_t startIndex = 0;
		size_t endIndex = elementString.getLength() - 1;

		if (elementString[startIndex] == '{' || elementString[endIndex] == '}')
		{
			if (elementString[startIndex] != '{')
			{
				throw InvalidJsonException(safeContextSubstr(elementString, startIndex, 50), "Expeced an opening curly brace({).");

			}
			if (elementString[endIndex] != '}')
			{
				throw InvalidJsonException(safeContextSubstr(elementString, endIndex, 50), "Expeced a closing curly brace(}).");

			}

			return parseObject(elementString.substr(startIndex + 1, endIndex - startIndex - 1));
		}
		else if (elementString[startIndex] == '[' || elementString[endIndex] == ']')
		{
			if (elementString[startIndex] != '[')
			{
				throw InvalidJsonException(safeContextSubstr(elementString, startIndex, 50), "Expeced an opening square bracket([).");

			}
			if (elementString[endIndex] != ']')
			{
				throw InvalidJsonException(safeContextSubstr(elementString, endIndex, 50), "Expeced a closing square bracket(]).");

			}

			return parseArray(elementString.substr(startIndex + 1, endIndex - startIndex - 1));
		}
		else
		{
			return parsePrimitive(elementString.substr(startIndex, endIndex - startIndex + 1));
		}
	}

public:

	JsonElementParser() = delete;


	static JsonDocument parseFile(const MyString& filePath)
	{
		std::ifstream ifs(filePath.c_str());

		if (!ifs.is_open())
		{
			throw FileParseException(filePath, "Could not open file.");
		}

		MyString documentStr = readFile(ifs);

		try {
			JsonElement parsed = parseElement(documentStr);
			return JsonDocument(parsed);
		}
		catch (InvalidJsonException& ex)
		{
			throw FileParseException(filePath, MyString("Could not parse file.\n") + MyString(ex.what()));
		}

	}

	static JsonElement parseElement(MyString elementString)
	{
		return JsonElement(parseUnknownElement(elementString));
	}
};