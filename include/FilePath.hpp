
#ifndef  FILE_PATH_HPP
# define FILE_PATH_HPP

# include <string>
# include <vector>

# include <iosfwd>

/*
	split single string into segments
	string is split by / or \

	does not check if Path points to a valid File
*/

class FilePath
{
	public:
		std::vector<std::string> Segments;

	public:
		FilePath();
		FilePath(std::string path);
		~FilePath();

		FilePath(const FilePath & other);
		void operator = (const FilePath & other);

	public:
		static FilePath Here();
		FilePath Trim() const;

		std::string ToString() const;

	public:
		bool IsAbsolute() const;
		bool IsRelative() const;

		FilePath ToAbsolute() const;
		FilePath ToRelative(const FilePath & root) const;

	public:
		FilePath Parent() const;
		FilePath Child(std::string name) const;
};

std::ostream & operator << (std::ostream & s, const FilePath & val);

#endif
