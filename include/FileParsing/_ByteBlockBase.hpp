#ifndef  BYTE_BLOCK_BASE_HPP
# define BYTE_BLOCK_BASE_HPP

# include "ValueType/uint.hpp"

class ByteBlockBase
{
	protected:
	uint64	_Size;
	uint8 *	_Data;



	public:
	uint64 Size() const;

	uint8 * Data();
	const uint8 * Data() const;

	uint8 * DataAt(uint64 idx);
	const uint8 * DataAt(uint64 idx) const;

	uint8 & operator[](uint64 idx);
	const uint8 & operator[](uint64 idx) const;



	public:
	virtual ~ByteBlockBase();
	ByteBlockBase();
	ByteBlockBase(uint64 size);
	ByteBlockBase(uint64 size, uint8 * data);

	ByteBlockBase(const ByteBlockBase & other) = delete;
	ByteBlockBase & operator=(const ByteBlockBase & other) = delete;
};

#endif