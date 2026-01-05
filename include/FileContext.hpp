
#ifndef  FILE_CONTEXT_HPP
# define FILE_CONTEXT_HPP

# include "FilePath.hpp"
# include "FileInfo.hpp"

# include <string>
# include <exception>

class Image;

class DirectoryContext;

class FileContext
{
	public:
	FilePath Path;
	FileInfo Info;

	public:
	FileContext();
	FileContext(const char * path);
	FileContext(FilePath path);

	FileContext(const FileContext & other);
	FileContext & operator =(const FileContext & other);

	public:
	bool Exists() const;

	bool IsDirectory() const;
	DirectoryContext ToDirectory() const;

	public:
	DirectoryContext Directory() const;
	std::string DirectoryString() const;
	std::string Name() const;
	std::string Extension() const;

	public:
	std::string LoadText() const;
	void SaveText(std::string text) const;

	Image * LoadImagePNG() const;

	private:
	class Exception_FileProblem : public std::exception
	{
		private: std::string Text;
		public: Exception_FileProblem(const std::string & file_path);
		public: const char * what() const noexcept;
	};
	class Exception_FileNotFound : public std::exception
	{
		private: std::string Text;
		public: Exception_FileNotFound(const std::string & file_path);
		public: const char * what() const noexcept;
	};
};

#endif
