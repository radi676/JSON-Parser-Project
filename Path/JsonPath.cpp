#include "./JsonPath.h"
#include "../Utils/Parser/Parser.h"

void JsonPath::push(JsonKey key)
{
	path.pushBack(key);
}

const MyString& JsonPath::key(size_t i) const
{
	if (i >= path.getCount())
	{
		throw std::out_of_range("Index out of range.");
	}

	return path[i].key();
}

size_t JsonPath::arrayIndex(size_t i) const
{
	if (i >= path.getCount())
	{
		throw std::out_of_range("Index out of range.");
	}

	return path[i].arrayIndex();
}

size_t JsonPath::isArray(size_t i) const
{
	if (i >= path.getCount())
	{
		throw std::out_of_range("Index out of range.");
	}

	return path[i].isArray();
}

size_t JsonPath::length() const
{
	return path.getCount();
}

const JsonKey& JsonPath::getLast() const
{
	return path.getLast();
}

JsonPath JsonPath::parent() const
{
	JsonPath parentPath = *this;
	parentPath.path.removeAt(path.getCount() - 1);
	return parentPath;
}

MyString JsonPath::toString() const noexcept
{
	MyString result = "$";
	if (path.getCount() > 0)
	{
		result += ".";
	}

	for (size_t i = 0; i < path.getCount(); i++)
	{
		if (path[i].isArray())
		{
			result += "[" + Parser::parseToString(path[i].arrayIndex()) + "]";
		}
		else
		{
			result += "['" + path[i].key() + "']";
		}

		if (i + 1 < path.getCount() && !path[i + 1].isArray())
		{
			result += ".";
		}
	}

	return result;
}
