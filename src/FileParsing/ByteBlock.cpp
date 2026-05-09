#include "FileParsing/ByteBlock.hpp"



uint64 ByteBlock::Size() const { return _Size; }

uint8 * ByteBlock::Data() { return _Data; }
const uint8 * ByteBlock::Data() const { return _Data; }

uint8 * ByteBlock::DataAt(uint64 idx) { return _Data + idx; }
const uint8 * ByteBlock::DataAt(uint64 idx) const { return _Data + idx; }

uint8 & ByteBlock::operator[](uint64 idx) { return _Data[idx]; }
const uint8 & ByteBlock::operator[](uint64 idx) const { return _Data[idx]; }

ByteBlock ByteBlock::BlockAt(uint64 idx, uint64 size) const
{
	//return ByteBlock::Bind(size, _Data + idx);
	return ByteBlock(size, _Data + idx);
}



void ByteBlock::mForget()
{
	if (_Know != nullptr)
	{
		(*_Know)--;
	}
	_Data = nullptr;
	_Know = nullptr;
	_Size = 0;
}
void ByteBlock::mDelete()
{
	if (_Know != nullptr)
	{
		if ((*_Know) == 0)
		{
			delete _Know;
			delete[] _Data;
		}
	}
	mForget();
}
void ByteBlock::mNew(uint64 size)
{
	mDelete();
	_Data = new uint8[size];
	_Know = new uint8; (*_Know) = 0;
	_Size = size;
}
void ByteBlock::mRemember(uint64 size, uint8 * data)
{
	mDelete();
	_Data = data;
	_Know = nullptr;
	_Size = size;
}
void ByteBlock::mBind(const ByteBlock & other)
{
	mDelete();
	_Size = other._Size;
	_Know = other._Know;
	_Data = other._Data;
	if (_Know != nullptr) { (*_Know)++; }
}



ByteBlock::~ByteBlock()
{ mDelete(); }
void ByteBlock::Dispose()
{ mDelete(); }



ByteBlock::ByteBlock()
{ }
ByteBlock::ByteBlock(uint64 size)
{ mNew(size); }
ByteBlock::ByteBlock(uint64 size, uint8 * data)
{ mRemember(size, data); }
ByteBlock::ByteBlock(uint64 size, const uint8 * data)
{ mRemember(size, (uint8*)data); }



ByteBlock::ByteBlock(const ByteBlock & other)
{ mBind(other); }
ByteBlock ByteBlock::operator=(const ByteBlock & other)
{
	mBind(other);
	return *this;
}



/*ByteBlock ByteBlock::Bind() const
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
}*/



ByteBlock & ByteBlock::Concatenation(uint64 size)
{
	ByteBlock block;
	block._Size = _Size;
	block._Data = _Data;

	_Data = nullptr;
	mNew(block._Size + size);

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

	_Data = nullptr;
	mNew(block._Size + other._Size);

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
{
	mNew(str.length());
	for (uint64 i = 0; i < _Size; i++)
	{
		_Data[i] = str[i];
	}
}
