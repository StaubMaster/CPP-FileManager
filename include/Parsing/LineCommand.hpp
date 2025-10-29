
#include <string>

#include <vector>
#include <sstream>

#include <iostream>

#include "FileContext.hpp"

class LineCommand
{
	public:
		std::string Name;
		std::vector<std::string> Args;
		unsigned int Count;
	public:
		LineCommand(std::string text);



	public:
		static size_t FindFirstOf(const std::string & str, size_t idx, unsigned int count, const char chars[]);
		static std::string RemoveCharFromString(const std::string & str, unsigned int count, const char chars[]);
	public:
template <typename ObjectType>
static void Split(const FileContext & file, ObjectType & object, void (ObjectType::*func)(const LineCommand &))
{
	std::stringstream stream(file.LoadText());
	std::string segment;
	while (std::getline(stream, segment, '\r'))
	{
		(object.*func)(LineCommand(RemoveCharFromString(segment, 2, "\n\r")));
	}
}



};
