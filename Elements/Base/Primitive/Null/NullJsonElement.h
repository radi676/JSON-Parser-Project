#pragma once
#include "../PrimitiveJsonElement.h"

class NullJsonElement : public PrimitiveJsonElement<char>
{
public:
    NullJsonElement() : PrimitiveJsonElement(0,JsonElementBaseType::Null)
    {
    }

    virtual JsonElementBase *clone() const override
    {
        return new NullJsonElement();
    }

    virtual char get() const override
    {
        throw std::logic_error("Null element");
    }

    virtual void set(const char &value) override
    {
        throw std::logic_error("Null element");
    }

    virtual void print(std::ostream &o, size_t inset = 0) const override
    {
        o << "null";
    }
};