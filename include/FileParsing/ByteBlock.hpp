#ifndef  BYTE_BLOCK_HPP
# define BYTE_BLOCK_HPP

# include "ValueType/uint.hpp"
# include <string>

class ByteBlock
{
	private:
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

	ByteBlock BlockAt(uint64 idx, uint64 size) const;



	public:
	~ByteBlock();
	void Dispose();

	ByteBlock();
	ByteBlock(uint64 size);
	ByteBlock(uint64 size, uint8 * data);
	ByteBlock(uint64 size, const uint8 * data);

	ByteBlock(const ByteBlock & other);
	ByteBlock operator=(const ByteBlock & other);



	public:
	ByteBlock Bind() const;
	ByteBlock Copy() const;

	static ByteBlock Bind(const ByteBlock & other);
	static ByteBlock Copy(const ByteBlock & other);

	static ByteBlock Bind(uint64 size, uint8 * data);
	static ByteBlock Copy(uint64 size, uint8 * data);



	public:
	ByteBlock & Concatenation(uint64 size);
	ByteBlock & Concatenation(const ByteBlock & other);

	ByteBlock(const std::string & str);
	ByteBlock & Concatenation(const std::string & str);
};

#endif