#pragma once
#include "../../../JsonElement.h"
#include "../CompoundJsonElement.h"
#include "../../../../Utils/Output/Output.h"

// collection of json elements
class JsonArray : public CompoundJsonElement<JsonElement>
{

public:
    JsonArray() : CompoundJsonElement(JsonElementBaseType::Array) {}
    virtual void print(std::ostream &o, size_t inset = 0) const override
    {
        o << "[" << std::endl;
        CompoundJsonElement::print(o, inset + 1);
        o << std::endl;
        printInset(o, inset);
        o << "]";
    }

    virtual JsonElementBase *clone() const override
    {
        return new JsonArray(*this);
    };
};