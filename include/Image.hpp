#ifndef  IMAGE_HPP
# define IMAGE_HPP

# include "uint.hpp"

# include "ValueType/ColorU4.hpp"
# include "ValueType/VectorU2.hpp"
# include "ValueType/LoopU2.hpp"

class Image
{
	private:
	VectorU2	_Size;
	ColorU4 *	_Data;
	// also Count like ByteBlock

	public:
	bool	Empty() const;
	uint32	W() const;
	uint32	H() const;
	VectorU2		Size() const;
	const void *	Data() const;
	LoopU2			Loop() const;
	void *			Data();

	public:
	ColorU4 &			Pixel(VectorU2 udx);		// operator[]
	const ColorU4 &		Pixel(VectorU2 udx) const;	// operator[]
	ColorU4 &			Pixel(uint32 x, uint32 y);
	const ColorU4 &		Pixel(uint32 x, uint32 y) const;
	uint8 &				Pixel(uint32 x, uint32 y, uint8 col);
	const uint8 &		Pixel(uint32 x, uint32 y, uint8 col) const;
	ColorU4 &			Pixel(uint32 udx);			// operator[]
	const ColorU4 &		Pixel(uint32 udx) const;	// operator[]

	public:
	Image();
	Image(VectorU2 size);
	Image(uint32 w, uint32 h);
	~Image();

	Image(const Image & other);
	Image & operator=(const Image & other);

	public:
	void Init(VectorU2 size);
	void Init(uint32 w, uint32 h);
	void Dispose();

	public:
	void Bind(const Image & other);
	void Copy(const Image & other);
	Image Bind();
	Image Copy();

	void Scale(VectorU2 size);
	Image Scaled(VectorU2 size) const;

	public:
	static Image Missing(VectorU2 size);
};

#endif