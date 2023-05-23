#pragma once
#include "JsonElement.h"
#include "../Utils/String/MyString.h"
#include "../Utils/Output/Output.h"

class KeyedJsonElement : public JsonElement
{
    // Possible change - a class Pair of keys and values
    MyString _key;

public:
    KeyedJsonElement() : JsonElement(JsonElementType::KeyValueElement, nullptr) {}
    KeyedJsonElement(const MyString &key, const JsonElementBase &value) : JsonElement(JsonElementType::KeyValueElement, value.clone()), _key(key) {}

    virtual void print(std::ostream &o, size_t inset = 0, bool shouldInset = true) const override
    {
        printInset(o, inset);
        o << "\"" << _key << "\" : ";
        _value->print(o, inset);
    }

    MyString &key()
    {
        return _key;
    }

    const MyString &key() const
    {
        return _key;
    }
};