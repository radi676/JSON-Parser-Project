#pragma once

template <typename K, typename V>
class Pair
{
    K fisrt;
    V second;

public:
    Pair() = default;
    Pair(const K &k, const V &v) : first(k), second(v) {}

    K &first()
    {
        return first;
    }

    V &second()
    {
        return second;
    }

    const K &first() const
    {
        return first;
    }

    const V &second() const
    {
        return second;
    }
};