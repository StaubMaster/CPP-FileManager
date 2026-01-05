#include "FilePathSegmentCollection.hpp"

#if defined(_WIN32)
# define SLASH '\\'
#endif

#if defined(__APPLE__)
# define SLASH '/'
#endif



FilePathSegmentCollection::FilePathSegmentCollection() :
	Count(0),
	Segments(nullptr)
{ }
FilePathSegmentCollection::~FilePathSegmentCollection()
{
	delete[] Segments;
}

FilePathSegmentCollection::FilePathSegmentCollection(const FilePathSegmentCollection & other) :
	Count(other.Count),
	Segments(new FilePathSegment[Count])
{
	for (unsigned int i = 0; i < Count; i++)
	{
		Segments[i] = other.Segments[i];
	}
}
FilePathSegmentCollection & FilePathSegmentCollection::operator=(const FilePathSegmentCollection & other)
{
	delete[] Segments;
	Count = other.Count;
	Segments = new FilePathSegment[Count];
	for (unsigned int i = 0; i < Count; i++)
	{
		Segments[i] = other.Segments[i];
	}
	return *this;
}



FilePathSegmentCollection FilePathSegmentCollection::RemoveLast() const
{
	FilePathSegmentCollection collection;
	if (Count != 0) { collection.Count = Count - 1; }
	collection.Segments = new FilePathSegment[collection.Count];
	for (unsigned int i = 0; i < collection.Count; i++)
	{
		collection.Segments[i] = Segments[i];
	}
	return collection;
}
FilePathSegmentCollection FilePathSegmentCollection::Append(const FilePathSegmentCollection & other) const
{
	FilePathSegmentCollection collection;
	collection.Count = Count + other.Count;
	collection.Segments = new FilePathSegment[collection.Count];
	for (unsigned int i = 0; i < Count; i++)
	{
		collection.Segments[i] = Segments[i];
	}
	for (unsigned int i = 0; i < other.Count; i++)
	{
		collection.Segments[i + Count] = other.Segments[i];
	}
	return collection;
}



FilePathSegmentCollection FilePathSegmentCollection::Split(const char * path)
{
	unsigned int len = 0;
	while (path[len] != '\0') { len++; }
	char * str = new char[len + 1];
	for (unsigned int i = 0; i < len; i++)
	{
		if (path[i] == '/' || path[i] == '\\')
		{ str[i] = SLASH; }
		else
		{ str[i] = path[i]; }
	}
	str[len] = '\0';

	FilePathSegmentCollection collection;
	
	//	Count
	if (len != 0)
	{
		unsigned int i = 0;
		if (str[i] == SLASH)
		{
			for (; i < len; i++)
			{
				if (str[i] != SLASH)
				{
					i++;
					collection.Count++;
					break;
				}
			}
			if (i == len) { collection.Count++; }
		}
		else
		{
			collection.Count++;
		}

		for (; i < len; i++)
		{
			if (str[i] != SLASH && (i != 0 && str[i - 1] == SLASH))
			{
				collection.Count++;
			}
		}
	}

	//	Take
	collection.Segments = new FilePathSegment[collection.Count];
	if (len != 0)
	{
		unsigned int idx = 0;
		unsigned int off;
		unsigned int i = 0;
		if (str[i] == SLASH)
		{
			for (; i < len; i++)
			{
				if (str[i] != SLASH)
				{
					off = i - 1;
					i++;
					break;
				}
			}
			if (i == len)
			{
				collection.Segments[idx].FromTo(str, len - 1, len);
			}
		}
		else
		{
			off = i;
		}

		for (; i < len; i++)
		{
			if (str[i] != SLASH && (i != 0 && str[i - 1] == SLASH))
			{
				off = i;
			}
			if (str[i] == SLASH && (i != 0 && str[i - 1] != SLASH))
			{
				collection.Segments[idx].FromTo(str, off, i);
				idx++;
			}
		}
		if (str[len - 1] != SLASH)
		{
			collection.Segments[idx].FromTo(str, off, len);
			idx++;
		}
	}
	delete[] str;

	return collection;
}



char * FilePathSegmentCollection::ToString() const
{
	unsigned int len = 0;
	for (unsigned int i = 0; i < Count; i++)
	{
		len += Segments[i].Length;
	}
	if (Count != 0) { len += Count - 1; }

	unsigned int idx = 0;
	char * str = new char[len + 1];
	for (unsigned int i = 0; i < Count; i++)
	{
		if (i != 0)
		{
			str[idx] = SLASH;
			idx++;
		}
		for (unsigned int j = 0; j < Segments[i].Length; j++)
		{
			str[idx] = Segments[i].String[j];
			idx++;
		}
	}
	str[len] = '\0';
	return str;
}





#include <iostream>
std::ostream & operator<<(std::ostream & o, const FilePathSegmentCollection & obj)
{
	char * str = obj.ToString();
	o << ((const char *)str);
	delete[] str;
	return o;
}
