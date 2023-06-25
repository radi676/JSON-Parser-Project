#pragma once
#include <iostream>

#include "./Command.h"
#include "../../JsonDocument.h"

class SearchCommand : public Command
{
	JsonDocument *document;
	MyString _key;

public:
	const static MyString NAME;

	SearchCommand(JsonDocument *document, const MyString &key) : document(document), _key(key)
	{
	}

	void execute(std::ostream &os) const override
	{
		try
		{
			//TODO: search result to be json array
			List<JsonElement> result = document->search(_key);
			os << "[" << std::endl;
			for (int i = 1; i < (int)result.getCount(); i++)
			{
				result[i - 1].print(os, 1);
				os << "," << std::endl;
			}

			if (result.getCount() > 0)
			{
				result.getLast().print(os, 1);
				os << std::endl;
			}

			os << "]" << std::endl;
		}
		catch (const std::exception &ex)
		{
			os << "ERROR: " << ex.what() << std::endl;
		}
		catch (...)
		{
			os << "Unexpected error occured!" << std::endl;
		}
	}
};

const MyString SearchCommand::NAME = "search";