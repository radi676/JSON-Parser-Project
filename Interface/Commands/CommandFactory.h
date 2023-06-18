#pragma once

#include "./Command.h"
#include "../../JsonDocument.h"

#include "../../Utils/List/List.hpp"
#include "../../Utils/SharedPtr/SharedPtr.hpp"

class CommandFactory
{
public:
	CommandFactory() = delete;
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;

	static SharedPtr<Command> create(const List<MyString>& arguments, JsonDocument* document);
};
