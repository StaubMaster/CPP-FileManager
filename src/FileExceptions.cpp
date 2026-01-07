#include "FileExceptions.hpp"
#include <sstream>
#include <errno.h>
#include <string.h>



TextExceptionBase::TextExceptionBase()
{ }
const char * TextExceptionBase::what() const noexcept
{ return Text.c_str(); }



InvalidPath::InvalidPath(const std::string & path)
{
	Text = "Invalid Path " + path + ".";
}
InvalidExtension::InvalidExtension(const std::string & extention)
{
	Text = "Invalid Extension " + extention + ".";
}



FileProblem::FileProblem(const std::string & path)
{
	std::stringstream ss;
	ss << "Problem with File " << path << ".";
	if (errno != 0)
	{
		ss << " Errno: " << strerror(errno) << ".";
	}
	Text = ss.str();
}
FileNotFound::FileNotFound(const std::string & path)
{
	Text = "File " + path + " not found.";
}
FileIsNotFile::FileIsNotFile(const std::string & path)
{
	Text = "File " + path + " is not a File.";
}



DirectoryProblem::DirectoryProblem(const std::string & path)
{
	std::stringstream ss;
	ss << "Problem with Directory " << path << ".";
	if (errno != 0)
	{
		ss << " Errno: " << strerror(errno) << ".";
	}
	Text = ss.str();
}
DirectoryNotFound::DirectoryNotFound(const std::string & path)
{
	Text = "Directory " + path + " not found.";
}
DirectoryIsNotDirectory::DirectoryIsNotDirectory(const std::string & path)
{
	Text = "Directory " + path + " is not a Directory.";
}
