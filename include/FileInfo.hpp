#ifndef  FILE_INFO_HPP
# define FILE_INFO_HPP

# include "FileSystemInfo.hpp"

# include <string>

class Image;

class DirectoryInfo;

class FileInfo : public FileSystemInfo
{
	public:
	FileInfo();
	~FileInfo();
	FileInfo(const FileInfo & other);
	FileInfo & operator=(const FileInfo & other);

	public:
	FileInfo(const char * path);
	FileInfo(const std::string & path);
	FileInfo(const FilePath & path);
	DirectoryInfo ToDirectory() const;

	public:
	void Delete();
	void Create();

	public:
	DirectoryInfo Directory() const;
	std::string DirectoryString() const;
	std::string Extension() const;

	public:
	std::string LoadText() const;
	void SaveText(std::string text) const;

	Image LoadImage(bool debug = false) const;
};

#endif