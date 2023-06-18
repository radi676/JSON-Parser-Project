#include "NullJsonElement.h"


NullJsonElement::NullJsonElement() : PrimitiveJsonElement(0, JsonElementBaseType::Null)
{
}

JsonElementBase* NullJsonElement::clone() const
{
	return new NullJsonElement();
}

char NullJsonElement::get() const
{
	throw std::logic_error("Null element");
}

void NullJsonElement::set(const char& value)
{
	throw std::logic_error("Null element");
}

void  NullJsonElement::print(std::ostream& o, size_t inset) const 
{
	o << "null";
}
