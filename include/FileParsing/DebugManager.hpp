#ifndef  DEBUG_MANAGER_HPP
# define DEBUG_MANAGER_HPP

# include <iosfwd>
# include <fstream>

// different Streams

// Debug
// Info
// Warning
// Error

// Enable / Disable
// put Color
//  Ansi Color vs ColorU4

// Tabs ?
// TabsInc and TabsDec dosent change Log, just have a uint that you can ++ or --
// mave a TabArea Object, ++ when constructed, -- destructed

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