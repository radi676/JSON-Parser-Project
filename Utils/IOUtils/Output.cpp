#include "./Output.h"

void Output::printInset(std::ostream& o, size_t inset)
{
    for (size_t i = 0; i < inset; i++)
    {
        o << INSET_SYMBOL;
    }
}