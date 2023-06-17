#pragma once
#include "../CompoundJsonElement.h"
#include "../../../JsonElement.h"
#include "../../../../Utils/IOutils/Output.h"
#include "../../../../Exceptions/NoKeyFoundException.h"
#include "../../../../Utils/Optional/Optional.hpp"
#include "../../../../Utils/Pair/Pair.hpp"

class JsonObject : public CompoundJsonElement<Pair<MyString, JsonElement>>
{

public:
	JsonObject() : CompoundJsonElement(JsonElementBaseType::Object) {}
	virtual void print(std::ostream& o, size_t inset = 0) const override
	{
		o << "{" << std::endl;
		CompoundJsonElement::print(o, [](std::ostream& o, const Pair<MyString, JsonElement>& p, size_t inset)
			{
				printInset(o, inset);
				o << '"' << p.first() << "\" : ";
				p.second().print(o, inset, false); },
			inset + 1);

		o << std::endl;
		printInset(o, inset);
		o << "}";
	}

	Optional<Pair<MyString, JsonElement>*> getByKey(const MyString& key)
	{
		for (size_t i = 0; i < data.getCount(); i++)
		{
			if (data[i].first() == key)
			{
				return &data[i];
			}
		}

		return Optional<Pair<MyString, JsonElement>*>::empty();
	}

	bool removeByKey(const MyString& key)
	{
		for (size_t i = 0; i < data.getCount(); i++)
		{
			if (data[i].first() == key)
			{
				data.removeAt(i);
				return true;
			}
		}

		return false;
	}

	bool pushBack(const MyString& key, const JsonElement& value)
	{
		for (size_t i = 0; i < data.getCount(); i++)
		{
			if (data[i].first() == key)
			{
				return false;
			}
		}

		data.pushBack({ key, value });
		return true;
	}

	virtual JsonElementBase* clone() const override
	{
		return new JsonObject(*this);
	}
};