#pragma once
#include "./JsonArray.h"
#include "../../../../Utils/IOutils/Output.h"


JsonArray::JsonArray() : CompoundJsonElement(JsonElementBaseType::Array) {}

void JsonArray::print(std::ostream& o, size_t inset) const
{
	o << "[" << std::endl;
	CompoundJsonElement::print(o, [](std::ostream& o, const JsonElement& p, size_t inset) {
		p.print(o, inset); },
		inset + 1);

	o << std::endl;
	Output::printInset(o, inset);
	o << "]";
}

void JsonArray::removeAt(size_t index)
{
	data.removeAt(index);
}

void JsonArray::insertAt(const JsonElement& element, size_t index)
{
	data.insertAt(element, index);
}

void JsonArray::pushBack(const JsonElement& element)
{
	data.pushBack(element);
}

JsonElementBase* JsonArray::clone() const
{
	return new JsonArray(*this);
}
