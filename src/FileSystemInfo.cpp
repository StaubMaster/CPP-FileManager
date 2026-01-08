#include "FileSystemInfo.hpp"



FileSystemInfo::FileSystemInfo() :
	FileSystemStat(),
	Path(),
	_OriginalPath()
{ }
FileSystemInfo::~FileSystemInfo()
{ }
FileSystemInfo::FileSystemInfo(const FileSystemInfo & other) :
	FileSystemStat(other),
	Path(other.Path),
	_OriginalPath(other._OriginalPath)
{ }
FileSystemInfo & FileSystemInfo::operator=(const FileSystemInfo & other)
{
	FileSystemStat::operator=(other);
	Path = other.Path;
	_OriginalPath = other._OriginalPath;
	return *this;
}



FileSystemInfo::FileSystemInfo(const char * path) :
	FileSystemStat(),
	Path(path),
	_OriginalPath(path)
{
	FileSystemStat::Refresh(Path.ToString());
}
FileSystemInfo::FileSystemInfo(const std::string & path) :
	FileSystemStat(),
	Path(path.c_str()),
	_OriginalPath(path)
{
	FileSystemStat::Refresh(Path.ToString());
}
FileSystemInfo::FileSystemInfo(const FilePath & path) :
	FileSystemStat(),
	Path(path),
	_OriginalPath(path.ToString())
{
	FileSystemStat::Refresh(Path.ToString());
}



void FileSystemInfo::Refresh() { FileSystemStat::Refresh(Path.ToString()); }
bool FileSystemInfo::Exists() const { return Valid; }
std::string FileSystemInfo::OriginalPath() const { return _OriginalPath; }
std::string FileSystemInfo::Name() const { return std::string(Path.Name()); }





#include <iostream>
std::ostream & operator<<(std::ostream & o, const FileSystemInfo & obj)
{
	o << "Path: " << obj.Path << '\n';
	o << "OriginalPath: " << obj.OriginalPath() << '\n';
	o << *((FileSystemStat*)&obj);
	return o;
}
