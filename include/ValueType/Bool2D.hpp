#ifndef  BOOL_2D_HPP
# define BOOL_2D_HPP

struct Bool2D
{
	private:
	unsigned char Bits;
	Bool2D(unsigned char bits);

	public:
	Bool2D();
	Bool2D(bool val);
	Bool2D(bool x, bool y);
	~Bool2D();
	
	Bool2D(const Bool2D & other);
	Bool2D & operator=(const Bool2D & other);

	public:
	Bool2D operator&(const Bool2D & other);
	Bool2D operator|(const Bool2D & other);
	Bool2D operator^(const Bool2D & other);

	bool operator==(const Bool2D & other);
	bool operator!=(const Bool2D & other);

	bool GetX() const;
	bool GetY() const;

	void SetX(bool val);
	void SetY(bool val);

	bool All(bool val) const;
	bool Any(bool val) const;
};

#endif