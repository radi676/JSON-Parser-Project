#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

class PrintCommand : public Command
{
	JsonDocument *document;

public:
	const static MyString NAME;

	PrintCommand(JsonDocument *document) : document(document)
	{
	}

	void execute(std::ostream &os) const override
	{
		try
		{
			document->print(os);
			os << std::endl;
		}
		catch (const std::exception &ex)
		{
			os << "ERROR: " << ex.what() << std::endl;
		}
		catch (...)
		{
			os << "Unexpected error occured!" << std::endl;
		}
	}
};

const MyString PrintCommand::NAME = "print";