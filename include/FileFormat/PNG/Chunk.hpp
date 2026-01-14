
#ifndef  PNG_CHUNKS_HPP
# define PNG_CHUNKS_HPP

# include "FileParsing/BitStream.hpp"
# include "ValueType/uint.hpp"

struct Chunk
{
	const uint32	Length;
	const uint32	Type;
	const uint8 *	Data;
	const uint32	CRC;

	const BitStream & BitS;

	Chunk(BitStream & bits);

	uint32		calc_CRC() const;
	BitStream	ToBitStream() const;

	std::string	ToString() const;

	bool		CheckType(uint8 c0, uint8 c1, uint8 c2, uint8 c3);
	bool		CheckType(const char * str);
};

#endif
