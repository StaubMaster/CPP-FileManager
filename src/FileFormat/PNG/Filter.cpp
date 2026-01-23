#include "FileFormat/PNG/Filter.hpp"



/*PNG::Filter::PixelData::PixelData(Image & img) :
	img(img)
{ }*/

/*uint32	PNG::Filter::PixelIndex(PixelData pxl)
{
	return (((pxl.img.W() * pxl.y + pxl.x) * 4) + pxl.col);
}*/

uint8	PNG::Filter::getPixel(Image & img, Undex2D pxl, uint8 col, uint8 rel)
{
	if ((rel & rel_X) != 0)
	{
		if (pxl.X == 0)
			return (0);
		pxl.X--;
	}

	if ((rel & rel_Y) != 0)
	{
		if (pxl.Y == 0)
			return (0);
		pxl.Y--;
	}

	return (img.Pixel(pxl.X, pxl.Y, col));
}

void	PNG::Filter::filter_None(Image & img, Undex2D pxl, uint8 col, uint8 byte)
{
	img.Pixel(pxl.X, pxl.Y, col) = byte;
}
void	PNG::Filter::filter_Sub(Image & img, Undex2D pxl, uint8 col, uint8 byte)
{
	uint8	a = getPixel(img, pxl, col, rel_X);
	img.Pixel(pxl.X, pxl.Y, col) = byte + a;
}
void	PNG::Filter::filter_Up(Image & img, Undex2D pxl, uint8 col, uint8 byte)
{
	uint8	b = getPixel(img, pxl, col, rel_Y);
	img.Pixel(pxl.X, pxl.Y, col) = byte + b;
}
void	PNG::Filter::filter_Avg(Image & img, Undex2D pxl, uint8 col, uint8 byte)
{
	uint8	a = getPixel(img, pxl, col, rel_X);
	uint8	b = getPixel(img, pxl, col, rel_Y);
	img.Pixel(pxl.X, pxl.Y, col) = byte + ((a + b) >> 1);
}
void	PNG::Filter::filter_Paeth(Image & img, Undex2D pxl, uint8 col, uint8 byte)
{
	uint8	a = getPixel(img, pxl, col, rel_X);
	uint8	b = getPixel(img, pxl, col, rel_Y);
	uint8	c = getPixel(img, pxl, col, rel_XY);

	int	p = (a + b) - c;
	int diff_a = abs(p - a);
	int diff_b = abs(p - b);
	int diff_c = abs(p - c);

	if (diff_a <= diff_b && diff_a <= diff_c)	{ img.Pixel(pxl.X, pxl.Y, col) = byte + a; }
	else if (diff_b <= diff_c)					{ img.Pixel(pxl.X, pxl.Y, col) = byte + b; }
	else										{ img.Pixel(pxl.X, pxl.Y, col) = byte + c; }
}

void	PNG::Filter::filter(IHDR head, ByteStream & data, Image & img)
{
	void (*filterFunc)(Image &, Undex2D, uint8, uint8);

	data.Index = 0;

	uint8	data_byte;
	Undex2D	pxl;
	for (pxl.Y = 0; pxl.Y < img.H(); pxl.Y++)
	{
		data_byte = data.Get();
		data.Next();

		if (data_byte == 0)      { filterFunc = &filter_None; }
		else if (data_byte == 1) { filterFunc = &filter_Sub; }
		else if (data_byte == 2) { filterFunc = &filter_Up; }
		else if (data_byte == 3) { filterFunc = &filter_Avg; }
		else if (data_byte == 4) { filterFunc = &filter_Paeth; }

		for (pxl.X = 0; pxl.X < img.W(); pxl.X++)
		{
			if (head.color_type == 2)
			{
				filterFunc(img, pxl, 0, data.Get());	data.Next();
				filterFunc(img, pxl, 1, data.Get());	data.Next();
				filterFunc(img, pxl, 2, data.Get());	data.Next();
				img.Pixel(pxl.X, pxl.Y, 3) = 0xFF;
			}
			if (head.color_type == 6)
			{
				filterFunc(img, pxl, 0, data.Get());	data.Next();
				filterFunc(img, pxl, 1, data.Get());	data.Next();
				filterFunc(img, pxl, 2, data.Get());	data.Next();
				filterFunc(img, pxl, 3, data.Get());	data.Next();
			}
		}
	}
}
