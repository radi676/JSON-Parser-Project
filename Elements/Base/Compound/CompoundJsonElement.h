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
	CompoundJsonElement(const JsonElementBaseType& type) : JsonElementBase(type) {}
	template<class PrintFunc>
	void print(std::ostream& o, PrintFunc printSpec, size_t inset = 0) const
	{
		for (int i = 0; i < (int)data.getCount() - 1; i++)
		{
			printSpec(o, data[i], inset);
			o << "," << std::endl;
		}

		if (data.getCount() > 0)
		{
			printSpec(o, data.getLast(), inset);
		}
	}

	size_t getCount()const
	{
		return data.getCount();
	}

	const T& getLast() const
	{
		return data.getLast();
	}

	T& getLast()
	{
		return data.getLast();
	}

	T& operator[](size_t index)
	{
		return data[index];
	}

	const T& operator[](size_t index) const
	{
		return data[index];
	}


	virtual JsonElementBase* clone() const = 0;
};