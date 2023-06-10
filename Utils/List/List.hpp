#pragma once

const size_t RESIZE_FACTOR = 2;
const size_t INITIAL_CAPACITY = 10;

template <typename T>
class List
{
protected:
	T* data;
	size_t count;
	size_t capacity;
	void copyFrom(const List<T>& other);
	void moveFrom(List<T>&& other);
	void free();
	void resize(size_t newCapacity);

public:
	List();
	explicit List(size_t capacity);
	List(const List<T>& other);
	List(List<T>&& other);
	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);
	~List<T>();

	void clear();
	bool contains(const T& element) const;
	size_t getCount() const;

	void pushBack(T&& other);
	void pushBack(const T& other);
	void pushFront(T&& other);
	void pushFront(const T& other);
	void insertAt(T&& other, size_t index);
	void insertAt(const T& other, size_t index);
	bool remove(const T& toRemove);
	bool removeAt(size_t position);

	template <class CheckFunc>
	bool removeFirstWhere(CheckFunc predicate);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T& getLast();
	const T& getLast() const;
};

template <typename T>
void List<T>::moveFrom(List<T>&& other)
{
	this->data = other.data;
	this->capacity = other.capacity;
	this->count = other.count;
	other.data = nullptr;
}

template <typename T>
void List<T>::resize(size_t newCapacity)
{
	capacity = newCapacity;
	T* newArr = new T[capacity];
	for (size_t i = 0; i < count; i++)
	{
		newArr[i] = data[i];
	}

	delete[] data;
	data = newArr;
}

template <typename T>
void List<T>::pushBack(T&& other)
{
	if (count == capacity)
	{
		resize(capacity * RESIZE_FACTOR);
	}
	data[count++] = std::move(other);
}

template <typename T>
void List<T>::pushBack(const T& other)
{
	if (count == capacity)
	{
		resize(capacity * RESIZE_FACTOR);
	}
	data[count++] = other;
}

template <typename T>
void List<T>::pushFront(T&& other)
{
	if (count == capacity)
	{
		resize(capacity * RESIZE_FACTOR);
	}

	for (size_t i = count; i > 0; i--)
	{
		data[i] = data[i - 1];
	}

	data[0] = std::move(other);
	count++;
}

template <typename T>
void List<T>::pushFront(const T& other)
{
	if (count == capacity)
	{
		resize(capacity * RESIZE_FACTOR);
	}

	for (size_t i = count; i > 0; i--)
	{
		data[i] = data[i - 1];
	}

	data[0] = other;
	count++;
}

template <typename T>
void List<T>::insertAt(T&& other, size_t index)
{
	if (index > count)
	{
		throw std::invalid_argument("Index out of range");
	}

	if (count == capacity)
	{
		resize(capacity * RESIZE_FACTOR);
	}

	for (size_t i = count; i > index; i--)
	{
		data[i] = data[i - 1];
	}

	data[index] = std::move(other);
	count++;
}

template <typename T>
void List<T>::insertAt(const T& other, size_t index)
{
	if (index > count)
	{
		throw std::invalid_argument("Index out of range");
	}

	if (count == capacity)
	{
		resize(capacity * RESIZE_FACTOR);
	}

	for (size_t i = count; i > index; i--)
	{
		data[i] = data[i - 1];
	}

	data[index] = other;
	count++;
}

template <typename T>
T& List<T>::operator[](size_t index)
{
	if (index >= count)
	{
		throw std::invalid_argument("Index out of range exception.");
	}

	return data[index];
}

template <typename T>
const T& List<T>::operator[](size_t index) const
{
	if (index >= count)
	{
		throw std::invalid_argument("Index out of range exception.");
	}

	return data[index];
}

template <typename T>
void List<T>::copyFrom(const List& other)
{
	count = other.count;
	capacity = other.capacity;
	data = new T[capacity];
	for (size_t i = 0; i < count; i++)
	{
		data[i] = other.data[i];
	}
}

template <typename T>
void List<T>::free()
{
	delete[] data;
}

template <typename T>
List<T>::List() : List(INITIAL_CAPACITY)
{
}

template <typename T>
List<T>::List(size_t capacity)
{
	count = 0;
	this->capacity = capacity;
	data = new T[this->capacity];
}

template <typename T>
List<T>::List(const List& other)
{
	copyFrom(other);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this != &other)
	{
		copyFrom(other);
		free();
	}

	return *this;
}

template <typename T>
List<T>::~List()
{
	free();
}

template <typename T>
void List<T>::clear()
{
	count = 0;
}

template <typename T>
size_t List<T>::getCount() const
{
	return count;
}

template <typename T>
bool List<T>::remove(const T& element)
{
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] == element)
		{
			return removeAt(i);
		}
	}

	return false;
}

template <typename T>
bool List<T>::removeAt(size_t index)
{
	if (index >= count)
	{
		throw std::out_of_range("Index out of range");
	}

	if (count * RESIZE_FACTOR * RESIZE_FACTOR <= capacity)
	{
		resize(capacity / RESIZE_FACTOR);
	}

	--count;

	for (size_t i = index; i < count; i++)
	{
		data[i] = data[i + 1];
	}

	return true;
}

template <typename T>
template <class CheckFunc>
bool List<T>::removeFirstWhere(CheckFunc predicate)
{
	for (size_t i = 0; i < count; i++)
	{
		if (predicate(data[i]))
		{
			return removeAt(i);
		}
	}

	return false;
}

template <typename T>
bool List<T>::contains(const T& element) const
{
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] == element)
		{
			return true;
		}
	}

	return false;
}

template <typename T>
List<T>::List(List&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
List<T>& List<T>::operator=(List&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

// TODO: check if is ok
template <typename T>
T& List<T>::getLast()
{
	if (count == 0)
	{
		throw std::exception();
	}

	return data[count - 1];
}
template <typename T>
const T& List<T>::getLast() const
{
	if (count == 0)
	{
		throw std::exception();
	}

	return data[count - 1];
}