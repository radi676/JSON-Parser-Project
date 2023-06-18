#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

class PrintCommand : public Command
{
	JsonDocument* document;
public:
	const static MyString NAME;

	PrintCommand( JsonDocument* document) : document(document)
	{

	}

	void execute(std::ostream& os) const override
	{
		document->print(os);
		os << std::endl;
	}
};

const MyString PrintCommand::NAME = "print";