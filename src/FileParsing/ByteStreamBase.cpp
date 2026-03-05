#include "FileParsing/ByteStreamBase.hpp"



ByteStreamBase::~ByteStreamBase() { }
ByteStreamBase::ByteStreamBase()
	: Block()
	, Index(0)
	, Order(ByteOrder::HiToLo)
{ }



ByteStreamBase::ByteStreamBase(const ByteBlock & block)
	: Block(block)
	, Index(0)
	, Order(ByteOrder::HiToLo)
{ }
/*ByteStreamBase & ByteStreamBase::Concatenation(const std::string & str)
{
	Block.Concatenation(block);
	return *this;
}*/



void ByteStreamBase::Move()
{
	Index++;
}
void ByteStreamBase::Move(uint64 move)
{
	Index += move;
}
