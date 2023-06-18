#include "./JsonKey.h"

void JsonKey::copyFrom(const JsonKey& other)
{
	_isArray = other._isArray;
	if (_isArray)
	{
		_data.arrayIndex = other._data.arrayIndex;
	}
	else
	{
		_data.key = other._data.key;
	}
}

JsonKey::JsonKey(const MyString& key)
{
	setKey(key);
}

JsonKey::JsonKey(const char* key)
{
	setKey(key);
}

JsonKey::JsonKey(size_t index)
{
	setArray(index);
}

// Needed _data key is not primitive data type
JsonKey::JsonKey(const JsonKey& other)
{
	copyFrom(other);
}

JsonKey& JsonKey::operator=(const JsonKey& other)
{
	copyFrom(other);
	return *this;
}

const MyString& JsonKey::key() const
{
	if (_isArray)
	{
		throw std::logic_error("Json key is index.");
	}
	return _data.key;
}

size_t JsonKey::arrayIndex() const
{
	if (!_isArray)
	{
		throw std::logic_error("Json key is not index.");
	}

	return _data.arrayIndex;
}

void JsonKey::setArray(size_t index)
{
	_isArray = true;
	_data.arrayIndex = index;
}

void JsonKey::setKey(const MyString& key)
{
	_isArray = false;
	_data.key = key;
}

bool JsonKey::isArray() const
{
	return _isArray;
}