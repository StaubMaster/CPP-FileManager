#ifndef  DEBUG_MANAGER_HPP
# define DEBUG_MANAGER_HPP

# include <iosfwd>
# include <fstream>

namespace DebugManager
{
	struct LogChange
	{
		char Data;
		LogChange(char data);
		bool operator==(const LogChange & other) const;
	};

	extern LogChange Tabs;
	extern LogChange TabInc;
	extern LogChange TabDec;

	extern std::ostream * Console;

	void ChangeConsoleToDump();
	void ChangeConsoleToCOut();
};

std::ostream & operator<<(std::ostream & log, DebugManager::LogChange & type);

#endif