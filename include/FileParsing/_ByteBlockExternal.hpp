#ifndef  BYTE_BLOCK_EXTERNAL_HPP
# define BYTE_BLOCK_EXTERNAL_HPP

# include "FileParsing/ByteBlockBase.hpp"
# include <string>

class ByteBlockExternal : public ByteBlockBase
{
	public:
	~ByteBlockExternal();
	ByteBlockExternal();

	ByteBlockExternal(const ByteBlockExternal & other);
	ByteBlockExternal & operator=(const ByteBlockExternal & other);

	ByteBlockExternal(ByteBlockBase & other);
	ByteBlockExternal & operator=(ByteBlockBase & other);

	ByteBlockExternal(uint64 size, uint8 * data);

	// only use for accessing, dont try to change
	ByteBlockExternal(std::string & str);
};

#endif