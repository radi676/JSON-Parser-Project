#include "../Utils/String/MyString.h"


//If a union contains a non-static data member with a non-trivial special member function (copy/move constructor, copy/move assignment, or destructor), that function is deleted by default in the union and needs to be defined explicitly by the programmer.
//If a union contains a non-static data member with a non-trivial default constructor, the default constructor of the union is deleted by default unless a variant member of the union has a default member initializer .
class JsonKey
{
	union data
	{
		//key си предефенира конструктори, деструктпор и оператор= , затова трябва да има конструктор и деструктор заради mystring
		MyString key;
		size_t arrayIndex;
		// Needed bcs key is not primitive data type
		data() : key() {}
		~data() {}
	} _data;

	bool _isArray;

	// Needed _data key is not primitive data type
	void copyFrom(const JsonKey& other)
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

public:
	JsonKey() = default;

	JsonKey(const MyString& key)
	{
		setKey(key);
	}

	JsonKey(const char* key)
	{
		setKey(key);
	}

	JsonKey(size_t index)
	{
		setArray(index);
	}

	// Needed _data key is not primitive data type
	JsonKey(const JsonKey& other)
	{
		copyFrom(other);
	}

	JsonKey& operator=(const JsonKey& other)
	{
		copyFrom(other);
		return *this;
	}

	const MyString& key() const
	{
		if (_isArray)
		{
			throw std::exception();
		}
		return _data.key;
	}

	size_t arrayIndex() const
	{
		if (!_isArray)
		{
			throw std::exception();
		}

		return _data.arrayIndex;
	}

	void setArray(size_t index)
	{
		_isArray = true;
		_data.arrayIndex = index;
	}

	void setKey(const MyString& key)
	{
		_isArray = false;
		_data.key = key;
	}

	bool isArray() const
	{
		return _isArray;
	}
};