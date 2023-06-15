#pragma once

#include <iostream>
#include "./Commands/CommandFactory.h"
#include "./Commands/HelpCommand.h"

#include "../Utils/IOutils/Input.h"

class Interface
{
public:
	static void run(std::ostream& os, std::istream& is)
	{
		os << "Welcome to Json Parser!" << std::endl;
		os << "Type help to see available commands!" << std::endl;
		HelpCommand(os).execute();


		bool isFileOpened = false;
		MyString currentFile;
		JsonDocument document;
		MyString cmd;
		while (true)
		{
			cmd.getline(is, 1024);
			List<MyString> args = getFields(cmd);

			if (args.getCount() == 1 && args[0] == "exit")
			{
				CommandFactory::freeInstance();
				break;
			}

			if (!isFileOpened && args.getCount() == 2 && args[0] == "open")
			{
				currentFile = args[1];
				try
				{
					document = JsonParser::parseFile(currentFile);
					isFileOpened = true;
					CommandFactory::createInstance(os, &document);
					os << "File opened successfully!" << std::endl;

				}
				catch (std::exception& ex)
				{
					os << ex.what() << std::endl;
				}

				continue;
			}

			if (!isFileOpened)
			{
				os << "File not opened! Please open a file. See help for more info." << std::endl;
				continue;
			}

			if (args.getCount() == 1 && args[0] == "close")
			{
				isFileOpened = false;
				CommandFactory::freeInstance();
				os << "File closed!" << std::endl;
				continue;
			}

			if (args.getCount() >= 1 && args[0] == "save")
			{
				args.insertAt(currentFile, 1);
			}

			if (args.getCount() == 0)
			{
				os << "Type help to see available commands!" << std::endl;
			}

			SharedPtr<Command> command = CommandFactory::getInstance()->create(args);

			command->execute();
		}

	}
};
