#include "FileException.hpp"
#include <sstream>



FileException::ExceptionBase::ExceptionBase() :
	Text()
{ }
const char * FileException::ExceptionBase::what() const noexcept
{
	return Text.c_str();
}



FileException::FileProblem::FileProblem(const std::string & file_path)
{
	Text = "FileException: Problem with File '" + file_path + "'.";
}



FileException::FileNotFound::FileNotFound(const std::string & file_path)
{
	Text = "FileException: File '" + file_path + "' not found.";
}



FileException::InvalidPath::InvalidPath(const std::string & path)
{
	Text = "FileException: Invalid Path '" + path + "'.";
}



FileException::InvalidExtension::InvalidExtension(const std::string & extention)
{
	Text = "FileException: Invalid Extension '" + extention + "'.";
}
