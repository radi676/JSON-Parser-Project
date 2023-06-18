#pragma once
#include "../PrimitiveJsonElement.hpp"

class DecimalJsonElement : public PrimitiveJsonElement<double>
{

public:
	DecimalJsonElement(double num);
	virtual JsonElementBase* clone() const override;
};