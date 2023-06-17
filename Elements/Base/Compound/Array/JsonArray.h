#pragma once
#include "../../../JsonElement.h"
#include "../CompoundJsonElement.h"
#include "../../../../Utils/IOutils/Output.h"

class JsonArray : public CompoundJsonElement<JsonElement>
{
public:
	JsonArray() : CompoundJsonElement(JsonElementBaseType::Array) {}
	virtual void print(std::ostream& o, size_t inset = 0) const override
	{
		o << "[" << std::endl;
		//CompoundJsonElement::print(o, inset + 1);
		CompoundJsonElement::print(o, [](std::ostream& o,const JsonElement& p, size_t inset) {
			p.print(o, inset); },
			inset + 1);

		o << std::endl;
		printInset(o, inset);
		o << "]";
	}

	void removeAt(size_t index)
	{
		data.removeAt(index);
	}
	
	void insertAt(const JsonElement& element, size_t index)
	{
		data.insertAt(element, index);
	}

	void pushBack(const JsonElement& element)
	{
		data.pushBack(element);
	}

	virtual JsonElementBase* clone() const override
	{
		return new JsonArray(*this);
	};
};