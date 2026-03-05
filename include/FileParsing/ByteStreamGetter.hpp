#ifndef  BYTE_STREAM_GETTER_HPP
# define BYTE_STREAM_GETTER_HPP

# include "FileParsing/ByteStreamBase.hpp"

# include <exception>
# include <string>

struct ByteStreamGetter : public ByteStreamBase
{
	public:
	~ByteStreamGetter();
	ByteStreamGetter() = delete;

	private:
	ByteStreamGetter(const ByteStreamGetter & other) = delete;
	ByteStreamGetter & operator=(const ByteStreamGetter & other) = delete;

	public:
	ByteStreamGetter(const ByteBlock & block);
	ByteStreamGetter & Concatenation(const ByteBlock & block);

	public:
	uint8		Get1();
	uint16		Get2();
	uint32		Get4();
	uint64		Get8();
	ByteBlock	Get(uint64 size);
};

#endif