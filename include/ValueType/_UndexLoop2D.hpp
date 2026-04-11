#ifndef  UNDEX_LOOP_2D_HPP
# define UNDEX_LOOP_2D_HPP

# include "Undex2D.hpp"
# include "UndexBox2D.hpp"
# include "Bool2D.hpp"

struct UndexLoop2D
{
	public:
	UndexBox2D	Range;
	Bool2D		MinExclude;	// false means (udx >= Min); true means (udx > Min)
	Bool2D		MaxExclude;	// false means (udx <= Max); true means (udx < Max)

	public:
	UndexLoop2D();
	UndexLoop2D(Undex2D min, Undex2D max);
	UndexLoop2D(Undex2D min, Bool2D minEx, Undex2D max, Bool2D maxEx);
	~UndexLoop2D();

	UndexLoop2D(const UndexLoop2D & other);
	UndexLoop2D & operator=(const UndexLoop2D & other);

	public:
	Undex2D Min() const;
	Undex2D Max() const;

	public:
	Bool2D Check(Undex2D udx) const;

	public:
	void Next(Undex2D & udx) const;
	void Prev(Undex2D & udx) const;
};

#endif