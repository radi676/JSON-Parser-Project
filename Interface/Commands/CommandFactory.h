#pragma once
#include "./Command.h"
#include "./PrintCommand.h"
#include "./CreateCommand.h"
#include "./SetCommand.h"
#include "./DeleteCommand.h"
#include "./MoveCommand.h"
#include "./SearchCommand.h"
#include "./SaveCommand.h"
#include "../../Utils/List/List.hpp"
#include "../../Utils/String/MyString.h"

#include "../../Utils/SharedPtr/SharedPtr.hpp"

#include "../../JsonDocument.h"

#include "./UnknownCommand.h"


class CommandFactory
{
public:
	CommandFactory() = delete;
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;

public:
	static SharedPtr<Command> create(const List<MyString>& arguments, JsonDocument* document)
	{
		MyString cmd = arguments[0];
		List<MyString> args = arguments;
		args.removeAt(0);

		if (cmd == PrintCommand::NAME)
		{
			return new PrintCommand(document);
		}
		else if (cmd == SearchCommand::NAME)
		{
			if (args.getCount() != 1)
			{
				return new UnknownCommand("Invalid arguments count!");
			}

			return new SearchCommand(document, args[0]);
		}
		else if (cmd == SetCommand::NAME)
		{
			if (args.getCount() != 2)
			{
				return new UnknownCommand("Invalid arguments count!");
			}

			return new SetCommand(document, args[0], args[1]);
		}
		else if (cmd == CreateCommand::NAME)
		{
			if (args.getCount() != 2)
			{
				return new UnknownCommand("Invalid arguments count!");
			}

			return new CreateCommand(document, args[0], args[1]);
		}
		else if (cmd == DeleteCommand::NAME)
		{
			if (args.getCount() != 1)
			{
				return new UnknownCommand("Invalid arguments count!");
			}

			return new DeleteCommand(document, args[0]);
		}
		else if (cmd == MoveCommand::NAME)
		{
			if (args.getCount() != 2)
			{
				return new UnknownCommand("Invalid arguments count!");
			}

			return new MoveCommand(document, args[0], args[1]);
		}
		else if (cmd == SaveCommand::NAME || cmd == "saveas")
		{
			if (args.getCount() == 0 || args.getCount() > 2)
			{
				return new UnknownCommand("Invalid arguments count!");
			}

			if (args.getCount() == 2)
			{
				return new SaveCommand(document, args[0], args[1]);
			}

			return new SaveCommand(document, args[0]);
		}

		return new UnknownCommand();

	}
};
