#include "./JsonElementParser.h"
#include "../JsonDocument.h"

#include "../Elements/Base/Primitive/Boolean/BooleanJsonElement.h"
#include "../Elements/Base/Primitive/Null/NullJsonElement.h"
#include "../Elements/Base/Primitive/Number/DecimalJsonElement.h"
#include "../Elements/Base/Primitive/Number/IntegerJsonElement.h"
#include "../Elements/Base/Primitive/String/StringJsonElement.h"

#include "../Utils/File/FileUtils.h"
#include "../Utils/Pair/Pair.hpp"
#include "../Utils/String/MyString.h"
#include "../Utils/Helpers.h"

#include "../Exceptions/InvalidJsonException.h"
#include "../Exceptions/FileParseException.h"
#include "../Exceptions/InvalidPathException.h"


	 JsonElementBase* JsonElementParser::parseObject(MyString elementString)
	{
		elementString.trim();

		JsonObject* object = new JsonObject();

		size_t startIndex = 0;

		while ((startIndex = Helpers::skipWithespace(elementString, startIndex)) < elementString.getLength())
		{
			//in the beginning we need a quote. It is followed by key
			if (elementString[startIndex] != '"')
			{
				throw InvalidJsonException(Helpers::safeContextSubstr(elementString, startIndex, 30), "Expeced a key surronded in quotes(\"). Missing opening quote.");
			}

			startIndex++;
			size_t endKeyIndex = startIndex;

			while (elementString[endKeyIndex] != '\0' && elementString[endKeyIndex] != '"' && elementString[endKeyIndex - 1] != '\\')
			{
				endKeyIndex++;
			}

			if (elementString[endKeyIndex] != '"')
			{
				throw InvalidJsonException(Helpers::safeContextSubstr(elementString, endKeyIndex, 30), "Expeced a key surronded in quotes(\"). Missing closing quote.");
			}

			MyString key = elementString.substr(startIndex, endKeyIndex - startIndex);

			startIndex = endKeyIndex + 1;

			startIndex = Helpers::skipWithespace(elementString, startIndex);

			if (elementString[startIndex] != ':')
			{
				throw InvalidJsonException(Helpers::safeContextSubstr(elementString, startIndex, 30), "Expeced a semi-column separating key and value.");
			}

			startIndex++;

			startIndex = Helpers::skipWithespace(elementString, startIndex);

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
				throw InvalidJsonException(objStr, "Unknown error occured while parsing json element. \nDetails: " + MyString(ex.what()));
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

	 JsonElementBase* JsonElementParser::parseArray(MyString elementString)
	{
		elementString.trim();

		JsonArray* array = new JsonArray();

		size_t startIndex = 0;

		while (startIndex < elementString.getLength())
		{
			startIndex = Helpers::skipWithespace(elementString, startIndex);

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
				throw InvalidJsonException(arrStr, "Unknown error occured while parsing json element. \nDetails:" + MyString(ex.what()));
			}

			// skip comma
			startIndex = endUnknownElementIndex + 2;
		}

		return array;
	}

	 JsonElementBase* JsonElementParser::parsePrimitive(MyString elementString)
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
		else if (Parser::isInteger(elementString))
		{
			return new IntegerJsonElement(Parser::parseInt(elementString));
		}
		else if (Parser::isDecimal(elementString))
		{
			return new DecimalJsonElement(Parser::parseDecimal(elementString));
		}
		else
		{
			throw InvalidJsonException(elementString, "Unknown json element value. Could not determine element type.");
		}
	}

	JsonElementBase* JsonElementParser::parseUnknownElement(MyString elementString)
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
				throw InvalidJsonException(Helpers::safeContextSubstr(elementString, startIndex, 50), "Expeced an opening curly brace({).");

			}
			if (elementString[endIndex] != '}')
			{
				throw InvalidJsonException(Helpers::safeContextSubstr(elementString, endIndex, 50), "Expeced a closing curly brace(}).");

			}

			return parseObject(elementString.substr(startIndex + 1, endIndex - startIndex - 1));
		}
		else if (elementString[startIndex] == '[' || elementString[endIndex] == ']')
		{
			if (elementString[startIndex] != '[')
			{
				throw InvalidJsonException(Helpers::safeContextSubstr(elementString, startIndex, 50), "Expeced an opening square bracket([).");

			}
			if (elementString[endIndex] != ']')
			{
				throw InvalidJsonException(Helpers::safeContextSubstr(elementString, endIndex, 50), "Expeced a closing square bracket(]).");

			}

			return parseArray(elementString.substr(startIndex + 1, endIndex - startIndex - 1));
		}
		else
		{
			return parsePrimitive(elementString.substr(startIndex, endIndex - startIndex + 1));
		}
	}


	 JsonDocument JsonElementParser::parseFile(const MyString& filePath)
	{
		std::ifstream ifs(filePath.c_str());

		if (!ifs.is_open())
		{
			throw FileParseException(filePath, "Could not open file.");
		}

		MyString documentStr = FileUtils::readFile(ifs);

		try {
			JsonElement parsed = parseElement(documentStr);
			return JsonDocument(parsed);
		}
		catch (InvalidJsonException& ex)
		{
			throw FileParseException(filePath, MyString("Could not parse file.\n") + MyString(ex.what()));
		}

	}

	 JsonElement JsonElementParser::parseElement(MyString elementString)
	{
		return JsonElement(parseUnknownElement(elementString));
	}


	size_t JsonElementParser::skipObjectTillComma(const MyString& str, int startIndex)
	{
		int currlyBraces = 0;
		int parenthasis = 0;
		int quotes = 0;

		if (str[startIndex] == ',')
		{
			throw std::invalid_argument("Error parsing json, got unexpected comma(,) which lead to incorrect syntax!");
		}

		while (str[startIndex = Helpers::skipWithespace(str, startIndex)] != '\0')
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
					throw std::invalid_argument("Error parsing json, got an extra closing curly brace(}) without opening which lead to incorrect syntax!");
				break;
			case '[':
				if (quotes == 0)
					parenthasis++;
				break;
			case ']':
				if (quotes == 0)
					parenthasis--;
				if (parenthasis < 0)
					throw std::invalid_argument("Error parsing json, got an extra closing parenthasis(]) without opening which lead to incorrect syntax!");
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