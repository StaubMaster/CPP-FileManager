#include "Format/Image.hpp"



uint32	Image::W() const { return _W; }
uint32	Image::H() const { return _H; }
const void *	Image::Data() const { return _Data; }



ColorU4 & Image::Pixel(uint32 x, uint32 y)
{
	return _Data[x + y * _W];
}
const ColorU4 & Image::Pixel(uint32 x, uint32 y) const
{
	return _Data[x + y * _W];
}
uint8 & Image::Pixel(uint32 x, uint32 y, uint8 col)
{
	uint8 * data = (uint8*)&_Data[x + y * _W];
	return data[col];
}
const uint8 & Image::Pixel(uint32 x, uint32 y, uint8 col) const
{
	const uint8 * data = (const uint8*)&_Data[x + y * _W];
	return data[col];
}



Image::Image() :
	_W(0),
	_H(0),
	_Data(nullptr)
{ }
Image::Image(uint32 w, uint32 h) :
	_W(w),
	_H(h),
	_Data(new ColorU4[_W * _H])
{ }
Image::~Image()
{
	//delete [] _Data;
}

Image::Image(const Image & other) :
	_W(other._W),
	_H(other._H),
	_Data(other._Data)
{ }
Image & Image::operator=(const Image & other)
{
	this -> Bind(other);
	return *this;
}



void Image::Dispose()
{
	delete[] _Data;
}



void Image::Bind(const Image & other)
{
	delete[] _Data;
	_W = other._W;
	_H = other._H;
	_Data = other._Data;
}
void Image::Copy(const Image & other)
{
	delete[] _Data;
	_W = other._W;
	_H = other._H;
	_Data = new ColorU4[_W * _H];
	unsigned int size = _W * _H;
	for (unsigned int i = 0; i < size; i++)
	{
		_Data[i] = other._Data[i];
	}
}
Image Image::Bind()
{
	Image img;
	img.Bind(*this);
	return img;
}
Image Image::Copy()
{
	Image img;
	img.Copy(*this);
	return img;
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
		scale_y = (((float)y) / ((float)h)) * ((float)_H);

		for (uint32 x = 0; x < w; x++)
		{
			scale_x = (((float)x) / ((float)w)) * ((float)_W);

			idx_old = (scale_x + scale_y * _W);
			idx_new = (x + y * w);

			img -> _Data[idx_new] = _Data[idx_old];
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
			img -> Pixel(x, y) = pxl;
			//img -> setPixelRGBA(x, y, pxl);
		}
	}

	return (img);
}