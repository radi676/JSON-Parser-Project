#pragma once
#include <iostream>

#include "./Command.h"

class UnknownCommand : public Command
{
public:
	UnknownCommand(std::ostream& os) : Command(os)
	{

	}

	void execute() const override
	{
		os << "Unknown command. Type help for more info." << std::endl;
	}
};