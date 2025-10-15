#ifndef  FILE_MODE_HPP
# define FILE_MODE_HPP

# include <iosfwd>

class FileMode
{
	private:
		const unsigned short & Mode;

	public:
		FileMode(const unsigned short & mode);

	public:
		bool	IsFile() const;
		bool	IsDirectory() const;

	public:
		bool	UserR() const;
		bool	UserW() const;
		bool	UserX() const;
		bool	UserAll() const;

		bool	GroupR() const;
		bool	GroupW() const;
		bool	GroupX() const;
		bool	GroupAll() const;

		bool	OtherR() const;
		bool	OtherW() const;
		bool	OtherX() const;
		bool	OtherAll() const;

		bool	AllR() const;
		bool	AllW() const;
		bool	AllX() const;
		bool	AllAll() const;
};

std::ostream & operator << (std::ostream & s, const FileMode & val);

#endif
