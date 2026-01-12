#ifndef  IMAGE_HPP
# define IMAGE_HPP

# include "ValueType/uint.hpp"
# include "ValueType/ColorU4.hpp"
# include "ValueType/Undex2D.hpp"
# include "ValueType/UndexLoop2D.hpp"

class Image
{
	private:
	Undex2D		_Size;
	ColorU4 *	_Data;

	public:
	bool	Empty() const;
	uint32	W() const;
	uint32	H() const;
	Undex2D			Size() const;
	const void *	Data() const;
	UndexLoop2D		Loop() const;

	public:
	ColorU4 &			Pixel(Undex2D udx);
	const ColorU4 &		Pixel(Undex2D udx) const;
	ColorU4 &			Pixel(uint32 x, uint32 y);
	const ColorU4 &		Pixel(uint32 x, uint32 y) const;
	uint8 &				Pixel(uint32 x, uint32 y, uint8 col);
	const uint8 &		Pixel(uint32 x, uint32 y, uint8 col) const;

	public:
	Image();
	Image(Undex2D size);
	Image(uint32 w, uint32 h);
	~Image();

	Image(const Image & other);
	Image & operator=(const Image & other);

	public:
	void Init(Undex2D size);
	void Init(uint32 w, uint32 h);
	void Dispose();

	public:
	void Bind(const Image & other);
	void Copy(const Image & other);
	Image Bind();
	Image Copy();

	void Scale(Undex2D size);
	Image Scaled(Undex2D size) const;

	public:
	static Image Missing(Undex2D size);
};

#endif