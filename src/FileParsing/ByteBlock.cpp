#include "FileParsing/ByteBlock.hpp"



uint64 ByteBlock::Size() const { return _Size; }

uint8 * ByteBlock::Data() { return _Data; }
const uint8 * ByteBlock::Data() const { return _Data; }

uint8 * ByteBlock::DataAt(uint64 idx) { return _Data + idx; }
const uint8 * ByteBlock::DataAt(uint64 idx) const { return _Data + idx; }

uint8 & ByteBlock::operator[](uint64 idx) { return _Data[idx]; }
const uint8 & ByteBlock::operator[](uint64 idx) const { return _Data[idx]; }

ByteBlock ByteBlock::BlockAt(uint64 idx, uint64 size) const { return ByteBlock::Bind(size, _Data + idx); }



ByteBlock::~ByteBlock() { }
void ByteBlock::Dispose() { _Size = 0; delete[] _Data; _Data = nullptr; }



ByteBlock::ByteBlock()
	: _Size(0)
	, _Data(nullptr)
{ }
ByteBlock::ByteBlock(uint64 size)
	: _Size(size)
	, _Data(new uint8[_Size])
{ }
ByteBlock::ByteBlock(uint64 size, uint8 * data)
	: _Size(size)
	, _Data(data)
{ }
ByteBlock::ByteBlock(uint64 size, const uint8 * data)
	: _Size(size)
	, _Data((uint8 *)data)
{ }



ByteBlock::ByteBlock(const ByteBlock & other)
	: _Size(other._Size)
	, _Data(other._Data)
{ }
ByteBlock ByteBlock::operator=(const ByteBlock & other)
{
	_Size = other._Size;
	_Data = other._Data;
	return *this;
}



ByteBlock ByteBlock::Bind() const
{
	return ByteBlock(*this);
}
ByteBlock ByteBlock::Copy() const
{
	ByteBlock block(_Size);
	for (uint64 i = 0; i < _Size; i++)
	{
		block._Data[i] = _Data[i];
	}
	return block;
}

ByteBlock ByteBlock::Bind(const ByteBlock & other)
{
	return ByteBlock(other.Bind());
}
ByteBlock ByteBlock::Copy(const ByteBlock & other)
{
	return ByteBlock(other.Copy());
}

ByteBlock ByteBlock::Bind(uint64 size, uint8 * data)
{
	ByteBlock block(size);
	block._Data = data;
	return block;
}
ByteBlock ByteBlock::Copy(uint64 size, uint8 * data)
{
	ByteBlock block(size);
	for (uint64 i = 0; i < size; i++)
	{
		block._Data[i] = data[i];
	}
	return block;
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
