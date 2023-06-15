#pragma once

class Command
{
protected:
	std::ostream& os;
public:
	Command(std::ostream& os) : os(os) {}
	virtual void execute()const = 0;
	virtual ~Command() = default;
};