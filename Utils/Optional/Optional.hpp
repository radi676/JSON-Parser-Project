template <typename T>
class Optional
{
private:
    T *data = nullptr;

    void copyFrom(const Optional<T> &other)
    {
        if (other.data)
            data = new T(*other.data); // copy constr!!
        else
            data = nullptr;
    }

    void free()
    {
        delete data;
    }

public:
    static Optional<T> empty()
    {
        return Optional<T>();
    }

    Optional() = default;

    Optional(const T &value)
    {
        data = new T(value);
    }

    Optional(T &&value)
    {
        data = new T(std::move(value));
    }

    Optional(const Optional<T> &other)
    {
        copyFrom(other);
    }

    Optional(Optional<T> &&other)
    {
        data = other.data;
        other.data = nullptr;
    }

    Optional<T> &operator=(const Optional<T> &other)
    {
        return *this;
    }

    const T &operator*() const
    {
        if (!data)
            throw std::logic_error("Optional is empty!");
        return *data;
    }

    T &operator*()
    {
        if (!data)
            throw std::logic_error("Optional is empty!");
        return *data;
    }

    void setValue(const T &value)
    {
        delete data;
        data = new T(value); // copy constr!
    }

    void setValue(T &&value)
    {
        delete data;
        data = new T(std::move(value)); // move constr!
    }

    void reset()
    {
        delete data;
        data = nullptr;
    }

    operator bool() const
    {
        return data != nullptr;
    }
};