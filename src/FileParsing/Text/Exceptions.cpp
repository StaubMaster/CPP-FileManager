#include "FileParsing/Text/Exceptions.hpp"
#include "FileParsing/Text/TextCommand.hpp"

#include <sstream>



UnknownCommandName::UnknownCommandName(const TextCommand & cmd)
{
	std::stringstream ss;
	ss << "Unknown Command Name " << cmd << ".";
	Text = ss.str();
}



InvalidCommandArgumentCount::InvalidCommandArgumentCount(const TextCommand & cmd)
{
	std::stringstream ss;
	ss << "Invalid Command Argument Count " << cmd << ".";
	Text = ss.str();
}
InvalidCommandArgumentCount::InvalidCommandArgumentCount(const TextCommand & cmd, const char * comparison)
{
	std::stringstream ss;
	ss << "Invalid Command Argument Count " << cmd << ". ";
	ss << "Comparison: (" << comparison << ").";
	Text = ss.str();
}
