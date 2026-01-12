#ifndef  UNDEX_BOX_2D_HPP
# define UNDEX_BOX_2D_HPP

# include "Undex2D.hpp"
# include "Bool2D.hpp"

struct UndexBox2D
{
	public:
	Undex2D	Min;
	Undex2D	Max;

	public:
	UndexBox2D();
	UndexBox2D(Undex2D min, Undex2D max);
	~UndexBox2D();

	UndexBox2D(const UndexBox2D & other);
	UndexBox2D & operator=(const UndexBox2D & other);

	public:
	Bool2D CheckIn(Undex2D udx) const;
	Bool2D CheckEx(Undex2D udx) const;
	Bool2D CheckEdge(Undex2D udx) const;
};

#endif