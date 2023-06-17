#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/JsonPathParser.h"

class SaveCommand : public Command
{
	JsonDocument* document;
	MyString _path;
	MyString _element;

public:
	SaveCommand(std::ostream& os, JsonDocument* document, const MyString& path, const MyString& elementPath = "$") : Command(os), document(document), _path(path), _element(elementPath)
	{

	}

	void execute() const override
	{
		try
		{
			JsonPath path = JsonPathParser::parsePath(_element);
			document->save(_path, path);
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