#pragma once
#include <iostream>

#include "./Command.h"

class UnknownCommand : public Command
{
	MyString msg;
public:
	UnknownCommand(const MyString& msg = "") : msg(msg)
	{

	}

	void execute(std::ostream& os) const override
	{
		os << "Unknown command. " + msg + " Type help for more info." << std::endl;
	}
};