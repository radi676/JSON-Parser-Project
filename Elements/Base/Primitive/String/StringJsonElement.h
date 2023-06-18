#pragma once
#include "../PrimitiveJsonElement.hpp"
#include "../../../../Utils/String/MyString.h"

class StringJsonElement : public PrimitiveJsonElement<MyString>
{

public:
    StringJsonElement(const MyString& str);
    virtual JsonElementBase* clone() const override;
    virtual void print(std::ostream& o, size_t inset = 0) const override;
};