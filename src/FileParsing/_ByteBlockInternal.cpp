#include "FileParsing/ByteBlockInternal.hpp"



ByteBlockInternal::~ByteBlockInternal()
{
	delete[] _Data;
}
ByteBlockInternal::ByteBlockInternal()
	: ByteBlockBase(0, nullptr)
{ }



ByteBlockInternal::ByteBlockInternal(const ByteBlockBase & other)
	: ByteBlockBase(other.Size())
{
	for (uint64 i = 0; i < _Size; i++)
	{
		_Data[i] = other[i];
	}
}
ByteBlockInternal & ByteBlockInternal::operator=(const ByteBlockBase & other)
{
	delete[] _Data;
	_Size = other.Size();
	_Data = new uint8[_Size];
	for (uint64 i = 0; i < _Size; i++)
	{
		_Data[i] = other[i];
	}
	return *this;
}
ByteBlockInternal & ByteBlockInternal::Concatenation(const ByteBlockBase & other)
{
	uint64	temp_size = _Size;
	uint8 *	temp_data = _Data;

	_Size = temp_size + other.Size();
	_Data = new uint8[_Size];

	for (uint64 i = 0; i < temp_size; i++)
	{
		_Data[i] = temp_data[i];
	}
	for (uint64 i = 0; i < other.Size(); i++)
	{
		_Data[i + temp_size] = other[i];
	}

	return *this;
}



ByteBlockInternal::ByteBlockInternal(uint64 size)
	: ByteBlockBase(size)
{ }
ByteBlockInternal & ByteBlockInternal::Concatenation(uint64 size)
{
	uint64	temp_size = _Size;
	uint8 *	temp_data = _Data;

	_Size = temp_size + size;
	_Data = new uint8[_Size];

	for (uint64 i = 0; i < temp_size; i++)
	{
		_Data[i] = temp_data[i];
	}

	return *this;
}



ByteBlockInternal::ByteBlockInternal(uint64 size, uint8 * data)
	: ByteBlockBase(size)
{
	for (uint64 i = 0; i < _Size; i++)
	{
		_Data[i] = data[i];
	}
}
ByteBlockInternal & ByteBlockInternal::Concatenation(uint64 size, uint8 * data)
{
	uint64	temp_size = _Size;
	uint8 *	temp_data = _Data;

	_Size = temp_size + size;
	_Data = new uint8[_Size];

	for (uint64 i = 0; i < temp_size; i++)
	{
		_Data[i] = temp_data[i];
	}
	for (uint64 i = 0; i < size; i++)
	{
		_Data[i + temp_size] = data[i];
	}

	return *this;
}



ByteBlockInternal::ByteBlockInternal(const std::string & str)
	: ByteBlockBase(str.length())
{
	for (uint64 i = 0; i < _Size; i++)
	{
		_Data[i] = str[i];
	}
}
