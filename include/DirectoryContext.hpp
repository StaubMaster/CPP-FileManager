
#ifndef  DIRECTORY_CONTEXT_HPP
# define DIRECTORY_CONTEXT_HPP

# include "FilePath.hpp"
# include "FileInfo.hpp"

# include <string>
# include <exception>
# include <vector>

class FileContext;

class DirectoryContext
{
	public:
	FilePath Path;
	FileInfo Info;

	public:
	DirectoryContext();
	DirectoryContext(const char * path);
	DirectoryContext(FilePath path);

	DirectoryContext(const DirectoryContext & other);
	DirectoryContext & operator =(const DirectoryContext & other);

	static DirectoryContext Here();

	public:
	bool Exists() const;

	bool IsFile() const;
	FileContext ToFile() const;

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
