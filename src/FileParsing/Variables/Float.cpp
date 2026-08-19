#include "FileParsing/Variables/Float.hpp"



ParsingVariable::Float::~Float()
{ }
ParsingVariable::Float::Float()
	: Name()
	, Value()
{ }
ParsingVariable::Float::Float(std::string name, float value)
	: Name(name)
	, Value(value)
{ }
ParsingVariable::Float::Float(const Float & other)
	: Name(other.Name)
	, Value(other.Value)
{ }
ParsingVariable::Float & ParsingVariable::Float::operator=(const Float & other)
{
	Name = other.Name;
	Value = other.Value;
	return *this;
}





ParsingVariable::FloatMemory::~FloatMemory()
{ }
ParsingVariable::FloatMemory::FloatMemory()
	: Variables()
{ }
ParsingVariable::FloatMemory::FloatMemory(const FloatMemory & other)
	: Variables(other.Variables)
{ }
ParsingVariable::FloatMemory & ParsingVariable::FloatMemory::operator=(const FloatMemory & other)
{
	Variables = other.Variables;
	return *this;
}



ParsingVariable::Float * ParsingVariable::FloatMemory::Find(std::string name)
{
	for (unsigned int i = 0; i < Variables.Count(); i++)
	{
		if (Variables[i].Name == name)
		{
			return &Variables[i];
		}
	}
	return nullptr;
}
const ParsingVariable::Float * ParsingVariable::FloatMemory::Find(std::string name) const
{
	for (unsigned int i = 0; i < Variables.Count(); i++)
	{
		if (Variables[i].Name == name)
		{
			return &Variables[i];
		}
	}
	return nullptr;
}



void ParsingVariable::FloatMemory::Put(std::string name, float value)
{
	Float * var = Find(name);
	if (var != nullptr)
	{
		var -> Value = value;
	}
	else
	{
		Variables.Insert(Float(name, value));
	}
}
float ParsingVariable::FloatMemory::To(std::string str) const
{
	char c = str[0];

	bool s = false;
	s = (c == '+' || c == '-');

	if (s) { c = str[1]; }

	if ((c >= '0' && c <= '9'))
	{
		for (unsigned int i = 0; i < str.length(); i++)
		{
			if (str[i] == ',') { str[i] = '.'; }
		}
		return std::stof(str);
	}

	if (s) { c = str[0]; str.erase(0, 1); }

	const Float * var = Find(str);
	if (var != nullptr)
	{
		float v = var -> Value;
		if (s)
		{
			if (c == '+') { v = +v; }
			if (c == '-') { v = -v; }
		}
		return v;
	}
	return 0.0f; // return NaN ?
}



#include "FileParsing/Text/TextCommandArgs.hpp"
#include "FileParsing/Text/Exceptions.hpp"

// remove TextCommandArgs functions
// implement them in the parsers
void ParsingVariable::FloatMemory::Put(const TextCommandArgs & cmd_args)
{
	if (!(cmd_args.Count() == 2)) { throw TextCommand::InvalidArgumentCount(cmd_args, "n == 2"); }
	Put(cmd_args.ToString(0), cmd_args.ToFloat(1));

	// no Value (n == 1) should remove the Variable
}
float ParsingVariable::FloatMemory::To(const TextCommandArgs & cmd_args, unsigned int idx) const
{
	return To(cmd_args.ToString(idx));
}
