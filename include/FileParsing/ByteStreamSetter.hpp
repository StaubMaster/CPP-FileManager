#ifndef  BYTE_STREAM_SETTER_HPP
# define BYTE_STREAM_SETTER_HPP

# include "FileParsing/ByteStreamBase.hpp"

struct ByteStreamSetter : public ByteStreamBase
{
	public:
	~ByteStreamSetter();
	ByteStreamSetter() = delete;

	private:
	ByteStreamSetter(const ByteStreamSetter & other) = delete;
	ByteStreamSetter & operator=(const ByteStreamSetter & other) = delete;

	public:
	ByteStreamSetter(uint64 size);
	ByteStreamSetter & Concatenation(uint64 size);

	public:
	void	Set1(uint8 val);
	void	Set2(uint16 val);
	void	Set4(uint32 val);
	void	Set8(uint64 val);
	void	Set(ByteBlock block);

	public:
	void	Set1(uint64 idx, uint8 val);
	void	Set2(uint64 idx, uint16 val);
	void	Set4(uint64 idx, uint32 val);
	void	Set8(uint64 idx, uint64 val);
	void	Set(uint64 idx, ByteBlock block);
};

#endif