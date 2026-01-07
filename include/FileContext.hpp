#ifndef  FILE_CONTEXT_HPP
# define FILE_CONTEXT_HPP

# include "FileSystemInfo.hpp"

# include <string>

class Image;

class DirectoryContext;

class FileContext : public FileSystemInfo
{
	public:
	FileContext();
	~FileContext();
	FileContext(const FileContext & other);
	FileContext & operator=(const FileContext & other);

	public:
	FileContext(const char * path);
	FileContext(const std::string & path);
	FileContext(const FilePath & path);
	DirectoryContext ToDirectory() const;

	public:
	void Create();
	void Delete();

	public:
	DirectoryContext Directory() const;
	std::string DirectoryString() const;
	std::string Extension() const;

	public:
	std::string LoadText() const;
	void SaveText(std::string text) const;

	Image * LoadImage() const;
};

#endif