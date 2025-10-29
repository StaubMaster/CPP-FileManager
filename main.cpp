#include "FileContext.hpp"
#include "Parsing/LineCommand.hpp"

struct Test
{
	void TestFunc(const LineCommand & cmd)
	{
		//std::cout << "Name: '" << cmd.Name << "'\n";
		(void)cmd;
	}
};

int main()
{
	//Test obj;
	//LineCommand::Split(FileContext("main.cpp"), obj, &Test::TestFunc);

	std::string str = "asd|123#|qwe#";
	std::cout << "'" << LineCommand::RemoveCharFromString(str, 2, "#|") << "'\n";

	return 0;
}
