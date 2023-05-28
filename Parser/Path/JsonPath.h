#pragma once
#include "../../Utils/List/List.hpp"
#include "./JsonKey.h"


class JsonPath
{
	//a list of keys or indexes
	List<JsonKey> path;

public:
	void push(JsonKey key)
	{
		path.pushBack(key);
	}

	const MyString& key(size_t i) const
	{
		if (i >= path.getCount())
		{
			throw std::exception();
		}

		return path[i].key();
	}

	size_t arrayIndex(size_t i) const
	{
		if (i >= path.getCount())
		{
			throw std::exception();
		}

		return path[i].arrayIndex();
	}

	size_t isArray(size_t i) const
	{
		if (i >= path.getCount())
		{
			throw std::exception();
		}

		return path[i].isArray();
	}

	size_t length() const
	{
		return path.getCount();
	}

	const JsonKey& getLast() const
	{
		return path.getLast();
	}

	JsonPath parent() const
	{
		JsonPath parentPath = *this;
		parentPath.path.removeAt(path.getCount() - 1);
		return std::move(parentPath);
	}

	MyString toString() const noexcept
	{
		MyString result;
		for (size_t i = 0; i < path.getCount(); i++)
		{
			if (path[i].isArray())
			{
				// TODO: fix
                //Parse to Integer in Helpers
				result += "NumberHere";
			}
			else
			{
				// TODO: точки
				// ако следващото е арей няма точка
				// и на последното
				result += path[i].key();
			}
		}
		// няма смисъл от копие и живее само в този скоуш
		return std::move(result);
		// ще се муувне на mystring
	}
};