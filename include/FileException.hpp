#ifndef  FILE_EXCEPTION_HPP
# define FILE_EXCEPTION_HPP

# include <exception>
# include <string>

//	get rid of NameSpace
namespace FileException
{
	class ExceptionBase : public std::exception
	{
		protected: std::string Text;
		public: ExceptionBase();
		public: const char * what() const noexcept;
	};

	/*	PathProblems
			InvalidPath		unused ?
	*/
	/*	File
			Problem				generic problem
			NotFound			dosent exist / isnt a File
			InvalidExtension	something that uses the File dosent like the Extension
	*/
	/*	Directory
			Problem				generic problem
			NotFound			dosent exist / isnt a Directory
	*/

	class FileProblem : public ExceptionBase
	{
		public: FileProblem(const std::string & file_path);
	};
	class FileNotFound : public ExceptionBase
	{
		public: FileNotFound(const std::string & file_path);
	};
	class InvalidPath : public ExceptionBase
	{
		public: InvalidPath(const std::string & path);
	};
	class InvalidExtension : public ExceptionBase
	{
		public: InvalidExtension(const std::string & extention);
	};
};

#endif