#include "ValueType/ColorU4.hpp"



ColorU4::ColorU4() :
	R(0),
	G(0),
	B(0),
	A(0)
{ }
ColorU4::ColorU4(uint32 rgba)
{
	R = (rgba) & 0xFF;
	G = (rgba >> 8) & 0xFF;
	B = (rgba >> 16) & 0xFF;
	A = (rgba >> 24) & 0xFF;
}
ColorU4::ColorU4(uint8 r, uint8 g, uint8 b) :
	R(r),
	G(g),
	B(b),
	A(0xFF)
{ }
ColorU4::ColorU4(uint8 r, uint8 g, uint8 b, uint8 a) :
	R(r),
	G(g),
	B(b),
	A(a)
{ }
ColorU4::~ColorU4()
{ }

ColorU4::ColorU4(const ColorU4 & other) :
	R(other.R),
	G(other.G),
	B(other.B),
	A(other.A)
{ }
ColorU4 & ColorU4::operator=(const ColorU4 & other)
{
	R = other.R;
	G = other.G;
	B = other.B;
	A = other.A;
	return *this;
}



uint32 ColorU4::ToUInt32_RGBA() const
{
	uint32 val = 0;
	val |= R << 0;
	val |= G << 8;
	val |= B << 16;
	val |= A << 24;
	return val;
}
