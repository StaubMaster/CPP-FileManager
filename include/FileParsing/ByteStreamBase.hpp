#ifndef  BYTE_STREAM_BASE_HPP
# define BYTE_STREAM_BASE_HPP

# include "ValueType/uint.hpp"

class ByteStreamBase
{
	public:
	ByteStreamBase();
	virtual ~ByteStreamBase();

	public:
	ByteStreamBase(const ByteStreamBase & other) = delete;
	ByteStreamBase & operator=(const ByteStreamBase & other) = delete;

	public:
	virtual bool Done();

	public:
	virtual void Move() = 0;
	virtual void Move(uint32 idx) = 0;

	public:
	virtual ByteStreamBase & Set1(uint8 & val) = 0;
	virtual ByteStreamBase & Set2(uint16 & val) = 0;
	virtual ByteStreamBase & Set4(uint32 & val) = 0;
	virtual ByteStreamBase & Set8(uint64 & val) = 0;

	public:
	virtual ByteStreamBase & Get1(uint8 & val) = 0;
	virtual ByteStreamBase & Get2(uint16 & val) = 0;
	virtual ByteStreamBase & Get4(uint32 & val) = 0;
	virtual ByteStreamBase & Get8(uint64 & val) = 0;
};

#endif
