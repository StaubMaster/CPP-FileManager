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
