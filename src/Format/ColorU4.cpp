#include "Format/ColorU4.hpp"



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
