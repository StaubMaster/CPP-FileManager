#include "FileSystemStat.hpp"

#include <unistd.h>



FileSystemStat::FileSystemStat() :
	Valid(false),
	Mode(),
	Idone(0),
	UserID(0),
	GroupID(0),
	DeviceID(0),
	SpecialID(0),
	LinkCount(0),
	CreateTime(0),
	ModifyTime(0),
	AccessTime(0),
	Size(0)
{ }
FileSystemStat::~FileSystemStat()
{ }
FileSystemStat::FileSystemStat(const FileSystemStat & other) :
	Valid(other.Valid),
	Mode(other.Mode),
	Idone(other.Idone),
	UserID(other.UserID),
	GroupID(other.GroupID),
	DeviceID(other.DeviceID),
	SpecialID(other.SpecialID),
	LinkCount(other.LinkCount),
	CreateTime(other.CreateTime),
	ModifyTime(other.ModifyTime),
	AccessTime(other.AccessTime),
	Size(other.Size)
{ }
FileSystemStat & FileSystemStat::operator=(const FileSystemStat & other)
{
	Valid = other.Valid;
	Mode = other.Mode;
	Idone = other.Idone;
	UserID = other.UserID;
	GroupID = other.GroupID;
	DeviceID = other.DeviceID;
	SpecialID = other.SpecialID;
	LinkCount = other.LinkCount;
	CreateTime = other.CreateTime;
	ModifyTime = other.ModifyTime;
	AccessTime = other.AccessTime;
	Size = other.Size;
	return *this;
}



FileSystemStat::FileSystemStat(const char * path) :
	Valid(false),
	Mode(),
	Idone(0),
	UserID(0),
	GroupID(0),
	DeviceID(0),
	SpecialID(0),
	LinkCount(0),
	CreateTime(0),
	ModifyTime(0),
	AccessTime(0),
	Size(0)
{
	if (access(path, 0) == 0)
	{
		struct stat sys_stat;
		Valid = (stat(path, &sys_stat) == 0);
		Mode = sys_stat.st_mode;
		Idone = sys_stat.st_ino;
		UserID = sys_stat.st_uid;
		GroupID = sys_stat.st_gid;
		DeviceID = sys_stat.st_dev;
		SpecialID = sys_stat.st_rdev;
		LinkCount = sys_stat.st_nlink;
		CreateTime = sys_stat.st_ctime;
		ModifyTime = sys_stat.st_mtime;
		AccessTime = sys_stat.st_atime;
		Size = sys_stat.st_size;;
	}
}
void FileSystemStat::Refresh(const char * path)
{
	Valid = false;
	Mode = FileMode(0);
	Idone = 0;
	UserID = 0;
	GroupID = 0;
	DeviceID = 0;
	SpecialID = 0;
	LinkCount = 0;
	CreateTime = 0;
	ModifyTime = 0;
	AccessTime = 0;
	Size = 0;
	if (access(path, 0) == 0)
	{
		struct stat sys_stat;
		Valid = (stat(path, &sys_stat) == 0);
		Mode = sys_stat.st_mode;
		Idone = sys_stat.st_ino;
		UserID = sys_stat.st_uid;
		GroupID = sys_stat.st_gid;
		DeviceID = sys_stat.st_dev;
		SpecialID = sys_stat.st_rdev;
		LinkCount = sys_stat.st_nlink;
		CreateTime = sys_stat.st_ctime;
		ModifyTime = sys_stat.st_mtime;
		AccessTime = sys_stat.st_atime;
		Size = sys_stat.st_size;;
	}
}



#include <iostream>
std::ostream & operator<<(std::ostream & o, const FileSystemStat & obj)
{
	o << "Valid " << obj.Valid << '\n';
	o << "Mode " << obj.Mode << '\n';
	o << "Inode " << obj.Idone << '\n';
	o << "Links " << obj.LinkCount << '\n';
	o << "UserID " << obj.UserID << '\n';
	o << "GroupID " << obj.GroupID << '\n';
	o << "DeviceID " << obj.DeviceID << '\n';
	o << "SpecialID " << obj.SpecialID << '\n';
	o << "CreateTime " << obj.CreateTime << '\n';
	o << "ModifyTime " << obj.ModifyTime << '\n';
	o << "AccessTime " << obj.AccessTime << '\n';
	o << "Size " << obj.Size << '\n';
	return o;
}
