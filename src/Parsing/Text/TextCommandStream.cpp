#include "Parsing/Text/TextCommandStream.hpp"
#include "Parsing/StringHelp.hpp"
#include <string>

#include <iostream>



TextCommandStream::TextCommandStream(const std::string & text) :
	_Stream(text)
{ }



bool TextCommandStream::Continue(TextCommand & cmd)
{
	std::string line;
	if (_Stream.Continue(line))
	{
		line = StringHelp::RemoveFromString(line, StringHelp::CharPallet("#"), StringHelp::CharPallet("\n"));
		cmd.Split(line);
		return true;
	}
	return false;
}
