#pragma once
#include <iostream>
#include "JsonElementType.h"
#include "./Base/JsonElementBase.h"
#include "../Utils/Output/Output.h"
#include "../Utils/SharedPtr/SharedPtr.hpp"

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

    virtual void print(std::ostream &o, size_t inset = 0, bool shouldInset = true) const
    {
        printInset(o, shouldInset ? inset : 0);
        _value->print(o, inset);
    }

    void setValue(JsonElementBase *ptr)
    {
        _value = SharedPtr<JsonElementBase>(ptr);
    }

    void setValue(const SharedPtr<JsonElementBase> &ptr)
    {
        _value = ptr;
    }

    SharedPtr<JsonElementBase> &value()
    {
        return _value;
    }

    const SharedPtr<JsonElementBase> &value() const
    {
        return _value;
    }
};