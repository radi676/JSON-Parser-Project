#pragma once

#include <iostream>
#include "./Commands/CommandFactory.h"
#include "./Commands/HelpCommand.h"

#include "../Utils/IOutils/Input.h"

class Interface
{

public:
	Interface() = delete;

	static void run(std::ostream& os, std::istream& is)
	{
		os << "Welcome to Json Parser!" << std::endl;
		os << std::endl;
		HelpCommand().execute(os);
		os << std::endl;
		os << "Open a file with 'open <filePath>'" << std::endl;
		os << "Type help to see available commands!" << std::endl;

		bool isFileOpened = false;
		MyString currentFile;
		JsonDocument document;
		MyString cmd;
		while (true)
		{
			os << "> ";
			cmd.getline(is, 1024);
			List<MyString> args = getFields(cmd);

			if (args.getCount() == 0)
			{
				os << "Type help to see available commands!" << std::endl;
				continue;
			}

			if (args[0] == "exit")
			{
				break;
			}

			if (args[0] == "help")
			{
				HelpCommand().execute(os);
				continue;
			}

			if (args[0] == "open")
			{
				if (isFileOpened)
				{
					os << "File already opened!" << std::endl;
					continue;
				}

				if (args.getCount() == 2)
				{
					currentFile = args[1];
					try
					{
						document = JsonElementParser::parseFile(currentFile);
						isFileOpened = true;
						os << "File opened successfully!" << std::endl;
					}
					catch (std::exception& ex)
					{
						os << ex.what() << std::endl;
					}
				}
				else
				{
					os << "Invalid number of arguments!" << std::endl;
				}

				continue;
			}

			if (!isFileOpened)
			{
				os << "File not opened! Please open a file. See help for more info." << std::endl;
				continue;
			}

			if (args[0] == "close")
			{
				isFileOpened = false;
				os << "File closed!" << std::endl;
				continue;
			}

			if (args[0] == "save")
			{
				args.insertAt(currentFile, 1);
			}

			SharedPtr<Command> command = CommandFactory::create(args, &document);

			command->execute(os);
		}

	}
};
