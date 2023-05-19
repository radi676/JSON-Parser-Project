template <typename T>
class SharedPtr
{
	T* data;
	unsigned* pointersCount;

	void free()
	{
		if (*pointersCount == 1)
		{
			delete data;
			delete pointersCount;
		}
		else
			(*pointersCount)--;
	}

	void copyFrom(const SharedPtr<T>& other)
	{
		data = other.data;
		pointersCount = other.pointersCount;
		(*pointersCount)++;
	}

public:
	SharedPtr(T* data)
	{
		this->data = data;
		pointersCount = new unsigned(1);
	}

	SharedPtr(const SharedPtr<T>& other)
	{
		data = other.data;
		pointersCount = other.pointersCount;
		(*pointersCount)++;
	}

	SharedPtr& operator=(const SharedPtr<T>& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}
		return *this;
	}

	const T& operator*() const
	{
		return data;
	}
	
	T& operator*()
	{
		return data;
	}

	~SharedPtr()
	{
		if (*pointersCount == 1)
		{
			delete data;
			delete pointersCount;
		}
		else
			(*pointersCount)--;
	}
};