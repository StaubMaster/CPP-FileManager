
#ifndef DEFLATE_HPP
# define DEFLATE_HPP

# include "ValueType/uint.hpp"

# include <exception>

class BitStream;
class ByteStreamSetter;
class HuffmanTree;

class DEFLATE
{
	public:
	static uint8 *	dynamic_Huffman(BitStream & bits, uint32 H_LIT, uint32 H_DIST, uint32 H_CLEN);
	static void		decode_Huffman(BitStream & bits, HuffmanTree & literal, HuffmanTree & distance, ByteStreamSetter & data);

	public:
	static void	Block_direct(BitStream & bits, ByteStreamSetter & data);
	static void	Block_static(BitStream & bits, ByteStreamSetter & data);
	static void	Block_dynamic(BitStream & bits, ByteStreamSetter & data);
	static void	Blocks(BitStream & bits, ByteStreamSetter & data);

	private:
	class Exception_NotImplemented : public std::exception
	{
		private:
			std::string Text;
		public:
			Exception_NotImplemented(std::string head, std::string name);
		public: 
			const char * what() const noexcept;
	};
	class Exception_InvalidBlockType : public std::exception
	{
		private:
			std::string Text;
		public:
			Exception_InvalidBlockType(uint32 type);
		public:
			const char * what() const noexcept;
	};
	class Exception_InvalidData : public std::exception
	{
		private:
			std::string Text;
		public:
			Exception_InvalidData(std::string head, uint32 value);
		public:
			const char * what() const noexcept;
	};
};

#endif
