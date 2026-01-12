#ifndef  PARSING_TEXT_EXCEPTIONS_HPP
# define PARSING_TEXT_EXCEPTIONS_HPP

# include "TextExceptionBase.hpp"

class TextCommand;



class UnknownCommandName : public TextExceptionBase
{
	public: UnknownCommandName(const TextCommand & cmd);
};
class InvalidCommandArgumentCount : public TextExceptionBase
{
	public: InvalidCommandArgumentCount(const TextCommand & cmd, const char * comparison);
};
class InvalidCommandArgument : public TextExceptionBase
{
	public: InvalidCommandArgument(const TextCommand & cmd, unsigned int idx);
};

#endif