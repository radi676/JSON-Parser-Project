#include "DecimalJsonElement.h"


DecimalJsonElement::DecimalJsonElement(double num) : PrimitiveJsonElement(num, JsonElementBaseType::Decimal)
{
}

JsonElementBase* DecimalJsonElement::clone() const
{
	return new DecimalJsonElement(*this);
}
