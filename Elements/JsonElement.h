#pragma once
#include <iostream>
#include "JsonElementType.h"
#include "./Base/JsonElementBase.h"
#include "../Utils/Output/Output.h"

// TODO:Big 4
class JsonElement
{
protected:
    JsonElementType type;
    JsonElementBase *_value;

    JsonElement(JsonElementType type, JsonElementBase *value) : type(type), _value(value) {}

public:
    JsonElement() : JsonElement(JsonElementType::ValueElement, nullptr) {}
    JsonElement(const JsonElementBase &value) : JsonElement(JsonElementType::ValueElement, value.clone()) {}

    virtual void print(std::ostream &o, size_t inset = 0, bool shouldInset = true) const
    {
        printInset(o, shouldInset ? inset : 0);
        _value->print(o, inset);
    }

    JsonElementType getType() const
    {
        return type;
    }

    JsonElementBase *&value()
    {
        return _value;
    }

    const JsonElementBase *value() const
    {
        return _value;
    }
};