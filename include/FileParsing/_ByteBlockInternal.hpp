#ifndef  BYTE_BLOCK_INTERNAL_HPP
# define BYTE_BLOCK_INTERNAL_HPP

# include "FileParsing/ByteBlockBase.hpp"
# include <string>

class ByteBlockInternal : public ByteBlockBase
{
	public:
	~ByteBlockInternal();
	ByteBlockInternal();

	ByteBlockInternal(const ByteBlockInternal & other) = delete;
	ByteBlockInternal & operator=(const ByteBlockInternal & other) = delete;

	ByteBlockInternal(const ByteBlockBase & other);
	ByteBlockInternal & operator=(const ByteBlockBase & other);
	ByteBlockInternal & Concatenation(const ByteBlockBase & other);

	ByteBlockInternal(uint64 size);
	ByteBlockInternal & Concatenation(uint64 size);

	ByteBlockInternal(uint64 size, uint8 * data);
	ByteBlockInternal & Concatenation(uint64 size, uint8 * data);

	ByteBlockInternal(const std::string & str);
//	ByteBlockInternal & Concatenation(const std::string & str);
};

#endif