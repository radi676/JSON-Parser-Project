#pragma once
#include "../../../Utils/List/List.h"
#include "../../../Utils/Output/Output.h"

template <typename T>
class CompoundJsonElement : public JsonElementBase, public List<T>
{

public:
    CompoundJsonElement(const JsonElementBaseType &type) : JsonElementBase(type) {}
    virtual void print(std::ostream &o, size_t inset = 0) const override
    {
        for (size_t i = 0; i < List<T>::count - 1; i++)
        {
            List<T>::data[i].print(o, inset);
            o << "," << std::endl;
        }

        List<T>::data[List<T>::count - 1].print(o, inset);
    }

    virtual JsonElementBase *clone() const = 0;
};