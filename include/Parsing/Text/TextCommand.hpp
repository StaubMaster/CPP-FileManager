#ifndef  TEXT_COMMAND_HPP
# define TEXT_COMMAND_HPP

# include <string>
# include <vector>
#include <iosfwd>

class TextCommand
{
	private:
	//std::vector<std::string> Segments;
	unsigned int _Count;
	std::string * _Segments;

	public:
	bool Empty() const;
	std::string Name() const;
	unsigned int Count() const;

	public:
	std::string		ToString(unsigned int idx) const;
	float			ToFloat(unsigned int idx) const;
	unsigned int	ToUInt32(unsigned int idx) const;
	int				ToInt32(unsigned int idx) const;

	public:
	TextCommand();
	~TextCommand();
	TextCommand(const TextCommand & other);
	TextCommand & operator=(const TextCommand & other);

	void Split(const std::string & str);
};

std::ostream & operator<<(std::ostream & o, const TextCommand & obj);

#endif