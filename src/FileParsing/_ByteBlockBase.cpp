#include "FileParsing/ByteBlockBase.hpp"



uint64 ByteBlockBase::Size() const { return _Size; }

uint8 * ByteBlockBase::Data() { return _Data; }
const uint8 * ByteBlockBase::Data() const { return _Data; }

uint8 * ByteBlockBase::DataAt(uint64 idx) { return _Data + idx; }
const uint8 * ByteBlockBase::DataAt(uint64 idx) const { return _Data + idx; }

uint8 & ByteBlockBase::operator[](uint64 idx)
{
	return _Data[idx];
}
const uint8 & ByteBlockBase::operator[](uint64 idx) const
{
	return _Data[idx];
}



ByteBlockBase::~ByteBlockBase()
{ }
ByteBlockBase::ByteBlockBase()
	: _Size(0)
	, _Data(nullptr)
{ }
ByteBlockBase::ByteBlockBase(uint64 size)
	: _Size(size)
	, _Data(new uint8[_Size])
{ }
ByteBlockBase::ByteBlockBase(uint64 size, uint8 * data)
	: _Size(size)
	, _Data(data)
{ }
