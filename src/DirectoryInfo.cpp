#include "DirectoryInfo.hpp"
#include "FileExceptions.hpp"
#include "FileInfo.hpp"

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <cctype>

#include <iostream>



DirectoryInfo::DirectoryInfo() :
	FileSystemInfo()
{ }
DirectoryInfo::~DirectoryInfo()
{ }
DirectoryInfo::DirectoryInfo(const DirectoryInfo & other) :
	FileSystemInfo(other)
{ }
DirectoryInfo & DirectoryInfo::operator=(const DirectoryInfo & other)
{
	FileSystemInfo::operator=(other);
	return *this;
}

DirectoryInfo::DirectoryInfo(const char * path) :
	FileSystemInfo(path)
{ }
DirectoryInfo::DirectoryInfo(const std::string & path) :
	FileSystemInfo(path)
{ }
DirectoryInfo::DirectoryInfo(const FilePath & path) :
	FileSystemInfo(path)
{ }

FileInfo DirectoryInfo::ToFile() const { return FileInfo(OriginalPath()); }



DirectoryInfo DirectoryInfo::Here() { return DirectoryInfo(FilePath::Here()); }





bool DirectoryInfo::IsEmpty() const
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
void DirectoryInfo::Delete()
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
				FileInfo file(path);
				file.Delete();
			}
			if (stat.Mode.IsDirectory())
			{
				DirectoryInfo directory(path);
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
void DirectoryInfo::Create()
{
	if (Exists() && !Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	if (Path.ToString()[0] == '\0')
	{
		throw DirectoryProblem(Path);
	}

	DirectoryInfo parent = Parent();
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





bool DirectoryInfo::HasParent() const
{
	FileSystemInfo info(Path.Parent().ToString());
	return (info.Exists() && info.Mode.IsDirectory());
}
bool DirectoryInfo::HasChild(const char * name) const
{
	FileSystemInfo info(Path.Child(name).ToString());
	return (info.Exists() && info.Mode.IsDirectory());
}
DirectoryInfo DirectoryInfo::Parent() const
{
	return DirectoryInfo(Path.Parent().ToString());
}
DirectoryInfo DirectoryInfo::Child(const char * name) const
{
	return DirectoryInfo(Path.Child(name).ToString());
}



std::vector<FilePath> DirectoryInfo::Children() const
{
	if (!Exists()) { throw DirectoryNotFound(Path); }
	if (!Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	DIR * dir;
	struct dirent * ent;

	dir = opendir(Path.ToString());
	if (dir == NULL) { throw DirectoryProblem(Path, "opendir"); }

	std::vector<FilePath> children;

	ent = readdir(dir);
	while (ent != NULL)
	{
		children.push_back(FilePath(ent -> d_name));
		ent = readdir(dir);
	}

	if (closedir(dir) != 0) { throw DirectoryProblem(Path, "closedir"); }

	return children;
}
std::vector<FileInfo> DirectoryInfo::Files() const
{
	if (!Exists()) { throw DirectoryNotFound(Path); }
	if (!Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	DIR * dir;
	struct dirent * ent;

	dir = opendir(Path.ToString());
	if (dir == NULL) { throw DirectoryProblem(Path, "opendir"); }

	std::vector<FileInfo> children;

	ent = readdir(dir);
	while (ent != NULL)
	{
		//if (ent -> d_type == DT_REG)
		FileSystemInfo info(ent -> d_name);
		if (info.Mode.IsFile())
		{
			children.push_back(info.Path);
			//children.push_back(FilePath(ent -> d_name));
		}
		ent = readdir(dir);
	}

	if (closedir(dir) != 0) { throw DirectoryProblem(Path, "closedir"); }

	return children;
}
std::vector<DirectoryInfo> DirectoryInfo::Directorys() const
{
	if (!Exists()) { throw DirectoryNotFound(Path); }
	if (!Mode.IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	DIR * dir;
	struct dirent * ent;

	dir = opendir(Path.ToString());
	if (dir == NULL) { throw DirectoryProblem(Path, "opendir"); }

	std::vector<DirectoryInfo> children;

	ent = readdir(dir);
	while (ent != NULL)
	{
		//if (ent -> d_type == DT_DIR)
		FileSystemInfo info(ent -> d_name);
		if (info.Mode.IsDirectory())
		{
			children.push_back(info.Path);
			//children.push_back(FilePath(ent -> d_name));
		}
		ent = readdir(dir);
	}

	if (closedir(dir) != 0) { throw DirectoryProblem(Path, "closedir"); }

	return children;
}



bool DirectoryInfo::HasFile(const char * name) const
{
	FileSystemInfo info(Path.Child(name));
	return (info.Exists() && info.Mode.IsFile());
}
FileInfo DirectoryInfo::File(const char * name) const
{
	return FileInfo(Path.Child(name));
}
