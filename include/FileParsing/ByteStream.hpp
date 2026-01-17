
#ifndef  BYTE_STREAM_HPP
# define BYTE_STREAM_HPP
# include "ValueType/uint.hpp"

class ByteStream
{
	public:
		uint32	Len;
		uint8	*Data;

	public:
		uint32	Index;

	public:
		ByteStream(uint32 len);
		~ByteStream();

		void	Concatenation(const uint8 * data, uint32 len);

		void	Next();

		void	Set(uint8 val);
		uint8	Get();

		void	SetRange(uint8 * ptr, uint32 len);
};

#endif
