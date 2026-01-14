#include "FileFormat/PNG/PNG.hpp"
#include "FileFormat/PNG/PNG_IHDR.hpp"
#include "FileFormat/PNG/Chunk.hpp"
#include "FileFormat/PNG/ZLIB.hpp"
#include "FileFormat/PNG/Huffman.hpp"
#include "FileFormat/PNG/DEFLATE.hpp"
#include "FileFormat/PNG/PNG_Filter.hpp"

#include "FileParsing/ByteStream.hpp"
#include "FileParsing/DebugManager.hpp"

#include <iostream>
#include <fstream>
#include <sstream>



Image PNG::Load(const FileInfo & file, bool debug)
{
	(void)debug;
	DebugManager::SetOut(false);
	std::ostream & os = DebugManager::GetOut();
	Image img;

	try
	{
		os << "loading '" << file.Path.ToString() << "' ...\n";
		std::string file_str = file.LoadText();

		os << "file length: " << file_str.size() << "\n";
		BitStream file(file_str);

		os << "\n";
		{
			uint64	signature_template = 0x0A1A0A0D474E5089;
			//	89
			//	50 4E 47
			//	0D 0A 1A 0A
			uint64	signature_received;

			signature_received = file.GetIncBits64();
			os << "signature\n";
			os << "template: " << ToBase16(signature_template) << "\n";
			os << "received: " << ToBase16(signature_received) << "\n";

			if (signature_received != signature_template)
			{
				throw PNG_Exception_Signature();
			}
		}
		os << "\n";

		IHDR imageHead;
		ByteStream imageData(0);

		while (1)
		{
			os << "\n";
			Chunk chunk(file);
			BitStream chunk_stream = chunk.ToBitStream();
			os << chunk.ToString();
			os << "\n";
			if (chunk.CheckType("IEND"))
			{
				break;
			}
			else if (chunk.CheckType("IHDR"))
			{
				imageHead = IHDR(chunk_stream);
				imageHead.ToString(os);
			}
			else if (chunk.CheckType("IDAT"))
			{
				imageData.Concatenation(chunk_stream.Data, chunk_stream.Len);
			}
			else
			{
				std::cout << "PNG Unknown Type: " << uint_Chr(chunk.Type) << '\n';
			}
		}

		BitStream bits(imageData.Data, imageData.Len);

		ByteStream * data = new ByteStream(0xFFFFFFFF);
		ZLIB::decompress(bits, *data);

		img.Init(imageHead.width, imageHead.height);
		PNG_Filter::filter(*data, img);
		delete data;

		return (img);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception while loading Image: " << e.what() << "\n";
		img.Dispose();
	}
	return (img);
}



const char * PNG::PNG_Exception_Signature::what() const throw() { return "Bad Signature"; }
