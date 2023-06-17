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
	std::ostream& os;
	JsonDocument* document;

	static CommandFactory* instance;
	CommandFactory(std::ostream& os, JsonDocument* document) : os(os), document(document)
	{

	}

public:
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;

	static CommandFactory* createInstance(std::ostream& os, JsonDocument* document);
	static CommandFactory* getInstance();
	static void freeInstance();

public:
	SharedPtr<Command> create(const List<MyString>& arguments)
	{
		MyString cmd = arguments[0];
		List<MyString> args = arguments;
		args.removeAt(0);

		// TODO: enum
		if (cmd == "print")
		{
			return new PrintCommand(os, document);
		}
		else if (cmd == "search")
		{
			if (args.getCount() != 1)
			{
				os << "Invalid arguments count! For more info view help!" << std::endl;
				return new UnknownCommand(os);
			}

			return new SearchCommand(os, document, args[0]);
		}
		else if (cmd == "set")
		{
			if (args.getCount() != 2)
			{
				os << "Invalid arguments count! For more info view help!" << std::endl;
				return new UnknownCommand(os);
			}

			return new SetCommand(os, document, args[0], args[1]);
		}
		else if (cmd == "create")
		{
			if (args.getCount() != 2)
			{
				os << "Invalid arguments count! For more info view help!" << std::endl;
				return new UnknownCommand(os);
			}

			return new CreateCommand(os, document, args[0], args[1]);
		}
		else if (cmd == "delete")
		{
			if (args.getCount() != 1)
			{
				os << "Invalid arguments count! For more info view help!" << std::endl;
				return new UnknownCommand(os);
			}

			return new DeleteCommand(os, document, args[0]);
		}
		else if (cmd == "move")
		{
			if (args.getCount() != 2)
			{
				os << "Invalid arguments count! For more info view help!" << std::endl;
				return new UnknownCommand(os);
			}

			return new MoveCommand(os, document, args[0], args[1]);
		}
		else if (cmd == "save" || cmd == "saveas")
		{
			if (args.getCount() == 0 || args.getCount() > 2)
			{
				os << "Invalid arguments count! For more info view help!" << std::endl;
				return new UnknownCommand(os);
			}

			if (args.getCount() == 2)
			{
				return new SaveCommand(os, document, args[0], args[1]);
			}

			return new SaveCommand(os, document, args[0]);
		}

		return new UnknownCommand(os);

	}
};

CommandFactory* CommandFactory::getInstance() {
	if (instance == nullptr) {
		throw std::exception();
	}

	return instance;
}

CommandFactory* CommandFactory::createInstance(std::ostream& os, JsonDocument* document)
{
	if (instance != nullptr)
	{
		throw std::exception();
	}

	instance = new CommandFactory(os, document);
}


void CommandFactory::freeInstance()
{
	delete instance;
	instance = nullptr;
}

CommandFactory* CommandFactory::instance = nullptr;
