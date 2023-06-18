#pragma once
#include <iostream>

class Interface
{

public:
	Interface() = delete;

	static void run(std::ostream& os, std::istream& is);
};
