#pragma once
#include "../JsonElementBase.h"

template <typename T>
class PrimitiveJsonElement : public JsonElementBase
{
protected:
    T data; // whetjer boolean, null, number or string data

public:
    PrimitiveJsonElement(const T &data, const JsonElementBaseType &type) : JsonElementBase(type), data(data)
    {
    }
    virtual T get() const
    {
        return this->data;
    }

    virtual void set(const T &value)
    {
        data = value;
    }

    virtual void print(std::ostream &o, size_t inset = 0) const override
    {
        o << data;
    }

    virtual JsonElementBase *clone() const = 0;
};