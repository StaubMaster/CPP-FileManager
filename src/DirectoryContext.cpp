#include "DirectoryContext.hpp"
#include "FileExceptions.hpp"
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





bool DirectoryContext::IsEmpty() const
{
	if (!Exists() || !Mode.IsDirectory())
	{
		throw DirectoryNotFound(Path);
	}

	DIR * dir = opendir(Path.ToString());
	if (dir == NULL)
	{
		throw DirectoryProblem(Path, "opendir");
	}

	bool empty = true;

	struct dirent * ent;
	ent = readdir(dir);
	while (ent != NULL)
	{
		std::string name = ent -> d_name;
		if (name != "." && name != "..")
		{
			empty = false;
			break;
		}
		ent = readdir(dir);
	}

	if (closedir(dir) != 0)
	{
		throw DirectoryProblem(Path, "closedir");
	}
	return empty;
}
void DirectoryContext::Delete()
{
	if (!Exists()) { throw DirectoryNotFound(Path); }
	if (!Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	DIR * dir = opendir(Path.ToString());
	if (dir == NULL)
	{
		throw DirectoryProblem(Path, "opendir");
	}

	struct dirent * ent;
	ent = readdir(dir);
	while (ent != NULL)
	{
		std::string name = ent -> d_name;
		if (name != "." && name != "..")
		{
			FilePath path = Path.Child(ent -> d_name);
			FileSystemStat stat(path.ToString());
			if (stat.Mode.IsFile())
			{
				FileContext file(path);
				file.Delete();
			}
			if (stat.Mode.IsDirectory())
			{
				DirectoryContext directory(path);
				directory.Delete();
			}
		}
		ent = readdir(dir);
	}

	if (closedir(dir) != 0)
	{
		throw DirectoryProblem(Path, "closedir");
	}

	//std::cout << "Delete Directory: " << Mode << ' ' << Path << '\n';
	if (rmdir(Path.ToString()) != 0)
	{
		throw DirectoryProblem(Path, "rmdir");
	}

	Refresh();
	//std::cout << "Directory: " << Mode << ' ' << Path << '\n';
	//std::cout << "Directory Info\n" << *this << '\n';
}
void DirectoryContext::Create()
{
	if (Exists() && !Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	if (Path.ToString()[0] == '\0')
	{
		throw DirectoryProblem(Path);
	}

	DirectoryContext parent = Parent();
	if (!parent.Exists() && !parent.Path.IsNone())
	{
		parent.Create();
	}

	//std::cout << "Create Directory: " << Mode << ' ' << Path << '\n';
	if (mkdir(Path.ToString()) != 0)
	{
		throw DirectoryProblem(Path, "mkdir");
	}

	Refresh();
	//std::cout << "Directory: " << Mode << ' ' << Path << '\n';
	//std::cout << "Directory Info\n" << *this << '\n';
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
	if (!Exists()) { throw DirectoryNotFound(Path); }
	if (!Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	DIR * dir = opendir(Path.ToString());
	if (dir == NULL)
	{
		throw DirectoryProblem(Path, "opendir");
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
		throw DirectoryProblem(Path, "closedir");
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
