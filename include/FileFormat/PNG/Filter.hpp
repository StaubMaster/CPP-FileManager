
#ifndef PNG_FILTER_HPP
# define PNG_FILTER_HPP

# include "FileParsing/ByteStream.hpp"
# include "IHDR.hpp"
# include "ValueType/Undex2D.hpp"
# include "PNG.hpp"

class	Image;

namespace PNG
{
namespace Filter
{
	static const uint8	rel_X = 0b01;
	static const uint8	rel_Y = 0b10;
	static const uint8	rel_XY = 0b11;

	uint8	getPixel(Image & img, Undex2D pxl, uint8 col, uint8 rel);

	void	filter_None(Image & img, Undex2D pxl, uint8 col, uint8 byte);
	void	filter_Sub(Image & img, Undex2D pxl, uint8 col, uint8 byte);
	void	filter_Up(Image & img, Undex2D pxl, uint8 col, uint8 byte);
	void	filter_Avg(Image & img, Undex2D pxl, uint8 col, uint8 byte);
	void	filter_Paeth(Image & img, Undex2D pxl, uint8 col, uint8 byte);

	void	filter(IHDR head, ByteStream & data, Image & img);
};
};

#endif
