#include "IntegerJsonElement.h"

IntegerJsonElement::IntegerJsonElement(int num) : PrimitiveJsonElement(num, JsonElementBaseType::Integer)
{
}

JsonElementBase* IntegerJsonElement::clone() const
{
	return new IntegerJsonElement(*this);
}
