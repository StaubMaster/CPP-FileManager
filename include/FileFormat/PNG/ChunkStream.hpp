#ifndef  PNG_CHUNK_STREAM_HPP
# define PNG_CHUNK_STREAM_HPP

# include "FileParsing/ByteStreamBase.hpp"
# include "FileFormat/PNG/Chunk.hpp"
# include "ValueType/uint.hpp"

namespace PNG
{
class ChunkStream : public ByteStreamBase
{
	private:
	uint32	Limit;
	Chunk *	Data;

	uint32	SetIndex;
	uint32	GetIndex;

	public:
	ChunkStream();
	virtual ~ChunkStream();

	public:
	ChunkStream(const ChunkStream & other) = delete;
	ChunkStream & operator=(const ChunkStream & other) = delete;

	public:
	bool Done() override;

	public:
	void Move() override;
	void Move(uint32 idx) override;

	public:
	ByteStreamBase & Set1(uint8 & val) = delete;
	ByteStreamBase & Set2(uint16 & val) = delete;
	ByteStreamBase & Set4(uint32 & val) = delete;
	ByteStreamBase & Set8(uint64 & val) = delete;

	public:
	ByteStreamBase & Get1(uint8 & val) override;
	ByteStreamBase & Get2(uint16 & val) override;
	ByteStreamBase & Get4(uint32 & val) override;
	ByteStreamBase & Get8(uint64 & val) override;
};
};

#endif