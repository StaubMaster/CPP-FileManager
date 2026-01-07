#ifndef  FILE_SYSTEM_INFO_HPP
# define FILE_SYSTEM_INFO_HPP

# include "FileSystemStat.hpp"
# include "FilePath.hpp"

# include <string>

class FileSystemInfo : public FileSystemStat
{
	public:		FilePath	Path;
	private:	std::string	_OriginalPath;

	public:
	FileSystemInfo();
	~FileSystemInfo();
	FileSystemInfo(const FileSystemInfo & other);
	FileSystemInfo & operator=(const FileSystemInfo & other);

	public:
	FileSystemInfo(const char * path);
	FileSystemInfo(const std::string & path);
	FileSystemInfo(const FilePath & path);

	public:
	void Refresh();
	bool Exists() const;
	std::string OriginalPath() const;
	std::string Name() const;

	# include <iosfwd>
	public:
	void Log() const;
};

//std::ostream & operator<<(std::ostream & o, const FileSystemInfo & obj);

#endif