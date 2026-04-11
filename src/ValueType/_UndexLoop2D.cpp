#include "ValueType/UndexLoop2D.hpp"


UndexLoop2D::UndexLoop2D() :
	Range()
{ }
UndexLoop2D::UndexLoop2D(Undex2D min, Undex2D max) :
	Range(min, max),
	MinExclude(false),
	MaxExclude(true)
{ }
UndexLoop2D::UndexLoop2D(Undex2D min, Bool2D minEx, Undex2D max, Bool2D maxEx) :
	Range(min, max),
	MinExclude(minEx),
	MaxExclude(maxEx)
{ }
UndexLoop2D::~UndexLoop2D()
{ }

UndexLoop2D::UndexLoop2D(const UndexLoop2D & other) :
	Range(other.Range)
{ }
UndexLoop2D & UndexLoop2D::operator=(const UndexLoop2D & other)
{
	Range = other.Range;
	return *this;
}



Undex2D UndexLoop2D::Min() const
{
	Undex2D udx(Range.Min);
	if (MinExclude.GetX()) { udx.X++; }
	if (MinExclude.GetY()) { udx.Y++; }
	return udx;
}
Undex2D UndexLoop2D::Max() const
{
	Undex2D udx(Range.Max);
	if (MaxExclude.GetX()) { udx.X--; }
	if (MaxExclude.GetY()) { udx.Y--; }
	return udx;
}



Bool2D UndexLoop2D::Check(Undex2D udx) const
{
	Bool2D min;
	if (MinExclude.GetX()) { min.SetX(udx.X > Range.Min.X); } else { min.SetX(udx.X >= Range.Min.X); }
	if (MinExclude.GetY()) { min.SetY(udx.Y > Range.Min.Y); } else { min.SetY(udx.Y >= Range.Min.Y); }

	Bool2D max;
	if (MaxExclude.GetX()) { max.SetX(udx.X < Range.Max.X); } else { max.SetX(udx.X <= Range.Max.X); }
	if (MaxExclude.GetY()) { max.SetY(udx.Y < Range.Max.Y); } else { max.SetY(udx.Y <= Range.Max.Y); }

	return min & max;
}



/*	Problem
Overflow might happen
check before ++ and --
*/
void UndexLoop2D::Next(Undex2D & udx) const
{
	Undex2D	min = Min();
	Undex2D	max = Max();

	if (udx.X >= max.X)
	{
		udx.X = min.X;
		udx.Y++;
	}
	else
	{
		udx.X++;
	}
}
void UndexLoop2D::Prev(Undex2D & udx) const
{
	udx.X--;
	if (udx.X < Range.Min.X)
	{
		udx.X = Range.Max.X;
		udx.Y--;
	}
}
