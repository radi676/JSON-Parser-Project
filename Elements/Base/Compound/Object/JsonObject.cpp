#include "JsonObject.h"
#include "../../../../Utils/IOutils/Output.h"
#include "../../../../Exceptions/NoKeyFoundException.h"

JsonObject::JsonObject() : CompoundJsonElement(JsonElementBaseType::Object) {}

void JsonObject::print(std::ostream& o, size_t inset) const
{
	o << "{" << std::endl;
	CompoundJsonElement::print(o, [](std::ostream& o, const Pair<MyString, JsonElement>& p, size_t inset)
		{
			Output::printInset(o, inset);
			o << '"' << p.first() << "\" : ";
			p.second().print(o, inset, false); },
		inset + 1);

	o << std::endl;
	Output::printInset(o, inset);
	o << "}";
}

Optional<Pair<MyString, JsonElement>*> JsonObject::getByKey(const MyString& key)
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

bool JsonObject::removeByKey(const MyString& key)
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

bool JsonObject::pushBack(const MyString& key, const JsonElement& value)
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

JsonElementBase* JsonObject::clone() const
{
	return new JsonObject(*this);
}