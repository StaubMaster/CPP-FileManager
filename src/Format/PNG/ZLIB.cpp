#include "Format/PNG/ZLIB.hpp"
#include "Format/PNG/DEFLATE.hpp"

#include "Parsing/BitStream.hpp"
#include "Parsing/ByteStream.hpp"
#include "Parsing/DebugManager.hpp"



ZLIB::ZLIB(BitStream & bits)
{
	CMF = bits.GetIncBits8();
	FLG = bits.GetIncBits8();

	if ((FLG >> 5) & 0b1)
	{
		DICTID = bits.GetIncBits32();
		Length = bits.Len - 10;
	}
	else
	{
		DICTID = 0;
		Length = bits.Len - 6;
	}

	Data = bits.DataAtIndex();
	bits.MoveToNextByte();
	bits.IncByBytes(Length);
	ADLER32 = bits.GetIncBits32();
}

BitStream	ZLIB::ToBitStream() const
{
	return (BitStream(Data, Length));
	//return BitStream(BitS, Length);
}



std::string	ZLIB::ToString() const
{
	std::ostream & os = DebugManager::GetOut();

	uint8	CM = (CMF >> 0) & 0b1111;
	uint8	CINFO = (CMF >> 4) & 0b1111;
	os << "CMF   : " << ToBase2(CMF) << "\n";
	os << "CM    : "    << ToBase2(CM, 3) << "\n";
	os << "CINFO : " << ToBase2(CINFO, 3) << "\n";

	uint8	FCHECK = (FLG >> 0) & 0b11111;
	uint8	FDICT = (FLG >> 5) & 0b1;
	uint8	FLEVEL = (FLG >> 6) & 0b11;
	os << "FLG    : " << ToBase2(FLG) << "\n";
	os << "FCHECK : "    << ToBase2(FCHECK, 4) << "\n";
	os << "FDICT  : " << ToBase2(FDICT, 0) << "\n";
	os << "FLEVEL : " << ToBase2(FLEVEL, 1) << "\n";

	os << "DICTID  : " << ToBase16(DICTID) << "\n";
	os << "ADLER32 : " << ToBase16(ADLER32) << "\n";

	os << "Length : " << Length << "\n";

	return (std::string());
}


void	ZLIB::decompress(BitStream & bits, ByteStream & data)
{
	std::ostream & os = DebugManager::GetOut();
	os << "\e[34mzlib ...\e[m\n";

	ZLIB zlib(bits);
	zlib.ToString();
	os << "\n";

	BitStream deflate = zlib.ToBitStream();
	DEFLATE::Blocks(deflate, data);

	os << "\e[34mzlib done\e[m\n";
}
