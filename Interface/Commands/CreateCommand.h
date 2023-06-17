#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/JsonPathParser.h"
#include "../../Parser/JsonElementParser.h"

class CreateCommand : public Command
{
	JsonDocument* document;
	MyString _path;
	MyString _element;

public:
	CreateCommand(std::ostream& os, JsonDocument* document, const MyString& path, const MyString& element) : Command(os), document(document), _path(path), _element(element)
	{

	}

	void execute() const override
	{
		try
		{
			JsonPath path = JsonPathParser::parsePath(_path);
			JsonElement element = JsonElementParser::parseElement(_element);
			document->create(path, element);
			os << "Command executed successfully!" << std::endl;
		}
		catch (const std::exception& ex)
		{
			os << "ERROR: " << ex.what() << std::endl;
		}
		catch (...)
		{
			os << "Unexpected error occured!"<<std::endl;
		}
	}
};