#include "FileInfo.hpp"
#include "FileExceptions.hpp"
#include "DirectoryInfo.hpp"

#include "Image.hpp"
#include "FileFormat/PNG/PNG.hpp"

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#include <iostream>



FileInfo::FileInfo() :
	FileSystemInfo()
{ }
FileInfo::~FileInfo()
{ }
FileInfo::FileInfo(const FileInfo & other) :
	FileSystemInfo(other)
{ }
FileInfo & FileInfo::operator=(const FileInfo & other)
{
	FileSystemInfo::operator=(other);
	return *this;
}

FileInfo::FileInfo(const char * path) :
	FileSystemInfo(path)
{ }
FileInfo::FileInfo(const std::string & path) :
	FileSystemInfo(path)
{ }
FileInfo::FileInfo(const FilePath & path) :
	FileSystemInfo(path)
{ }

DirectoryInfo FileInfo::ToDirectory() const { return DirectoryInfo(OriginalPath()); }





void FileInfo::Delete()
{
	if (!Exists()) { throw FileNotFound(Path); }
	if (!Mode.IsFile()) { throw FileIsNotFile(Path); }

	//FilePath path = Path.ToAbsolute();
	//std::cout << "Delete File: " << Mode << ' ' << Path << '\n';
	if (unlink(Path.ToString()) != 0)
	{
		throw FileProblem(Path, "unlink");
	}

	Refresh();
	//std::cout << "File: " << Mode << ' ' << Path << '\n';
	//std::cout << "File Info\n" << *this << '\n';
}
void FileInfo::Create()
{
	if (Exists() && !Mode.IsFile()) { throw FileIsNotFile(Path); }

	DirectoryInfo parent = DirectoryInfo(Path.Parent());
	if (!parent.Exists() && !parent.Path.IsNone())
	{
		//std::cout << "needs Parent '" << parent.Path << "'\n";
		parent.Create();
	}

	FileMode mode;
	//FilePath path = Path.ToAbsolute();
	//std::cout << "Create File: " << mode << ' ' << Path << '\n';
	int fd = creat(Path.ToString(), mode.Data);
	if (fd <= -1)
	{
		throw FileProblem(Path, "creat");
	}
	if (close(fd) != 0)
	{
		throw FileProblem(Path, "close");
	}

	mode.AllAll(true);
	if (chmod(Path.ToString(), mode.Data) != 0)
	{
		throw FileProblem(Path, "chmod");
	}

	Refresh();
	//std::cout << "File: " << Mode << ' ' << Path << '\n';
	//std::cout << "File Info\n" << *this << '\n';
}





DirectoryInfo FileInfo::Directory() const { return DirectoryInfo(Path.Parent()); }
std::string FileInfo::DirectoryString() const { return std::string(Path.Parent().ToString()); }
std::string FileInfo::Extension() const
{
	std::string str(Path.Name());
	size_t idx = str.find_last_of('.');
	if (idx != std::string::npos) { return str.substr(idx); }
	return std::string();
}



std::string FileInfo::LoadText() const
{
	if (!Exists()) { throw FileNotFound(Path); }
	if (!Mode.IsFile()) { throw FileIsNotFile(Path); }

	std::ifstream stream(Path.ToString(), std::ios::binary);
	if (!stream.is_open())
	{
		throw FileProblem(Path);
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
/*void FileInfo::SaveText(std::string text) const
{
	(void)text;
}*/



Image FileInfo::LoadImage() const
{
	std::string extension = Extension();
	if (extension == ".png") { return PNG::Load(*this, true); }
	if (extension == ".PNG") { return PNG::Load(*this, true); }
	throw InvalidExtension(extension);
}
