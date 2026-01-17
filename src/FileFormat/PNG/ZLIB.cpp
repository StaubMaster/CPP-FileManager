#include "FileFormat/PNG/ZLIB.hpp"
#include "FileFormat/PNG/DEFLATE.hpp"

#include "FileParsing/BitStream.hpp"
#include "FileParsing/ByteStream.hpp"
#include "FileParsing/DebugManager.hpp"



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
	//	maybe check this ?
}

BitStream	ZLIB::ToBitStream() const
{
	return (BitStream(Data, Length));
	//return BitStream(BitS, Length);
}



void	ZLIB::decompress(BitStream & bits, ByteStream & data)
{
	//*DebugManager::Console << "\e[34mzlib ...\e[m\n";

	ZLIB zlib(bits);
	//zlib.ToConsole();
	//*DebugManager::Console << "\n";

	BitStream deflate = zlib.ToBitStream();
	DEFLATE::Blocks(deflate, data);

	//*DebugManager::Console << "\e[34mzlib done\e[m\n";
}



void ZLIB::ToConsole() const
{
	uint8	CM = (CMF >> 0) & 0b1111;
	uint8	CINFO = (CMF >> 4) & 0b1111;
	*DebugManager::Console << "CMF   : " << ToBase2(CMF) << "\n";
	*DebugManager::Console << "CM    : "    << ToBase2(CM, 3) << "\n";
	*DebugManager::Console << "CINFO : " << ToBase2(CINFO, 3) << "\n";

	uint8	FCHECK = (FLG >> 0) & 0b11111;
	uint8	FDICT = (FLG >> 5) & 0b1;
	uint8	FLEVEL = (FLG >> 6) & 0b11;
	*DebugManager::Console << "FLG    : " << ToBase2(FLG) << "\n";
	*DebugManager::Console << "FCHECK : "    << ToBase2(FCHECK, 4) << "\n";
	*DebugManager::Console << "FDICT  : " << ToBase2(FDICT, 0) << "\n";
	*DebugManager::Console << "FLEVEL : " << ToBase2(FLEVEL, 1) << "\n";

	*DebugManager::Console << "DICTID  : " << ToBase16(DICTID) << "\n";
	*DebugManager::Console << "ADLER32 : " << ToBase16(ADLER32) << "\n";

	*DebugManager::Console << "Length : " << Length << "\n";
}
