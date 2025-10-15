
#ifndef  PNG_IHDR_HPP
# define PNG_IHDR_HPP

# include "../../Parsing/BitStream.hpp"
# include "../../Parsing/uint.hpp"

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

			void	ToString(std::ostream & os) const;
		};

#endif
