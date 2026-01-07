#ifndef  FILE_SYSTEM_STAT_HPP
# define FILE_SYSTEM_STAT_HPP

#include "FileMode.hpp"

#include <sys/stat.h>

class FileSystemStat
{
	//	make this store the individual values
	//	only use struct stat for getting the data

	private:	struct stat sys_stat;
	public:		FileMode Mode;
	public:		bool Valid;

	public:
	FileSystemStat();
	~FileSystemStat();
	FileSystemStat(const FileSystemStat & other);
	FileSystemStat & operator=(const FileSystemStat & other);

	public:
	FileSystemStat(const char * path);
	protected:
	void Refresh(const char * path);

/*F:\msys64\ucrt64\include\_mingw_stat64.h
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
	public:
	_ino_t Idone() const;
	short LinkCount() const;

	short UserID() const;
	short GroupID() const;

	_dev_t DeviceID() const;
	_dev_t SpecialID() const;

	time_t CreateTime() const;
	time_t ModifyTime() const;
	time_t AccessTime() const;

	_off_t Size() const;
};

std::ostream & operator<<(std::ostream & o, const FileSystemStat & obj);

#endif