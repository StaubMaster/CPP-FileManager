#include "DirectoryContext.hpp"
#include <iostream>



int main()
{
	std::cout << '\n';
	{
		DirectoryContext dir;
		dir = DirectoryContext::Here().Child("test0/test1/test2/test3");
		if (dir.Exists())
		{
			dir = DirectoryContext::Here().Child("test0");
			dir.Delete();
		}
		else
		{
			dir.Create();
		}
	}
	std::cout << '\n';

	std::cout << "main return\n";
	return 0;
}
