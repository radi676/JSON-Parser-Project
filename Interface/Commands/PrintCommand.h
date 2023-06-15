#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

class PrintCommand : public Command
{
	JsonDocument* document;
public:
	PrintCommand(std::ostream& os, JsonDocument* document) : Command(os), document(document)
	{

	}

	void execute() const override
	{
		document->print(os);
	}
};