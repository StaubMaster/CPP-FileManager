#include "Parsing/Text/LineStream.hpp"
#include "FileContext.hpp"

#include <iostream>

int main()
{
	std::cout << '\n';
	{
		FileContext file("mainLines.cpp");
		LineStream stream(file.LoadText());
		std::string line;
		while (stream.Continue(line))
		{
			std::cout << '<';
			for (unsigned int i = 0; i < line.size(); i++)
			{
				char & c = line[i];
				if (c >= 0 && c < ' ')
				{
					std::cout << '\\';
					if (c == '\0') { std::cout << '0'; }
					else if (c == '\n') { std::cout << 'n'; }
					else if (c == '\r') { std::cout << 'r'; }
					else if (c == '\t') { std::cout << 't'; }
					else { std::cout << ((int)c); }
				}
				else { std::cout << c; }
			}
			std::cout << '>';
			std::cout << '\n';
		}
	}
	std::cout << '\n';
	return 0;
}
