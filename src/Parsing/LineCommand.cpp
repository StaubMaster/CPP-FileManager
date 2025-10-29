#include "Parsing/LineCommand.hpp"



LineCommand::LineCommand(std::string text)
{
	std::vector<std::string> segments;
	{
		std::stringstream stream(text);
		std::string segment;
		while (std::getline(stream, segment, ' '))
		{
			segments.push_back(segment);
		}
	}

	if (segments.size() != 0)
	{
		Name = segments[0];
	}
	for (size_t i = 1; i < segments.size(); i++)
	{
		Args.push_back(segments[i]);
	}
	Count = Args.size();
}



size_t LineCommand::FindFirstOf(const std::string & str, size_t idx, unsigned int count, const char chars[])
{
	for (size_t i = idx; i < str.length(); i++)
	{
		const char & c = str[i];
		for (unsigned int j = 0; j < count; j++)
		{
			if (chars[j] == c)
			{
				return i;
			}
		}
	}
	return std::string::npos;
}
std::string LineCommand::RemoveCharFromString(const std::string & str, unsigned int count, const char chars[])
{
	std::string s = "";

	size_t i0 = 0;
	size_t i1 = FindFirstOf(str, i0, count, chars);
	while (i1 != std::string::npos)
	{
		s += str.substr(i0, (i1 - i0));
		i0 = i1 + 1;
		i1 = FindFirstOf(str, i0, count, chars);
	}
	s += str.substr(i0);

	return s;
}
