#ifndef  PARSING_COMMAND_HPP
# define PARSING_COMMAND_HPP

# include <string>
# include <exception>

# include <vector>
# include <sstream>

# include <iostream>

# include "Parsing/StringHelp.hpp"
# include "Parsing/ExceptionBase.hpp"
# include "Parsing/CountCheck.hpp"

class FileContext;

class ParsingCommand
{
	private:
		std::vector<std::string> Segments;
	public:
		ParsingCommand(std::string text);

	public:
		std::string Name() const;
		unsigned int Count() const;

		bool CheckCount(const CountCheck & check) const;

	public:
		std::string		ToString(unsigned int idx) const;
		float			ToFloat(unsigned int idx) const;
		unsigned int	ToUInt32(unsigned int idx) const;

	public:
		class ExceptionUnknownName : public ExceptionBase
		{
			public:
				ExceptionUnknownName(const ParsingCommand & cmd);
		};
		class ExceptionInvalidCount : public ExceptionBase
		{
			public:
				ExceptionInvalidCount(const ParsingCommand & cmd, const CountCheck & check);
		};
		class ExceptionInvalidArg : public ExceptionBase
		{
			public:
				ExceptionInvalidArg(const ParsingCommand & cmd, unsigned int idx);
		};

	public:
		struct EnvironmentData
		{
			const FileContext & File;
			EnvironmentData(const FileContext & file);
			virtual void Parse(const ParsingCommand & cmd) = 0;
		};
		static void SplitFileIntoCommands(EnvironmentData & data);
};

std::ostream & operator <<(std::ostream & os, const ParsingCommand & obj);

#endif
