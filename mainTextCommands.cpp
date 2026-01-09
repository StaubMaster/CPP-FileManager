#include "Parsing/Text/TextCommandStream.hpp"
#include "FileContext.hpp"

#include <iostream>

int main()
{
	std::cout << '\n';
	{
		FileContext file("commands.txt");
		TextCommandStream stream(file.LoadText());
		TextCommand cmd;
		while (stream.Continue(cmd))
		{
			std::cout << cmd << '\n';
		}
		std::cout << "done\n";
	}
	std::cout << '\n';
	return 0;
}
