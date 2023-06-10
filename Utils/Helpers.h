#pragma once

#include "./String/MyString.h"

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

size_t skipWithespace(const MyString &str, size_t startIndex)
{
    while (str[startIndex] == ' ' || str[startIndex] == '\t' || str[startIndex] == '\n')
    {
        startIndex++;
    }

    return startIndex;
}

// a function that skips all objects till that comma that determines where the next element in an array or an object is
size_t skipObjectTillComma(const MyString &str, int startIndex)
{
    int currlyBraces = 0;
    int parenthasis = 0;
    int quotes = 0;
    while (str[startIndex = skipWithespace(str, startIndex)] != '\0')
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
                throw std::exception();
            break;
        case '[':
            if (quotes == 0)
                parenthasis++;
            break;
        case ']':
            if (quotes == 0)
                parenthasis--;
            if (parenthasis < 0)
                throw std::exception();
            break;
        case '"':
            // escaped quote
            if (str[startIndex - 1] == '\\')
            {
                break;
            }

            //  for every opened '"' should be a closed '"'
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

        // in order to get the ',' we should be sure that quotes, parenthasis and curlyBraces are all closed
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

    // quotes == 0 && parenthasis == 0 && currlyBraces == 0 is not true->exception
    //  TODO: any other case ?
    return startIndex;
}

bool isInteger(MyString elementString)
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
        if (!isDigit(elementString[ind]))
        {
            return false;
        }

        ind++;
    }

    return true;
}

int parseInt(MyString elementString)
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
        if (!isDigit(elementString[ind]))
        {
            throw std::exception();
        }
        result = result * 10 + elementString[ind] - '0';
        ind++;
    }

    return result * negative;
}

bool parseDecimal(MyString elementString)
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
        throw std::exception();
    }

    if (!isDigit(elementString[ind]))
    {
        throw std::exception();
    }

    bool isValidPoint = false;
    double beforeDot = 0;
    double afterDot = 0;

    while (ind < elementString.getLength())
    {
        if (!isDigit(elementString[ind]))
        {
            if (!isValidPoint && elementString[ind] == '.')
            {
                isValidPoint = true;
                ind++;
                continue;
            }
            else
            {
                throw std::exception();
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

double isDecimal(MyString elementString)
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

    if (!isDigit(elementString[ind]))
    {
        return false;
    }

    bool isValidPoint = false;

    while (ind < elementString.getLength())
    {
        if (!isDigit(elementString[ind]))
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

size_t parseUInt(const MyString &str)
{
    int res = parseInt(str);
    if (res < 0)
    {
        throw std::exception();
    }

    return res;
}