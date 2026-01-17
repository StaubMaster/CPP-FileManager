#ifndef  PNG_IHDR_HPP
# define PNG_IHDR_HPP

# include "FileParsing/BitStream.hpp"
# include "ValueType/uint.hpp"

namespace PNG
{
struct IHDR
{
	uint32	width;
	uint32	height;

	uint8	bit_depth;
	uint8	color_type;

	uint8	compression_method;
	uint8	filter_method;
	uint8	interlace_method;

	IHDR();
	IHDR(BitStream & bits);

	void	ToConsole() const;
};
};

#endif