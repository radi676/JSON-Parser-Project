#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/Parser.h"

class DeleteCommand : public Command
{
	JsonDocument* document;
	MyString _path;

public:
	DeleteCommand(std::ostream& os, JsonDocument* document, const MyString& path) : Command(os), document(document), _path(path)
	{

	}

	void execute() const override
	{
		try
		{
			JsonPath path = JsonParser::parsePath(_path);
			document->deleteElement(path);
		}
		//TODO: add specific errors
		catch (const std::exception& ex)
		{
			std::cout << "Unexpected error occurred: " << ex.what() << std::endl;
		}
		catch (...)
		{
			throw;
		}
	}
};