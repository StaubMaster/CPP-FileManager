#include "FileParsing/Text/TextCommand.hpp"

#include <iostream>



std::string TextCommand::Name() const
{
	if (_Count == 0) { return ""; }
	return _Segments[0];
}
unsigned int TextCommand::Count() const
{
	if (_Count == 0) { return 0; }
	return _Count - 1;
}



std::string		TextCommand::ToString(unsigned int idx) const
{
	if (idx >= _Count - 1) { return ""; }
	return _Segments[idx + 1];
}
float			TextCommand::ToFloat(unsigned int idx) const
{
	if (idx >= _Count - 1) { return 0.0f; }
	std::string str = _Segments[idx + 1];
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == ',') { str[i] = '.'; }
	}
	return std::stof(str);
}
unsigned int	TextCommand::ToUInt32(unsigned int idx) const
{
	if (idx >= _Count - 1) { return 0; }
	return std::stoul(_Segments[idx + 1]);
}
int				TextCommand::ToInt32(unsigned int idx) const
{
	if (idx >= _Count - 1) { return 0; }
	return std::stoi(_Segments[idx + 1]);
}



TextCommand::TextCommand() :
	_Count(0),
	_Segments(0)
{ }
TextCommand::~TextCommand()
{
	delete[] _Segments;
}
TextCommand::TextCommand(const TextCommand & other) :
	_Count(other._Count),
	_Segments(new std::string[_Count])
{
	for (unsigned int i = 0; i < _Count; i++)
	{
		_Segments[i] = other._Segments[i];
	}
}
TextCommand & TextCommand::operator=(const TextCommand & other)
{
	delete[] _Segments;
	_Count = other._Count;
	_Segments = new std::string[_Count];
	for (unsigned int i = 0; i < _Count; i++)
	{
		_Segments[i] = other._Segments[i];
	}
	return *this;
}



static bool IsWhiteSpace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

void TextCommand::Split(const std::string & str)
{
	delete[] _Segments;
	_Count = 0;

	if (str.size() == 0)
	{
		_Segments = 0;
		return;
	}

	//	Count
	{
		if (!IsWhiteSpace(str[0]))
		{
			_Count++;
		}
		for (unsigned int i = 1; i < str.size(); i++)
		{
			if (!IsWhiteSpace(str[i]) && IsWhiteSpace(str[i - 1]))
			{
				_Count++;
			}
		}
	}

	_Segments = new std::string[_Count];

	//	Take
	{
		unsigned int idx = 0;
		unsigned int off;
		unsigned int i = 0;
		for (; i < str.size(); i++)
		{
			if (!IsWhiteSpace(str[i]))
			{
				break;
			}
		}
		off = i;
		for (i++; i < str.size(); i++)
		{
			if (!IsWhiteSpace(str[i]) && IsWhiteSpace(str[i - 1]))
			{
				off = i;
			}
			if (IsWhiteSpace(str[i]) && !IsWhiteSpace(str[i - 1]))
			{
				_Segments[idx] = std::string(str, off, (i - off));
				idx++;
			}
		}
		if (!IsWhiteSpace(str[str.size() - 1]))
		{
			_Segments[idx] = std::string(str, off, (str.size() - off));
			idx++;
		}
	}
}





std::ostream & operator<<(std::ostream & o, const TextCommand & obj)
{
	o << '(';
	o << obj.Name() << ':';
	for (unsigned int i = 0; i < obj.Count(); i++)
	{
		o << ' ' << obj.ToString(i);
	}
	o << ')';
	return o;
}
