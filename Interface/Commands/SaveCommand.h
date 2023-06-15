#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/Parser.h"

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
			std::ofstream file(_path.c_str());

			if (!file.is_open())
			{
				//TODO:`fix
				os << "ERRORRRRR!!!!!" << std::endl;
				return;
			}

			JsonPath path = JsonParser::parsePath(_element);
			document->save(file, path);
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