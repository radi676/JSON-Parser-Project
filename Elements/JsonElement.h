#pragma once

#include <iostream>
#include <sstream>

#include "./Base/JsonElementBase.h"

#include "../Utils/IOutils/Output.h"
#include "../Utils/String/MyString.h"
#include "../Utils/SharedPtr/SharedPtr.hpp"

class JsonElement
{
protected:
	SharedPtr<JsonElementBase> _value;

public:
	JsonElement() : JsonElement(nullptr) {}

	JsonElement(const JsonElementBase& value) : _value(value.clone()) {}
	JsonElement(JsonElementBase* ptr) : _value(ptr) {}
	JsonElement(const SharedPtr<JsonElementBase>& ptr) : _value(ptr) {}

	virtual void print(std::ostream& o, size_t inset = 0, bool shouldInset = true) const
	{
		Output::printInset(o, shouldInset ? inset : 0);
		_value->print(o, inset);
	}


	void setValue(JsonElementBase* ptr)
	{
		_value = SharedPtr<JsonElementBase>(ptr);
	}

	void setValue(const JsonElementBase& value)
	{
		_value = value.clone();
	}

	void setValue(const SharedPtr<JsonElementBase>& ptr)
	{
		_value = ptr;
	}

	SharedPtr<JsonElementBase>& value()
	{
		return _value;
	}

	const SharedPtr<JsonElementBase>& value() const
	{
		return _value;
	}

	JsonElementBaseType type() const
	{
		return _value->getType();
	}

	MyString toString() const
	{
		std::stringstream ss;
		print(ss, 0, 0);
		return ss.str().c_str();
	}

	template<typename T>
	T* to()
	{
		return dynamic_cast<T*>(_value.ptr());
	}
};