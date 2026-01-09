
#ifndef  PNG_CHUNKS_HPP
# define PNG_CHUNKS_HPP

# include "Parsing/BitStream.hpp"
# include "ValueType/uint.hpp"

class Chunk
{
	private:
		static uint8	knownTypeIndex(uint32 type);

	public:
		const uint32	Length;
		const uint32	Type;
		const uint8 *	Data;
		const uint32	CRC;

		const uint8		typeIndex;

		const BitStream & BitS;

		Chunk(BitStream & bits);

	private:
		uint32		calc_CRC() const;
	public:
		BitStream	ToBitStream() const;

		std::string	ToString() const;

		bool		isIHRD() const;
		bool		isIDAT() const;
		bool		isIEND() const;
};

#endif
