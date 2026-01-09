#ifndef  IMAGE_HPP
# define IMAGE_HPP

# include "ValueType/uint.hpp"
# include "ColorU4.hpp"

class Image
{
	private:
	uint32	_W;
	uint32	_H;
	ColorU4 *	_Data;

	public:
	uint32	W() const;
	uint32	H() const;
	const void *	Data() const;

	public:
	ColorU4 &			Pixel(uint32 x, uint32 y);
	const ColorU4 &		Pixel(uint32 x, uint32 y) const;
	uint8 &				Pixel(uint32 x, uint32 y, uint8 col);
	const uint8 &		Pixel(uint32 x, uint32 y, uint8 col) const ;

	public:
	Image();
	Image(uint32 w, uint32 h);
	~Image();

	Image(const Image & other);
	Image & operator=(const Image & other);

	public:
	void Dispose();

	public:
	void Bind(const Image & other);
	void Copy(const Image & other);
	Image Bind();
	Image Copy();

	Image * Scale(uint32 w, uint32 h) const;

	public:
	static Image * Missing();
};

#endif