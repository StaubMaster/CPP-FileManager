#include "FileSystemStat.hpp"



FileSystemStat::FileSystemStat() :
	sys_stat(),
	Mode(sys_stat.st_mode),
	Valid(false)
{ }
FileSystemStat::~FileSystemStat()
{ }
FileSystemStat::FileSystemStat(const FileSystemStat & other) :
	sys_stat(other.sys_stat),
	Mode(sys_stat.st_mode),
	Valid(other.Valid)
{ }
FileSystemStat & FileSystemStat::operator=(const FileSystemStat & other)
{
	Valid = other.Valid;
	sys_stat = other.sys_stat;
	return *this;
}



FileSystemStat::FileSystemStat(const char * path) :
	sys_stat(),
	Mode(sys_stat.st_mode),
	Valid(false)
{
	if (access(path, 0) == 0)
	{
		Valid = (stat(path, &sys_stat) == 0);
	}
}
#include <iostream>
void FileSystemStat::Refresh(const char * path)
{
	Valid = false;
	std::cout << "Path '" << path << "'\n";
	if (access(path, 0) == 0)
	{
		Valid = (stat(path, &sys_stat) == 0);
	}
}



_ino_t FileSystemStat::Idone() const { return sys_stat.st_ino; }
short FileSystemStat::LinkCount() const { return sys_stat.st_nlink; }

short FileSystemStat::UserID() const { return sys_stat.st_uid; }
short FileSystemStat::GroupID() const { return sys_stat.st_gid; }

_dev_t FileSystemStat::DeviceID() const { return sys_stat.st_dev; }
_dev_t FileSystemStat::SpecialID() const { return sys_stat.st_rdev; }

time_t FileSystemStat::CreateTime() const { return sys_stat.st_ctime; }
time_t FileSystemStat::ModifyTime() const { return sys_stat.st_mtime; }
time_t FileSystemStat::AccessTime() const { return sys_stat.st_atime; }

_off_t FileSystemStat::Size() const { return sys_stat.st_size; }



#include <iostream>
std::ostream & operator<<(std::ostream & o, const FileSystemStat & obj)
{
	o << "Valid " << obj.Valid << '\n';
	o << "Mode " << obj.Mode << '\n';
	o << "Inode " << obj.Idone() << '\n';
	o << "Links " << obj.LinkCount() << '\n';
	o << "UserID " << obj.UserID() << '\n';
	o << "GroupID " << obj.GroupID() << '\n';
	o << "DeviceID " << obj.DeviceID() << '\n';
	o << "SpecialID " << obj.SpecialID() << '\n';
	o << "CreateTime " << obj.CreateTime() << '\n';
	o << "ModifyTime " << obj.ModifyTime() << '\n';
	o << "AccessTime " << obj.AccessTime() << '\n';
	o << "Size " << obj.Size() << '\n';
	return o;
}
