#ifndef  UNDEX_2D_HPP
# define UNDEX_2D_HPP

# include "Bool2D.hpp"

struct Undex2D
{
	public:
	unsigned int X;
	unsigned int Y;

	public:
	Undex2D();
	Undex2D(unsigned int x, unsigned int y);
	~Undex2D();

	Undex2D(const Undex2D & other);
	Undex2D & operator=(const Undex2D & other);



	Undex2D operator+(const Undex2D & other) const;
	Undex2D operator-(const Undex2D & other) const;
	Undex2D operator*(unsigned int shift) const;
	Undex2D operator/(unsigned int shift) const;

	Undex2D operator<<(unsigned int shift) const;
	Undex2D operator>>(unsigned int shift) const;

	Undex2D operator%(const Undex2D & other) const;



	Bool2D operator==(const Undex2D & other) const;
	Bool2D operator<=(const Undex2D & other) const;
	Bool2D operator>=(const Undex2D & other) const;
	Bool2D operator!=(const Undex2D & other) const;
	Bool2D operator<(const Undex2D & other) const;
	Bool2D operator>(const Undex2D & other) const;
};

#endif