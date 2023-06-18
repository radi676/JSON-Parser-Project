#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/JsonElementParser.h"
#include "../../Parser/JsonPathParser.h"

class SetCommand : public Command
{
	JsonDocument* document;
	MyString _path;
	MyString _element;

public:
	const static MyString NAME;

	SetCommand(JsonDocument* document, const MyString& path, const MyString& element) :  document(document), _path(path), _element(element)
	{

	}

	void execute(std::ostream& os) const override
	{
		try
		{
			JsonPath path = JsonPathParser::parsePath(_path);
			JsonElement element = JsonElementParser::parseElement(_element);
			document->set(path, element);
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

const MyString SetCommand::NAME = "set";
