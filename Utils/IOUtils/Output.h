#pragma once
#include <iostream>

class Output
{
    static const char INSET_SYMBOL = '\t';

public:
    Output() = delete;
    static void printInset(std::ostream& o, size_t inset);
};

