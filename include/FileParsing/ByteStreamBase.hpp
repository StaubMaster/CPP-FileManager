#ifndef  BYTE_STREAM_BASE_HPP
# define BYTE_STREAM_BASE_HPP

# include "ValueType/uint.hpp"
# include "FileParsing/ByteBlock.hpp"
# include "FileParsing/ExceptionBase.hpp"

# include <exception>
# include <string>

// make this like a Queue ? FIFO ?
// no
// yes ?
// for BitMaps, I just need a stream of Bytes. no going back at any point
// for PNG, mostyl read a stream of Bytes, but sometimes Blocks, and within these blocks,
// I do the BitStream stuff. which sometimes checks without moving.
// but that is all handled in the BitStream thing
// these are all just cpp streams ?
// but cpp streams suck. they are complicated, with weird names and behaviour
// but I also dont want to waste time on implementing my own

// BitMap
// reading currently reads the whole File
// and puts it into a ByteStream
//
// writing should write to a ByteStream
// and then put all that into a File
//
// add SaveText to FileInfo
// add LoadBytes to FileInfo
// add SaveBytes to FileInfo

struct ByteStreamBase
{
	enum ByteOrder : bool
	{
		HiToLo = 0,
		LoToHi = 1,
	};

	public:
	ByteBlock	Block;
	uint64		Index;
	ByteOrder	Order;

	protected:
	virtual ~ByteStreamBase();
	ByteStreamBase();

	private:
	ByteStreamBase(const ByteStreamBase & other) = delete;
	ByteStreamBase & operator=(const ByteStreamBase & other) = delete;

	protected:
	ByteStreamBase(const ByteBlock & block);
//	ByteStreamBase & Concatenation(const std::string & str);

	public:
	void Move();
	void Move(uint64 move);
};

#endif