#include "FileParsing/ByteStreamGetter.hpp"



ByteStreamGetter::~ByteStreamGetter() { }



ByteStreamGetter::ByteStreamGetter(const ByteBlock & block)
	: ByteStreamBase(block)
{ }
ByteStreamGetter & ByteStreamGetter::Concatenation(const ByteBlock & block)
{
	Block.Concatenation(block);
	return *this;
}



uint8 ByteStreamGetter::Get1()
{
	uint64 data = 0;
	if (Order == ByteOrder::HiToLo)
	{
		data |= ((uint64)Block[Index + 0]) << (0 * 8);
	}
	else
	{
		data |= ((uint64)Block[Index + 0]) << (0 * 8);
	}
	Index += 1;
	return data;
}
uint16 ByteStreamGetter::Get2()
{
	uint16 data = 0;
	if (Order == ByteOrder::HiToLo)
	{
		data |= ((uint16)Block[Index + 0]) << (0 * 8);
		data |= ((uint16)Block[Index + 1]) << (1 * 8);
	}
	else
	{
		data |= ((uint16)Block[Index + 0]) << (1 * 8);
		data |= ((uint16)Block[Index + 1]) << (0 * 8);
	}
	Index += 2;
	return data;
}
uint32 ByteStreamGetter::Get4()
{
	uint32 data = 0;
	if (Order == ByteOrder::HiToLo)
	{
		data |= ((uint32)Block[Index + 0]) << (0 * 8);
		data |= ((uint32)Block[Index + 1]) << (1 * 8);
		data |= ((uint32)Block[Index + 2]) << (2 * 8);
		data |= ((uint32)Block[Index + 3]) << (3 * 8);
	}
	else
	{
		data |= ((uint32)Block[Index + 0]) << (3 * 8);
		data |= ((uint32)Block[Index + 1]) << (2 * 8);
		data |= ((uint32)Block[Index + 2]) << (1 * 8);
		data |= ((uint32)Block[Index + 3]) << (0 * 8);
	}
	Index += 4;
	return data;
}
uint64 ByteStreamGetter::Get8()
{
	uint64 data = 0;
	if (Order == ByteOrder::HiToLo)
	{
		data |= ((uint64)Block[Index + 0]) << (0 * 8);
		data |= ((uint64)Block[Index + 1]) << (1 * 8);
		data |= ((uint64)Block[Index + 2]) << (2 * 8);
		data |= ((uint64)Block[Index + 3]) << (3 * 8);
		data |= ((uint64)Block[Index + 4]) << (4 * 8);
		data |= ((uint64)Block[Index + 5]) << (5 * 8);
		data |= ((uint64)Block[Index + 6]) << (6 * 8);
		data |= ((uint64)Block[Index + 7]) << (7 * 8);
	}
	else
	{
		data |= ((uint64)Block[Index + 0]) << (7 * 8);
		data |= ((uint64)Block[Index + 1]) << (6 * 8);
		data |= ((uint64)Block[Index + 2]) << (5 * 8);
		data |= ((uint64)Block[Index + 3]) << (4 * 8);
		data |= ((uint64)Block[Index + 4]) << (3 * 8);
		data |= ((uint64)Block[Index + 5]) << (2 * 8);
		data |= ((uint64)Block[Index + 6]) << (1 * 8);
		data |= ((uint64)Block[Index + 7]) << (0 * 8);
	}
	Index += 8;
	return data;
}
