#include "FileParsing/ByteStream.hpp"

#include <iostream>



ByteStream::ByteStream(uint32 len)
{
	Len = len;
	Data = new uint8[Len];
	Index = 0;
}
ByteStream::~ByteStream()
{
	delete [] Data;
}



/*
	instead of reallocating and copying
	just store pointers to the chunk data and length
	then Indax it with a double Index
	maybe do something similar to the Deflat stuff
	so it also acts as a Stream
*/
void	ByteStream::Concatenation(const uint8 * data, uint32 len)
{
	uint8	* newData = new uint8[Len + len];

	for (uint32 i = 0; i < Len; i++)
	{
		newData[i] = Data[i];
	}
	for (uint32 i = 0; i < len; i++)
	{
		newData[i + Len] = data[i];
	}

	Len = Len + len;
	delete [] Data;
	Data = newData;
}



void	ByteStream::Next()
{
	Index++;
}



void	ByteStream::Set(uint8 val)
{
	if (Index >= Len)
	{
		std::cout << "\e[31mByteStream Limit\e[m\n";
	}

	Data[Index] = val;
}
uint8	ByteStream::Get()
{
	if (Index >= Len)
	{
		std::cout << "\e[31mByteStream Limit\e[m\n";
	}

	return Data[Index];
}



void	ByteStream::SetRange(uint8 * ptr, uint32 len)
{
	if (Index + len >= Len)
	{
		std::cout << "\e[31mByteStream Limit\e[m\n";
	}

	for (uint32 i = 0; i < len; i++, Index++)
	{
		Data[Index] = ptr[i];
	}
}
