#ifndef  PARSING_VARIABLE_FLOAT_HPP
# define PARSING_VARIABLE_FLOAT_HPP

# include <string>

# include "Miscellaneous/Container/Binary.hpp"

class TextCommand;

namespace ParsingVariable
{
	struct Float
	{
		std::string		Name;
		float			Value;

		~Float();
		Float();
		Float(std::string name, float value);
		Float(const Float & other);
		Float & operator=(const Float & other);
	};

	struct FloatMemory
	{
		Container::Binary<Float>		Variables;

		~FloatMemory();
		FloatMemory();
		FloatMemory(const FloatMemory & other);
		FloatMemory & operator=(const FloatMemory & other);

		Float *	Find(std::string name);
		void	Put(std::string name, float value);
		float	To(std::string str);

		void	Put(const TextCommand & cmd);
		float	To(const TextCommand & cmd, unsigned int idx);
	};
};

#endif