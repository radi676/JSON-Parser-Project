#pragma once

#include "../String/MyString.h"
#include <fstream>


size_t getFileSize(std::ifstream& ifs)
{
	size_t pos = ifs.tellg();

	ifs.seekg(0, std::ios::end);
	size_t res = ifs.tellg();

	ifs.seekg(pos, std::ios::beg);
	return res;
}

MyString readFile(std::ifstream& ifs)
{
	size_t capacity = getFileSize(ifs);
	MyString res(capacity + 1);
	size_t i = 0;
	while (true)
	{
		res[i] = ifs.get();

		if (ifs.eof())
		{
			break;
		}

		i++;
	}

	res[i] = '\0';
	res.length = i;
	return std::move(res);
}