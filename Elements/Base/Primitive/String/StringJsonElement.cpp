#include "./StringJsonElement.h"

StringJsonElement::StringJsonElement(const MyString& str) : PrimitiveJsonElement(str, JsonElementBaseType::String)
{
}

JsonElementBase* StringJsonElement::clone() const
{
	return new StringJsonElement(*this);
}

void StringJsonElement::print(std::ostream& o, size_t inset) const
{
	o << "\"" << data << "\"";
}