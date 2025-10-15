#include "FilePath.hpp"

#include <sstream>
#include <vector>
#include <dirent.h>

#include <iostream>



#if defined(_WIN32)
# include <windows.h>
# define SLASH '\\'
#endif

#if defined(__APPLE__)
# include <unistd.h>
# define SLASH '/'
#endif

#define THIS_DIR "."
#define META_DIR ".."



FilePath::FilePath()
{ }
FilePath::FilePath(std::string path)
{
	std::stringstream ss(path);
	std::string segment;
	while (std::getline(ss, segment, SLASH))
	{
		Segments.push_back(segment);
	}
}
FilePath::~FilePath()
{ }

FilePath::FilePath(const FilePath & other) :
	Segments(other.Segments)
{ }
void FilePath::operator = (const FilePath & other)
{
	Segments = std::vector<std::string>(other.Segments);
}





FilePath FilePath::Here()
{
#if defined(_WIN32)
	TCHAR path[MAX_PATH];
	//DWORD len = GetCurrentDirectory(MAX_PATH, buf);
	if (GetCurrentDirectory(MAX_PATH, path) == 0)
	{
		std::cout << "Error getting current Dir\n";
	}
	return FilePath(std::string((const char *)path));
#endif

#if defined(__APPLE__)
	char path[PATH_MAX];
	if (getwd(path) == NULL)
	{
		std::cout << "Error getting current Dir\n";
	}
	return FilePath(std::string(path));
#endif
}



std::string FilePath::ToString() const
{
	std::string path;
	for (size_t i = 0; i < Segments.size(); i++)
	{
		if (i != 0) { path += SLASH; }
		path += Segments[i];
	}
	return path;
}



bool FilePath::IsAbsolute() const
{
	const std::string & seg = Segments[0];
#if defined(_WIN32)
	if (seg.size() < 2) { return false; }
	if (!std::isalpha(seg[0])) { return false; }
	if (seg[1] != ':') { return false; }
#endif
#if defined(__APPLE__)
	if (!seg.empty()) { return false; }
#endif
	return true;
}
bool FilePath::IsRelative() const
{
	return !IsAbsolute();
}

FilePath FilePath::ToAbsolute() const
{
	if (IsAbsolute()) { return FilePath(ToString()); }
	return FilePath(Here().ToString() + SLASH + ToString());
}
FilePath FilePath::ToRelative(const FilePath & root) const
{
	size_t i0 = 0;
	size_t i1 = 0;

	if (Segments[i0] == THIS_DIR) { i0++; }

	for (; i0 < Segments.size() && i1 < root.Segments.size(); i0++, i1++)
	{
		if (Segments[i0] != root.Segments[i1])
		{
			break;
		}
	}

	//FilePath path((root.Segments.size() - i0) + (Segments.size() - i1) + 1);
	FilePath path;

	path.Segments.push_back(THIS_DIR);

	for (; i1 < root.Segments.size(); i1++)
	{
		path.Segments.push_back(META_DIR);
	}

	for (; i0 < Segments.size(); i0++)
	{
		path.Segments.push_back(Segments[i0]);
	}

	return FilePath(path);
}



FilePath FilePath::Parent() const
{
	FilePath path;
	for (unsigned int i = 0; i < Segments.size() - 1; i++)
	{
		path.Segments.push_back(Segments[i]);
	}
	return path;
}
FilePath FilePath::Child(std::string name) const
{
	FilePath path;
	for (unsigned int i = 0; i < Segments.size(); i++)
	{
		path.Segments.push_back(Segments[i]);
	}
	path.Segments.push_back(name);
	return path;
}





#include <sstream>
std::ostream & operator << (std::ostream & s, const FilePath & obj)
{
	for (size_t i = 0; i < obj.Segments.size(); i++)
	{
		if (i != 0) { s << SLASH; }
		s << obj.Segments[i];
	}
	return s;
}

