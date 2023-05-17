#pragma once
#include "../PrimitiveJsonElement.h"
#include "../../../../Utils/String/MyString.h"

class StringJsonElement : public PrimitiveJsonElement<MyString>
{

public:
    StringJsonElement(const MyString &str) : PrimitiveJsonElement(str,JsonElementBaseType::String)
    {
    }

    virtual JsonElementBase *clone() const override
    {
        return new StringJsonElement(*this);
    }

    virtual void print(std::ostream &o, size_t inset = 0) const override
    {
        o << "\"" << data << "\"";
    }
};