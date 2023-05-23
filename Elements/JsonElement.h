#pragma once
#include <iostream>
#include "JsonElementType.h"
#include "./Base/JsonElementBase.h"
#include "../Utils/Output/Output.h"
#include "../Utils/SharedPtr/SharedPtr.hpp"

// TODO:Big 4
class JsonElement
{
protected:
    JsonElementType type;
    // sharedPtr<JsonElementBase> is a pointer to JsonElementBase whether a string, an integer, a decimal, Integer, Boolean, Null, object, array
    SharedPtr<JsonElementBase> _value;
    JsonElement(JsonElementType type, JsonElementBase *value) : type(type), _value(value) {}

public:
    JsonElement() : JsonElement(JsonElementType::ValueElement, nullptr) {}
    JsonElement(const JsonElementBase &value) : JsonElement(JsonElementType::ValueElement, value.clone()) {}

    // it can't be keyed value element
    
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
        return _value.ptr();
    }

    const JsonElementBase *value() const
    {
        return _value.ptr();
    }
};