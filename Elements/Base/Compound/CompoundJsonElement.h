#pragma once

#include "../JsonElementBase.h"
#include "../../../Utils/List/List.hpp"
#include "../../../Utils/Output/Output.h"

template <typename T>
class CompoundJsonElement : public JsonElementBase, public List<T>
{

public:
    CompoundJsonElement(const JsonElementBaseType &type) : JsonElementBase(type) {}
    template <class PrintFunc>
    void print(std::ostream &o, PrintFunc printSpec, size_t inset = 0) const
    {
        for (int i = 0; i < (int)List<T>::count - 1; i++)
        {
            printSpec(o, List<T>::data[i], inset);
            o << "," << std::endl;
        }

        if (List<T>::count > 0)
        {
            printSpec(o, List<T>::data[List<T>::count - 1], inset);
        }
    }

    virtual JsonElementBase *clone() const = 0;
};