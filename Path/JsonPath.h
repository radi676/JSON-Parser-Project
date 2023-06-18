#pragma once

#include "../Utils/List/List.hpp"
#include "./JsonKey.h"

class JsonPath
{
	List<JsonKey> path;

public:
	void push(JsonKey key);
	const MyString& key(size_t i) const;
	size_t arrayIndex(size_t i) const;
	size_t isArray(size_t i) const;
	size_t length() const;
	const JsonKey& getLast() const;
	JsonPath parent() const;
	MyString toString() const noexcept;
};