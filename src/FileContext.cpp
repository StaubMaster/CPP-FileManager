#include "FileContext.hpp"
#include "FileExceptions.hpp"
#include "DirectoryContext.hpp"

#include "Format/Image.hpp"
#include "Format/PNG/PNG.hpp"

#include <sys/stat.h>
#include <fstream>
#include <unistd.h>

#include <iostream>



FileContext::FileContext() :
	FileSystemInfo()
{ }
FileContext::~FileContext()
{ }
FileContext::FileContext(const FileContext & other) :
	FileSystemInfo(other)
{ }
FileContext & FileContext::operator=(const FileContext & other)
{
	FileSystemInfo::operator=(other);
	return *this;
}

FileContext::FileContext(const char * path) :
	FileSystemInfo(path)
{ }
FileContext::FileContext(const std::string & path) :
	FileSystemInfo(path)
{ }
FileContext::FileContext(const FilePath & path) :
	FileSystemInfo(path)
{ }

DirectoryContext FileContext::ToDirectory() const { return DirectoryContext(OriginalPath()); }





void FileContext::Delete()
{
	if (!Exists()) { throw FileNotFound(Path.ToString()); }
	if (!Mode.IsFile()) { throw FileIsNotFile(Path.ToString()); }

	std::cout << "Delete File " << Path.ToString() << '\n';
	if (unlink(Path.ToString()) != 0)
	{
		throw FileProblem(Path.ToString());
	}
}
void FileContext::Create()
{
	if (Exists() && !Mode.IsFile()) { throw FileIsNotFile(Path.ToString()); }

	DirectoryContext parent = DirectoryContext(Path.Parent());
	if (!parent.Exists() && !parent.Path.IsNone())
	{
		std::cout << "needs Parent '" << parent.Path.ToString() << "'\n";
		parent.Create();
	}

	std::cout << "Create File " << Path.ToString() << '\n';
	int fd = creat(Path.ToString(), 0);
	if (fd == -1)
	{
		throw FileProblem(Path.ToString());
	}
	close(fd);

	Refresh();
	std::cout << "File Info\n" << *((FileSystemStat*)this);
}





DirectoryContext FileContext::Directory() const { return DirectoryContext(Path.Parent()); }
std::string FileContext::DirectoryString() const { return std::string(Path.Parent().ToString()); }
std::string FileContext::Extension() const
{
	std::string str(Path.Name());
	size_t idx = str.find_last_of('.');
	if (idx != std::string::npos) { return str.substr(idx); }
	return std::string();
}



std::string FileContext::LoadText() const
{
	if (!Exists()) { throw FileNotFound(Path.ToString()); }
	if (!Mode.IsFile()) { throw FileIsNotFile(Path.ToString()); }

	std::ifstream stream(Path.ToString(), std::ios::binary);
	if (!stream.is_open())
	{
		throw FileProblem(Path.ToString());
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
/*void FileContext::SaveText(std::string text) const
{
	(void)text;
}*/



Image * FileContext::LoadImage() const
{
	std::string extension = Extension();
	if (extension == ".png") { return PNG::Load(*this, true); }
	if (extension == ".PNG") { return PNG::Load(*this, true); }
	throw InvalidExtension(extension);
}
