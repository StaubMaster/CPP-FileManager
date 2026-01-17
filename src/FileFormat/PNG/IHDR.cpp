#include "FileFormat/PNG/IHDR.hpp"
#include "FileParsing/DebugManager.hpp"

#include <sstream>

#include <iostream>



PNG::IHDR::IHDR()
{ }
PNG::IHDR::IHDR(BitStream & bits)
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



void PNG::IHDR::ToConsole() const
{
	*DebugManager::Console << " width: " << width << "\n";
	*DebugManager::Console << "height: " << height << "\n";

	*DebugManager::Console << " bit_depth: " << (uint16)bit_depth << "\n";
	*DebugManager::Console << "color_type: " << (uint16)color_type << "\n";

	*DebugManager::Console << "compression_method: " << (uint16)compression_method << "\n";
	*DebugManager::Console << "     filter_method: " << (uint16)filter_method << "\n";
	*DebugManager::Console << "  interlace_method: " << (uint16)interlace_method << "\n";
}
