#include "./FileUtils.h"


size_t FileUtils::getFileSize(std::ifstream& ifs)
{
	size_t pos = ifs.tellg();

	ifs.seekg(0, std::ios::end);
	size_t res = ifs.tellg();

	ifs.seekg(pos, std::ios::beg);
	return res;
}


MyString FileUtils::readFile(std::ifstream& ifs)
{
	size_t capacity = getFileSize(ifs);
	char* res = new char[capacity];
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
	MyString r = res;
	delete res;
	return r;
}