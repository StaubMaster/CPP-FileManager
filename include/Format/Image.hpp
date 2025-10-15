
#ifndef  IMAGE_HPP
# define IMAGE_HPP

# include "Parsing/uint.hpp"

class Image
{
	public:
		const uint32	W;
		const uint32	H;
		uint32	*Data32;
		uint8	*Data8;

	public:
		Image(uint32 w, uint32 h);
		~Image();

	public:
		void	setPixel(uint32 x, uint32 y, uint32 pxl);
		uint32	getPixel(uint32 x, uint32 y);

		Image * Scale(uint32 w, uint32 h);

	public:
		static Image * Missing();
};

#endif
