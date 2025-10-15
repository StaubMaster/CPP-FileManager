
#include "FileContext.hpp"
#include "FileMode.hpp"
#include "DirectoryContext.hpp"

#include "Format/Image.hpp"
#include "Format/PNG/PNG.hpp"

#include <sys/stat.h>
#include <fstream>



FileContext::FileContext() : 
	Path(""),
	Info("")
{ }
FileContext::FileContext(std::string path) :
	Path(path),
	Info(path)
{ }
FileContext::FileContext(FilePath path) :
	Path(path),
	Info(path.ToString())
{ }



FileContext::FileContext(const FileContext & other) :
	Path(other.Path),
	Info(Path.ToString())
{ }
FileContext & FileContext::operator =(const FileContext & other)
{
	Path = other.Path;
	Info = FileInfo(Path.ToString());
	return *this;
}



bool FileContext::Exists() const
{
	return (Info.Valid && Info.Mode.IsFile());
}

bool FileContext::IsDirectory() const
{
	return (Info.Valid && Info.Mode.IsDirectory());
}
DirectoryContext FileContext::ToDirectory() const
{
	return DirectoryContext(Path);
}



std::string FileContext::Directory() const
{
	return Path.Parent().ToString();
}
std::string FileContext::Name() const
{
	return Path.Segments[Path.Segments.size() - 1];
}
std::string FileContext::Extension() const
{
	const std::string & str = Path.Segments[Path.Segments.size() - 1];
	size_t idx = str.find_last_of('.');
	if (idx != std::string::npos) { return str.substr(idx); }
	return "";
}



std::string FileContext::LoadText() const
{
	if (!Exists())
	{
		throw Exception_FileNotFound(Path.ToString());
	}

	std::ifstream stream(Path.ToString(), std::ios::binary);
	if (!stream.is_open())
	{
		throw Exception_FileProblem(Path.ToString());
	}

	std::string text;
	char	binary_block[1024];

	stream.read(binary_block, 1024);
	while (!stream.eof())
	{
		text += std::string(binary_block, 1024);
		stream.read(binary_block, 1024);
	}
	text += std::string(binary_block, stream.gcount());

	return (text);
}
void FileContext::SaveText(std::string text) const
{
	(void)text;
}



Image * FileContext::LoadImagePNG() const
{
	return PNG::Load(*this, true);
}





FileContext::Exception_FileProblem::Exception_FileProblem(const std::string & file_path)
{
	Text = "FileContext: Problem with File '" + file_path + "'.";
}
const char * FileContext::Exception_FileProblem::what() const noexcept
{
	return Text.c_str();
}



FileContext::Exception_FileNotFound::Exception_FileNotFound(const std::string & file_path)
{
	Text = "FileContext: File '" + file_path + "' not found.";
}
const char * FileContext::Exception_FileNotFound::what() const noexcept
{
	return Text.c_str();
}
