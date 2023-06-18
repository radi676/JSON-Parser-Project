#pragma once
#include "../PrimitiveJsonElement.hpp"

class IntegerJsonElement : public PrimitiveJsonElement<int>
{
public:
	IntegerJsonElement(int num);
	virtual JsonElementBase* clone() const override;
};