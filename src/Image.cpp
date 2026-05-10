#include "Image.hpp"
#include <iostream>


/*
void Image::mForget()
{
	if (_Know != nullptr)
	{
		(*_Know)--;
	}
	_Data = nullptr;
	_Know = nullptr;
	_Size = 0;
}
void Image::mDelete()
{
	if (_Know != nullptr)
	{
		if ((*_Know) == 0)
		{
			std::cout << "Image: delete[] " << _Data << '\n';
			delete _Know;
			delete[] _Data;
		}
	}
}
void Image::mNew(VectorU2 size)
{
	_Data = new ColorU4[size.Product()];
	_Know = new uint64; (*_Know) = 0;
	_Size = size;
	std::cout << "Image: new[] " << _Data << '\n';
}
void Image::mBind(const Image & other)
{
	mDelete();
	_Size = other._Size;
	_Know = other._Know;
	_Data = other._Data;
	if (_Know != nullptr) { (*_Know)++; }
}
*/

/*
bool			Image::Empty() const { return (_Data == nullptr); }
uint32			Image::W() const { return Pixels.LengthX(); }
uint32			Image::H() const { return Pixels.LengthY(); }
VectorU2		Image::Size() const { return _Size; }
const void *	Image::Data() const { return _Data; }
void *			Image::Data() { return _Data; }
LoopU2			Image::Loop() const { return LoopU2(VectorU2(), _Size); }
*/


bool			Image::Empty() const { return Pixels.IsNull(); }
//uint32			Image::W() const { return Pixels.LengthX(); }
//uint32			Image::H() const { return Pixels.LengthY(); }
uint32			Image::W() const { return Pixels.Size().X; }
uint32			Image::H() const { return Pixels.Size().Y; }
VectorU2		Image::Size() const { return Pixels.Size(); }
const void *	Image::Data() const { return Pixels.Data(); }
void *			Image::Data() { return Pixels.Data(); }
LoopU2			Image::Loop() const { return LoopU2(VectorU2(), Pixels.Size()); }

ColorU4 & Image::Pixel(VectorU2 udx)
{
//	return Pixels[udx.X + udx.Y * Pixels.LengthX()];
	return Pixels[udx];
}
const ColorU4 & Image::Pixel(VectorU2 udx) const
{
//	return Pixels[udx.X + udx.Y * Pixels.LengthX()];
	return Pixels[udx];
}
ColorU4 & Image::Pixel(uint32 x, uint32 y)
{
//	return Pixels[x + y * Pixels.LengthX()];
	return Pixels[VectorU2(x, y)];
}
const ColorU4 & Image::Pixel(uint32 x, uint32 y) const
{
//	return Pixels[x + y * Pixels.LengthX()];
	return Pixels[VectorU2(x, y)];
}
uint8 & Image::Pixel(uint32 x, uint32 y, uint8 col)
{
//	uint8 * data = (uint8*)&Pixels[x + y * Pixels.LengthX()];
	uint8 * data = (uint8*)&Pixels[VectorU2(x, y)];
	return data[col];
}
const uint8 & Image::Pixel(uint32 x, uint32 y, uint8 col) const
{
//	const uint8 * data = (const uint8*)&Pixels[x + y * Pixels.LengthX()];
	const uint8 * data = (const uint8*)&Pixels[VectorU2(x, y)];
	return data[col];
}
ColorU4 & Image::Pixel(uint32 udx)
{
	return Pixels[udx];
}
const ColorU4 & Image::Pixel(uint32 udx) const
{
	return Pixels[udx];
}



Image::~Image() { }
Image::Image()
	: Pixels()
{ }
Image::Image(VectorU2 size)
	: Pixels(size)
{ }
Image::Image(uint32 w, uint32 h)
	: Pixels(VectorU2(w, h))
{ }

Image::Image(const Image & other)
	: Pixels(other.Pixels)
{ }
Image & Image::operator=(const Image & other)
{
	Pixels = other.Pixels;
	return *this;
}



void Image::Init(VectorU2 size)
{
	Pixels.ChangeSize(size);
}
void Image::Init(uint32 w, uint32 h)
{
	Pixels.ChangeSize(VectorU2(w, h));
}
void Image::Dispose()
{
	Pixels.Clear();
}



/*void Image::Bind(const Image & other)
{
	_Size = other._Size;
	_Data = other._Data;
}
void Image::Copy(const Image & other)
{
	_Size = other._Size;
	_Data = new ColorU4[Pixels.LengthX() * Pixels.LengthX()];
	unsigned int size = Pixels.LengthX() * Pixels.LengthX();
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
}*/



void Image::Scale(VectorU2 size)
{
	Pixels.Bind(Scaled(size).Pixels);
}
Image Image::Scaled(VectorU2 size) const
{
	Image img(size);

	VectorU2	scaled;
	//uint32		idx_old;
	//uint32		idx_new;
	for (uint32 y = 0; y < size.Y; y++)
	{
		//scaled.Y = (((float)y) / ((float)size.Y)) * ((float)Pixels.LengthY());
		scaled.Y = (((float)y) / ((float)size.Y)) * ((float)Pixels.Size().Y);

		for (uint32 x = 0; x < size.X; x++)
		{
			//scaled.X = (((float)x) / ((float)size.X)) * ((float)Pixels.LengthX());
			scaled.X = (((float)x) / ((float)size.X)) * ((float)Pixels.Size().X);

			//idx_old = (scaled.X + scaled.Y * Pixels.LengthX());
			//idx_old = (scaled.X + scaled.Y * Pixels.LengthX());
			//idx_new = (x + y * size.X);

			//img.Pixels[idx_new] = Pixels[idx_old];
			img.Pixels[VectorU2(x, y)] = Pixels[scaled];
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
