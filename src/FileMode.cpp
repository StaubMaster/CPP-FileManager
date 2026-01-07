#include "FileMode.hpp"

#include <sys/stat.h>



static void ChangeBit(unsigned short & data, unsigned short bits, bool val)
{
	if (val)
	{ data = data | bits; }
	else
	{ data = data & (~bits); }
}



FileMode::FileMode(unsigned short & mode) :
	Mode(mode)
{ }



bool	FileMode::IsFile() const		{ return ((Mode & S_IFMT) == S_IFREG); }
bool	FileMode::IsDirectory() const	{ return ((Mode & S_IFMT) == S_IFDIR); }





bool FileMode::UserR() const { return ((Mode & S_IRUSR) != 0); }
bool FileMode::UserW() const { return ((Mode & S_IWUSR) != 0); }
bool FileMode::UserX() const { return ((Mode & S_IXUSR) != 0); }
bool FileMode::UserAll() const { return (UserR() && UserW() && UserX()); }

bool FileMode::GroupR() const { return ((Mode & S_IRGRP) != 0); }
bool FileMode::GroupW() const { return ((Mode & S_IWGRP) != 0); }
bool FileMode::GroupX() const { return ((Mode & S_IXGRP) != 0); }
bool FileMode::GroupAll() const { return (GroupR() && GroupW() && GroupX()); }

bool FileMode::OtherR() const { return ((Mode & S_IROTH) != 0); }
bool FileMode::OtherW() const { return ((Mode & S_IWOTH) != 0); }
bool FileMode::OtherX() const { return ((Mode & S_IXOTH) != 0); }
bool FileMode::OtherAll() const { return (OtherR() && OtherW() && OtherX()); }

bool FileMode::AllR() const { return (UserR() && GroupR() && OtherR()); }
bool FileMode::AllW() const { return (UserW() && GroupW() && OtherW()); }
bool FileMode::AllX() const { return (UserX() && GroupX() && OtherX()); }
bool FileMode::AllAll() const { return (UserAll() && GroupAll() && OtherAll()); }



void FileMode::UserR(bool val) { ChangeBit(Mode, S_IRUSR, val); }
void FileMode::UserW(bool val) { ChangeBit(Mode, S_IWUSR, val); }
void FileMode::UserX(bool val) { ChangeBit(Mode, S_IXUSR, val); }
void FileMode::UserAll(bool val) { UserR(val); UserW(val); UserX(val); }

void FileMode::GroupR(bool val) { ChangeBit(Mode, S_IRGRP, val); }
void FileMode::GroupW(bool val) { ChangeBit(Mode, S_IWGRP, val); }
void FileMode::GroupX(bool val) { ChangeBit(Mode, S_IXGRP, val); }
void FileMode::GroupAll(bool val) { GroupR(val); GroupW(val); GroupX(val); }

void FileMode::OtherR(bool val) { ChangeBit(Mode, S_IROTH, val); }
void FileMode::OtherW(bool val) { ChangeBit(Mode, S_IWOTH, val); }
void FileMode::OtherX(bool val) { ChangeBit(Mode, S_IXOTH, val); }
void FileMode::OtherAll(bool val) { OtherR(val); OtherW(val); OtherX(val); }

void FileMode::AllR(bool val) { UserR(val); GroupR(val); OtherR(val); }
void FileMode::AllW(bool val) { UserW(val); GroupW(val); OtherW(val); }
void FileMode::AllX(bool val) { UserX(val); GroupX(val); OtherX(val); }
void FileMode::AllAll(bool val) { UserAll(val); GroupAll(val); OtherAll(val); }





#include <iostream>
std::ostream & operator<<(std::ostream & o, const FileMode & obj)
{
	if (obj.IsFile())			{ o << "f---"; }
	else if (obj.IsDirectory())	{ o << "-d--"; }
	else						{ o << "----"; }

	o << "...";

	if (obj.UserR())  { o << "r"; } else { o << "-"; }
	if (obj.UserW())  { o << "w"; } else { o << "-"; }
	if (obj.UserX())  { o << "x"; } else { o << "-"; }
	
	if (obj.GroupR()) { o << "r"; } else { o << "-"; }
	if (obj.GroupW()) { o << "w"; } else { o << "-"; }
	if (obj.GroupX()) { o << "x"; } else { o << "-"; }

	if (obj.OtherR()) { o << "r"; } else { o << "-"; }
	if (obj.OtherW()) { o << "w"; } else { o << "-"; }
	if (obj.OtherX()) { o << "x"; } else { o << "-"; }

	return o;
}
