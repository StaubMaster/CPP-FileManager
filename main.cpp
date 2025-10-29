#include "FileContext.hpp"
#include "Parsing/LineCommand.hpp"
#include "Parsing/StringHelp.hpp"
#include "FilePath.hpp"

struct Test
{
	void TestFunc(const LineCommand & cmd)
	{
		std::cout << "Name: '" << cmd.Name << "'\n";
	}
};

void TestLineCommands()
{
	std::cout << "\n";

	//	Stuff	# comment
	//	Stuff
	//	Stuff	#                    comment

	Test obj;
	LineCommand::Split(FileContext("main.cpp"), obj, &Test::TestFunc);

	std::cout << "\n";
}

void TestRemoveAll()
{
	std::cout << "\n";

	std::string str0 = "#asd|123#|qwe#asd";
	std::string str1 = "asd123qweasd";
	std::string str2 = StringHelp::RemoveFromString(str0, StringHelp::CharPallet("#|"));

	std::cout << "Have  : " << "'" << str0 << "'\n";
	std::cout << "Want  : " << "'" << str1 << "'\n";
	std::cout << "Result: " << "'" << str2 << "'\n";

	std::cout << "\n";
}

void TestRemovePair(std::string have, std::string want, StringHelp::CharPallet pallet0, StringHelp::CharPallet pallet1)
{
	std::cout << "\n";

	std::string result = StringHelp::RemoveFromString(have, pallet0, pallet1);

	std::cout << "Have  : " << "'" << have << "'\n";
	std::cout << "Want  : " << "'" << want << "'\n";
	std::cout << "Result: " << "'" << result << "'\n";

	std::cout << "\n";
}
void TestRemovePair()
{
	std::cout << "\n";

	StringHelp::CharPallet pallet0("<");
	StringHelp::CharPallet pallet1(">");

	TestRemovePair("asd<123>asd<123>asd", "asdasdasd", pallet0, pallet1);
	TestRemovePair("<123>asd<123>", "asd", pallet0, pallet1);
	TestRemovePair("asd<123>asd<123", "asdasd", pallet0, pallet1);
	TestRemovePair("asd", "asd", pallet0, pallet1);

	std::cout << "\n";
}

int main()
{
	//TestLineCommands();
	//TestRemoveAll();
	//TestRemovePair();
	FilePath path("test/test\\test");
	std::cout << path.Segments.size() << "\n";
	return 0;
}
