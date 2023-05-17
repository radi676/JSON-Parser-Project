#pragma once
#include "../../../KeyedJsonElement.h"
#include "../CompoundJsonElement.h"
#include "../../../../Utils/Output/Output.h"


class JsonObject : public CompoundJsonElement<KeyedJsonElement>
{

public:
    JsonObject() : CompoundJsonElement(JsonElementBaseType::Object) {}
    virtual void print(std::ostream &o, size_t inset = 0) const override
    {
        o << "{" << std::endl;
        CompoundJsonElement::print(o, inset + 1);
        o << std::endl;
        printInset(o, inset);
        o << "}";
    }

    KeyedJsonElement &getByKey(const MyString &key)
    {
        for (size_t i = 0; i < getCount(); i++)
        {
            if (data[i].key() == key)
            {
                return data[i];
            }
        }

       //TODO: exception
    }

    virtual JsonElementBase *clone() const override
    {
        return new JsonObject(*this);
    }
};