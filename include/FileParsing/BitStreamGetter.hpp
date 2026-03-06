#ifndef  BIT_STREAM_GETTER_HPP
# define BIT_STREAM_GETTER_HPP

# include "FileParsing/BitStreamBase.hpp"

class BitStreamGetter : public BitStreamBase
{
	private:
	uint8			BitIndex;	// IndexGetBit
	uint32			ByteIndex;	// IndexGetByte

	public:
	~BitStreamGetter();
	BitStreamGetter() = delete;

	private:
	BitStreamGetter(const BitStreamGetter & other) = delete;
	BitStreamGetter & operator=(const BitStreamGetter & other) = delete;

	public:
	BitStreamGetter(ByteBlock block);

	public:
	const uint8 *	DataAtIndex() const;

	public:
	void	MoveToNextByte();				// MoveNextByte
	void	IncByBytes(uint32 count = 1);	// MoveByte
	void	IncByBits(uint32 count = 1);	// MoveBit

	public:
	uint8	GetBits8(uint8 bit_count = UINT8_BIT_COUNT) const;		// Get8
	uint16	GetBits16(uint8 bit_count = UINT16_BIT_COUNT) const;
	uint32	GetBits32(uint8 bit_count = UINT32_BIT_COUNT) const;
	uint64	GetBits64(uint8 bit_count = UINT64_BIT_COUNT) const;

	uint8	GetIncBits8(uint8 bit_count = UINT8_BIT_COUNT);			// Get8Move
	uint16	GetIncBits16(uint8 bit_count = UINT16_BIT_COUNT);
	uint32	GetIncBits32(uint8 bit_count = UINT32_BIT_COUNT);
	uint64	GetIncBits64(uint8 bit_count = UINT64_BIT_COUNT);

	private:
	class LenReachedException : public std::exception { public: const char * what() const throw(); };
};

#endif