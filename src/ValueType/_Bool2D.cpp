#include "ValueType/Bool2D.hpp"



Bool2D::Bool2D(unsigned char bits) :
	Bits(bits)
{ }
Bool2D::Bool2D() :
	Bits(0)
{ }
Bool2D::Bool2D(bool val) :
	Bits((val << 0) | (val << 1))
{ }
Bool2D::Bool2D(bool x, bool y) :
	Bits((x << 0) | (y << 1))
{ }
Bool2D::~Bool2D()
{ }

Bool2D::Bool2D(const Bool2D & other) :
	Bits(other.Bits)
{ }
Bool2D & Bool2D::operator=(const Bool2D & other)
{
	Bits = other.Bits;
	return *this;
}



Bool2D Bool2D::operator&(const Bool2D & other) { return Bool2D((unsigned char)(Bits & other.Bits)); }
Bool2D Bool2D::operator|(const Bool2D & other) { return Bool2D((unsigned char)(Bits | other.Bits)); }
Bool2D Bool2D::operator^(const Bool2D & other) { return Bool2D((unsigned char)(Bits ^ other.Bits)); }



bool Bool2D::operator==(const Bool2D & other) { return Bits == other.Bits; }
bool Bool2D::operator!=(const Bool2D & other) { return Bits != other.Bits; }



bool Bool2D::GetX() const { return (Bits >> 0) & 1; }
bool Bool2D::GetY() const { return (Bits >> 1) & 1; }

void Bool2D::SetX(bool val) { Bits = (Bits & 0b110) | (val << 0); }
void Bool2D::SetY(bool val) { Bits = (Bits & 0b101) | (val << 1); }

bool Bool2D::All(bool val) const { return ((GetX() == val) & (GetY() == val)); }
bool Bool2D::Any(bool val) const { return ((GetX() == val) | (GetY() == val)); }
