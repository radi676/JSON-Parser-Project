#pragma once
#include "iostream"

const char INSET_SYMBOL = '\t';

void printInset(std::ostream &o, size_t inset)
{
    for (size_t i = 0; i < inset; i++)
    {
        std::cout << INSET_SYMBOL;
    }
}