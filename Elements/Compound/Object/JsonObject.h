#pragma once
#include "../CompoundJsonElement.h"
#include "../../../JsonElement.h"
#include "../../../../Utils/Output/Output.h"
#include "../../../../Exceptions/NoKeyFoundException.h"
#include "../../../../Utils/Optional/Optional.hpp"
#include "../../../../Utils/Pair/Pair.hpp"

class JsonObject : public CompoundJsonElement<Pair<MyString, JsonElement>>
{

public:
    JsonObject() : CompoundJsonElement(JsonElementBaseType::Object) {}
    virtual void print(std::ostream &o, size_t inset = 0) const override
    {
        o << "{" << std::endl;
        CompoundJsonElement::print(
            o, [](std::ostream &o, Pair<MyString, JsonElement> &p, size_t inset)
            {
			printInset(o, inset);
			o << '"' << p.first() << "\" : ";
			p.second().print(o, inset, false); },
            inset + 1);

        // printInset(o, inset);
        o << std::endl;
        printInset(o, inset);
        o << "}";
    }

    // search by predicate
    template <class CheckFunc>
    Optional<Pair<MyString, JsonElement> *> getBy(CheckFunc check)
    {
        for (size_t i = 0; i < getCount(); i++)
        {
            if (check(data[i]))
            {
                return &data[i];
            }
        }

        return Optional<Pair<MyString, JsonElement> *>::empty();
    }

    Optional<Pair<MyString, JsonElement> *> getByKey(const MyString &key)
    {
        return getBy([key](Pair<MyString, JsonElement> &element)
                     { return element.first() == key; });
    }

    virtual JsonElementBase *clone() const override
    {
        return new JsonObject(*this);
    }
};