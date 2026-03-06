#ifndef  PNG_CHUNKS_HPP
# define PNG_CHUNKS_HPP

# include "FileParsing/ByteBlock.hpp"
# include "FileParsing/ByteStreamGetter.hpp"
# include "FileParsing/BitStreamGetter.hpp"
# include "ValueType/uint.hpp"

struct Chunk
{
	const uint32	Length;
	const uint32	CRC_Calc;
	const uint32	Type;
	const uint8 *	Data;
	const uint32	CRC_Read;

	Chunk(ByteStreamGetter & stream);

	ByteBlock	ToBlock() const;

	bool	CheckCRC();
	bool	CheckType(uint8 c0, uint8 c1, uint8 c2, uint8 c3);
	bool	CheckType(const char * str);

	void	ToConsole() const;
};

#endif