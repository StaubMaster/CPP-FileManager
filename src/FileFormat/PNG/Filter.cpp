#include "FileFormat/PNG/Filter.hpp"



PNG::Filter::PixelData::PixelData(Image & img) :
	img(img)
{ }

/*uint32	PNG::Filter::PixelIndex(PixelData pxl)
{
	return (((pxl.img.W() * pxl.y + pxl.x) * 4) + pxl.col);
}*/

uint8	PNG::Filter::getPixel(PixelData pxl, uint8 rel)
{
	if ((rel & rel_X) != 0)
	{
		if (pxl.x == 0)
			return (0);
		pxl.x--;
	}

	if ((rel & rel_Y) != 0)
	{
		if (pxl.y == 0)
			return (0);
		pxl.y--;
	}

	return (pxl.img.Pixel(pxl.x, pxl.y, pxl.col));
}

void	PNG::Filter::filter_None(PixelData pxl, uint8 byte)
{
	pxl.img.Pixel(pxl.x, pxl.y, pxl.col) = byte;
}
void	PNG::Filter::filter_Sub(PixelData pxl, uint8 byte)
{
	uint8	a = getPixel(pxl, rel_X);
	pxl.img.Pixel(pxl.x, pxl.y, pxl.col) = byte + a;
}
void	PNG::Filter::filter_Up(PixelData pxl, uint8 byte)
{
	uint8	b = getPixel(pxl, rel_Y);
	pxl.img.Pixel(pxl.x, pxl.y, pxl.col) = byte + b;
}
void	PNG::Filter::filter_Avg(PixelData pxl, uint8 byte)
{
	uint8	a = getPixel(pxl, rel_X);
	uint8	b = getPixel(pxl, rel_Y);
	pxl.img.Pixel(pxl.x, pxl.y, pxl.col) = byte + ((a + b) >> 1);
}
void	PNG::Filter::filter_Paeth(PixelData pxl, uint8 byte)
{
	uint8	a = getPixel(pxl, rel_X);
	uint8	b = getPixel(pxl, rel_Y);
	uint8	c = getPixel(pxl, rel_XY);

	int	p = (a + b) - c;
	int diff_a = abs(p - a);
	int diff_b = abs(p - b);
	int diff_c = abs(p - c);

	if (diff_a <= diff_b && diff_a <= diff_c)
		pxl.img.Pixel(pxl.x, pxl.y, pxl.col) = byte + a;
	else if (diff_b <= diff_c)
		pxl.img.Pixel(pxl.x, pxl.y, pxl.col) = byte + b;
	else
		pxl.img.Pixel(pxl.x, pxl.y, pxl.col) = byte + c;
}

void	PNG::Filter::filter(ByteStream & data, Image & img)
{
	PixelData pxl(img);
	void (*filterFunc)(PixelData, uint8);

	data.Index = 0;

	uint8	data_byte;
	for (pxl.y = 0; pxl.y < img.H(); pxl.y++)
	{
		data_byte = data.Get();
		data.Next();
		if (data_byte == 0)
			filterFunc = &filter_None;
		else if (data_byte == 1)
			filterFunc = &filter_Sub;
		else if (data_byte == 2)
			filterFunc = &filter_Up;
		else if (data_byte == 3)
			filterFunc = &filter_Avg;
		else if (data_byte == 4)
			filterFunc = &filter_Paeth;

		for (pxl.x = 0; pxl.x < img.W(); pxl.x++)
		{
			pxl.col = 0;
			data_byte = data.Get();
			data.Next();
			filterFunc(pxl, data_byte);

			pxl.col = 1;
			data_byte = data.Get();
			data.Next();
			filterFunc(pxl, data_byte);

			pxl.col = 2;
			data_byte = data.Get();
			data.Next();
			filterFunc(pxl, data_byte);

			pxl.col = 3;
			//	color_type = 6
			data_byte = data.Get();
			data.Next();
			filterFunc(pxl, data_byte);

			//	color_type = 2
			//img.data[PixelIndex(pxl)] = 0xFF;
		}
	}
}
