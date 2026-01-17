
#ifndef PNG_FILTER_HPP
# define PNG_FILTER_HPP

# include "FileParsing/ByteStream.hpp"

# include "PNG.hpp"

class	Image;

namespace PNG
{
namespace Filter
{
	static const uint8	rel_X = 0b01;
	static const uint8	rel_Y = 0b10;
	static const uint8	rel_XY = 0b11;

	struct PixelData
	{
		uint32	x;
		uint32	y;
		uint8	col;
		Image &	img;

		PixelData(Image & img);
	};

	uint8	getPixel(PixelData pxl, uint8 rel);

	void	filter_None(PixelData pxl, uint8 byte);
	void	filter_Sub(PixelData pxl, uint8 byte);
	void	filter_Up(PixelData pxl, uint8 byte);
	void	filter_Avg(PixelData pxl, uint8 byte);
	void	filter_Paeth(PixelData pxl, uint8 byte);

	void	filter(ByteStream & data, Image & img);
};
};

#endif
