#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "FileSystemStat.hpp"
#include <iostream>

#include <sys/stat.h>
#include "Parsing/uint.hpp"



int main()
{
	std::cout << '\n';
	{
		try
		{
			DirectoryContext dir("test0");
			FileContext file("test0/test1/test2/test3");
			if (dir.Exists())
			{
				std::cout << "Delete\n";
				dir.Delete();
			}
			else
			{
				std::cout << "Create\n";
				file.Create();
			}
		}
		catch (std::exception & ex)
		{
			std::cerr << "exception::what(): " << ex.what() << '\n';
		}
	}
	std::cout << '\n';

	std::cout << "main return\n";
	return 0;
}
