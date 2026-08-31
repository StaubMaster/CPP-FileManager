#ifndef  DIRECTORY_INFO_HPP
# define DIRECTORY_INFO_HPP

# include "FileSystemInfo.hpp"

# include <string>
# include <exception>
# include <vector>

class FileInfo;

// tabs before function names

class DirectoryInfo : public FileSystemInfo
{
	public:
	DirectoryInfo();
	~DirectoryInfo();
	DirectoryInfo(const DirectoryInfo & other);
	DirectoryInfo & operator=(const DirectoryInfo & other);

	public:
	DirectoryInfo(const char * path);
	DirectoryInfo(const std::string & path);
	DirectoryInfo(const FilePath & path);
	FileInfo ToFile() const;

	public:
	static DirectoryInfo Here();

	public:
	bool IsEmpty() const;
	void Delete();
	void Create();
	// CreateRecursive()
	// DeleteRecursive()

	public:
	bool HasParent() const;
	bool HasChild(const char * name) const;
	DirectoryInfo Parent() const;
	DirectoryInfo Child(const char * name) const;
	// make these also use std::string

	public:
	bool HasFile(const char * name) const;
	bool HasDirectory(const char * name) const;
	FileInfo File(const char * name) const;
	DirectoryInfo Directory(const char * name) const;
	// make these also use std::string

	public:
	std::vector<FilePath> Children() const;
	std::vector<FileInfo> Files() const;
	std::vector<DirectoryInfo> Directorys() const;
	// return Container::Array<>
};

#endif