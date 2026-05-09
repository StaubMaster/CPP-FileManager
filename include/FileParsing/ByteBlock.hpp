#ifndef  BYTE_BLOCK_HPP
# define BYTE_BLOCK_HPP

# include "ValueType/uint.hpp"
# include <string>

class ByteBlock
{
	private:
	uint8 *		_Data = nullptr;
	uint8 *		_Know = nullptr;
	uint64		_Size = 0;



	public:
	uint64 Size() const;

	uint8 * Data();
	const uint8 * Data() const;

	uint8 * DataAt(uint64 idx);
	const uint8 * DataAt(uint64 idx) const;

	uint8 & operator[](uint64 idx);
	const uint8 & operator[](uint64 idx) const;

	ByteBlock BlockAt(uint64 idx, uint64 size) const;



	private:
	void	mForget();
	void	mDelete();
	void	mNew(uint64 size);
	void	mRemember(uint64 size, uint8 * data);
	void	mBind(const ByteBlock & other);



	public:
	~ByteBlock();
	void	Dispose();

	ByteBlock();
	ByteBlock(uint64 size); // delete
	ByteBlock(uint64 size, uint8 * data); // delete
	ByteBlock(uint64 size, const uint8 * data); // dont delete

	ByteBlock(const ByteBlock & other);
	ByteBlock operator=(const ByteBlock & other);



	public:
//	ByteBlock Bind() const;
//	ByteBlock Copy() const;
//
//	static ByteBlock Bind(const ByteBlock & other);
//	static ByteBlock Copy(const ByteBlock & other);
//
//	static ByteBlock Bind(uint64 size, uint8 * data); // dont delete
//	static ByteBlock Copy(uint64 size, uint8 * data); // delete



	public:
	ByteBlock & Concatenation(uint64 size);
	ByteBlock & Concatenation(const ByteBlock & other);

	ByteBlock(const std::string & str);
	ByteBlock & Concatenation(const std::string & str);
};

#endif