#include "FileParsing/Text/Exceptions.hpp"
#include "FileParsing/Text/TextCommandArgs.hpp"

#include <sstream>



TextCommand::Unknown::Unknown(const TextCommandArgs & cmd_args)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "unknown Name";
	ss << '.';
	Text = ss.str();
}



TextCommand::NotImplemented::NotImplemented(const TextCommandArgs & cmd_args)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "not implemented";
	ss << '.';
	Text = ss.str();
}



TextCommand::InvalidArgumentCount::InvalidArgumentCount(const TextCommandArgs & cmd_args, const char * comparison)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "invalid Argument Count: ";
	ss << cmd_args.Count();
	ss << " is not ";
	ss << '(' << comparison << ')';
	ss << '.';
	Text = ss.str();
}



TextCommand::InvalidArgument::InvalidArgument(const TextCommandArgs & cmd_args, unsigned int idx)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "Invalid Command Argument: ";
	ss << '"' << cmd_args.ToString(idx) << '"';
	ss << '.';
	Text = ss.str();
}
TextCommand::InvalidArgument::InvalidArgument(const TextCommandArgs & cmd_args, unsigned int idx,  const char * description)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "Invalid Command Argument: ";
	ss << '"' << cmd_args.ToString(idx) << '"';
	ss << ": ";
	ss << description;
	ss << '.';
	Text = ss.str();
}



TextCommand::InvalidState::InvalidState(const TextCommandArgs & cmd_args, const char * description)
{
	std::stringstream ss;
	ss << cmd_args.Name() << ": ";
	ss << "invalid State: ";
	ss << description;
	ss << '.';
	Text = ss.str();
}
