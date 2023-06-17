#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/JsonPathParser.h"

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
			JsonPath path = JsonPathParser::parsePath(_path);
			document->deleteElement(path);
			os << "Command executed successfully!" << std::endl;
		}
		catch (const std::exception& ex)
		{
			os << "ERROR: " << ex.what() << std::endl;
		}
		catch (...)
		{
			os << "Unexpected error occured!" << std::endl;
		}
	}
};