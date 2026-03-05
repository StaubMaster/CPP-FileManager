#include "FileFormat/BitMap/BitMap.hpp"
#include "FileFormat/BitMap/Headers/BITMAPINFOHEADER.hpp"

#include "FileParsing/ByteBlock.hpp"
#include "FileParsing/ByteStreamGetter.hpp"
#include "FileParsing/ByteStreamSetter.hpp"
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
void SaveRGB(ByteStreamSetter & stream, const Image & img, uint32 data_size)
{
	ColorU4 col;
	for (uint32 u = 0; u < data_size; u++)
	{
		col = img.Pixel(u);
		stream.Set1(col.B);
		stream.Set1(col.G);
		stream.Set1(col.R);
	}

}



Image BitMap::Load(const FileInfo & file)
{
	ByteStreamGetter stream(file.LoadBytes());

	Image img;
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



void BitMap::Save(const FileInfo & file, const Image & img)
{
	ByteStreamSetter stream(img.W() * img.H() * 3 * 2);
	// too lazy to figure out the exact size right now
	// make sure to not save empty space at the end of the file
	// but that shouldnt effect anything anyway

	uint64 file_size_idx;
	{
		stream.Set2(0x4D42);
		file_size_idx = stream.Index;
		stream.Move(4);
		stream.Move(2); // Reserved
		stream.Move(2); // Reserved
	}

	uint64 data_offset_idx = stream.Index;
	stream.Move(4);

	stream.Set4(40);
	BITMAPINFOHEADER header(img);
	header.Put(stream);

	uint32 data_size = img.W() * img.H() * 3;
	stream.Set4(data_offset_idx, stream.Index);

	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	SaveRGB(stream, img, data_size);
	std::cout << __FILE__ << ':' << __LINE__ << '\n';

	stream.Set4(file_size_idx, stream.Index);

	std::cout << __FILE__ << ':' << __LINE__ << '\n';
	file.SaveBytes(stream.Block);
	std::cout << __FILE__ << ':' << __LINE__ << '\n';
}
