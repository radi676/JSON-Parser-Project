#pragma once
#include "../JsonElementBase.h"

template <typename T>
class PrimitiveJsonElement : public JsonElementBase
{
protected:
	T data;

public:
	PrimitiveJsonElement(const T& data, const JsonElementBaseType& type);

	virtual T get() const;
	virtual void set(const T& value);
	virtual void print(std::ostream& o, size_t inset = 0) const override;

	virtual JsonElementBase* clone() const = 0;
};


template <typename T>
PrimitiveJsonElement<T>::PrimitiveJsonElement(const T& data, const JsonElementBaseType& type) : JsonElementBase(type), data(data)
{
}

template <typename T>
 T PrimitiveJsonElement<T>::get() const
{
	return data;
}

template <typename T>
 void PrimitiveJsonElement<T>::set(const T& value)
{
	data = value;
}

template <typename T>
void PrimitiveJsonElement<T>::print(std::ostream& o, size_t inset) const
{
	o << data;
}
