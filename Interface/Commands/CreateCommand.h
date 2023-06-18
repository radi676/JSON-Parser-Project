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

	const static MyString NAME;

	CreateCommand(JsonDocument* document, const MyString& path, const MyString& element) : document(document), _path(path), _element(element)
	{

	}

	void execute(std::ostream& os) const override
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

const MyString CreateCommand::NAME = "create";