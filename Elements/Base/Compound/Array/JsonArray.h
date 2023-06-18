#pragma once
#include "../../../JsonElement.h"
#include "../CompoundJsonElement.hpp"

class JsonArray : public CompoundJsonElement<JsonElement>
{
public:
	JsonArray();
	virtual void print(std::ostream& o, size_t inset = 0) const override;
	void insertAt(const JsonElement& element, size_t index);
	void removeAt(size_t index);
	void pushBack(const JsonElement& element);
	virtual JsonElementBase* clone() const override;
};