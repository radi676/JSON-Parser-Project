#pragma once
#include "../PrimitiveJsonElement.hpp"

class NullJsonElement : public PrimitiveJsonElement<char>
{
public:
	NullJsonElement();
	virtual JsonElementBase* clone() const override;
	virtual char get() const override;
	virtual void set(const char& value) override;
	virtual void print(std::ostream& o, size_t inset = 0) const override;
};