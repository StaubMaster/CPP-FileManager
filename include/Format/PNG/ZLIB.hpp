
#ifndef  ZLIB_HPP
# define ZLIB_HPP

# include "ValueType/uint.hpp"

class BitStream;
class ByteStream;

class ZLIB
{
	public:
		uint8	CMF;
		uint8	FLG;

	private:
		const uint8	*Data;
		//BitStream	& BitS;
	public:
		uint32		Length;

		uint32	DICTID;
		uint32	ADLER32;

		ZLIB(BitStream & bits);

		BitStream	ToBitStream() const;

		std::string	ToString() const;

		static void	decompress(BitStream & bits, ByteStream & data);
};

#endif
