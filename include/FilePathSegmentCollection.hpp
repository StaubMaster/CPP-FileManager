#ifndef  FILE_PATH_SEGMENT_COLLECTION_HPP
# define FILE_PATH_SEGMENT_COLLECTION_HPP

# include "FilePathSegment.hpp"

struct FilePathSegmentCollection
{
	unsigned int Count;
	FilePathSegment * Segments;

	FilePathSegmentCollection();
	~FilePathSegmentCollection();

	FilePathSegmentCollection(const FilePathSegmentCollection & other);
	FilePathSegmentCollection & operator=(const FilePathSegmentCollection & other);

	FilePathSegmentCollection RemoveLast() const;
	FilePathSegmentCollection Append(const FilePathSegmentCollection & other) const;

	static FilePathSegmentCollection Split(const char * path);

	char * ToString() const;
};

# include <iosfwd>
std::ostream & operator<<(std::ostream & o, const FilePathSegmentCollection & obj);

#endif