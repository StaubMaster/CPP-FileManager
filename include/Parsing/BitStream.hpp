
#ifndef  BITSTREAM_HPP
# define BITSTREAM_HPP
# include "uint.hpp"

class BitStream
{
	public:
		const uint8*	Data;
		const uint32	Len;
	private:
		uint8			BitIndex;
		uint32			ByteIndex;

	public:
		BitStream(const void * ptr, uint32 len);
		BitStream(const std::string & str);

		BitStream(const BitStream & other, uint32 len);
		BitStream & operator =(const BitStream & other);

	public:
		const uint8 *	DataAtIndex() const;

	public:
		void	MoveToNextByte();

		void	IncByBytes(uint32 count = 1);
		void	IncByBits(uint32 count = 1);

	public:
		uint8	GetBits8(uint8 bit_count = UINT8_BIT_COUNT) const;
		uint16	GetBits16(uint8 bit_count = UINT16_BIT_COUNT) const;
		uint32	GetBits32(uint8 bit_count = UINT32_BIT_COUNT) const;
		uint64	GetBits64(uint8 bit_count = UINT64_BIT_COUNT) const;

		uint8	GetIncBits8(uint8 bit_count = UINT8_BIT_COUNT);
		uint16	GetIncBits16(uint8 bit_count = UINT16_BIT_COUNT);
		uint32	GetIncBits32(uint8 bit_count = UINT32_BIT_COUNT);
		uint64	GetIncBits64(uint8 bit_count = UINT64_BIT_COUNT);

	private:
		class LenReachedException : public std::exception { public: const char * what() const throw(); };
};

#endif
