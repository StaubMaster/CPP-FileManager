#include "ValueType/Undex2D.hpp"



Undex2D::Undex2D() :
	X(0),
	Y(0)
{ }
Undex2D::Undex2D(unsigned int x, unsigned int y) :
	X(x),
	Y(y)
{ }
Undex2D::~Undex2D()
{ }



Undex2D::Undex2D(const Undex2D & other) :
	X(other.X),
	Y(other.Y)
{ }
Undex2D & Undex2D::operator=(const Undex2D & other)
{
	X = other.X;
	Y = other.Y;
	return (*this);
}



Undex2D Undex2D::operator+(const Undex2D & other) const
{
	return Undex2D(
		X + other.X,
		Y + other.Y
	);
}
Undex2D Undex2D::operator-(const Undex2D & other) const
{
	return Undex2D(
		X - other.X,
		Y - other.Y
	);
}



Undex2D Undex2D::operator%(const Undex2D & other) const
{
	return Undex2D(
		X % other.X,
		Y % other.Y
	);
}



/*Bool3D Undex2D::operator==(const Undex2D & other) const
{
	return Bool3D(
		X == other.X,
		Y == other.Y,
		Z == other.Z
	);
}
Bool3D Undex2D::operator<=(const Undex2D & other) const
{
	return Bool3D(
		X <= other.X,
		Y <= other.Y,
		Z <= other.Z
	);
}
Bool3D Undex2D::operator>=(const Undex2D & other) const
{
	return Bool3D(
		X >= other.X,
		Y >= other.Y,
		Z >= other.Z
	);
}
Bool3D Undex2D::operator!=(const Undex2D & other) const
{
	return Bool3D(
		X != other.X,
		Y != other.Y,
		Z != other.Z
	);
}
Bool3D Undex2D::operator<(const Undex2D & other) const
{
	return Bool3D(
		X < other.X,
		Y < other.Y,
		Z < other.Z
	);
}
Bool3D Undex2D::operator>(const Undex2D & other) const
{
	return Bool3D(
		X > other.X,
		Y > other.Y,
		Z > other.Z
	);
}*/
