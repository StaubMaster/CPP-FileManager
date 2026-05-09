#include "Image.hpp"



bool	Image::Empty() const { return (_Data == 0); }
uint32	Image::W() const { return _Size.X; }
uint32	Image::H() const { return _Size.Y; }
VectorU2			Image::Size() const { return _Size; }
const void *	Image::Data() const { return _Data; }
LoopU2		Image::Loop() const { return LoopU2(VectorU2(), _Size); }
void *			Image::Data() { return _Data; }



ColorU4 & Image::Pixel(VectorU2 udx)
{
	return _Data[udx.X + udx.Y * _Size.X];
}
const ColorU4 & Image::Pixel(VectorU2 udx) const
{
	return _Data[udx.X + udx.Y * _Size.X];
}
ColorU4 & Image::Pixel(uint32 x, uint32 y)
{
	return _Data[x + y * _Size.X];
}
const ColorU4 & Image::Pixel(uint32 x, uint32 y) const
{
	return _Data[x + y * _Size.X];
}
uint8 & Image::Pixel(uint32 x, uint32 y, uint8 col)
{
	uint8 * data = (uint8*)&_Data[x + y * _Size.X];
	return data[col];
}
const uint8 & Image::Pixel(uint32 x, uint32 y, uint8 col) const
{
	const uint8 * data = (const uint8*)&_Data[x + y * _Size.X];
	return data[col];
}
ColorU4 & Image::Pixel(uint32 udx)
{
	return _Data[udx];
}
const ColorU4 & Image::Pixel(uint32 udx) const
{
	return _Data[udx];
}



Image::Image() :
	_Size(),
	_Data(NULL)
{ }
Image::Image(VectorU2 size) :
	_Size(size),
	_Data(new ColorU4[_Size.X * _Size.Y])
{ }
Image::Image(uint32 w, uint32 h) :
	_Size(w, h),
	_Data(new ColorU4[_Size.X * _Size.Y])
{ }
Image::~Image()
{ }

Image::Image(const Image & other) :
	_Size(other._Size),
	_Data(other._Data)
{ }
Image & Image::operator=(const Image & other)
{
	this -> Bind(other);
	return *this;
}



void Image::Init(VectorU2 size)
{
	Dispose();
	_Size = size;
	_Data = new ColorU4[_Size.X * _Size.Y];
}
void Image::Init(uint32 w, uint32 h)
{
	Dispose();
	_Size = VectorU2(w, h);
	_Data = new ColorU4[_Size.X * _Size.Y];
}
void Image::Dispose()
{
	_Size = VectorU2();
	delete[] _Data;
	_Data = NULL;
}



void Image::Bind(const Image & other)
{
	_Size = other._Size;
	_Data = other._Data;
}
void Image::Copy(const Image & other)
{
	_Size = other._Size;
	_Data = new ColorU4[_Size.X * _Size.X];
	unsigned int size = _Size.X * _Size.X;
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



void Image::Scale(VectorU2 size)
{
	Image img = Scaled(size);
	Dispose();
	Bind(img);
}
Image Image::Scaled(VectorU2 size) const
{
	Image img(size);

	VectorU2	scaled;
	uint32	idx_old;
	uint32	idx_new;
	for (uint32 y = 0; y < size.Y; y++)
	{
		scaled.Y = (((float)y) / ((float)size.Y)) * ((float)_Size.Y);

		for (uint32 x = 0; x < size.X; x++)
		{
			scaled.X = (((float)x) / ((float)size.X)) * ((float)_Size.X);

			idx_old = (scaled.X + scaled.Y * _Size.X);
			idx_new = (x + y * size.X);

			img._Data[idx_new] = _Data[idx_old];
			//img -> Data8[idx_new + 0] = Data8[idx_old + 0];
			//img -> Data8[idx_new + 1] = Data8[idx_old + 1];
			//img -> Data8[idx_new + 2] = Data8[idx_old + 2];
			//img -> Data8[idx_new + 3] = Data8[idx_old + 3];
		}
	}

	return img;
}



Image Image::Missing(VectorU2 size)
{
	Image img(size);

	for (uint32 y = 0; y < size.Y; y++)
	{
		for (uint32 x = 0; x < size.X; x++)
		{
			ColorU4 col;
			if ((x & 1) == (y & 1))
				col = ColorU4(0x00, 0x00, 0x00);
			else
				col = ColorU4(0xFF, 0x00, 0xFF);
			img.Pixel(x, y) = col;
			//uint32 pxl;
			//if ((x & 1) == (y & 1))
			//	pxl = 0x000000FF;
			//else
			//	pxl = 0xFF00FFFF;
			//img -> Pixel(x, y) = pxl;
			//img -> setPixelRGBA(x, y, pxl);
		}
	}

	return img;
}
