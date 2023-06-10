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

static class JsonParser
{
private:
    static JsonElementBase *parseObject(MyString elementString)
    {
        elementString.trim();

        JsonObject *object = new JsonObject();

        size_t startIndex = 0;

        while ((startIndex = skipWithespace(elementString, startIndex)) < elementString.getLength())
        {
            if (elementString[startIndex] != '"')
            {
                throw std::exception();
            }

            startIndex++;
            size_t endKeyIndex = startIndex; // start key index

            while (elementString[endKeyIndex] != '"' && elementString[endKeyIndex - 1] != '\\')
            {
                endKeyIndex++;
            }

            MyString key = elementString.substr(startIndex, endKeyIndex - startIndex);

            startIndex = endKeyIndex + 1;

            startIndex = skipWithespace(elementString, startIndex);

            if (elementString[startIndex] != ':')
            {
                throw std::exception();
            }

            startIndex++;

            startIndex = skipWithespace(elementString, startIndex);

            size_t startUnknownElementIndex = startIndex;
            size_t endUnknownElementIndex = skipObjectTillComma(elementString, startIndex);

            // TODO: mem leak
            object->pushBack(Pair<MyString, JsonElement>(key, *parseUnknownElement(elementString.substr(startUnknownElementIndex, endUnknownElementIndex - startUnknownElementIndex + 1))));

            // skip comma
            startIndex = endUnknownElementIndex + 2;
        }

        return object;
    }

    static JsonElementBase *parseArray(MyString elementString)
    {
        elementString.trim();

        JsonArray *array = new JsonArray();

        size_t startIndex = 0;

        while (startIndex < elementString.getLength())
        {
            startIndex = skipWithespace(elementString, startIndex);

            size_t startUnknownElementIndex = startIndex;
            size_t endUnknownElementIndex = skipObjectTillComma(elementString, startIndex);

            // TODO: mem leak
            array->pushBack(JsonElement(*parseUnknownElement(elementString.substr(startUnknownElementIndex, endUnknownElementIndex - startUnknownElementIndex + 1))));

            // skip comma
            startIndex = endUnknownElementIndex + 2;
        }

        return array;
    }

    static JsonElementBase *parsePrimitive(MyString elementString)
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
            throw std::exception();
        }
    }

    static JsonElementBase *parseUnknownElement(MyString elementString)
    {
        elementString.trim();
        size_t startIndex = 0;
        int endIndex = elementString.getLength() - 1;

        if (elementString[startIndex] == '{' || elementString[endIndex] == '}')
        {
            if (elementString[startIndex] != '{' || elementString[endIndex] != '}')
            {
                throw std::exception();
            }

            return parseObject(elementString.substr(startIndex + 1, endIndex - startIndex - 1));
        }
        else if (elementString[startIndex] == '[' || elementString[endIndex] == ']')
        {
            if (elementString[startIndex] != '[' || elementString[endIndex] != ']')
            {
                throw std::exception();
            }

            return parseArray(elementString.substr(startIndex + 1, endIndex - startIndex - 1));
        }
        else
        {
            return parsePrimitive(elementString.substr(startIndex, endIndex - startIndex + 1));
        }
    }

public:
    static JsonDocument parseFile(const MyString &filePath)
    {
        std::ifstream ifs(filePath.c_str());

        if (!ifs.is_open())
        {
            throw std::exception();
        }

        MyString documentStr = readFile(ifs);

        JsonElement parsed = parseElement(documentStr);

        return JsonDocument(parsed);
    }

    // in the beginning we dont know what kind of element it is
    static JsonElement parseElement(MyString elementString)
    {
        return JsonElement(parseUnknownElement(elementString));
    }

    static JsonPath parsePath(MyString path)
    {
        JsonPath res;
        List<MyString> split;

        path.trim();

        if (path.getLength() == 0 || path[0] != '$')
        {
            throw std::exception();
        }

        size_t startIndex = 1;
        if (path[startIndex] == '.')
        {
            startIndex++;
        }

        while (path[startIndex] != '\0')
        {
            bool inQuotes = false;
            bool inBlock = false;

            if (path[startIndex] == '.')
            {
                startIndex++;
            }

            // two consequent ..
            if (path[startIndex] == '.')
            {
                throw std::exception();
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
                        res.push(JsonKey(parseUInt(path.substr(startOfKey, endIndex - startOfKey + 1))));
                        break;
                    }
                }
                else
                {
                    if (path[startIndex + 1] == '.' || path[startIndex + 1] == '[')
                    {
                        endIndex = startIndex;
                        startIndex = startIndex + 1;
                        res.push(JsonKey(path.substr(startOfKey, endIndex - startOfKey + 1)));
                        break;
                    }
                    else if (path[startIndex + 1] == '\'' || path[startIndex + 1] == ']')
                    {
                        throw std::exception();
                    }
                }

                startIndex++;
            }
        }

        return res;
    }
};
