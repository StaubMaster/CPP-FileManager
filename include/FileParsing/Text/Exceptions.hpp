#ifndef  PARSING_TEXT_EXCEPTIONS_HPP
# define PARSING_TEXT_EXCEPTIONS_HPP

# include "TextExceptionBase.hpp"

class TextCommand;



class UnknownCommandName : public TextExceptionBase // CommandUnknownName
{
	public: UnknownCommandName(const TextCommand & cmd);
};
class InvalidCommandArgumentCount : public TextExceptionBase // CommandInvalidArgumentCount
{
	public: InvalidCommandArgumentCount(const TextCommand & cmd, const char * comparison);
};
class InvalidCommandArgument : public TextExceptionBase // CommandInvalidArgument
{
	public: InvalidCommandArgument(const TextCommand & cmd, unsigned int idx);
};
class CommandNotImplemented : public TextExceptionBase
{
	public: CommandNotImplemented(const TextCommand & cmd);
};
class CommandInvalidState : public TextExceptionBase
{
	public: CommandInvalidState(const TextCommand & cmd, const char * description);
};

#endif