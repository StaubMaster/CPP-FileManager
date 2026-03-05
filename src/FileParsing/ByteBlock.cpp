#include "FileParsing/ByteBlock.hpp"



uint64 ByteBlock::Size() const { return _Size; }

uint8 * ByteBlock::Data() { return _Data; }
const uint8 * ByteBlock::Data() const { return _Data; }

uint8 & ByteBlock::operator[](uint64 idx)
{
	return _Data[idx];
}
const uint8 & ByteBlock::operator[](uint64 idx) const
{
	return _Data[idx];
}



ByteBlock::~ByteBlock()
{
	delete[] _Data;
}
ByteBlock::ByteBlock()
	: _Size(0)
	, _Data(nullptr)
{ }
ByteBlock::ByteBlock(uint64 size)
	: _Size(size)
	, _Data(new uint8[_Size])
{ }

ByteBlock::ByteBlock(const ByteBlock & other)
	: _Size(other._Size)
	, _Data(new uint8[_Size])
{
	for (uint64 i = 0; i < _Size; i++)
	{
		_Data[i] = other._Data[i];
	}
}
ByteBlock ByteBlock::operator=(const ByteBlock & other)
{
	delete[] _Data;
	_Size = other._Size;
	_Data = new uint8[_Size];
	for (uint64 i = 0; i < _Size; i++)
	{
		_Data[i] = other._Data[i];
	}
	return *this;
}



ByteBlock & ByteBlock::Concatenation(uint64 size)
{
	ByteBlock block;
	block._Size = _Size;
	block._Data = _Data;

	_Size = block._Size + size;
	_Data = new uint8[_Size];

	for (uint64 i = 0; i < block._Size; i++)
	{
		_Data[i] = block._Data[i];
	}

	return *this;
}
ByteBlock & ByteBlock::Concatenation(const ByteBlock & other)
{
	ByteBlock block;
	block._Size = _Size;
	block._Data = _Data;

	_Size = block._Size + other._Size;
	_Data = new uint8[_Size];

	for (uint64 i = 0; i < block._Size; i++)
	{
		_Data[i] = block._Data[i];
	}
	for (uint64 i = 0; i < other._Size; i++)
	{
		_Data[i + block._Size] = other._Data[i];
	}

	return *this;
}



ByteBlock::ByteBlock(const std::string & str)
	: _Size(str.length())
	, _Data(new uint8[_Size])
{
	for (uint64 i = 0; i < _Size; i++)
	{
		_Data[i] = str[i];
	}
}