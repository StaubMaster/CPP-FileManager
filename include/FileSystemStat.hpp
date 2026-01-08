#ifndef  FILE_SYSTEM_STAT_HPP
# define FILE_SYSTEM_STAT_HPP

#include "FileMode.hpp"

#include <sys/stat.h>

/*msys64\ucrt64\include\_mingw_stat64.h
  struct stat {
    _dev_t st_dev;
    _ino_t st_ino;
    unsigned short st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    _dev_t st_rdev;
    _off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
  };
*/
class FileSystemStat
{
	//	make this store the individual values
	//	only use struct stat for getting the data
	public:
	bool Valid;

	FileMode Mode;		//unsigned short st_mode;
	_ino_t Idone;		//_ino_t st_ino;
	short UserID;		//short st_uid;
	short GroupID;		//short st_gid;
	_dev_t DeviceID;	//_dev_t st_dev;
	_dev_t SpecialID;	//_dev_t st_rdev;
	short LinkCount;	//short st_nlink;
	time_t CreateTime;	//time_t st_ctime;
	time_t ModifyTime;	//time_t st_mtime;
	time_t AccessTime;	//time_t st_atime;
	_off_t Size;		//_off_t st_size;
	//struct stat sys_stat;

	public:
	FileSystemStat();
	~FileSystemStat();
	FileSystemStat(const FileSystemStat & other);
	FileSystemStat & operator=(const FileSystemStat & other);

	public:
	FileSystemStat(const char * path);
	protected:
	void Refresh(const char * path);
};

std::ostream & operator<<(std::ostream & o, const FileSystemStat & obj);

#endif