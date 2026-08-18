#ifndef  PARSING_TEXT_EXCEPTIONS_HPP
# define PARSING_TEXT_EXCEPTIONS_HPP

# include "TextExceptionBase.hpp"

class TextCommandArgs;

namespace TextCommand
{
class Fatal : public TextExceptionBase
{
	public: Fatal(const TextCommandArgs & cmd_args);
	public: Fatal(const TextCommandArgs & cmd_args, const char * description);
};
class Unknown : public TextExceptionBase
{
	public: Unknown(const TextCommandArgs & cmd_args);
};
class NotImplemented : public TextExceptionBase
{
	public: NotImplemented(const TextCommandArgs & cmd_args);
};
class InvalidArgumentCount : public TextExceptionBase
{
	public: InvalidArgumentCount(const TextCommandArgs & cmd_args, const char * comparison);
};
class InvalidArgument : public TextExceptionBase
{
	public: InvalidArgument(const TextCommandArgs & cmd_args, unsigned int idx);
	public: InvalidArgument(const TextCommandArgs & cmd_args, unsigned int idx, const char * description);
};
class InvalidState : public TextExceptionBase
{
	public: InvalidState(const TextCommandArgs & cmd_args, const char * description);
};
};

#endif