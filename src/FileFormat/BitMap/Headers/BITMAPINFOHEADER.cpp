#include "FileFormat/BitMap/Headers/BITMAPINFOHEADER.hpp"

#include <iostream>



BitMap::BITMAPINFOHEADER::BITMAPINFOHEADER(ByteStreamGetter & stream)
{
	ImageSizeW = stream.Get4();
	ImageSizeH = stream.Get4();
	NumberOfColorPlanes = stream.Get2();
	NumberOfBitsPerPixel = stream.Get2();
	Compression = stream.Get4();
	ImageDataSize = stream.Get4();
	HoriPixelPerMetre = stream.Get4();
	VertPixelPerMetre = stream.Get4();
	NumberOfColorsInPallet = stream.Get4();
	NumberOfImportantColors = stream.Get4();
}

void BitMap::BITMAPINFOHEADER::Show() const
{
	std::cout << "\nBITMAPINFOHEADER\n";
	std::cout << "ImageSizeW" << ' ' << ImageSizeW << '\n';
	std::cout << "ImageSizeH" << ' ' << ImageSizeH << '\n';
	std::cout << "NumberOfColorPlanes" << ' ' << NumberOfColorPlanes << '\n';
	std::cout << "NumberOfBitsPerPixel" << ' ' << NumberOfBitsPerPixel << '\n';
	std::cout << "Compression" << ' ' << Compression << '\n';
	std::cout << "ImageDataSize" << ' ' << ImageDataSize << '\n';
	std::cout << "HoriPixelPerMetre" << ' ' << HoriPixelPerMetre << '\n';
	std::cout << "VertPixelPerMetre" << ' ' << VertPixelPerMetre << '\n';
	std::cout << "NumberOfColorsInPallet" << ' ' << NumberOfColorsInPallet << '\n';
	std::cout << "NumberOfImportantColors" << ' ' << NumberOfImportantColors << '\n';
	std::cout << '\n';
}

bool BitMap::BITMAPINFOHEADER::Parse(ByteStreamGetter & stream, Image & img, uint32 & data_size)
{
	BITMAPINFOHEADER header(stream);
	//header.Show();

	bool ret = false;
	if (header.NumberOfColorPlanes != 1)		{ std::cout << "BITMAPINFOHEADER: Unimplemented: NumberOfColorPlanes " << header.NumberOfColorPlanes << ".\n"; ret = true; }
	if (header.NumberOfBitsPerPixel != 24)		{ std::cout << "BITMAPINFOHEADER: Unimplemented: NumberOfBitsPerPixel " << header.NumberOfBitsPerPixel << ".\n"; ret = true; }
	if (header.Compression != 0)				{ std::cout << "BITMAPINFOHEADER: Unimplemented: Compression " << header.Compression << ".\n"; ret = true; }
	if (header.NumberOfColorsInPallet != 0)		{ std::cout << "BITMAPINFOHEADER: Unimplemented: NumberOfColorsInPallet " << header.NumberOfColorsInPallet << ".\n"; ret = true; }
	if (header.NumberOfImportantColors != 0)	{ std::cout << "BITMAPINFOHEADER: Unimplemented: NumberOfImportantColors " << header.NumberOfImportantColors << ".\n"; ret = true; }

	img.Init(header.ImageSizeW, header.ImageSizeH);
	data_size = header.ImageDataSize;
	return ret;
}
