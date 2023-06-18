#pragma once

#include "../JsonElementBase.h"
#include "../../../Utils/List/List.hpp"
#include "../../../Utils/IOutils/Output.h"

template <typename T>
class CompoundJsonElement : public JsonElementBase
{
protected:
	List<T> data;

public:
	CompoundJsonElement(const JsonElementBaseType& type);

	template<class PrintFunc>
	void print(std::ostream& o, PrintFunc printSpec, size_t inset = 0) const;

	size_t getCount()const;
	const T& getLast() const;
	T& getLast();
	const T& at(size_t index) const;
	T& at(size_t index);
	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	virtual JsonElementBase* clone() const = 0;
};

template <typename T>
CompoundJsonElement<T>::CompoundJsonElement(const JsonElementBaseType& type) : JsonElementBase(type) {}

template <typename T>
template<class PrintFunc>
void CompoundJsonElement<T>::print(std::ostream& o, PrintFunc printSpec, size_t inset) const
{
	for (int i = 1; i < data.getCount(); i++)
	{
		printSpec(o, data[i - 1], inset);
		o << "," << std::endl;
	}

	if (data.getCount() > 0)
	{
		printSpec(o, data.getLast(), inset);
	}
}


template <typename T>
size_t  CompoundJsonElement<T>::getCount()const
{
	return data.getCount();
}

template <typename T>
const T& CompoundJsonElement<T>::getLast() const
{
	return data.getLast();
}

template <typename T>
T& CompoundJsonElement<T>::getLast()
{
	return data.getLast();
}

template <typename T>
const T& CompoundJsonElement<T>::at(size_t index) const
{
	if (index > data.getCount())
	{
		throw std::out_of_range("Index out of range.");
	}

	return data[index];
}

template <typename T>
T& CompoundJsonElement<T>::at(size_t index)
{
	if (index > data.getCount())
	{
		throw std::out_of_range("Index out of range.");
	}

	return data[index];
}

template <typename T>
T& CompoundJsonElement<T>:: operator[](size_t index)
{
	return at(index);
}
template <typename T>
const T& CompoundJsonElement<T>:: operator[](size_t index) const
{
	return at(index);
}
