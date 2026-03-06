#include "FileParsing/ByteBlockExternal.hpp"



ByteBlockExternal::~ByteBlockExternal()
{ }
ByteBlockExternal::ByteBlockExternal()
	: ByteBlockBase()
{ }



ByteBlockExternal::ByteBlockExternal(const ByteBlockExternal & other)
	: ByteBlockBase(other._Size, other._Data)
{ }
ByteBlockExternal & ByteBlockExternal::operator=(const ByteBlockExternal & other)
{
	_Size = other._Size;
	_Data = other._Data;
	return *this;
}



ByteBlockExternal::ByteBlockExternal(ByteBlockBase & other)
	: ByteBlockBase(other.Size(), other.Data())
{ }
ByteBlockExternal & ByteBlockExternal::operator=(ByteBlockBase & other)
{
	_Size = other.Size();
	_Data = other.Data();
	return *this;
}



ByteBlockExternal::ByteBlockExternal(uint64 size, uint8 * data)
	: ByteBlockBase(size, data)
{ }

ByteBlockExternal::ByteBlockExternal(std::string & str)
	: ByteBlockBase(str.size(), (uint8 *)str.data())
{ }
