#pragma once
#include <iostream>
#include "./Base/JsonElementBase.h"
#include "../Utils/Output/Output.h"
#include "../Utils/SharedPtr/SharedPtr.hpp"

class JsonElement
{
protected:
    SharedPtr<JsonElementBase> _value;

public:
	JsonElement() : JsonElement(nullptr) {}
    
	JsonElement(const JsonElementBase& value) : _value(value.clone()) {}
	JsonElement(const SharedPtr<JsonElementBase>& ptr) : _value(ptr) {}

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