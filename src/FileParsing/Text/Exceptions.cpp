#include "FileParsing/Text/Exceptions.hpp"
#include "FileParsing/Text/TextCommand.hpp"

#include <sstream>



UnknownCommandName::UnknownCommandName(const TextCommand & cmd)
{
	std::stringstream ss;
	ss << cmd.Name() << ": ";
	ss << "unknown Name";
	ss << '.';
	Text = ss.str();
}



InvalidCommandArgumentCount::InvalidCommandArgumentCount(const TextCommand & cmd, const char * comparison)
{
	std::stringstream ss;
	ss << cmd.Name() << ": ";
	ss << "invalid Argument Count: ";
	ss << cmd.Count();
	ss << " is not ";
	ss << '(' << comparison << ')';
	ss << '.';
	Text = ss.str();
}



InvalidCommandArgument::InvalidCommandArgument(const TextCommand & cmd, unsigned int idx)
{
	std::stringstream ss;
	ss << cmd.Name() << ": ";
	ss << "Invalid Command Argument: ";
	ss << '"' << cmd.ToString(idx) << '"';
	ss << '.';
	Text = ss.str();
}



CommandNotImplemented::CommandNotImplemented(const TextCommand & cmd)
{
	std::stringstream ss;
	ss << cmd.Name() << ": ";
	ss << "not implemented";
	ss << '.';
	Text = ss.str();
}



CommandInvalidState::CommandInvalidState(const TextCommand & cmd, const char * description)
{
	std::stringstream ss;
	ss << cmd.Name() << ": ";
	ss << "invalid State: ";
	ss << description;
	ss << '.';
	Text = ss.str();
}
