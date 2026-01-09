#include "FileFormat/PNG/PNG_IHDR.hpp"

#include <sstream>

#include <iostream>



IHDR::IHDR()
{
	
}
IHDR::IHDR(BitStream & bits)
{
	bits.MoveToNextByte();

	width = ReverseBytes(bits.GetIncBits32());
	height = ReverseBytes(bits.GetIncBits32());

	bit_depth = bits.GetIncBits8();
	color_type = bits.GetIncBits8();

	compression_method = bits.GetIncBits8();
	filter_method = bits.GetIncBits8();
	interlace_method = bits.GetIncBits8();
}
void	IHDR::ToString(std::ostream & os) const
{
	os << " width: " << width << "\n";
	os << "height: " << height << "\n";

	os << " bit_depth: " << (uint16)bit_depth << "\n";
	os << "color_type: " << (uint16)color_type << "\n";

	os << "compression_method: " << (uint16)compression_method << "\n";
	os << "     filter_method: " << (uint16)filter_method << "\n";
	os << "  interlace_method: " << (uint16)interlace_method << "\n";
}
