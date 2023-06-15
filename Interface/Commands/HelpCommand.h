#pragma once
#include <iostream>

#include "./Command.h"

class HelpCommand : public Command
{
public:
	HelpCommand(std::ostream& os) : Command(os)
	{

	}

	void execute() const override
	{
		os << "TODO" << std::endl;
	}
};