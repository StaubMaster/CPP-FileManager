#include "DirectoryContext.hpp"
#include <iostream>



int main()
{
	std::cout << '\n';
	{
		DirectoryContext dir = DirectoryContext::Here();
		dir = dir.Child("test0");
		std::cout << dir.Path << '\n';
		if (dir.Exists())
		{ dir.Delete(); }
		else
		{ dir.Create(); }
	}
	std::cout << '\n';

	std::cout << "main return\n";
	return 0;
}
