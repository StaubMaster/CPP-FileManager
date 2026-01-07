#ifndef  FILE_EXCEPTIONS_HPP
# define FILE_EXCEPTIONS_HPP

# include <exception>
# include <string>

class TextExceptionBase : public std::exception
{
	protected: std::string Text;
	public: TextExceptionBase();
	public: const char * what() const noexcept;
};



class InvalidPath : public TextExceptionBase
{
	public: InvalidPath(const std::string & path);
};
class InvalidExtension : public TextExceptionBase
{
	public: InvalidExtension(const std::string & extention);
};



class FileProblem : public TextExceptionBase
{
	public: FileProblem(const std::string & path);
};
class FileNotFound : public TextExceptionBase
{
	public: FileNotFound(const std::string & path);
};
class FileIsNotFile : public TextExceptionBase
{
	public: FileIsNotFile(const std::string & path);
};



class DirectoryProblem : public TextExceptionBase
{
	public: DirectoryProblem(const std::string & path);
};
class DirectoryNotFound : public TextExceptionBase
{
	public: DirectoryNotFound(const std::string & path);
};
class DirectoryIsNotDirectory : public TextExceptionBase
{
	public: DirectoryIsNotDirectory(const std::string & path);
};

#endif