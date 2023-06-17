#pragma once

template <typename K, typename V>
class Pair
{
	K k;
	V v;
public:

	Pair() = default;
	Pair(const K& k, const V& v) :k(k), v(v) { }

	K& first()
	{
		return k;
	}

	V& second()
	{
		return v;
	}

	const K& first()const
	{
		return k;
	}

	const V& second()const
	{
		return v;
	}
};