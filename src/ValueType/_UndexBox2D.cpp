#include "ValueType/UndexBox2D.hpp"



UndexBox2D::UndexBox2D() :
	Min(),
	Max()
{ }
UndexBox2D::UndexBox2D(Undex2D min, Undex2D max) :
	Min(min),
	Max(max)
{ }
UndexBox2D::~UndexBox2D()
{ }



UndexBox2D::UndexBox2D(const UndexBox2D & other) :
	Min(other.Min),
	Max(other.Max)
{ }
UndexBox2D & UndexBox2D::operator=(const UndexBox2D & other)
{
	Min = other.Min;
	Max = other.Max;
	return *this;
}



Bool2D UndexBox2D::CheckIn(Undex2D udx) const
{
	return (udx >= Min) & (udx <= Max);
}
Bool2D UndexBox2D::CheckEx(Undex2D udx) const
{
	return (udx > Min) & (udx < Max);
}
Bool2D UndexBox2D::CheckEdge(Undex2D udx) const
{
	return (udx == Min) | (udx == Max);
}
