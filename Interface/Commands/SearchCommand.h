#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Parser/Parser.h"

class SearchCommand : public Command
{
	JsonDocument* document;
	MyString _key;

public:
	SearchCommand(std::ostream& os, JsonDocument* document, const MyString& key) : Command(os), document(document), _key(key)
	{

	}

	void execute() const override
	{
		try
		{
			List<JsonElement> result = document->search(_key);
			os << "[" << std::endl;
			for (int i = 0; i < result.getCount() - 1; i++)
			{
				result[i].print(os, 0, 0);
				os << "," << std::endl;
			}

			if (result.getCount() > 0)
			{
				result.getLast().print(os, 0, 0);
				os << std::endl;
			}

			os << "]" << std::endl;
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