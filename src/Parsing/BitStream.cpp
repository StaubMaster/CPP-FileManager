#include "Parsing/BitStream.hpp"



BitStream::BitStream(const void * ptr, uint32 len) :
	Data((const uint8*)ptr),
	Len(len),
	BitIndex(0),
	ByteIndex(0)
{ }

BitStream::BitStream(const std::string & str) :
	Data((const uint8*)str.c_str()),
	Len(str.size()),
	BitIndex(0),
	ByteIndex(0)
{ }

BitStream::BitStream(const BitStream & other, uint32 len) :
	Data(other.Data),
	Len(len),
	BitIndex(0),
	ByteIndex(0)
{ }





const uint8 *	BitStream::DataAtIndex() const
{
	return Data + ByteIndex;
}



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

	uint32	bitI = BitIndex;
	uint32	byteI = ByteIndex;

	uint8 val = 0;
	uint8 byte_count = UINT8_BYTE_COUNT;
	if (bitI != 0)
	{
		val |= ((uint8)Data[byteI]) >> (bitI);
		byte_count++;
	}

	for (uint8 i = 0; i < byte_count; i++)
	{
		val |= ((uint8)Data[byteI + i]) << ((i * 8) - bitI);
	}

	if (bit_count != UINT8_BIT_COUNT)
	{
		val = val & (0xFF >> (UINT8_BIT_COUNT - bit_count));
	}
	return val;
}
uint16	BitStream::GetBits16(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT16_BIT_LIMIT) + 1;

	uint32	bitI = BitIndex;
	uint32	byteI = ByteIndex;

	uint16 val = 0;
	uint8 byte_count = UINT16_BYTE_COUNT;
	if (bitI != 0)
	{
		val |= ((uint16)Data[byteI]) >> (bitI);
		byte_count++;
	}

	for (uint8 i = 0; i < byte_count; i++)
	{
		val |= ((uint16)Data[byteI + i]) << ((i * 8) - bitI);
	}

	if (bit_count != UINT16_BIT_COUNT)
	{
		val = val & (0xFFFF >> (UINT16_BIT_COUNT - bit_count));
	}
	return val;
}
uint32	BitStream::GetBits32(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT32_BIT_LIMIT) + 1;

	uint32	bitI = BitIndex;
	uint32	byteI = ByteIndex;

	uint32 val = 0;

	uint8 byte_count = UINT32_BYTE_COUNT;
	if (bitI != 0)
	{
		val |= ((uint32)Data[byteI]) >> (bitI);
		byte_count++;
	}
	for (uint8 i = 0; i < byte_count; i++)
	{
		val |= ((uint32)Data[byteI + i]) << ((i * 8) - bitI);
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

	uint32	bitI = BitIndex;
	uint32	byteI = ByteIndex;

	uint64 val = 0;
	uint8 byte_count = UINT64_BYTE_COUNT;
	if (bitI != 0)
	{
		val |= ((uint64)Data[byteI]) >> (bitI);
		byte_count++;
	}

	for (uint8 i = 0; i < byte_count; i++)
	{
		val |= ((uint64)Data[byteI + i]) << ((i * 8) - bitI);
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
