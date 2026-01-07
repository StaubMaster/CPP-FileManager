#ifndef  COLORU4_HPP
# define COLORU4_HPP

# include "Parsing/uint.hpp"

struct ColorU4
{
	uint8	R;
	uint8	G;
	uint8	B;
	uint8	A;

	ColorU4();
	ColorU4(uint32 rgba);
	~ColorU4();

	ColorU4(const ColorU4 & other);
	ColorU4 & operator=(const ColorU4 & other);
};

#endif