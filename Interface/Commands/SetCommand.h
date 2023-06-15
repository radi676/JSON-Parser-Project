#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/Parser.h"

class SetCommand : public Command
{
	JsonDocument* document;
	MyString _path;
	MyString _element;

public:
	SetCommand(std::ostream& os, JsonDocument* document, const MyString& path, const MyString& element) : Command(os), document(document), _path(path), _element(element)
	{

	}

	void execute() const override
	{
		try
		{
			JsonPath path = JsonParser::parsePath(_path);
			JsonElement element = JsonParser::parseElement(_element);
			document->set(path, element);
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