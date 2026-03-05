#ifndef  BYTE_BLOCK_HPP
# define BYTE_BLOCK_HPP

# include "ValueType/uint.hpp"
# include <string>

// kind of the same std::string ?
// but less confusing about that it is
class ByteBlock
{
	private:
	uint64	_Size;
	uint8 *	_Data;



	public:
	uint64 Size() const;

	uint8 * Data();
	const uint8 * Data() const;

	uint8 & operator[](uint64 idx);
	const uint8 & operator[](uint64 idx) const;



	public:
	~ByteBlock();
	ByteBlock();
	ByteBlock(uint64 size);

	ByteBlock(const ByteBlock & other);
	ByteBlock operator=(const ByteBlock & other);

	ByteBlock & Concatenation(uint64 size);
	ByteBlock & Concatenation(const ByteBlock & other);

	ByteBlock(const std::string & str);
	ByteBlock & Concatenation(const std::string & str);
};

#endif