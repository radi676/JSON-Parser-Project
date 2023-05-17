#pragma once
#include "../PrimitiveJsonElement.h"

class IntegerJsonElement : public PrimitiveJsonElement<int>
{
public:
    IntegerJsonElement(int num) : PrimitiveJsonElement(num,JsonElementBaseType::Integer)
    {
    }
    
    virtual JsonElementBase *clone() const override
    {
        return new IntegerJsonElement(*this);
    }
};