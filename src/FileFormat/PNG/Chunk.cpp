#include "FileFormat/PNG/Chunk.hpp"
#include "FileParsing/DebugManager.hpp"
#include "FileFormat/PNG/ErrorDetection.hpp"

#include <sstream>





Chunk::Chunk(BitStream & bits) :
	Length(ReverseBytes(bits.GetIncBits32())),
	CRC_Calc(CRC32(bits.DataAtIndex(), Length + 4)),
	Type(bits.GetIncBits32()),
	Data(bits.DataAtIndex()),
	CRC_Read((bits.IncByBytes(Length), ReverseBytes(bits.GetIncBits32()))),
	BitS(bits)
{ }



BitStream	Chunk::ToBitStream() const
{
	return (BitStream(Data, Length));
}



bool	Chunk::CheckCRC()
{
	return (CRC_Calc == CRC_Read);
}
bool	Chunk::CheckType(uint8 c0, uint8 c1, uint8 c2, uint8 c3)
{
	return (
		((uint8)(Type >> 0)) == c0 &&
		((uint8)(Type >> 8)) == c1 &&
		((uint8)(Type >> 16)) == c2 &&
		((uint8)(Type >> 24)) == c3
	);
}
bool	Chunk::CheckType(const char * str)
{
	unsigned int len = 0;
	while (str[len] != '\0') { len++; }
	if (len != 4)
	{
		throw "Bad Type Check";
	}
	return CheckType(str[0], str[1], str[2], str[3]);
}



void Chunk::ToConsole() const
{
	*DebugManager::Console << "PNG Chunk:";
	*DebugManager::Console << ' ' << uint_Chr(Type);
	*DebugManager::Console << ' ' << Length;
	*DebugManager::Console << '\n';
}
