#include "FileMode.hpp"

#include <sys/stat.h>

#include <iostream>



FileMode::FileMode(const unsigned short & mode) :
	Mode(mode)
{ }



bool	FileMode::IsFile() const		{ return ((Mode & S_IFMT) == S_IFREG); }
bool	FileMode::IsDirectory() const	{ return ((Mode & S_IFMT) == S_IFDIR); }

bool	FileMode::UserR() const { return ((Mode & S_IRUSR) != 0); }
bool	FileMode::UserW() const { return ((Mode & S_IWUSR) != 0); }
bool	FileMode::UserX() const { return ((Mode & S_IXUSR) != 0); }
bool	FileMode::UserAll() const { return (UserR() && UserW() && UserX()); }

bool	FileMode::GroupR() const { return ((Mode & S_IRGRP) != 0); }
bool	FileMode::GroupW() const { return ((Mode & S_IWGRP) != 0); }
bool	FileMode::GroupX() const { return ((Mode & S_IXGRP) != 0); }
bool	FileMode::GroupAll() const { return (GroupR() && GroupW() && GroupX()); }

bool	FileMode::OtherR() const { return ((Mode & S_IROTH) != 0); }
bool	FileMode::OtherW() const { return ((Mode & S_IWOTH) != 0); }
bool	FileMode::OtherX() const { return ((Mode & S_IXOTH) != 0); }
bool	FileMode::OtherAll() const { return (OtherR() && OtherW() && OtherX()); }





#include <sstream>
std::ostream & operator << (std::ostream & s, const FileMode & obj)
{
	if (obj.IsFile())			{ s << "f---"; }
	else if (obj.IsDirectory())	{ s << "-d--"; }
	else						{ s << "----"; }

	s << "...";

	if (obj.UserR())  { s << "r"; } else { s << "-"; }
	if (obj.UserW())  { s << "w"; } else { s << "-"; }
	if (obj.UserX())  { s << "x"; } else { s << "-"; }
	
	if (obj.GroupR()) { s << "r"; } else { s << "-"; }
	if (obj.GroupW()) { s << "w"; } else { s << "-"; }
	if (obj.GroupX()) { s << "x"; } else { s << "-"; }

	if (obj.OtherR()) { s << "r"; } else { s << "-"; }
	if (obj.OtherW()) { s << "w"; } else { s << "-"; }
	if (obj.OtherX()) { s << "x"; } else { s << "-"; }

	return s;
}
