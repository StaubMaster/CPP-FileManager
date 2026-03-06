#ifndef  BYTE_STREAM_BASE_HPP
# define BYTE_STREAM_BASE_HPP

# include "ValueType/uint.hpp"
# include "FileParsing/ByteBlock.hpp"
# include "FileParsing/ExceptionBase.hpp"

# include <exception>
# include <string>

struct ByteStreamBase
{
	enum ByteOrder : bool
	{
		HiToLo = 0,
		LoToHi = 1,
	};

	public:
	ByteBlock	Block;
	uint64		Index;
	ByteOrder	Order;

	protected:
	virtual ~ByteStreamBase();
	ByteStreamBase() = delete;

	private:
	ByteStreamBase(const ByteStreamBase & other) = delete;
	ByteStreamBase & operator=(const ByteStreamBase & other) = delete;

	protected:
	ByteStreamBase(ByteBlock block);

	public:
	void Move();
	void Move(uint64 move);
};

#endif