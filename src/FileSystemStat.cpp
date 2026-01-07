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
