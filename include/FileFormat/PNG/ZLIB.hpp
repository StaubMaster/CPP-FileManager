#ifndef  ZLIB_HPP
# define ZLIB_HPP

# include "ValueType/uint.hpp"
# include "FileParsing/ByteStreamGetter.hpp"
# include "FileParsing/ByteStreamQueue.hpp"

class ZLIB
{
	public:
	uint8	CMF;
	uint8	FLG;

	private:
	const uint8	*Data;

	public:
	uint32		Length;

	uint32	DICTID;
	uint32	ADLER32;

	ZLIB(ByteStreamGetter & bits);

	ByteBlock	ToBlock() const;

	static void	decompress(ByteStreamGetter & bits, ByteStreamQueue & stream);

	void	ToConsole() const;
};

#endif