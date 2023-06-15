#pragma once
#include <iostream>

void printMenu(std::ostream& os)
{
	os << "Any argument containing space(' ') should be bounded by double quotes(\"<argument>\")" << std::endl;
	os << "If the argument contains any quotes characters(\"), it should be escaped(\\\")" << std::endl;
	os << std::endl;
	os << "Json path is a sequence of keys delimitered by period(.)" << std::endl;
	os << "Every valid Json path starts from the root object($)" << std::endl;
	os << "Valid key can be written as plain text or surronded by the following: [' <key> ']" << std::endl;
	os << "Any array index is written is [ <array index> ] with no separating dot beforehand." << std::endl;
	os << std::endl;
	os << "Example for valid Json path: $.firstLevel.['second'].array[1].['another'][2].last" << std::endl;
}