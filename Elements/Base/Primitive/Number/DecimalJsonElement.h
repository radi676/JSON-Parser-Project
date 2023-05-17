#pragma once
#include "../PrimitiveJsonElement.h"

class DecimalJsonElement : public PrimitiveJsonElement<double>
{
public:
    DecimalJsonElement(double num) : PrimitiveJsonElement(num,JsonElementBaseType::Decimal)
    {
    }

    virtual JsonElementBase *clone() const override
    {
        return new DecimalJsonElement(*this);
    }
};