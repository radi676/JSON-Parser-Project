#pragma once
#include "../PrimitiveJsonElement.hpp"

class BooleanJsonElement : public PrimitiveJsonElement<bool>
{
public:
	BooleanJsonElement(bool b);
	virtual JsonElementBase* clone() const override;
	virtual void print(std::ostream& o, size_t inset = 0) const override;
};