#ifndef  BITMAP_BITMAPINFOHEADER_HPP
# define BITMAP_BITMAPINFOHEADER_HPP

# include "FileParsing/ByteStreamGetter.hpp"
# include "ValueType/uint.hpp"
# include "Image.hpp"

namespace BitMap
{
struct BITMAPINFOHEADER
{
	uint32 ImageSizeW;
	uint32 ImageSizeH;
	uint16 NumberOfColorPlanes; // must be 1
	uint16 NumberOfBitsPerPixel;
	uint32 Compression;
	uint32 ImageDataSize;
	int HoriPixelPerMetre;
	int VertPixelPerMetre;
	uint32 NumberOfColorsInPallet;
	uint32 NumberOfImportantColors;

	BITMAPINFOHEADER(ByteStreamGetter & stream);

	void Show() const;

	static bool Parse(ByteStreamGetter & stream, Image & img, uint32 & data_size);
};
};

#endif