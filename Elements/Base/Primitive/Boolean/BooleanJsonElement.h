#pragma once
#include "../PrimitiveJsonElement.h"

class BooleanJsonElement : public PrimitiveJsonElement<bool>
{
public:
    BooleanJsonElement(bool b) : PrimitiveJsonElement(b, JsonElementBaseType::Boolean)
    {
    }


    virtual JsonElementBase *clone() const override
    {
        return new BooleanJsonElement(*this);
    }

    virtual void print(std::ostream &o, size_t inset = 0) const override
    {
        o << (data ? "true" : "false");
    }
};