#pragma once

class Command
{
public:
	virtual void execute(std::ostream& os)const = 0;
	virtual ~Command() = default;
};