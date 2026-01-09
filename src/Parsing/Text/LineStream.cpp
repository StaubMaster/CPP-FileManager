#include "Parsing/Text/LineStream.hpp"
#include "Parsing/StringHelp.hpp"
#include <string>

#include <iostream>



LineStream::LineStream(const std::string & text) :
	_Stream(text)
{ }



bool LineStream::Continue(std::string & line)
{
	if (_Stream.good())
	{
		std::getline(_Stream, line, '\n');
		line = StringHelp::RemoveFromString(line, StringHelp::CharPallet("\n\r"));
		return true;
	}
	return false;
}
