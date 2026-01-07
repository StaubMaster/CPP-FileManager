#include "DirectoryContext.hpp"
#include "FileContext.hpp"

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <cctype>

#include <iostream>



DirectoryContext::DirectoryContext() :
	FileSystemInfo()
{ }
DirectoryContext::~DirectoryContext()
{ }
DirectoryContext::DirectoryContext(const DirectoryContext & other) :
	FileSystemInfo(other)
{ }
DirectoryContext & DirectoryContext::operator=(const DirectoryContext & other)
{
	FileSystemInfo::operator=(other);
	return *this;
}

DirectoryContext::DirectoryContext(const char * path) :
	FileSystemInfo(path)
{ }
DirectoryContext::DirectoryContext(const std::string & path) :
	FileSystemInfo(path)
{ }
DirectoryContext::DirectoryContext(const FilePath & path) :
	FileSystemInfo(path)
{ }

FileContext DirectoryContext::ToFile() const { return FileContext(OriginalPath()); }



DirectoryContext DirectoryContext::Here() { return DirectoryContext(FilePath::Here()); }



void DirectoryContext::Create()
{
	FileSystemInfo info;
	info.Mode.AllR(true);
	info.Mode.AllW(true);
	info.Log();
	int ret = mkdir(Path.ToString());
	std::cout << "ret " << ret << '\n';
}
void DirectoryContext::Delete()
{
	FileSystemInfo::Log();
	int ret = rmdir(Path.ToString());
	std::cout << "ret " << ret << '\n';
}



bool DirectoryContext::HasParent() const
{
	FileSystemInfo info(Path.Parent().ToString());
	return (info.Exists() && info.Mode.IsDirectory());
}
bool DirectoryContext::HasChild(const char * name) const
{
	FileSystemInfo info(Path.Child(name).ToString());
	return (info.Exists() && info.Mode.IsDirectory());
}
DirectoryContext DirectoryContext::Parent() const
{
	return DirectoryContext(Path.Parent().ToString());
}
DirectoryContext DirectoryContext::Child(const char * name) const
{
	return DirectoryContext(Path.Child(name).ToString());
}



std::vector<FilePath> DirectoryContext::Children() const
{
	DIR * dir = opendir(Path.ToString());
	if (dir == NULL)
	{
		std::cout << "DirectoryContext: Error: opendir\n";
	}

	std::vector<FilePath> children;

	struct dirent * ent;
	ent = readdir(dir);
	while (ent != NULL)
	{
		children.push_back(FilePath(ent -> d_name));
		ent = readdir(dir);
	}

	if (closedir(dir) != 0)
	{
		std::cout << "DirectoryContext: Error: closedir\n";
	}
	return children;
}
std::vector<FileContext> DirectoryContext::Files() const
{
	std::vector<FilePath> paths = Children();

	std::vector<FileContext> files;

	for (size_t i = 0; i < paths.size(); i++)
	{
		FileSystemInfo info(paths[i].ToString());
		if (info.Mode.IsFile())
		{
			files.push_back(FileContext(paths[i]));
		}
	}

	return files;
}
std::vector<DirectoryContext> DirectoryContext::Directorys() const
{
	std::vector<FilePath> paths = Children();

	std::vector<DirectoryContext> dirs;

	for (size_t i = 0; i < paths.size(); i++)
	{
		FileSystemInfo info(paths[i].ToString());
		if (Mode.IsDirectory())
		{
			dirs.push_back(DirectoryContext(paths[i]));
		}
	}

	return dirs;
}



bool DirectoryContext::HasFile(const char * name) const
{
	FileSystemInfo info(Path.Child(name));
	return (info.Exists() && info.Mode.IsFile());
}
FileContext DirectoryContext::File(const char * name) const
{
	return FileContext(Path.Child(name));
}





DirectoryContext::Exception_DirectoryProblem::Exception_DirectoryProblem(const std::string & dir_path)
{
	Text = "DirectoryContext: Problem with Directory '" + dir_path + "'.";
}
const char * DirectoryContext::Exception_DirectoryProblem::what() const noexcept
{
	return Text.c_str();
}



DirectoryContext::Exception_DirectoryNotFound::Exception_DirectoryNotFound(const std::string & dir_path)
{
	Text = "DirectoryContext: Directory '" + dir_path + "' not found.";
}
const char * DirectoryContext::Exception_DirectoryNotFound::what() const noexcept
{
	return Text.c_str();
}
