#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "FileSystemStat.hpp"
#include <iostream>



int main()
{
	std::cout << '\n';
	{
		DirectoryContext dir("test0");
		FileContext file("test0/test1/test2/test3");
		//if (dir.Exists())
		//{
		//	std::cout << "Delete\n";
		//	dir.Delete();
		//}
		//else
		{
			std::cout << "Create\n";
			file.Create();
		}
	}
	std::cout << '\n';
	{
		FileSystemStat stat;
		std::cout << stat << '\n';
	}
	std::cout << '\n';

	std::cout << "main return\n";
	return 0;
}
