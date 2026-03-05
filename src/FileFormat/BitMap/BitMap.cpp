#include "FileFormat/BitMap/BitMap.hpp"
#include "FileFormat/BitMap/Headers/BITMAPINFOHEADER.hpp"

#include "FileParsing/ByteBlock.hpp"
#include "FileParsing/ByteStreamGetter.hpp"
#include "ValueType/uint.hpp"

#include <iostream>



void LoadRGB(ByteStreamGetter & stream, Image & img, uint32 data_size)
{
	ColorU4 col;
	col.A = 0xFF;
	for (uint32 u = 0; u < data_size; u++)
	{
		col.B = stream.Get1();
		col.G = stream.Get1();
		col.R = stream.Get1();
		img.Pixel(u) = col;
	}
}



Image BitMap::Load(const FileInfo & file)
{
	std::string file_text = file.LoadText();
	ByteBlock file_data(file_text);
	Image img;

	ByteStreamGetter stream(file_data);

	{
		uint16 signature = stream.Get2();
		if (signature != 0x4D42)
		{
			std::cout << "LoadBitMap: Error: Bad Signature.\n";
			return img;
		}
		uint32 file_size = stream.Get4();
		(void)file_size;
		stream.Move(2); // Reserved
		stream.Move(2); // Reserved
	}

	uint32 data_offset = stream.Get4();
	uint32 data_size;
	bool ret = false; // replace with Exception
	uint32 header_size = stream.Get4();
	switch (header_size)
	{
		case 40:
			ret = BITMAPINFOHEADER::Parse(stream, img, data_size);
			break;
		default:
			std::cout << "LoadBitMap: Error: Unknown Header Size.\n";
			return img;
	}
	if (ret) { return img; }

	stream.Index = data_offset;
	// data_size / 3 depends on BitsPerPixel being 24
	LoadRGB(stream, img, data_size / 3);

	return img;
}



//void SaveBitMap(const FileInfo & file, Image & img)