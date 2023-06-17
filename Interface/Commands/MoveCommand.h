#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/JsonPathParser.h"

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
			JsonPath from = JsonPathParser::parsePath(_fromPath);
			JsonPath to = JsonPathParser::parsePath(_toPath);
			document->move(from, to);
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