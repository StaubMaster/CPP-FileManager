#ifndef  TEXT_COMMAND_FUNC_HPP
# define TEXT_COMMAND_FUNC_HPP

# include <string>
# include "Generics/Function/Pointer.hpp"

class TextCommandArgs;

struct TextCommandFunc
{
	std::string		Name;
	FunctionPointer<const TextCommandArgs &>	Func;



	~TextCommandFunc()
	{ }
	TextCommandFunc(std::string name)
		: Name(name)
		, Func()
	{ }

	template<typename ObjectType> TextCommandFunc(
		std::string name,
		ObjectType * obj,
		void (ObjectType::*func)(const TextCommandArgs &)
	)
		: Name(name)
		, Func(obj, func)
	{ }
};

#endif