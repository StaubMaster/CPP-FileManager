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

//#include <chrono>



static void Parse_Chunk_tEXt(const Chunk & chunk)
{
	uint32 text_data_idx = 0;
	const char * text_key = (const char *)chunk.Data + text_data_idx;
	uint32 text_key_len = 0;
	while ((text_key[text_key_len] != '\0') && (text_data_idx < chunk.Length))
	{
		text_key_len++;
		text_data_idx++;
	}

	text_data_idx++;
	const char * text_value = (const char *)chunk.Data + text_data_idx;
	uint32 text_value_len = 0;
	while ((text_value[text_value_len] != '\0') && (text_data_idx < chunk.Length))
	{
		text_key_len++;
		text_data_idx++;
	}

	*DebugManager::Console << "Text";
	*DebugManager::Console << " [" << text_key_len << "|" << text_value_len << "] ";
	*DebugManager::Console << "\"" << text_key << "\" \"" << text_value << "\"";
	*DebugManager::Console << " " << text_data_idx << " | " << chunk.Length;
	*DebugManager::Console << '\n';
}



Image PNG::Load(const FileInfo & file, bool debug)
{
	if (debug) { DebugManager::ChangeConsoleToCOut(); }
	else { DebugManager::ChangeConsoleToDump(); }

	//std::chrono::time_point<std::chrono::high_resolution_clock> timeBase = std::chrono::high_resolution_clock::now();
	//std::chrono::nanoseconds time;

	Image img;
	try
	{
		//time = std::chrono::high_resolution_clock::now() - timeBase;
		//std::cout << "\ntime: " << (time.count() / 1000000000.0f) << '\n';
		*DebugManager::Console << "loading '" << file.Path.ToString() << "' ...\n";

		ByteStreamGetter file_data_stream(file.LoadBytes());
		//*DebugManager::Console << "file length: " << file_str.size() << "\n";

		*DebugManager::Console << "\n";
		{
			uint64	signature_template = 0x0A1A0A0D474E5089;
			//	89
			//	50 4E 47
			//	0D 0A 1A 0A
			uint64	signature_received;

			signature_received = file_data_stream.Get8();
			*DebugManager::Console << "signature\n";
			*DebugManager::Console << "template: " << ToBase16(signature_template) << "\n";
			*DebugManager::Console << "received: " << ToBase16(signature_received) << "\n";

			if (signature_received != signature_template)
			{
				throw PNG_Exception_Signature();
			}
		}
		*DebugManager::Console << "\n";

		IHDR ImageHeader;
		ByteBlock CompressedImageData;

		//time = std::chrono::high_resolution_clock::now() - timeBase;
		//std::cout << "\ntime: " << (time.count() / 1000000000.0f) << '\n';
		*DebugManager::Console << "PNG: Assambling Data ...\n";

		uint32 ChunkCount = 0;
		while (1)
		{
			Chunk chunk(file_data_stream);

			if (!chunk.CheckCRC())
			{
				//Throw an Error
				std::cout << "PNG Chunk: Bad CRC Value\n";
				break;
			}

			//*DebugManager::Console << "[" << ToBase16(ChunkCount) << "] ";
			//chunk.ToConsole();

			if (chunk.CheckType("IEND"))
			{
				break;
			}
			else if (chunk.CheckType("IHDR"))
			{
				ByteStreamGetter block_getter(chunk.ToBlock());
				ImageHeader = IHDR(block_getter);
				ImageHeader.ToConsole();
			}
			else if (chunk.CheckType("IDAT"))
			{
				CompressedImageData.Concatenation(chunk.ToBlock());
			}
			else if (chunk.CheckType("tEXt"))
			{
				Parse_Chunk_tEXt(chunk);
			}
			else
			{
				*DebugManager::Console << "PNG Chunk: Unknown Type: " << uint_Chr(chunk.Type) << '\n';
			}
			ChunkCount++;
		}
		file_data_stream.Block.Dispose();

		//time = std::chrono::high_resolution_clock::now() - timeBase;
		//std::cout << "\ntime: " << (time.count() / 1000000000.0f) << '\n';
		*DebugManager::Console << "PNG: Decompressing Data Init ...\n";

		ByteStreamGetter bits(CompressedImageData);

		// calculate how much is needed
		ByteBlock UncompressedImageData(0xFFFFFFFF);
		ByteStreamQueue UncompressedImageDataQueue(UncompressedImageData);

		//time = std::chrono::high_resolution_clock::now() - timeBase;
		//std::cout << "\ntime: " << (time.count() / 1000000000.0f) << '\n';
		*DebugManager::Console << "PNG: Decompressing Data ...\n";

		ZLIB::decompress(bits, UncompressedImageDataQueue);
		CompressedImageData.Dispose();

		//time = std::chrono::high_resolution_clock::now() - timeBase;
		//std::cout << "\ntime: " << (time.count() / 1000000000.0f) << '\n';
		*DebugManager::Console << "PNG: Filtering Data ...\n";

		img.Init(ImageHeader.width, ImageHeader.height);
		PNG::Filter::filter(ImageHeader, UncompressedImageDataQueue, img);

		UncompressedImageData.Dispose();

		//time = std::chrono::high_resolution_clock::now() - timeBase;
		//std::cout << "\ntime: " << (time.count() / 1000000000.0f) << '\n';
		*DebugManager::Console << "PNG: done\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception while loading Image: " << e.what() << "\n";
		img.Dispose();
	}
	return (img);
}



const char * PNG::PNG_Exception_Signature::what() const throw() { return "Bad Signature"; }
