#pragma once
#include <iostream>

#include "./Command.h"

#include "../../Utils/String/MyString.h"

class HelpCommand : public Command
{
public:
	const static MyString NAME;

	HelpCommand()
	{

	}

	void execute(std::ostream& os) const override
	{
		os << "IMPORTANT!" << std::endl;
		os << "Any argument containing space(' ') should be bounded by double quotes(\"<argument>\")" << std::endl;
		os << "If the argument contains any quotes characters(\"), it should be escaped(\\\") and the argument has to be surrounded with quotes(\")" << std::endl;
		os << std::endl;
		os << "Json path is a sequence of keys delimitered by period(.)" << std::endl;
		os << "Every valid Json path starts from the root object($)" << std::endl;
		os << "Valid key can be written as plain text or surronded by the following: [' <key> ']" << std::endl;
		os << "Any array index is written as [ <array index> ] with no separating dot needed beforehand." << std::endl;
		os << std::endl;
		os << "Example for valid Json path: $.firstLevel.['second'].array[1].['another space'][2].last" << std::endl;

		os << std::endl;
		os << "Available commands:" << std::endl;
		os << "open <file path> - load a file in the json parser" << std::endl;
		os << "close - close opened file" << std::endl;
		os << "save [<json path>] - save opened file, or a part of it" << std::endl;
		os << "saveas <path> [<json path>] - save opened file(or a part of it) as new file" << std::endl;
		os << "exit - close the editor" << std::endl;
		os << "create <json path> <json element> - create json element in the path specified" << std::endl;
		os << "delete <json path> - delete json element by path specified" << std::endl;
		os << "move <json path from> <json path to> - move json element from a path to another" << std::endl;
		os << "set <json path> <json element> - set a value of specific path to some element" << std::endl;
		os << "search <key> - search in the whole document for a key" << std::endl;
		os << "help - print the current help message" << std::endl;
	}
};