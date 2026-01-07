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
		throw DirectoryNotFound(Path.ToString());
	}

	DIR * dir = opendir(Path.ToString());
	if (dir == NULL)
	{
		throw DirectoryProblem(Path.ToString());
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
		throw DirectoryProblem(Path.ToString());
	}
	return empty;
}
void DirectoryContext::Create()
{
	if (Exists() && !Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path.ToString()); }

	DirectoryContext parent = Parent();
	if (!parent.Exists())
	{
		parent.Create();
	}

	//std::cout << "Create " << Path.ToString() << '\n';
	if (mkdir(Path.ToString()) != 0)
	{
		throw DirectoryProblem(Path.ToString());
	}
}
void DirectoryContext::Delete()
{
	if (!Exists()) { throw DirectoryNotFound(Path.ToString()); }
	if (!Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path.ToString()); }

	DIR * dir = opendir(Path.ToString());
	if (dir == NULL)
	{
		throw DirectoryProblem(Path.ToString());
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
		throw DirectoryProblem(Path.ToString());
	}

	//std::cout << "Delete " << Path.ToString() << '\n';
	if (rmdir(Path.ToString()) != 0)
	{
		throw DirectoryProblem(Path.ToString());
	}
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
	if (!Exists()) { throw DirectoryNotFound(Path.ToString()); }
	if (!Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path.ToString()); }

	DIR * dir = opendir(Path.ToString());
	if (dir == NULL)
	{
		throw DirectoryProblem(Path.ToString());
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
		throw DirectoryProblem(Path.ToString());
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
