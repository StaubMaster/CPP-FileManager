#include "FileInfo.hpp"
#include "FileMode.hpp"

#include <iostream>



bool stat_default(struct stat * info)
{
	(void)info;
	return false;
}
bool stat_copy(bool valid, const struct stat * other, struct stat * info)
{
	*info = *other;
	return valid;
}



FileInfo::FileInfo() :
	Valid(stat_default(&info)),
	Mode(info.st_mode)
{ }
FileInfo::FileInfo(std::string path) :
	Valid(stat(path.c_str(), &info) == 0),
	Mode(info.st_mode)
{ }



FileInfo::FileInfo(const FileInfo & other) :
	Valid(stat_copy(other.Valid, &other.info, &info)),
	Mode(info.st_mode),
	info(other.info)
{ }
FileInfo & FileInfo::operator = (const FileInfo & other)
{
	Valid = other.Valid;
	info = other.info;
	return *this;
}



short FileInfo::ID_User() const
{
	return info.st_uid;
}
short FileInfo::ID_Group() const
{
	return info.st_gid;
}
unsigned int FileInfo::ID_Device() const
{
	return info.st_dev;
}
unsigned int FileInfo::ID_Special() const
{
	return info.st_rdev;
}
long long FileInfo::TimeLastAccess() const
{
	return info.st_atime;
}
long long FileInfo::TimeLastModify() const
{
	return info.st_mtime;
}
long long FileInfo::TimeLastChange() const
{
	return info.st_ctime;
}
long FileInfo::Size() const
{
	return info.st_size;
}
