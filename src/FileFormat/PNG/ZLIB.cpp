#include "FileFormat/PNG/ZLIB.hpp"
#include "FileFormat/PNG/DEFLATE.hpp"

#include "FileParsing/DebugManager.hpp"



ZLIB::ZLIB(ByteStreamGetter & bits)
{
	CMF = bits.Get1();
	FLG = bits.Get1();

	if ((FLG >> 5) & 0b1)
	{
		DICTID = bits.Get4();
		Length = bits.Block.Size() - 10;
	}
	else
	{
		DICTID = 0;
		Length = bits.Block.Size() - 6;
	}

	//Data = bits.DataAtIndex();
	Data = bits.Block.DataAt(bits.Index);
	//bits.MoveToNextByte();
	bits.Move(Length);
	//bits.IncByBytes(Length);
	ADLER32 = bits.Get4(); // maybe check this ?
}

ByteBlock	ZLIB::ToBlock() const
{
	return ByteBlock(Length, Data);
}



void	ZLIB::decompress(ByteStreamGetter & bits, ByteStreamQueue & data)
{
	//*DebugManager::Console << "\e[34mzlib ...\e[m\n";

	ZLIB zlib(bits);
	//zlib.ToConsole();
	//*DebugManager::Console << "\n";

	BitStreamGetter deflate(zlib.ToBlock());
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
