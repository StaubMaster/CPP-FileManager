#include "FileFormat/PNG/PNG.hpp"
#include "FileFormat/PNG/IHDR.hpp"
#include "FileFormat/PNG/Filter.hpp"
#include "FileFormat/PNG/Chunk.hpp"
#include "FileFormat/PNG/ZLIB.hpp"
#include "FileFormat/PNG/Huffman.hpp"
#include "FileFormat/PNG/DEFLATE.hpp"

#include "FileParsing/DebugManager.hpp"

#include "FileParsing/ByteBlock.hpp"
#include "FileParsing/ByteStreamGetter.hpp"
#include "FileParsing/ByteStreamSetter.hpp"
#include "FileParsing/ByteStreamQueue.hpp"

#include <iostream>
#include <fstream>
#include <sstream>



Image PNG::Load(const FileInfo & file, bool debug)
{
	if (debug) { DebugManager::ChangeConsoleToCOut(); }
	else { DebugManager::ChangeConsoleToDump(); }

	Image img;
	try
	{
		ByteBlock ChunkData(file.LoadBytes());
		ByteStreamGetter ChunkStream(ChunkData);

		{
			uint64 signature_received = ChunkStream.Get8();
			if (signature_received != 0x0A1A0A0D474E5089)
			{
				throw PNG_Exception_Signature();
			}
		}

		IHDR ImageHeader;
		ByteBlock CompressedData;

		while (1)
		{
			Chunk chunk(ChunkStream);
			if (chunk.CheckCRC())
			{
				if      (chunk.CheckType("IEND"))	{ break; }
				else if (chunk.CheckType("IHDR"))	{ chunk.Parse_IHDR(ImageHeader); }
				else if (chunk.CheckType("IDAT"))	{ chunk.Parse_IDAT(CompressedData); }
				else if (chunk.CheckType("tEXt"))	{ chunk.Parse_tEXt(); }
				else
				{
					std::cout << "PNG: Chunk: Unknown Type: " << uint_Chr(chunk.Type) << '\n';
				}
			}
			else
			{
				//Throw an Error
				std::cout << "PNG: Chunk: Invalid CRC Value\n";
				//break;
			}
		}
		ChunkData.Dispose();

		ByteStreamGetter CompressedStream(CompressedData);

		// calculate how much is needed
		ByteBlock UncompressedData(0xFFFFFFFF);
		ByteStreamQueue UncompressedStream(UncompressedData);

		ZLIB::decompress(CompressedStream, UncompressedStream);
		CompressedData.Dispose();

		img.Init(ImageHeader.width, ImageHeader.height);
		PNG::Filter::filter(ImageHeader, UncompressedStream, img);
		UncompressedData.Dispose();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception while loading Image: " << e.what() << "\n";
		img.Dispose();
	}
	return (img);
}



const char * PNG::PNG_Exception_Signature::what() const throw() { return "Bad Signature"; }
