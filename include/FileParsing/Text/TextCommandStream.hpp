#ifndef  TEXT_COMMAND_STREAM_HPP
# define TEXT_COMMAND_STREAM_HPP

# include "TextCommandArgs.hpp"
# include "LineStream.hpp"

class TextCommandStream
{
	private:
	LineStream _Stream;

	public:
	TextCommandStream(const std::string & text);

	public:
	bool	Continue(TextCommandArgs & cmd);
};

#endif