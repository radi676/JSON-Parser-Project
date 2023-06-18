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
	const static MyString NAME;

	SaveCommand( JsonDocument* document, const MyString& path, const MyString& elementPath = "$") : document(document), _path(path), _element(elementPath)
	{

	}

	void execute(std::ostream& os) const override
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

const MyString SaveCommand::NAME = "save";