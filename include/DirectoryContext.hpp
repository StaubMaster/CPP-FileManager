#ifndef  DIRECTORY_CONTEXT_HPP
# define DIRECTORY_CONTEXT_HPP

# include "FileSystemInfo.hpp"

# include <string>
# include <exception>
# include <vector>

class FileContext;

class DirectoryContext : public FileSystemInfo
{
	public:
	DirectoryContext();
	~DirectoryContext();
	DirectoryContext(const DirectoryContext & other);
	DirectoryContext & operator=(const DirectoryContext & other);

	public:
	DirectoryContext(const char * path);
	DirectoryContext(const std::string & path);
	DirectoryContext(const FilePath & path);
	FileContext ToFile() const;

	static DirectoryContext Here();

	public:
	//bool IsEmpty() const;
	void Create();
	void Delete();

	public:
	bool HasParent() const;
	bool HasChild(const char * name) const;
	DirectoryContext Parent() const;
	DirectoryContext Child(const char * name) const;

	std::vector<FilePath> Children() const;
	std::vector<FileContext> Files() const;				//	all Files in this Directory
	std::vector<DirectoryContext> Directorys() const;	//	all Directorys in this Directory

	public:
	bool HasFile(const char * name) const;
	FileContext File(const char * name) const;

	//	move Exceptions into FileExceptions
	private:
	class Exception_DirectoryProblem : public std::exception
	{
		private: std::string Text;
		public: Exception_DirectoryProblem(const std::string & dir_path);
		public: const char * what() const noexcept;
	};
	class Exception_DirectoryNotFound : public std::exception
	{
		private: std::string Text;
		public: Exception_DirectoryNotFound(const std::string & dir_path);
		public: const char * what() const noexcept;
	};

};

#endif