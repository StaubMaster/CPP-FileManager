#include "FileParsing/ByteStreamBase.hpp"



ByteStreamBase::~ByteStreamBase() { }



ByteStreamBase::ByteStreamBase(ByteBlock block)
	: Block(block)
	, Index(0)
	, Order(ByteOrder::HiToLo)
{ }



void ByteStreamBase::Move()
{
	Index++;
}
void ByteStreamBase::Move(uint64 move)
{
	Index += move;
}
