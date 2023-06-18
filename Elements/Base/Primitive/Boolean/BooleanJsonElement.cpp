#include "BooleanJsonElement.h"


BooleanJsonElement::BooleanJsonElement(bool b) : PrimitiveJsonElement(b, JsonElementBaseType::Boolean)
{
}

JsonElementBase* BooleanJsonElement::clone() const
{
	return new BooleanJsonElement(*this);
}

void BooleanJsonElement::print(std::ostream& o, size_t inset) const
{
	o << (data ? "true" : "false");
}