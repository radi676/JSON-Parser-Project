#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/Parser.h"

class MoveCommand : public Command
{
	JsonDocument* document;
	MyString _fromPath;
	MyString _toPath;

public:
	MoveCommand(std::ostream& os, JsonDocument* document, const MyString& fromPath, const MyString& toPath) : Command(os), document(document), _fromPath(fromPath), _toPath(toPath)
	{

	}

	void execute() const override
	{
		try
		{
			JsonPath from = JsonParser::parsePath(_fromPath);
			JsonPath to = JsonParser::parsePath(_toPath);
			document->move(from, to);
		}
		//TODO: add specific errors
		catch (const std::exception& ex)
		{
			os << "Unexpected error occurred: " << ex.what() << std::endl;
		}
		catch (...)
		{
			throw;
		}
	}
};