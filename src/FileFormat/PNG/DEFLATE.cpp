#include "FileFormat/PNG/DEFLATE.hpp"
#include "FileFormat/PNG/Huffman.hpp"

#include "FileParsing/DebugManager.hpp"
#include "FileParsing/BitStream.hpp"
#include "FileParsing/ByteStream.hpp"
#include "ValueType/uint.hpp"



static uint32 len_base[] = {
    3, 4, 5, 6, 7, 8, 9, 10, //257 - 264
    11, 13, 15, 17,          //265 - 268
    19, 23, 27, 31,          //269 - 273
    35, 43, 51, 59,          //274 - 276
    67, 83, 99, 115,         //278 - 280
    131, 163, 195, 227,      //281 - 284
    258                      //285
};

static uint32 len_base_extra_bits[] = {
    0, 0, 0, 0, 0, 0, 0, 0, //257 - 264
    1, 1, 1, 1, //265 - 268
    2, 2, 2, 2, //269 - 273 
    3, 3, 3, 3, //274 - 276
    4, 4, 4, 4, //278 - 280
    5, 5, 5, 5, //281 - 284
    0           //285
};

static uint32 dist_base[] = {
    /*0*/ 1, 2, 3, 4,    //0-3
    /*1*/ 5, 7,          //4-5
    /*2*/ 9, 13,         //6-7
    /*3*/ 17, 25,        //8-9
    /*4*/ 33, 49,        //10-11
    /*5*/ 65, 97,        //12-13
    /*6*/ 129, 193,      //14-15
    /*7*/ 257, 385,      //16-17
    /*8*/ 513, 769,      //18-19
    /*9*/ 1025, 1537,    //20-21
    /*10*/ 2049, 3073,   //22-23
    /*11*/ 4097, 6145,   //24-25
    /*12*/ 8193, 12289,  //26-27
    /*13*/ 16385, 24577, //28-29
           0    , 0      //30-31, error, shouldn't occur
};

static uint32 dist_base_extra_bits[] = {
    /*0*/ 0, 0, 0, 0, //0-3
    /*1*/ 1, 1,       //4-5
    /*2*/ 2, 2,       //6-7
    /*3*/ 3, 3,       //8-9
    /*4*/ 4, 4,       //10-11
    /*5*/ 5, 5,       //12-13
    /*6*/ 6, 6,       //14-15
    /*7*/ 7, 7,       //16-17
    /*8*/ 8, 8,       //18-19
    /*9*/ 9, 9,       //20-21
    /*10*/ 10, 10,    //22-23
    /*11*/ 11, 11,    //24-25
    /*12*/ 12, 12,    //26-27
    /*13*/ 13, 13,    //28-29
            0 , 0     //30-31 error, they shouldn't occur
};



void	DEFLATE::decode_Huffman(BitStream & bits, HuffmanTree & literal, HuffmanTree & distance, ByteStream & data)
{
	//*DebugManager::Console << "\e[34mHuffman decode ... \e[m\n";

	uint32	decode_value;

	uint32	len_idx;
	uint32	len_len;

	uint32	dist_idx;
	uint32	dist_len;

	//uint32	back_idx;

	while (1)
	{
		decode_value = literal.decode(bits);

		if (decode_value < 256)
		{
			data.Set(decode_value);
			data.Next();
		}
		else if (decode_value == 256)
		{
			break;
		}
		else if (decode_value < 286)
		{
			len_idx = decode_value - 257;
			len_len = len_base[len_idx] + bits.GetIncBits32(len_base_extra_bits[len_idx]);

			dist_idx = distance.decode(bits);
			dist_len = dist_base[dist_idx] + bits.GetIncBits32(dist_base_extra_bits[dist_idx]);

			data.SetRange(&(data.Data[data.Index - dist_len]), len_len);
			/*back_idx = data.Index - dist_len;
			while (len_len != 0)
			{
				len_len--;
				data.Set(data.Data[back_idx]);
				data.Next();
				back_idx++;
			}*/
		}
		else
		{
			*DebugManager::Console << "\e[31mError: Invalid Huffman Decode\e[m\n";
			throw Exception_InvalidData("Huffman Decode: ", decode_value);
		}
	}
	//*DebugManager::Console << "\e[34mHuffman decode done \e[m\n";
}

uint8 *	DEFLATE::dynamic_Huffman(BitStream & bits, uint32 H_LIT, uint32 H_DIST, uint32 H_CLEN)
{
	uint8 codeLenCodeLenOrder[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
	uint8 codeLenCodeLen[19];
	for (uint32 i = 0; i < 19; i++)
		codeLenCodeLen[i] = 0;
	for (uint32 i = 0; i < H_CLEN; i++)
		codeLenCodeLen[codeLenCodeLenOrder[i]] = bits.GetIncBits32(3);

	HuffmanTree	Trees(codeLenCodeLen, 19);
	uint8 * Huffman_BitLen_Trees = new uint8[H_LIT + H_DIST];
	for (uint32 i = 0; i < H_LIT + H_DIST; i++)
		Huffman_BitLen_Trees[i] = 0;

	for (uint32 i = 0; i < H_LIT + H_DIST; i++)
	{
		uint32	decode_value = Trees.decode(bits);

		if (decode_value < 16)
		{
			Huffman_BitLen_Trees[i] = decode_value;
		}
		else
		{
			uint32	repeat_count = 0;
			uint8	repeat_data = 0;
			if (decode_value == 16)
			{
				repeat_count = bits.GetIncBits32(2) + 3;
				repeat_data = Huffman_BitLen_Trees[i - 1];
			}
			else if (decode_value == 17)
			{
				repeat_count = bits.GetIncBits32(3) + 3;
			}
			else if (decode_value == 18)
			{
				repeat_count = bits.GetIncBits32(7) + 11;
			}
			else
			{
				*DebugManager::Console << "\e[31mError: Invalid Huffman Decode\e[m\n";
				throw Exception_InvalidData("Huffman Decode: ", decode_value);
			}

			for (uint32 r = 0; r < repeat_count; r++)
			{
				Huffman_BitLen_Trees[i] = repeat_data;
				i++;
			}
			i--;
		}
	}

	return (Huffman_BitLen_Trees);
}



void	DEFLATE::Block_direct(BitStream & bits, ByteStream & data)
{
	//*DebugManager::Console << "\e[34mdirect Data ...\e[m\n";

	throw Exception_NotImplemented("direct Data Block", "");

	//*DebugManager::Console << "\e[34mdirect Data done\e[m\n";
	(void)bits;
	(void)data;
}
void	DEFLATE::Block_static(BitStream & bits, ByteStream & data)
{
	//*DebugManager::Console << "\e[34mstatic Huffman ...\e[m\n";

	throw Exception_NotImplemented("static Huffman Block", "");

	//*DebugManager::Console << "\e[34mstatic Huffman done\e[m\n";
	(void)bits;
	(void)data;
}
void	DEFLATE::Block_dynamic(BitStream & bits, ByteStream & data)
{
	//*DebugManager::Console << "\e[34mdynamic Huffman ...\e[m\n";

	uint32	H_LIT = bits.GetIncBits32(5) + 257;
	uint32	H_DIST = bits.GetIncBits32(5) + 1;
	uint32	H_CLEN = bits.GetIncBits32(4) + 4;
	//*DebugManager::Console << "Huffman:";
	//*DebugManager::Console << ' ' << H_LIT;
	//*DebugManager::Console << ' ' << H_DIST;
	//*DebugManager::Console << ' ' << H_CLEN;
	//*DebugManager::Console << '\n';
	//*DebugManager::Console << "H_LIT  : " << H_LIT  << "\n";
	//*DebugManager::Console << "H_DIST : " << H_DIST << "\n";
	//*DebugManager::Console << "H_CLEN : " << H_CLEN << "\n";

	uint8 * bitLens = DEFLATE::dynamic_Huffman(bits, H_LIT, H_DIST, H_CLEN);

	HuffmanTree	literal(&bitLens[0], H_LIT);
	HuffmanTree	distance(&bitLens[H_LIT], H_DIST);

	DEFLATE::decode_Huffman(bits, literal, distance, data);

	delete [] bitLens;

	//*DebugManager::Console << "\e[34mdynamic Huffman done\e[m\n";
}

void	DEFLATE::Blocks(BitStream & bits, ByteStream & data)
{
	uint8	BFINAL;
	uint8	BTYPE;

	uint32	BlockCount = 0;
	do
	{
		//*DebugManager::Console << "decoding ...  " << bits.get_ByteIndex() << "/" << bits.Len << "\n";
		//*DebugManager::Console << "decoding ...\n";

		BFINAL = bits.GetIncBits32(1);
		BTYPE = bits.GetIncBits32(2);
		//*DebugManager::Console << "[" << ToBase16(BlockCount) << "] ";
		//*DebugManager::Console << "Deflate Block: ";
		//if (BFINAL == 0) { *DebugManager::Console << "not final, "; }
		//else { *DebugManager::Console << "final, "; }
		//if (BTYPE == 0b00) { *DebugManager::Console << "direct."; }
		//else if (BTYPE == 0b01) { *DebugManager::Console << "static."; }
		//else if (BTYPE == 0b10) { *DebugManager::Console << "dynamic."; }
		//else { *DebugManager::Console << "Invalid."; }
		//*DebugManager::Console << '\n';

		if (BTYPE == 0b00)
		{
			Block_direct(bits, data);
		}
		else if (BTYPE == 0b01)
		{
			Block_static(bits, data);
		}
		else if (BTYPE == 0b10)
		{
			Block_dynamic(bits, data);
		}
		else
		{
			throw Exception_InvalidBlockType(BTYPE);
			*DebugManager::Console << "\e[31mError: Invalid Block Type\e[m\n";
		}
		//*DebugManager::Console << "\n";
		BlockCount++;
	}
	while (BFINAL == 0);
	//*DebugManager::Console << "decoding done " << bits.get_ByteIndex() << "/" << bits.Len << "\n";
	//*DebugManager::Console << "decoding done\n";
}





#include <sstream>
/*
	put this here so it dosent slow down compile of above stuff
	should probably put this in a seperate file
	but I want to make a BaseExceptin for these anyway
	that stores text
	this is just to make it compile for now
	also the headers here could use more foreward declate stuff
*/

DEFLATE::Exception_NotImplemented::Exception_NotImplemented(std::string head, std::string name)
{
	std::ostringstream ss("DEFLATE: not implemented: ");
	ss << head;
	ss << name;
	Text = ss.str();
}
const char * DEFLATE::Exception_NotImplemented::what() const noexcept
{
	return Text.c_str();
}

DEFLATE::Exception_InvalidBlockType::Exception_InvalidBlockType(uint32 type)
{
	std::ostringstream ss("DEFLATE: invalid Block Type: ");
	ss << type;
	Text = ss.str();
}
const char * DEFLATE::Exception_InvalidBlockType::what() const noexcept
{
	return Text.c_str();
}

DEFLATE::Exception_InvalidData::Exception_InvalidData(std::string head, uint32 value)
{
	std::ostringstream ss("DEFLATE: invalid Data: ");
	ss << head;
	ss << value;
	Text = ss.str();
}
const char * DEFLATE::Exception_InvalidData::what() const noexcept
{
	return Text.c_str();
}
