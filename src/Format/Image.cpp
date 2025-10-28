#include "Format/Image.hpp"



Image::Image(uint32 w, uint32 h) :
	W(w), H(h)
{
	Data32 = new uint32[W * H];
	Data8 = (uint8*)Data32;
}
Image::~Image()
{
	delete [] Data32;
}



void	Image::setPixel(uint32 x, uint32 y, uint32 pxl)
{
	Data32[x + y * W] = pxl;
}
uint32	Image::getPixel(uint32 x, uint32 y) const
{
	return Data32[x + y * W];
}



Image * Image::Scale(uint32 w, uint32 h) const
{
	Image * img = new Image(w, h);

	uint32	scale_x;
	uint32	scale_y;
	uint32	idx_old;
	uint32	idx_new;
	for (uint32 y = 0; y < h; y++)
	{
		scale_y = (((float)y) / ((float)h)) * ((float)H);

		for (uint32 x = 0; x < w; x++)
		{
			scale_x = (((float)x) / ((float)w)) * ((float)W);

			idx_old = (scale_x + scale_y * W);
			idx_new = (x + y * w);

			img -> Data32[idx_new] = Data32[idx_old];
			//img -> Data8[idx_new + 0] = Data8[idx_old + 0];
			//img -> Data8[idx_new + 1] = Data8[idx_old + 1];
			//img -> Data8[idx_new + 2] = Data8[idx_old + 2];
			//img -> Data8[idx_new + 3] = Data8[idx_old + 3];
		}
	}

	return img;
}





Image * Image::Missing()
{
	Image * img = new Image(8, 4);

	for (uint32 y = 0; y < 4; y++)
	{
		for (uint32 x = 0; x < 8; x++)
		{
			uint32 pxl;
			if ((x & 1) == (y & 1))
				pxl = 0x000000FF;
			else
				pxl = 0xFF00FFFF;
			img -> setPixel(x, y, pxl);
			//img -> setPixelRGBA(x, y, pxl);
		}
	}

	return (img);
}