#include "FileParsing/BitStream.hpp"



BitStream::BitStream(ByteBlock block)
	: Block(block)
	, BitIndex(0)
	, ByteIndex(0)
{ }



const uint8 * BitStream::DataAtIndex() const { return Block.DataAt(ByteIndex); }



void	BitStream::MoveToNextByte()
{
	if (BitIndex != 0)
	{
		BitIndex = 0;
		ByteIndex++;
	}
}

void	BitStream::IncByBytes(uint32 count)
{
	ByteIndex += count;
}
void	BitStream::IncByBits(uint32 count)
{
	BitIndex += count;
	ByteIndex += BitIndex >> 3;
	BitIndex &= 0b111;
}



uint8	BitStream::GetBits8(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT8_BIT_LIMIT) + 1;


	uint8 val;
	if (BitIndex != 0)
	{
		val = ((uint8)Block[ByteIndex]) >> (BitIndex);
		val |= ((uint8)Block[ByteIndex + 1]) << ((1 * 8) - BitIndex);
	}
	else
	{
		val = ((uint8)Block[ByteIndex]);
	}

	return val;
}
uint16	BitStream::GetBits16(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT16_BIT_LIMIT) + 1;

	uint16 val;
	if (BitIndex != 0)
	{
		val = ((uint16)Block[ByteIndex]) >> (BitIndex);
		val |= ((uint16)Block[ByteIndex + 1]) << ((1 * 8) - BitIndex);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint16)Block[ByteIndex + 2]) << ((2 * 8) - BitIndex); }
	}
	else
	{
		val = ((uint16)Block[ByteIndex]);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint16)Block[ByteIndex + 1]) << (1 * 8); }
	}

	return val;
}
uint32	BitStream::GetBits32(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT32_BIT_LIMIT) + 1;

	uint32 val;
	if (BitIndex != 0)
	{
		val = ((uint32)Block[ByteIndex]) >> (BitIndex);
		val |= ((uint32)Block[ByteIndex + 1]) << ((1 * 8) - BitIndex);
		if (bit_count > 7)	{ val |= ((uint32)Block[ByteIndex + 2]) << ((2 * 8) - BitIndex); }
		if (bit_count > 15)	{ val |= ((uint32)Block[ByteIndex + 3]) << ((3 * 8) - BitIndex); }
		if (bit_count > 23)	{ val |= ((uint32)Block[ByteIndex + 4]) << ((4 * 8) - BitIndex); }
	}
	else
	{
		val = ((uint32)Block[ByteIndex]);
		if (bit_count > 7)	{ val |= ((uint32)Block[ByteIndex + 1]) << (1 * 8); }
		if (bit_count > 15)	{ val |= ((uint32)Block[ByteIndex + 2]) << (2 * 8); }
		if (bit_count > 23)	{ val |= ((uint32)Block[ByteIndex + 3]) << (3 * 8); }
	}

	if (bit_count != UINT32_BIT_COUNT)
	{
		val = val & (0xFFFFFFFF >> (UINT32_BIT_COUNT - bit_count));
	}

	return val;
}
uint64	BitStream::GetBits64(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT64_BIT_LIMIT) + 1;

	uint64 val;
	if (BitIndex != 0)
	{
		val = ((uint64)Block[ByteIndex]) >> (BitIndex);
		val |= ((uint64)Block[ByteIndex + 1]) << ((1 * 8) - BitIndex);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 2]) << ((2 * 8) - BitIndex); }
		if (bit_count > (2 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 3]) << ((3 * 8) - BitIndex); }
		if (bit_count > (3 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 4]) << ((4 * 8) - BitIndex); }
		if (bit_count > (4 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 5]) << ((5 * 8) - BitIndex); }
		if (bit_count > (5 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 6]) << ((6 * 8) - BitIndex); }
		if (bit_count > (6 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 7]) << ((7 * 8) - BitIndex); }
		if (bit_count > (7 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 8]) << ((8 * 8) - BitIndex); }
	}
	else
	{
		val = ((uint64)Block[ByteIndex]);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 1]) << (1 * 8); }
		if (bit_count > (2 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 2]) << (2 * 8); }
		if (bit_count > (3 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 3]) << (3 * 8); }
		if (bit_count > (4 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 4]) << (4 * 8); }
		if (bit_count > (5 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 5]) << (5 * 8); }
		if (bit_count > (6 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 6]) << (6 * 8); }
		if (bit_count > (7 * 8) - 1)	{ val |= ((uint64)Block[ByteIndex + 7]) << (7 * 8); }
	}

	if (bit_count != UINT64_BIT_COUNT)
	{
		val = val & (0xFFFFFFFFFFFFFFFF >> (UINT64_BIT_COUNT - bit_count));
	}

	return val;
}



uint8	BitStream::GetIncBits8(uint8 bit_count)
{
	uint8 val = GetBits8(bit_count);
	IncByBits(bit_count);
	return val;
}
uint16	BitStream::GetIncBits16(uint8 bit_count)
{
	uint16 val = GetBits16(bit_count);
	IncByBits(bit_count);
	return val;
}
uint32	BitStream::GetIncBits32(uint8 bit_count)
{
	uint32 val = GetBits32(bit_count);
	IncByBits(bit_count);
	return val;
}
uint64	BitStream::GetIncBits64(uint8 bit_count)
{
	uint64 val = GetBits64(bit_count);
	IncByBits(bit_count);
	return val;
}





const char * BitStream::LenReachedException::what() const throw() { return "BitStream Length reached"; }
