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
	Valid(stat(path, &sys_stat) == 0)
{ }
void FileSystemStat::Refresh(const char * path)
{
	Valid = (stat(path, &sys_stat) == 0);
}



short FileSystemStat::UserID() const { return sys_stat.st_uid; }
short FileSystemStat::GroupID() const { return sys_stat.st_gid; }

unsigned int FileSystemStat::DeviceID() const { return sys_stat.st_dev; }
unsigned int FileSystemStat::SpecialID() const { return sys_stat.st_rdev; }

long long FileSystemStat::CreateTime() const { return sys_stat.st_ctime; }
long long FileSystemStat::ModifyTime() const { return sys_stat.st_mtime; }
long long FileSystemStat::AccessTime() const { return sys_stat.st_atime; }

long FileSystemStat::Size() const { return sys_stat.st_size; }



#include <iostream>
std::ostream & operator<<(std::ostream & o, const FileSystemStat & obj)
{
	//std::cout << "Valid " << 
	o << "Mode " << obj.Mode << '\n';
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
